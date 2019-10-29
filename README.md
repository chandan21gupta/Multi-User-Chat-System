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
3) The server is made to listen to any incoming connections from the clients. For each new client, a new thread is set up.
4) Each thread executes the listening() method. The listening method() accepts the incoming connections and sends and receives data.
5) recv() and send() calls are used to receive and send data from each server and client socket end points.
6) error-print() method is called to print relevant errors in case of a dead function call.
7) A client of type struct is made which contains the client's id, socket descriptor, client address of type struct, and the address length.
8) Arrays to store clients of type struct and threads.
9) existing_clients array which checks which clients have left the system.
10) pthread_join method, to close all the threads in case the server shuts down.

## client file
This file acts as one client. Each instance of this program acts as one client.<br>
1) A socket is made just like the server.<br>
2) connect() call connects to the server's address.
3) The client program accepts the user message. The user message is passed appropriately to the send_data() method to send the data to the server.
4) To simulate simultaneous send and receive messages, a separate thread is made to handle the receiving part. The thread executes the receiving() method.

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

## Restrictions
The default port is 8080.<br>
The address is localhost.<br>
The message buffer currently only handle 256 bytes of storage, including the Communication Rules.<br>
Maximum 1024 clients are currrently allowed to connect simultaneously to the server.<br>

