## Functional Requirements:

1. Client
   * Opens socket, binds to server, and can send requests.
   * Encrypts and sends request to server.
   * Receives and decrypts request result from server.

3. Proxy Server
   * Opens socket, listens to client requests.
   * Decrypts and processes client requests.
   * Encrypts and returns request results to client.

5. Encryption
   * Basic encryption and decryption algorithm (super super basic)
   * Encrypt and decrypt implemented in both client and server
