#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(void) {
  const char *PORT = "21202"; // for my birthday 02/12/2002
  
  // Socket
  struct addrinfo server_information;
  // Set configuration for getaddrinfo():
  server_information.ai_family = AF_UNSPEC;       // IPv4 or IPv6
  server_information.ai_socktype = SOCK_STREAM;   // TCP Stream Socket
  server_information.ai_flags = AI_PASSIVE;       // Automatically fill in host IP

  struct addrinfo *server_adress_info;

  printf("Getting host address information... ");

  int result = getaddrinfo(
    NULL,                     // automatically use host ip
    PORT,                     // use constant port number defined at top of file "21202"
    &server_information,      // points to struct with server information
    &server_adress_info       // points to result struct to hold address information
  );

  if (result == 0) {                        // If addrinfo successfuly generated...
    printf("Success\n");
  }
  else {                                    // Otherwise use gai_strerror to interpret error code and display
    printf("%s", gai_strerror(result));
  }

// TODO: Bind to socket

// TODO: Listen on socket

// TODO: Accept client socket

// TODO: Process request

// TODO: Reply

// TODO: Close

}