CC=gcc
OBJ = server-tls.o

tcp-server: server-tls.c
	$(CC) -o server-tls server-tls.c -lcyassl

.PHONY: clean

clean:
	rm -f *.o server-tls

