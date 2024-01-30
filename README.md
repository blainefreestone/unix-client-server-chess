## Functional Requirements:

1. Client
   a. Opens socket, binds to server, and can send requests.
   b. Encrypts and sends request to server.
   b. Receives and decrypts request result from server.

3. Proxy Server
   a. Opens socket, listens to client requests.
   b. Decrypts and processes client requests.
   c. Encrypts and returns request results to client.

5. Encryption
   a. Basic encryption and decryption algorithm (super super basic)
   b. Encrypt and decrypt implemented in both client and server
