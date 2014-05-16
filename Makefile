CC=gcc
CFLAGS=-Wall -I ../include
OBJ = tcp-server.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tcp-server: server-tcp.c
	$(CC) -o tcp-server server-tcp.c

.PHONY: clean

clean:
	rm -f *.o tcp-server

