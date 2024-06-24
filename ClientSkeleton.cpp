#include <stdio.h>
#include <iostream>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdlib.h>

void error(const char *msg)
{
  perror(msg);
  exit(1);
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
 
  //Client side Skeleton Above
  //Code below here
  
  


  

  //Code above here
  //Client side Skeleton Below
  close(sockfd);
}

