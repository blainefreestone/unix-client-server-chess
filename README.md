# Overview

[Demo Video](http://youtube.link.goes.here)

**This program leverages Unix sockets to establish communication channels between a server and two clients, facilitating a chess game between the two clients.**

The program follows the basic flow of Unix client-server connections and communications:

![Socket Programming Logic](./images/socket_programming.png)

I wrote this program as an exercise in network programming; to understand and implement basic network communication between two or more computers on a network. Moreover, I wanted to gain more experience in the C programming language.

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

The client gets the socket file descriptor of the server based on given information such as ip address and port number (of the server).

```c
getaddrinfo(
   ip,
   port,
   &server_information,
   &server_address_info
);

int server_socket = socket(server_address_info -> ai_family, server_address_info -> ai_socktype, server_address_info -> ai_protocol);   // get server socket descriptor
```

Then, it establishes a connection with the server.

```c
connect(server_socket, server_address_info -> ai_addr, server_address_info -> ai_addrlen);   // establish connection to server socket
```

Similar to the server, it uses the following functions to communicate with the server. The client however, first receives connection information from the server (in this case whether its player_one or player_two) and then is able to receive and send data.

```c
void get_connection_details(int server_socket, char *details)
void receive_message(int server_socket, char *message)
void send_message(int server_socket, const char *message)
```

Finally, the client closes its connection.

```c
close(server_socket);
```

## The Chess Logic

The logic for the chess game can be found in the `chess.c` file. Since the main purpose of the program was not the implementation of game logic, it will not be outlined here.

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

To run...

1. Compile the server and client programs using the gnu compiler on Linux `gcc -o Client client.c` and `gcc -o Server server.c`.
1. Run the server executable `./Server`.
1. Run the client executables (two connections required to begin the game) `./Client`
1. To close the connection send the message `exit` to the server from either client. 

# Useful Websites
* [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/split/)
* [Beej's Guide to C Programming](https://beej.us/guide/bgc/)
* [Geeks for Geeks - C Programming Language](https://www.geeksforgeeks.org/c-programming-language/)

# Future Work

* Implement more accurate and comprehensive logic in the chess game (piece movement verification, checking for checks on either king, castling, etc.)
* More standardized and flexible communication logic between the server and clients.