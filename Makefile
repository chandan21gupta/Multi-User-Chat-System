TARGET=client server
CC=gcc
normal: $(TARGET)
client: client.c
	$(CC) client.c -o client.o -lpthread
server: server.c
	$(CC) server.c -o server.o -lpthread
clean:
	$(RM) $(TARGET)
