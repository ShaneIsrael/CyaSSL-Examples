CC=gcc
OBJ = server-tls-threaded.o

server-tls: server-tls-threaded.c
	$(CC) -o server-tls-threaded server-tls-threaded.c -lpthread -lcyassl

.PHONY: clean

clean:
	rm -f *.o server-tls-threaded
