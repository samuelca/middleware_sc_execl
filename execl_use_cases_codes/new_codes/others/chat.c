/*
    Felipe Duarte Machado - Engenheiro de Pesquisa e Desenvolvimento

    07/11/2015

   Exemplo de Chat


	 para compilar:
  	$ gcc chat.c -o chat -lcurses -lpthread

	 para executar:
   $ ./chatserver <num_da_porta>
*/

#include <pthread.h>
#include <curses.h>
#include <termios.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


int done=0;

//char name[20];

int sockfd;
WINDOW *top;
WINDOW *bottom;
int line=1; // Line position of top
int input=1; // Line position of top
int maxx,maxy; // Screen dimensions
pthread_mutex_t mutexsum = PTHREAD_MUTEX_INITIALIZER;

void *get_in_addr(struct sockaddr *sa);

void *sendmessage(void *name);

void *listener();


int main()
{

	printf("Enter user name: ");
	char name[20];
	scanf("%s",name);

	// save old terminal settings
	struct termios oldt, newt;
	tcgetattr ( 0, &oldt );
	newt = oldt;

	// Disable echo and cannon
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr ( 0, TCSANOW, &newt );


	char password[10];
	char *in = password;

	char c;
	int i=0;


	printf("Enter password: ");
	puts("");

	// Read in one char of the password at a time
	while (1) {
		if (read(0, &c, sizeof(c)) > 0)
		{
			if ('\n' == c)
			{
				password[i]='\0';
				break;
			}
			password[i++]=c;

			// Print '*' per keystroke
			write(1, "*", 1);
		}
	}

	// Reset terminal
	tcsetattr ( 0, TCSANOW, &oldt );

	//Check password
	if(strcmp(password,"teste"))
	{
		printf("\nWrong password. Try teste.\n");
		return 0;
	}

	////////////////////////////////
	//      Build connection     //
	///////////////////////////////
	int len;
	int result;
	char buf[256];
	struct sockaddr_in address;

	// Make socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// attr
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(3333);

	len = sizeof(address);

	// Make connection
	result = connect(sockfd, (struct sockaddr *)&address, len);

	printf("\n\nBuilding connection\n\n");

	if(result == -1)
	{
		perror("\nConnection failed, try again.\n");
		exit(1);
	}
	else
	{
		printf("\n\nsuccess connecting\n");
	}


	///////////////////////////////
	//    Begin chat windows     //
	///////////////////////////////

	// Set up windows
	initscr();
	getmaxyx(stdscr,maxy,maxx);

	top = newwin(maxy/2,maxx,0,0);
	bottom= newwin(maxy/2,maxx,maxy/2,0);

	scrollok(top,TRUE);
	scrollok(bottom,TRUE);
	box(top,'|','=');
	box(bottom,'|','-');

	wsetscrreg(top,1,maxy/2-2);
	wsetscrreg(bottom,1,maxy/2-2);


	// Set up threads
	pthread_t threads[2];
	void *status;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	// Spawn the listen/receive deamons
	pthread_create(&threads[0], &attr, sendmessage, (void *)name);
	pthread_create(&threads[1], &attr, listener, NULL);

	// Keep alive until finish condition is done
	while(!done);

}



void *get_in_addr(struct sockaddr *sa)
{
	if(sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


// Send message from keyboard to server and update screen
void *sendmessage(void *name)
{

	char str[80];
	char msg[100];
	int bufsize=maxx-4;
	char *buffer=malloc(bufsize);

	while(1)
	{
		bzero(str,80);
		bzero(msg,100);
		bzero(buffer,bufsize);
		wrefresh(top);
		wrefresh(bottom);

		// Get user's message
		mvwgetstr(bottom,input,2,str);

		// Build the message: "name: message"
		strcpy(msg,name);
		strncat(msg,": \0",100-strlen(str));
		strncat(msg,str,100-strlen(str));

		// Check for quiting
		if(strcmp(str,"exit")==0)
		{

			done = 1;

			// Clean up
			endwin();
			pthread_mutex_destroy(&mutexsum);
			pthread_exit(NULL);
			close(sockfd);
		}

		// Send message to server
		write(sockfd,msg,strlen(msg));

		// write it in chat window (top)
		mvwprintw(top,line,2,msg);


		// scroll the top if the line number exceed height
		pthread_mutex_lock (&mutexsum);

		if(line!=maxy/2-2)
			line++;
		else
			scroll(top);

		// scroll the bottom if the line number exceed height
		if(input!=maxy/2-2)
			input++;
		else
			scroll(bottom);

		pthread_mutex_unlock (&mutexsum);
	}
}


// Listen for messages and display them
void *listener()
{
	char str[80];
	int bufsize=maxx-4;
	char *buffer=malloc(bufsize);

	while(1)
	{
		bzero(buffer,bufsize);
		wrefresh(top);
		wrefresh(bottom);

		//Receive message from server
		read(sockfd,buffer,bufsize);

		//Print on own terminal
		mvwprintw(top,line,3,buffer);

		// scroll the top if the line number exceed height
		pthread_mutex_lock (&mutexsum);
		if(line!=maxy/2-2)
			line++;
		else
			scroll(top);
		pthread_mutex_unlock (&mutexsum);
	}
}
