#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    
    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket failed" << std::endl;
        return -1;
    }
    
    // Attach socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "setsockopt" << std::endl;
        return -1;
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return -1;
    }
    
    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen" << std::endl;
        return -1;
    }
    
    // Accept the first incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        std::cerr << "Accept" << std::endl;
        return -1;
    }

    // Read string length first
    uint32_t length = 0;
    read(new_socket, &length, sizeof(length));
    length = ntohl(length);
    
    // Read the string
    char *buffer = new char[length + 1];
    read(new_socket, buffer, length);
    buffer[length] = '\0';
    
    std::string message(buffer);
    delete[] buffer;
    
    std::cout << "Received message: " << message << std::endl;
    
    close(new_socket);
    close(server_fd);
    return 0;
}

