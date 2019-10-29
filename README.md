# Multi-User-Chat-System
A multi user chat system in c using one of Linux IPC mechanisms(Sockets)

## Code Description
The source code contains three files in total:<br>
1) server.c -> server file
2) client.c -> client file
3) Makefile

## Makefile
For compiling the source code with necessary bindings and linking. 

## server file
This file acts as a server through which clients send and recerive data from specified users.<br>
The steps involved in making the server:<br>
1) A socket is made using the call socket() and the returned value (socket file descriptor) is stored in a variable.
2) The socket file descriptor is bound to an address data structure. The default address is the local host.
3) The server is made to listen to any incoming connections from the clients.
4) Since a typical socket program can only handle a single client at a time, to handle multiple requests, multiple threads are used. For each incoming new connection, a separate thread is made to process the request, thereby, each client gets its own thread of execution.
5)Each thread executes the listening() method. The listening method() accepts the incoming connections and sends and receives data.
6)recv() and send() calls are used to receive and send data from each server and client socket end points.

## client file
This file acts as one client. Each instance of this program acts as one client. 

## Running the source
1) clone this repository.<br>
2) go in the directory of the source code.<br>
3) run "make" command in the terminal (Make sure you are in root access).<br>
4) run the command "./server.o". Any one terminal can act as a server.<br>
5) open a new terminal and run the command "./client.o" in the same directory.
6) follow step 5 for creating new clients

## Communication Rules

### LIST
List the ids of the currently active clients.

### EXIT
The client shuts down and exits the network.

### SEND (Identifier) MESSAGE
Sends the message to other clients.
Identifiers<br>
ALL - Send the message to all the clients
client_id - Send the message to a specific client by using his id

## Description
