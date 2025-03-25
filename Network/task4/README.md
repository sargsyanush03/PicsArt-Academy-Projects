# Calculator Server

## Overview  
This is a simple client-server application using Linux Sockets that acts as a calculator. The server receives a mathematical expression from the client, evaluates it, and returns the result.

## Features  
- Supports basic arithmetic operations: addition (+), subtraction (-), multiplication (*), division (/), and modulo (%).
- Uses TCP sockets for communication.
- Handles invalid input and division by zero.

## Notes  
- The server listens on **127.0.0.1:8080**.  
- Ensure the server is running before starting the client.  
- The input format should be: `<number> <operator> <number>` (e.g., `10 * 5`).

## How It Works  
1. **Server:**  
   - Listens for client connections.  
   - Receives a mathematical expression as a string (e.g., "12 + 34").  
   - Parses the expression and calculates the result.  
   - Sends the result back to the client.  

2. **Client:**  
   - Connects to the server.  
   - Sends a mathematical expression.  
   - Receives and displays the result.

## Compilation & Execution  
```sh  
# Compile server and helper functions  
gcc itoa.c parse_exp.c cleanup.c server.c -o ./server  

# Compile client and helper functions  
gcc cleanup.c client.c -o ./client  

# Run the server  
./server  

# In a separate terminal, run the client  
./client  
