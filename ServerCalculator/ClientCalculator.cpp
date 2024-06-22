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

int num1, num2, ans, choice;

S : bzero(buffer ,255);
      //Read Server String
      n = read(sockfd, buffer, 255);
    if(n<0) error("Error reading from socket num1");
    std::cout<<"Server - "<<buffer<<std::endl;
    //Read num1
    std::cin>>num1;
    std::cin.ignore();
    //Send num1 to Server
    write(sockfd, &num1, sizeof(int));

    //Read Server String
    bzero(buffer ,255);
      n = read(sockfd, buffer, 255);
    if(n<0) error("Error reading from socket num2");
    std::cout<<"Server - "<<buffer<<std::endl;
    //Read num2
    std::cin>>num2;
    std::cin.ignore();
    //Send num2 to Server
    write(sockfd, &num2, sizeof(int));

    //Read Server String
    bzero(buffer ,255);
      n = read(sockfd, buffer, 255);
    if(n<0) error("Error reading from socket num2");
    std::cout<<"Server - "<<buffer<<std::endl;
    //Read Choice
    std::cin>>choice;
    std::cin.ignore();
    //Send choice to Server
    write(sockfd, &choice, sizeof(int));

      if(choice == 5)
        goto Q;

    read(sockfd, &ans, sizeof(int));
    std::cout<<"Server- The answer is: "<<ans<<std::endl;
    if(choice != 5)
      goto S;
      

Q : std::cout<<"You have selected to exit. Exit Successful."<<std::endl;
    close(sockfd);
    return 0;

}
