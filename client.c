#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#define PORT "21202" // for my birthday 02/12/2002
#define IP NULL
#define MESSAGE_SIZE 2000

int get_and_connect_to_server_socket(char *ip, char *port) {
  // get socket file descriptor
  struct addrinfo server_information;

  // set configuration for getaddrinfo():
  server_information.ai_family = AF_UNSPEC;       // IPv4 or IPv6
  server_information.ai_socktype = SOCK_STREAM;   // TCP Stream Socket
  server_information.ai_flags = AI_PASSIVE;       // automatically fill in host IP

  struct addrinfo *server_address_info;

  printf("Getting host address information... ");

  int result = getaddrinfo(
    ip,
    port,
    &server_information,
    &server_address_info
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

  int server_socket = socket(server_address_info -> ai_family, server_address_info -> ai_socktype, server_address_info -> ai_protocol);   // get server socket descriptor

  // success and error messages
  if (server_socket == -1) {
    printf("Failed\n");
    printf("Error Number: %i\n", errno);
    exit(EXIT_FAILURE);
  }
  else { 
    printf("Success\n");
  }

  // connect to server
  
  int connecting = connect(server_socket, server_address_info -> ai_addr, server_address_info -> ai_addrlen);   // establish connection to server socket

  // success and error messages
  if (connecting == -1) {
    printf("Failed\n");
    printf("Error Number: %i\n", errno);
    exit(EXIT_FAILURE);
  }
  else { 
    printf("Success\n");
  }

  return server_socket;
}

void get_connection_details(int server_socket, char *details) {
  printf("Getting connection details... ");
  recv(server_socket, details, MESSAGE_SIZE, 0);  // get information from server about connection in order to configure client logic
  printf("%s", details);
}

void receive_message(int server_socket, char *message) {
  printf("Waiting for opponent to make move.\n");
  int receiving = recv(server_socket, message, MESSAGE_SIZE, 0);   // wait and receive message from client socket and save to message string
  if (strcmp("invalid\n", message) == 0 || strcmp("exit\n", message) == 0) {
    printf("Invalid command, try again.\n");
  }
  else {
    printf("\e[1;1H\e[2J");
    printf("Board:\n%s", message);
  }
}

void send_message(int server_socket, const char *message) {
  send(server_socket, message, MESSAGE_SIZE, 0);    // send message to server
}

int communicate(int server_socket) {
  char send_message[MESSAGE_SIZE];                      // initialize message te be sent
  char message[MESSAGE_SIZE];                           // initialize message to be received
  printf("> ");                                         // indicate user input to be sent to server
  fgets(send_message, sizeof(send_message), stdin);     // receive user input to be sent to server and save to send_message

  int sending  = send(server_socket, send_message, sizeof(send_message), 0);    // send message to server

  // exit condition
  if (strcmp(send_message, "exit\n") == 0) {
    return 0;
  }

  receive_message(server_socket, message);     // receive return message from server

  // exit and invalid conditions
  if (strcmp("exit\n", message) == 0 || strcmp("invalid\n", message) == 0) {
      // exit condition
      if (strcmp("exit\n", message) == 0) {
          return 0;
      } 
      // invalid condition
      else {
          return -1;
      }
  }

  sleep(0.1);

  receive_message(server_socket, message);    // receive message from server (based on second client's message)

  // exit and invalid conditions
  if (strcmp("exit\n", message) == 0 || strcmp("invalid\n", message) == 0) {
      // exit condition
      if (strcmp("exit\n", message) == 0) {
          return 0;
      } 
      // invalid condition
      else {
          return -1;
      }
  }

  return 1;
}

void close_connection(int server_socket) {
  // close connection

  printf("Closing server socket... ");

  int closing = close(server_socket);             // close server socket to no longer send or recieve on connection with server

  // success and error messages
  if (closing == 0) {
    printf("Success\n");
  }
  else {
    printf("Failed to close server socket on port %s\n", PORT);
    printf("Error Number: %i", errno);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int server_socket;                        // initialize server socket fd
  char connection_details[MESSAGE_SIZE];    // ititialize connection details to specify configuration for logic
  char message[MESSAGE_SIZE];               // initialize message string

  // connect to server and get socket fd
  server_socket = get_and_connect_to_server_socket(IP, PORT);
  // get connectiot details for logic config
  get_connection_details(server_socket, connection_details);

  // receive_message(server_socket, message); // Receive starting board from server
  
  // if player_two, must listen for server again before sending data to server
  if (strcmp("player_two\n", connection_details) == 0) {
    receive_message(server_socket, message);
  }

  int status;   // keeps track of communication status for logic
  while (1) {
    status = communicate(server_socket);  // communicate with server

    // exit condition
    if (status == 0) {
      break;
    }
    // invalid condition
    else if (status == -1) {
      continue;
    }
  }

  // close connection with server
  close_connection(server_socket);
}