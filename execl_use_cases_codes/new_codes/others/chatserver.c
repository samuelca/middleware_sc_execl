/*
Felipe Duarte Machado - Engenheiro de Pesquisa e Desenvolvimento

07/11/2015

   para compilar:
     $ gcc chatserver.c -o chatserver
   para executar:
   $ ./chatserver <num_da_porta>

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/times.h>
#include <sys/select.h>
#include <unistd.h>

#define SERVER_BUSY "Sorry. The server is busy. bye\n"

#define MAX_USERS 20
#define MSG_LEN 4096

int socket_listening ;
/* for select() */
fd_set select_set ;

int  *list_of_sockets ;

int  max_users = MAX_USERS ;

/* grows up everytime an user
 * got a connection.
 * this variable stores the
 * current list size.*/
int  list_len = 0 ;

/* the user message */
char msg[MSG_LEN+1] ;

void show_help(char *name) {
printf("Chatserv 1.0\n") ;
printf("by Daemonio (undefinido gmail com)\n\n") ;
printf("[uso] %s <port> [<max_users>]\n", name) ;
}

/* if it's possible to insert a socket in
 * the list, this function returns 0 and
 * 1 otherwise.
 */
char insert_socket_into_list(int socket) {
    int i ;

    if ( list_len == max_users ) {
        return 1 ;
    }

    for ( i = 0; i < max_users; i++ ) {
        if ( list_of_sockets[i] == -1 ) {
            list_of_sockets[i] = socket ;
            list_len++ ;
            break ;
        }
    }
    return 0 ;
}

/* searches for a socket in the list
 * and closes it.
 */
void remove_socket_from_list(int _sock) {
    int i ;

    for ( i = 0; i < max_users; i++ ) {
        if ( list_of_sockets[i] == _sock ) {
            close(list_of_sockets[i]) ;
            list_of_sockets[i] = -1 ;
            list_len-- ;
            break ;
        }
    }
}

/* gets the message from an user.
 * this message will be in `msg'.
 * Returns 0 if the message was delivered
 * succesfully and 1 if the client
 * has finished the connection.
 */
char get_message_from_socket(int _sock) {
    int t ;

    memset(msg,0x0,MSG_LEN+1) ;
    t = recv(_sock, msg, MSG_LEN, 0 ) ;

    if ( t == 0 ) {
        remove_socket_from_list(_sock) ;
        return 1 ;
    }
    return 0 ;
}

/* after we got the message from the user,
 * we'll send it to all the others here.
 * note that an user cant send a message
 * to himself (list_of_sockets[i] != _sock).
 */
void send_message_to_all(int _sock) {
    int i ;

    for ( i = 0; i < max_users; i++ ) {
        if ( (list_of_sockets[i] != -1)    &&
             (list_of_sockets[i] != _sock) &&
             (list_of_sockets[i] != socket_listening) ) {

            send(list_of_sockets[i], msg, strlen(msg), 0) ;
        }
    }
}

int main(int argc, char **argv) {
    int port ;
    int t    ;

    struct sockaddr_in server ;
    struct timeval select_time ;

    if ( argc == 1 ) {
        show_help(argv[0]) ;
        return -1 ;
    }

    if ( argc > 2 ) {
        max_users = atoi(argv[2]) ;
    }

    port = atoi(argv[1]) ;

    socket_listening = socket(AF_INET, SOCK_STREAM, 0) ;

    if ( socket_listening < 0 ) {
        perror("socket") ;
        return -1 ;
    }

    server.sin_family = AF_INET ;
    server.sin_port = htons(port) ;
    server.sin_addr.s_addr = INADDR_ANY ;

    t = sizeof(struct sockaddr_in) ;
    if ( bind( socket_listening, (struct sockaddr *) &server, t ) < 0 ) {
        perror("bind") ;
        return -1 ;
    }

    if ( listen(socket_listening, 5) < 0 ) {
        perror("listen") ;
        return -1 ;
    }

    /* create the list of sockets.
     * for each client, there is a socket in this list.
     */
    list_of_sockets = (int *) malloc( max_users * sizeof(int) ) ;
    if ( list_of_sockets == NULL ) {
        perror("malloc") ;
        return -1 ;
    }

    /* "clean up" the list. */
    for ( t = 0; t < max_users; t++ )
        list_of_sockets[t] = -1 ;

    /* you'll need a ctrl+c to break this loop */
    while ( 1 ) {
        /* gets all the sockets and put in a
         * fd_set struct. */
        FD_ZERO(&select_set) ;
        FD_SET(socket_listening, &select_set) ;
        for ( t = 0; list_len > 0 && t < max_users; t++ ) {
            if ( list_of_sockets[t] != -1 ) {
                FD_SET(list_of_sockets[t], &select_set) ;
            }
        }

        printf("[+] Listening on %d [%d/%d] ...\n", port, list_len, max_users) ;

        /* select will wait 2 seconds before
         * returning. */
        select_time.tv_sec = 2 ;
        select_time.tv_usec = 0 ;

        /* select returns:
         * < 0 if error.
         * = 0 if nothing happened
         * > 0 number of sockets on the sets
         */
        if ( (t=select(FD_SETSIZE, &select_set, NULL, NULL, &select_time)) < 0 ) {
            perror("select") ;
            return -1 ;
        }

        /* wow, we have something ... */
        if ( t > 0 ) {
            /* if it's the listening socket, we have to
             * accept the incoming connection and add
             * the new socket in the list. */
            if ( FD_ISSET(socket_listening, &select_set) ) {
                int n ;

                if ( (n=accept(socket_listening, NULL, NULL)) < 0 ) {
                    perror("accept") ;
                } else if ( insert_socket_into_list(n) == 1 ) { /* server is busy */
                    send(n,SERVER_BUSY,strlen(SERVER_BUSY),0) ;
                    close(n) ;
                }
                continue ;
            } else {
                int i ;

                /* handle the incoming data. */
                for ( i = 0; i < max_users; i++ ) {
                    if ( FD_ISSET(list_of_sockets[i], &select_set) ) {
                        if ( get_message_from_socket(list_of_sockets[i]) == 0 ) {
                            send_message_to_all(list_of_sockets[i]) ;
                        }
                    }
                }
            }
        }
    } /* while */

    return 0 ;
} /* main */
