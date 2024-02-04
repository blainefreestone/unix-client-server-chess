## Functional Requirements:

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