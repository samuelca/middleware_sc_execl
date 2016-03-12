/*
    Felipe Duarte Machado - Engenheiro de Pesquisa e Desenvolvimento

    07/11/2015

   Exemplo de um cliente TCP/IP usando sockets.

   $ gcc -o client tcp_client.c
   para executar:
   $ ./client <ip_do_servidor> <num_da_porta>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
#include <sys/types.h>
#include <sys/socket.h>
//struct sockaddr_in, htons() e outras
#include <netinet/in.h>
//funções inet_*()
#include <arpa/inet.h>

#include <errno.h> /*perror()*/
#include <unistd.h> /*close()*/

int main(int argc, char *argv[])
{
   int sockfd;
   int bytes;
   socklen_t length;
   char recv_buffer[32], send_buffer[32], quit;
   struct sockaddr_in server; //declara servidor

   //cria socket
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if(sockfd < 0)
   {
      perror("client_sockfd:::");
      exit(1);
   }

   if(argc == 3)
   {
      //parametros de conexão com servidor
      server.sin_family  =  AF_INET;
      server.sin_port    =  htons(atoi(argv[2]));
      server.sin_addr.s_addr  =  inet_addr(argv[1]);
      memset(&(server.sin_zero), 0x00, 8);
   }
   else
   {
      printf("\n\tusage: %s <ip_do_host> <num_porta> \n\n", argv[0]);
      close(sockfd);
      exit(1);
   }

   //conectando-se ao servidor
   length = sizeof(struct sockaddr);
   if(connect(sockfd, (struct sockaddr *)&server, length) < 0)
   {
      perror("client_connect:::");
      close(sockfd);
      exit(1);
   }

   quit = 'N';
   while(quit != 'S')
   {
      //recebe do servidor
      bytes = recv(sockfd, recv_buffer, 32, 0);

      //supondo que não ocorreu um erro acima
      recv_buffer[bytes] = 0x00;//ponha o caractere '{FONTE}'

      //servidor fechou a conexão ou ocorreu um erro
      if(bytes <= 0)//ocorreu um erro = -1, fechou conexão = 0
      {
         perror("client_recv:::");
         close(sockfd);
         exit(1);
      }

      printf("\nDIGITE UMA MENSAGEM PARA ENVIAR AO SERVIDOR:\n");
      //lendo da entrada padrão
      fgets(send_buffer, 32, stdin);
      //se no inicio da string estiver o 'S' então esse é o ultimo loop
      quit = send_buffer[0];

      //enviando string ao servidor. strlen(send_buffer) pode ser menor que 32
      bytes = send(sockfd, send_buffer, strlen(send_buffer), 0);
      if(bytes < 0)
      {
         perror("client_send:::");
         close(sockfd);
         exit(1);
      }
      //só agora podemos ver a mensagem recebida do servidor
      printf("\nRECEBIDO:::%s\n\n", recv_buffer);
   }

   close(sockfd);

   return 0;
}
