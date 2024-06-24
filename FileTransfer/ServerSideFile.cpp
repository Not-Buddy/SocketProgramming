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

  //Socket Code skeleton Above
  //Code here

  FILE *fp;
  int ch = 0;
  fp = fopen("Glad_received.txt", "a");
  int words;
  


  // First Read coresponding to the write in Client Side
  // Reads the amount of words in the txt file
  read(newsockfd, &words, sizeof(int));

  while(ch != words)
  {
    //Recuring 2nd Read corresponding to the writes in 
    //Client Side
    //Reads the words 1 by 1
    read(newsockfd, buffer, 255);
    fprintf(fp, "%s", buffer);
    ch++;
  }
  std::cout<<"The file has been received successfully. It is saved by the name Glad_received.txt"<<std::endl;
  


  //Socket Code skeleton Below
  close(newsockfd);
  close(sockfd);
  return 0;
}
