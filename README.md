# Overview

{Provide a description the networking program that you wrote. Describe how to use your software.  If you did Client/Server, then you will need to describe how to start both.}

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
