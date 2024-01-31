#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

int main(void) {
  // get socket file descriptor

  const char *PORT = "21202";                     // server port number
  const char *ADDRESS = "127.0.0.1";
  struct addrinfo server_information;

  // set configuration for getaddrinfo():
  server_information.ai_family = AF_UNSPEC;       // IPv4 or IPv6
  server_information.ai_socktype = SOCK_STREAM;   // TCP Stream Socket

  struct addrinfo *server_adress_info;

  printf("Getting host address information... ");

  int result = getaddrinfo(
    ADDRESS,
    PORT,
    &server_information,
    &server_adress_info
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

  // TODO: connect to server

  // TODO: communicate with server

  // TODO: close connection
}