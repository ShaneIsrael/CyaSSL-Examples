CC=gcc
OBJ = tcp-server.o

tcp-server: server-tcp.c
	$(CC) -o tcp-server server-tcp.c

.PHONY: clean

clean:
	rm -f *.o tcp-server

