File Transfer Using Linux Socket API
Problem Description
This project demonstrates how to exchange data between a client and a server using the Linux Socket API by transferring a file. The client reads a file's content and sends it to the server, which then writes the content into a new file.

Objective:
The client will take command-line arguments for the IP address, port number, and the file name to transfer.
The client reads the file's content and sends it to the server using sockets.
The server receives the file content and writes it to a new file.
File Structure
bash
Copy code
task1/
│
├── server/
│   └── server_program.c   # Server code for receiving and saving the file.
│
├── client_program.c       # Client program located in the task1 directory (not in client folder).
│
└── file.txt               # Sample file to be transferred.
Server Side Instructions
Create the server socket:

The server creates a socket using the socket() system call.
Bind the server socket to a port:

The server binds the socket to the specified port using the bind() function.
Listen for incoming connections:

The server enters passive mode by calling the listen() function.
Accept the connection from the client:

The server accepts the client connection using the accept() function.
Receive file data:

The server reads the filename and file size from the client, and then receives the file content using read().
Write the file:

The server writes the received file content into a new file.
Close the socket and release resources:

After the file is received, the server closes the socket and releases resources.
Client Side Instructions
Take command-line arguments:

The client receives the IP address, port number, and file name from the command line.
Create the client socket:

The client creates a socket using the socket() system call.
Connect to the server:

The client connects to the server using the connect() function.
Read the file content:

The client opens the specified file, reads its content, and stores it in a buffer.
Send file data to the server:

The client sends the filename, file size, and content to the server using the write() function.
Close the socket:

After sending the file content, the client closes the socket.
Compilation Instructions
Compile the server:

bash
Copy code
gcc -o server/server_program server/server_program.c
Compile the client (since it's in the task1 directory):

bash
Copy code
gcc -o client_program client_program.c
Running the Programs
Start the server:

Navigate to the server directory and run the server program:
bash
Copy code
./server_program
Run the client:

Navigate to the task1 directory (where the client program is located) and run the client program, passing the IP address, port, and filename as arguments:
bash
Copy code
./client_program <Server IP> <Port> file.txt
Example:

bash
Copy code
./client_program 127.0.0.1 8080 file.txt
Example Workflow
The server listens for incoming connections on port 8080.
The client connects to the server, sends the filename (file.txt), the file size, and the file content.
The server receives the content and writes it to a new file on the server's machine.
Both the client and server close their respective sockets after the file transfer is complete.
Additional Notes
The server binds to port 8080 and listens for incoming connections.
The file transfer protocol is simple: the filename, file size, and file content are sent sequentially from the client to the server.
The program assumes that the client and server are on the same local network, but it can be modified to work over the internet by configuring proper port forwarding.
References
Linux Socket Programming Documentation
Linux man pages for socket functions

