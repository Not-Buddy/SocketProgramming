# SocketProgramming

```markdown
# SocketProgramming

A collection of C and C++ projects demonstrating core socket programming concepts,
including client-server communication, file transfer, messaging, and networked calculations.

## Features

- **Simple TCP Messaging:**  
  Basic client-server messaging using TCP sockets in C++.

- **File Transfer:**  
  Transfer files between client and server over a network.

- **Server Calculator:**  
  Networked calculator that processes arithmetic operations sent from clients.

- **Troubleshooting Utilities:**  
  Additional tools and skeleton code for debugging and learning socket programming.

## Folder Structure

- `SimpleTCPMessaginginCpp/` — Basic TCP messaging example
- `FileTransfer/` — File transfer implementation
- `ServerCalculator/` — Networked calculator server
- `BookCode/` — Reference implementations and book-based examples
- `Troubleshooting/` — Utilities and skeletons for debugging

## Getting Started

### Prerequisites

- GCC or any C/C++ compiler
- Basic knowledge of terminal/command line
- Unix/Linux environment recommended (for socket API compatibility)

### Compilation Example

Navigate to the relevant directory and compile the code. For example:

```
cd SimpleTCPMessaginginCpp
g++ server.cpp -o server
g++ client.cpp -o client
```

### Running the Programs

Start the server first:

```
./server
```

Then, in another terminal, start the client:

```
./client
```

Follow the prompts in each program for input and interaction.

## Learning Outcomes

- Hands-on experience with socket APIs in C and C++
- Understanding of TCP client-server architecture
- Practice with file transfer and remote computation over networks

```
