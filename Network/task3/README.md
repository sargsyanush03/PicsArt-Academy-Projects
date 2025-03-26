# Socket Time Server

## Overview  
A simple client-server application using Linux sockets. The server calculates the current date and time, sends it to the client, which then displays it.

## Features  
- Uses TCP sockets for communication.  
- Calculates time manually from the UNIX epoch.  
- Custom `itoa()` function for integer-to-string conversion.

## Notes  
- The server listens on **127.0.0.1:8080**.  
- Ensure the server is running before starting the client.  
- The server sends time in `YYYY/MM/DD HH:MM` format (UTC+4).

## How It Works  
1. **Server:**  
   - Listens for client connections.  
   - Computes the current date and time from the UNIX timestamp.  
   - Sends the formatted date and time string to the client.  

2. **Client:**  
   - Connects to the server.  
   - Receives the date and time string.  
   - Displays the received data.

## Compilation & Execution  
```sh  
# Compile server and helper functions  
gcc itoa.c server.c -o server  

# Compile client  
gcc client.c -o client  

# Run the server  
./server  

# In a separate terminal, run the client  
./client  
```

