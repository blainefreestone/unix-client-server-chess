#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
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

  if (result == 0) {                        // if addrinfo successfuly generated...
    printf("Success\n");
  }
  else {                                    // otherwise use gai_strerror to interpret error code and display
    printf("%s\n", gai_strerror(result));
    exit(EXIT_FAILURE);
  }

  printf("Getting socket file descriptor... ");

  int server_socket = socket(server_adress_info -> ai_family, server_adress_info -> ai_socktype, server_adress_info -> ai_protocol);   // get server socket descriptor

  if (server_socket == -1) {                        // if server socket was not retrieved print error and exit
    printf("Failed\n");
    printf("Error Number: %i\n", server_socket);
  }
  else {                                            // otherwise...
    printf("Success\n");
  }

// Bind socket to port

// TODO: Listen on socket

// TODO: Accept client socket

// TODO: Process request

// TODO: Reply

// TODO: Close

}