echo "# Socket Time Server and Client

## Overview
A simple **TCP client-server** program where the server calculates and sends the current date and time in \`YYYY/MM/DD HH:MM\` format, and the client receives and prints it.

## Compilation
\`\`\`sh
gcc -o server server.c itoa.c
gcc -o client client.c
\`\`\`

## Usage
Run the server first:
\`\`\`sh
./server
\`\`\`
Then run the client:
\`\`\`sh
./client
\`\`\`

## Notes
- The server manually calculates time from the UNIX epoch.
- Uses a custom \`itoa()\` implementation.
- Server sends time in UTC+4.