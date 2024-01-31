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
  struct addrinfo client_information;

  // set configuration for getaddrinfo():
  client_information.ai_family = AF_UNSPEC;       // IPv4 or IPv6
  client_information.ai_socktype = SOCK_STREAM;   // TCP Stream Socket

  struct addrinfo *client_address_info;

  printf("Getting host address information... ");

  int result = getaddrinfo(
    ADDRESS,
    PORT,
    &client_information,
    &client_address_info
  );

  // success and error messages
  if (result == 0) {
    printf("Success\n");
  }
  else {
    printf("%s\n", gai_strerror(result));
    exit(EXIT_FAILURE);
  }

  // TODO: connect to server

  // TODO: communicate with server

  // TODO: close connection
}