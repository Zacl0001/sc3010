# SC3010 – Heartbleed Demo (Client/Server)

This project demonstrates a vulnerable server and a fixed server implementation using sockets on Windows.

## Compilation (Windows)

Use `gcc` with the Winsock library:

```bash
gcc client.c -o client -lws2_32
gcc server_vuln.c -o server_vuln -lws2_32
gcc server_fixed.c -o server_fixed -lws2_32
```

# Running the Vulnerable Server
Open two terminals.
In the first terminal, start the vulnerable server:
```bash
./server_vuln
```
In the second terminal, run the client:
```bash
./client
```
Test with the following input:
Payload length: 1100
Data: A

# Running the Fixed Server
Stop the vulnerable server.
Open two terminals again.
In the first terminal, start the fixed server:
```bash
./server_fixed
```
In the second terminal, run the client:
```bash
./client
```

Test with the same input:
Payload length: 1100
Data: A
