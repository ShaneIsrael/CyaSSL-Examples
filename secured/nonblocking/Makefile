CC=gcc
OBJ = server-tls-nonblocking.o

server-tls-nonblocking: server-tls-nonblocking.c
	$(CC) -o server-tls-nonblocking server-tls-nonblocking.c -lcyassl

.PHONY: clean

clean:
	rm -f *.o server-tls-nonblocking

