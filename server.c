#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#define PORT "21202" // for my birthday 02/12/2002
#define BACKLOG 2
#define NUM_CLIENTS 2

int main(void) {
  // get socket file descriptor

  struct addrinfo server_information;
  // set configuration for getaddrinfo():
  server_information.ai_family = AF_UNSPEC;       // IPv4 or IPv6
  server_information.ai_socktype = SOCK_STREAM;   // TCP Stream Socket
  server_information.ai_flags = AI_PASSIVE;       // automatically fill in host IP if address NULL

  struct addrinfo *server_adress_info;

  printf("Getting host address information... ");

  int result = getaddrinfo(
    "10.0.2.15",              // host ip
    PORT,                     // use constant port number defined at top of file "21202"
    &server_information,      // points to struct with server information
    &server_adress_info       // points to result struct to hold address information
  );

  // success and error messages
  if (result == 0) {
    printf("Success\n");
  }
  else {
    printf("%s\n", gai_strerror(result));
    exit(EXIT_FAILURE);
  }

  printf("Getting socket file descriptor... ");

  // get server socket descriptor
  int server_socket = socket(server_adress_info -> ai_family, server_adress_info -> ai_socktype, server_adress_info -> ai_protocol);

  // success and error messages
  if (server_socket == -1) {
    printf("Failed\n");
    printf("Error Number: %i\n", errno);
    exit(EXIT_FAILURE);
  }
  else { 
    printf("Success\n");
  }


  // Bind socket to port

  printf("Binding socket to port %s... ", PORT);

  int bind_server_socket = bind(server_socket, server_adress_info -> ai_addr, server_adress_info -> ai_addrlen);  // bind socket file descriptior to port on the machine

  // success and error messages
  if (bind_server_socket == 0) {
    printf("Success\n");
  }
  else {
    printf("Failed to bind socket to port %s\n", PORT);
    printf("Error Number: %i\n", errno);
    exit(EXIT_FAILURE);
  }


  // Listen on socket

  printf("Preparing to listen for connections on port %s...", PORT);

  int listening = listen(server_socket, BACKLOG);   // listen on port binded to socked file descriptor with a single queued connection allowed

  // success and error messages
  if (listening == 0) {
    printf("Success\n");
  }
  else {
    printf("Failed to listen for connections on port %s\n", PORT);
    printf("Error Number: %i\n", errno);
  }


  // Accept client sockets
  printf("Waiting for clients...\n");

  int max_socket_fd = 0; // keeps track of highest socket file description for later select function
  int client_count = 0; // keeps track of number of clients connected
  int client_sockets[NUM_CLIENTS]; // array of client file descriptrs
  struct sockaddr_storage client_address;
  socklen_t address_size = sizeof(client_address);

  while (1) {
    // accept client connection and update client address and address size information
    client_sockets[client_count] = accept(server_socket, (struct sockaddr *)&client_address, &address_size);

    // success and error messages
    if (client_sockets[client_count] == -1) {
      printf("Failed to accept connection on port %s\n", PORT);
      printf("Error Number: %i\n", errno);
    }
    else {
      printf("Client %d succesfully connected\n", client_count + 1);

      if (client_sockets[client_count] > max_socket_fd) {
        max_socket_fd = client_sockets[client_count] + 1; // update max socket fd for later select function if it is higher than the current
      }

      client_count++; // increase program count of clients
    }

    if (client_count >= NUM_CLIENTS) { // number of clients has reached maximum
      printf("All %d client(s) connected\n", client_count);
      // declare client_one and client_two
      int client_one = client_sockets[0];
      int client_two = client_sockets[1];
      break;
    }
  }

  // Interact with clients

  // Listen to clients

  while(1) {
    char message[100];

    fd_set sockets;
    FD_ZERO(&sockets);

    for (int i = 0; i < 2; i++) {
      FD_SET(client_sockets[i], &sockets);
    }

    int select_result = select(max_socket_fd, &sockets, NULL, NULL, NULL);

    // error and failure messages
    if (select_result == 0) {
      printf("Did not receive any data\n");
      break;
    }
    else if (select_result == -1) {
      printf("Error\n");
      printf("Error number: %d\n", errno);
    }
    // if successful, loop through socket file descriptors to find and store message
    else {
      for (int i = 0; i < 2; i++) {
        if FD_ISSET(client_sockets[i], &sockets); {
          recv(client_sockets[i], message, 100, 0);
        }
      }
    }
  }

  // Reply to Client

  char *message = "Hello client!\n";
  int sending = send(client_sockets[1], message, 15, 0);   // send string to client socket

  // success and error messages
  if (sending == -1) {
    printf("Failed to send message to client\n");
    printf("Error Number: %i\n", errno);
  }
  else {
    printf("Successfully sent %i bytes\n", sending);
  }

  // Close Server Socket

  printf("Closing server socket... ");

  int closing = close(server_socket);             // close server socket to no longer send or recieve on connection with client socket

  // success and error messages
  if (closing == 0) {
    printf("Success\n");
  }
  else {
    printf("Failed to close server socket on port %s\n", PORT);
    printf("Error Number: %i", errno);
  }
}