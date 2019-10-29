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
This file acts as a server through which clients send and recerive data from specified users.

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

### SEND (Identifier) MESSAGE
#### Identifier
