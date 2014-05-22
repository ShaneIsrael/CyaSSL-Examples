CC=gcc
OBJ = server-tcp-nonblocking.o

tcp-server: server-tcp-nonblocking.c
	$(CC) -o server-tcp-nonblocking server-tcp-nonblocking.c -lcyassl

.PHONY: clean

clean:
	rm -f *.o server-tcp-nonblocking

