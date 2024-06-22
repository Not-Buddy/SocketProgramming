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

    int num1, num2, ans, choice;
    //Ask for Number 1
S : n = write(newsockfd, "Enter Number 1: ",strlen("Enter Number 1"));
    if(n<0) error("Error writing to socket");
    //Read num1
    read(newsockfd, &num1, sizeof(int));

    std::cout<<"Client - Number 1 is : "<<num1 <<std::endl;

    n = write(newsockfd,"Enter number 2 : ",strlen("Enter Number 1")); //Ask for Number 2 
    if(n<0) error("ERROR writing to socket");
    read(newsockfd, &num2, sizeof(int));
    std::cout<<"Client - Number 1 is : "<<num2<<std::endl;

    char ChoiceStatement[255]="Enter your choice :\n1. Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exit"; 

  // Ask for Choice 
  n=write(newsockfd,ChoiceStatement,strlen(ChoiceStatement)); 

  if(n<0) error("ERROR writing to socket");
  //Read Choice
  read(newsockfd, &choice, sizeof(int));
  std::cout<<"Client - Choice is : "<<choice<<std::endl;

  switch(choice)
  {
    case 1:
      ans = num1 + num2;
      break;
    case 2:
      ans = num1 - num2;
      break;
    case 3:
      ans = num1 * num2;
      break;
    case 4:
      ans = num1 / num2;
      break;
    case 5:
      goto Q;
      break;
  }

  write(newsockfd, &ans, sizeof(int));
  if(choice != 5)
    goto S;

Q :close(newsockfd);
   close(sockfd);
  return 0;

}







