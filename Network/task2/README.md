# Echo Server Using Linux Socket API

## Description
This program implements a simple Echo Server using the Linux Socket API. The server receives a message from the client, appends a response, and sends it back, demonstrating basic TCP communication.

## How It Works

### Server:
- Creates a socket and binds it to a port.
- Listens for incoming client connections.
- Accepts a client connection.
- Reads a message from the client.
- Appends a response and sends it back.
- Closes the connection.

### Client:
- Creates a socket and connects to the server.
- Sends a message to the server.
- Receives the modified message from the server.
- Displays the response.
- Closes the connection.

## Compilation
Compile both server and client using gcc:
```bash
gcc -o server server.c  
gcc -o client client.c  
```

## Running the Program
### Start the server:
```bash
./server
```

### Run the client:
```bash
./client
```

Enter a message in the client, and see the response from the server.
