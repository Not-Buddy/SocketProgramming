/*
 * filename server_ipaddress portno 
 *
 * argv[0] filename 
 * argv[1] server_ipaddress 
 * argv[2] portno 
*/

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[])
{
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[255];
  if(argc < 3)
  {
    std::cout<<"usage "<<argv[0]<<" hotname port\n"<<std::endl;
    exit(1);
  }

  portno=atoi(argv[2]);
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd < 0)
    error("ERROR opening socket");

    server=gethostbyname(argv[1]);
    if(server == NULL)
    {
      std::cout<<"Error , no such host"<<std::endl;
    }

    bzero((char *) &serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr , (char *) &serv_addr.sin_addr.s_addr , server->h_length);
    serv_addr.sin_port = htons(portno);
    if(connect(sockfd , (struct sockaddr *) &serv_addr , sizeof(serv_addr))<0)
      error("Connection Failed");
    
    while(1)
    {
      bzero(buffer , 255);
      std::cin.getline(buffer , 255);
      n = write(sockfd, buffer , strlen(buffer));
      if(n<0)
        error("Error on writing");
      bzero(buffer , 255);
      n = read(sockfd , buffer , 255);
      if(n<0)
        error("Error on reading.");
      std::cout<<"Server: "<<buffer<<std::endl;

      int i = strncmp("bye",buffer , 3);
      if(i==0)
        break;
    }

    close(sockfd);
    return 0;
}
