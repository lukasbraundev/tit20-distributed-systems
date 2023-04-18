# TIT20 Distributed Systems
Github Repository for the lecture Distributed Systems at DHBW Ravensburg in the course TIT20 of Computer Science.

## Task 1: UDP Echo Server
Create a UDP Echo Server
- Waiting for requests on a defined UDP port,
- When a request from a client arrives, it will be sent including a Counter sent back.
- Actions should be logged on the console of the server
- As a client a netcat client is sufficient (no own application necessary)
- Use the BSD Socket API in C.

The Task is completed at [UPD Echo Server](UDP-echo-client/udp_echo.c).
To execute the Programm clone the Repository and follow the steps below.
1. To compile the file use the GCC compiler in the directory of the **udp_echo.c file** and execute:
```
gcc udp_echo.c
```
2. To Start use:
```
.\a.out
```
3. You can test the application using the netcat command
```
netcat -u 127.0.0.1 8888
```
