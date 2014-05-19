CC=gcc
OBJ = server-tcp.o

tcp-server: server-tcp.c
	$(CC) -o server-tcp server-tcp.c -lcyassl

.PHONY: clean

clean:
	rm -f *.o server-tcp

