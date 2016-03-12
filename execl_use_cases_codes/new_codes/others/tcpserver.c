/*
		Felipe Duarte Machado - Engenheiro de Pesquisa e Desenvolvimento

		07/11/2015

   Exemplo de um servidor TCP/IP usando sockets.

   para compilar:
   $ gcc -o sever tcp_server.c
   para executar:
   $ ./server <num_da_porta>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

//funções inet_*()
#include <arpa/inet.h>
//struct sockaddr_in, ntol e outras
#include <netinet/in.h>

#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   int sockfd, new_sockfd;
   int bytes;
   socklen_t length;//para accept() e bind()
   char buffer[32], quit;
   struct sockaddr_in server;
   struct sockaddr_in client;

   //cria socket
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if(sockfd < 0)
   {
      perror("server_sockfd:::");
      exit(1);
   }

   if(argc == 2)
   {
      server.sin_family  =  AF_INET; // AF_INET = TCP, para usar UDP altera aqui (e em outros lugares tbm)
      server.sin_port    =  htons(atoi(argv[1]));
      server.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY = a qualquer IP pode conectar
      memset(&(server.sin_zero), 0x00, 8);
   }
   else
   {
      printf("\n\tusage: %s <num_porta> \n\n", argv[0]);
      close(sockfd);
      exit(1);
   }

   length = sizeof(struct sockaddr);
   if(bind(sockfd, (struct sockaddr *)&server, length) < 0)
   {
      perror("server_bind:::");
      close(sockfd);
      exit(1);
   }

   //o servidor aceitará no máximo apenas duas conexões
   if(listen(sockfd, 2) < 0)
   {
      perror("server_listen:::");
      close(sockfd);
      exit(1);
   }

   printf("\nAguardando por conexões na porta %s...\n\n", argv[1]);

   //aguardando por conexões
   new_sockfd = accept(sockfd, (struct sockaddr *)&client, &length);
   if(new_sockfd < 0)
   {
      perror("server_accept:::");
      close(sockfd);
      exit(1);
   }

   printf("\nAceitando conexão de %s\n\n", inet_ntoa(client.sin_addr));

   quit = 'N';
   while(quit != 'S')
   {
      bytes = send(new_sockfd, "SERVER:::ok!", 12, 0);
      //ocorreu um erro = -1
      if(bytes < 0)
      {
         perror("server_send:::");
         close(new_sockfd);
         close(sockfd);
         exit(1);
      }

      bytes = recv(new_sockfd, buffer, 32, 0);
      //NOTE:ocorreu um erro = -1 ou cliente fechou conexão = 0
      if(bytes <= 0)
      {
         perror("server_recv:::");
         close(new_sockfd);
         close(sockfd);
         exit(1);
      }

      buffer[bytes] = 0x00;//0x00 o mesmo que '{FONTE}'
      quit = buffer[0];
      printf("\nRECEBIDO:::%s\n\n", buffer);
   }

   close(new_sockfd);
   close(sockfd);

   return 0;
}
