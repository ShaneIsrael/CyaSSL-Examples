CC=gcc
OBJ = server-tls.o

server-tls: server-tls.c
	$(CC) -o server-tls server-tls.c -lcyassl

.PHONY: clean

clean:
	rm -f *.o server-tls