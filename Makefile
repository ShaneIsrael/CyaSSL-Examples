CC=gcc
CFLAGS=-Wall -I ../include
DEPS = ../include/unp.h
OBJ = tcp-server.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tcp-server: ../lib/*.c server-tcp.c
	$(CC) -o tcp-server ../lib/*.c server-tcp.c -I ../include -lm -lcyassl

.PHONY: clean

clean:
	rm -f *.o tcp-server

