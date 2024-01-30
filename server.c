#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

int main(void) {
  // get socket file descriptor
  
  const char *PORT = "21202"; // for my birthday 02/12/2002
  struct addrinfo server_information;
  // set configuration for getaddrinfo():
  server_information.ai_family = AF_UNSPEC;       // IPv4 or IPv6
  server_information.ai_socktype = SOCK_STREAM;   // TCP Stream Socket
  server_information.ai_flags = AI_PASSIVE;       // automatically fill in host IP

  struct addrinfo *server_adress_info;

  printf("Getting host address information... ");

  int result = getaddrinfo(
    NULL,                     // automatically use host ip
    PORT,                     // use constant port number defined at top of file "21202"
    &server_information,      // points to struct with server information
    &server_adress_info       // points to result struct to hold address information
  );

  // success and error messages
  if (result == 0) {                        // if addrinfo successfuly generated...
    printf("Success\n");
  }
  else {                                    // otherwise use gai_strerror to interpret error code and display
    printf("%s\n", gai_strerror(result));
    exit(EXIT_FAILURE);
  }

  printf("Getting socket file descriptor... ");

  int server_socket = socket(server_adress_info -> ai_family, server_adress_info -> ai_socktype, server_adress_info -> ai_protocol);   // get server socket descriptor

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

  int listening = listen(server_socket, 1);   // listen on port binded to socked file descriptor with a single queued connection allowed

  // success and error messages
  if (listening == 0) {
    printf("Success\n");
  }
  else {
    printf("Failed to listen for connections on port %s\n", PORT);
    printf("Error Number: %i\n", errno);
  }

  // TODO: Accept client socket

  struct sockaddr_storage client_address;
  socklen_t address_size;

  printf("Waiting to accept connection... ");
  fflush(stdout);   // allows text to print before waiting for client to be accepted

  int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_size);   // accept client connection and update client address and address size information

  // success and error messages
  if (client_socket == -1) {
    printf("Failed to accept connection on port %s\n", PORT);
    printf("Error Number: %i\n", errno);
  }
  else {
    printf("Success\n");
  }

  // TODO: Process request

  // Reply to Client

  char *message = "Hello world!\n";
  int sending = send(client_socket, message, 14, 0);   // send string to client socket

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