#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#define PORT "21202" // for my birthday 02/12/2002
#define IP "10.0.2.15"
#define BACKLOG 2
#define NUM_CLIENTS 2
#define MESSAGE_SIZE 200

int get_and_bind_to_socket(char *ip, char *port) {
  // get socket file descriptor

  // set configuration for getaddrinfo(): 
  struct addrinfo server_information;
  server_information.ai_family = AF_UNSPEC;       // IPv4 or IPv6
  server_information.ai_socktype = SOCK_STREAM;   // TCP Stream Socket
  server_information.ai_flags = AI_PASSIVE;       // automatically fill in host IP if address NULL

  struct addrinfo *server_adress_info;

  printf("Getting host address information... ");

  int result = getaddrinfo(
    ip,                       // host ip
    port,                     // use constant port number defined at top of file "21202"
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

  return server_socket;
}

void listen_on_socket(int server_socket) {
  printf("Preparing to listen for connections on port %s...", PORT);

  // listen on port binded to socked file descriptor with a single queued connection allowed
  int listening = listen(server_socket, BACKLOG);

  // success and error messages
  if (listening == 0) {
    printf("Success\n");
  }
  else {
    printf("Failed to listen for connections on port %s\n", PORT);
    printf("Error Number: %i\n", errno);
    exit(EXIT_FAILURE);
  }
}

void accept_client(int server_socket, int* client_socket, int* max_socket_fd) {
  // define parameters for accept function
  struct sockaddr_storage client_address;
  socklen_t address_size = sizeof(client_address);

  // accept client connection and update client address and address size information
  *client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_size);

  // success and error messages
  if (*client_socket == -1) {
    printf("Failed to accept connection on port %s\n", PORT);
    printf("Error Number: %i\n", errno);
    exit(EXIT_FAILURE);
  }
  else {
    printf("Client succesfully connected (fd: %d)\n", *client_socket);
  }

  // update max socket fd for later select function if new client socket fd is greater than running max
  if (*client_socket + 1 > *max_socket_fd) *max_socket_fd = *client_socket + 1;
}

void receive_message(int client_socket, char *message) {
  printf("Waiting for message from client\n");
  int receiving = recv(client_socket, message, MESSAGE_SIZE, 0);   // wait and receive message from client socket and save to message string
  printf("Received message:  %s", message);
}

const char* process_message(char* message) {
  // invalid case
  if (strcmp("invalid\n", message) == 0) {
    return "invalid\n";
  }
  else {
    return message;
  }
}

void send_message(int client_socket, const char *message) {
  send(client_socket, message, MESSAGE_SIZE, 0);  // send message to client socket
}

int communicate(int active_client_socket, int passive_client_socket) {
  char message[MESSAGE_SIZE];                         // initialize message string
  memset(message, 0, MESSAGE_SIZE);                   // empty out message string
  receive_message(active_client_socket, message);     // receive string from active_client and store in message

  // exit condition
  if (strcmp("exit\n", message) == 0) {
    send_message(passive_client_socket, "exit\n");    // notify passive client to disconnect
    return 0;                                         // client disconnect return value
  }

  const char* return_message = process_message(message);  // process message from client
  printf("Message to send: %s", return_message);

  // invalid message condition
  if (strcmp("invalid\n", return_message) == 0) {
    send_message(active_client_socket, return_message);     // notify active client that message was invalid
    return -1;                                              // client invalid message return value
  }

  // send both clients return message after active_client's message has been processed
  send_message(active_client_socket, return_message);
  send_message(passive_client_socket, return_message);

  return 1;
}

void close_connection(int server_socket) {
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

int main(void) {
  int server_socket;
  int client_one_socket;
  int client_two_socket;
  int max_socket_fd = 0;

  // Get and bind to host socket
  server_socket = get_and_bind_to_socket(IP, PORT);

  // Listen on server socket
  listen_on_socket(server_socket);

  // Accept client sockets
  printf("Waiting for clients...\n");

  accept_client(server_socket, &client_one_socket, &max_socket_fd);   // accept client one and save fd in client_one_socket
  send_message(client_one_socket, "player_one\n");

  accept_client(server_socket, &client_two_socket, &max_socket_fd);   // accept client two and save fd in client_two_socket
  send_message(client_two_socket, "player_two\n");

  printf("(max socket fd: %d)\n", max_socket_fd);   // print running maxfd (mostly for bugging)

  int status;   // keeps track of communicate status for program logic
  while (1) {
    communicate1:   // label to repeat communicate with client_one_socket in case of invalid message
    status = communicate(client_one_socket, client_two_socket);
    // invalid message condition
    if (status == -1) {
      goto communicate1;    // repeat communicate process
    }
    // exit condition
    else if (status == 0) {
      break;
    }

    communicate2:   // label to repeat communicate with client_one_socket in case of invalid message
    status = communicate(client_two_socket, client_one_socket);
    // invalid message condition
    if (status == -1) {
      goto communicate2;
    }
    // exit condition
    else if (status == 0) {
      break;
    }
  }

  // close connection and finish
  close_connection(server_socket);
}