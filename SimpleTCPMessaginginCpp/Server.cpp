#include <stdio.h>
#include <iostream>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <stdlib.h>

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[])
{

  if(argc<2)
  {
    std::cout<<"Port number not provided. Program terminated\n";
      exit(1);
  }

  int  sockfd, newsockfd, portno, n;
  char buffer[255];
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
  {
    error("Error opening Socket.");
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno=atoi(argv[1]);

  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr= INADDR_ANY;
  serv_addr.sin_port=htons(portno);
  if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("Binding Failed.");


  listen(sockfd, 5);
  clilen = sizeof(cli_addr);

  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

  if(newsockfd < 0)
    error("Error on Accept");

  while(1)
  {

    bzero(buffer, 255);
    n = read(newsockfd, buffer, 255);
    if(n<0)
      error("Error on reading");
    std::cout<<"Client : "<< buffer <<std::endl;

    bzero(buffer, 255);
    std::cin.getline(buffer,255);
    n = write(newsockfd, buffer, strlen(buffer));

    if(n<0)
      error("Error on Writing.");
    int i = strncmp("Bye", buffer, 3);
    if(i == 0)
      break;

  }
  close(newsockfd);
  close(sockfd);

  //sockfd=socket(int domain, int type, int protocol)
  //  For domain we are using AF_INET which is IPv4 
  //  For type we are using SOCK_STREAM    There are two types SOCK_STREAM and SOCK_DGRAM there are many others too though
  //  For protocol we are just using 0 for the default protocol
  /*
   *  int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
   */
  //
  //  struct sockaddr{
  //  sa_family_t sa_family;
  //  char sa_data[14];
  //  }
  //  This returns 0 if success and -1 if not succes
  //
  //  int listen(int sockfd, int backlog);
  //
  //  backlog is the number of connections the socket can handle at 1 time
  //
  //  newsockfd=accept(sockfd, (struct sockaddr*) ^addr,&addrlen);
  //
  //  int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  //
  //  int read(newsockfd,buffer ,buffer_size);
  //
  //  int write(newsockfd,buffer,buffer_size);
  //
  //  Some other function using which we can communicate are 
  //  send,receive
  //
  //  close() just closes the connection
  //  
  //

  return 0;
}
