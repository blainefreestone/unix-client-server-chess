# Overview

**This program leverages Unix sockets to establish communication channels between a server and two clients, facilitating a chess game between the two clients.**

The program follows the basic flow of Unix client-server connections and communications:

![Socket Programming Logic](./images/socket_programming.png)

## The Server

The server binds to a socket and gets its file descriptor.

```c
getaddrinfo(
   ip,                       // host ip
   port,                     // use constant port number defined a top of file "21202"
   &server_information,      // points to struct with server information
   &server_adress_info       // points to result struct to hold address information
);

int server_socket = socket(server_adress_info -> ai_family, server_adress_info -> ai_socktype, server_adress_info -> ai_protocol);

bind(server_socket, server_adress_info -> ai_addr, server_adress_info -> ai_addrlen);  // bind socket file descriptior to port on the machine
```

Then, it listens for connections on that socket ( `BACKLOG` specifies the number of clients allowed to wait for connection at once ).

```c
listen(server_socket, BACKLOG);
```

The server then accepts two clients and stores their socket file descriptors for future communication.

```c
*client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_size);
```

The server uses the following functions to communicate with the clients:

```c
void receive_message(int client_socket, char *message)
const char* process_message(char* message, int player_num)
void send_message(int client_socket, const char *message)
```

The `process_message()` function is used to implement the chess game logic found in the `chess.c` file.

Finally, the server closes the connection with both clients.

```c
close(server_socket); 
```

## The Client


{Describe your purpose for writing this software.}

[Demo Video](http://youtube.link.goes.here)

# Network Communication

This implements a client-server TCP network with specific logic to handle two seperate client connections. 

The messages between the client and the server are all strings; the server has logic to process client messages and return strings.

# Development

## Functional Requirements (updated through development):

1. Client
   * Opens socket, binds to server, configures self as player 1 or player 2.
   * Sends from and receives data from server.

2. Proxy Server
   * Opens socket, listens to clients.
   * Receives data from clients, processes it, and returns response to each client accordingly.

3. Chess Game
   * Displays screen with pieces on terminal. 
   * Pieces can be moved and controlled with commands.
   * (Strech) Implement proper game mechanics and rules.

## Environment

This program was developed...
* in the Ubuntu Linux Distribution
* with VS Code
* using the GCC C compiler

## Requirements

This program uses Unix socket functions in Linux.

# Useful Websites

{Make a list of websites that you found helpful in this project}
* [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/split/)
* [Beej's Guide to C Programming](https://beej.us/guide/bgc/)
* [Geeks for Geeks - C Programming Language](https://www.geeksforgeeks.org/c-programming-language/)

# Future Work

{Make a list of things that you need to fix, improve, and add in the future.}
* Item 1
* Item 2
* Item 3
