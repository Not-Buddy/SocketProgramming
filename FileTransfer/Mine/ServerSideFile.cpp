#include <stdio.h>
#include <iostream>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <stdlib.h>
#include <fstream>

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
  std::string *buffer;
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

  std::ofstream outFile("Received_File.txt");
  if(!outFile.is_open())
    error("Error: Program was not able to make a File");

  int LineCount{};

  //First Read corresponding to the write in the Client side
  //Accepts the total Lines in the txt File
  read(newsockfd, &LineCount, sizeof(int));
  std::cout<<"File has "<<LineCount<<" Lines"<<std::endl;

  for(int i{0};i<LineCount;i++)
  {
    //Recuring 2nd write corresponding to the write in 
    //Client side 
    uint32_t length{0};
    read(newsockfd, &length, sizeof(length));
    length=ntohl(length);

    //Creating std::string from c_str()
    //Cause retarded std::string cannot be 
    //transffered itself
    char *buffer = new char[length + 1];

    //char *charArray = new char[size];
    read(newsockfd, buffer, length);
    buffer[length]='\0';
    std::string line(buffer);
    std::cout<<"Writing Line: "<<line<<" Size: "<<length<<std::endl;

    //std::cout<<*buffer<<" Size:"<<buffer->size()<<std::endl;
    outFile<<line;
    outFile<<"\n";
    delete[] buffer;
  }
  std::cout<<"The file has been received successfully. It is saved by the \nSaved by name: Received_File.txt"<<std::endl;
  


  //Socket Code skeleton Below
  close(newsockfd);
  close(sockfd);
  return 0;
}
