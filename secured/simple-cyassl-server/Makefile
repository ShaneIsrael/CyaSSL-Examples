CC=gcc

server: server.c
	$(CC) -o server server.c -lcyassl

.PHONY: clean

clean:
	rm -f *.o server-tls