// C++ program to illustrate the client application in the 
// socket programming 
#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h> 

int main() 
{ 
	// creating socket 
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0); 






	// specifying address 
	sockaddr_in serverAddress; 
	serverAddress.sin_family = AF_INET; 
	serverAddress.sin_port = htons(8080); 
	serverAddress.sin_addr.s_addr = inet_addr("144.24.102.106"); 

	// sending connection request 
	int connection_status = connect(clientSocket, (struct sockaddr*)&serverAddress,
			sizeof(serverAddress)); 

      if(connection_status == -1)
      {
      std::cout<<"There was an error making a connection to the remote socket \n\n";
      }
      else 
      {
      std::cout<<"The connection to the remote socket was successfull\n";
      }

	// sending data 
	const char* message = "Hello, server!"; 
	send(clientSocket, message, strlen(message), 0); 

	// closing socket 
	close(clientSocket); 

	return 0; 
}

