#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <unistd.h>

int main()
{ 
  // create a socket

  int network_socket;
  network_socket = socket(AF_INET, SOCK_STREAM, 0);

  // specify an address for the socket 
  struct sockaddr_in server_address;
  server_address.sin_family=AF_INET;
  server_address.sin_port=htons(8080);
  server_address.sin_addr.s_addr= INADDR_ANY;
 
  int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
  // check for error with the connectione  
  if(connection_status== -1)
  {
    std::cout<<"There was an error making a connection to the remote socket \n\n";
  }

  //receiver data from the server 
  char server_response[256];
  recv(network_socket, &server_response, sizeof(server_response), 0);

  //print out the server's response 
  std::cout<<"The server sent the data: " << server_response << std::endl;

  close(network_socket);


  return 0;
}
