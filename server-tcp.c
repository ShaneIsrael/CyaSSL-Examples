/* server-tcp.c
 *
 * Copyright (C) 2006-2014 wolfSSL Inc.
 *
 * This file is part of CyaSSL.
 *
 * CyaSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * CyaSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 * =============================================================================
 *
 * This is a super basic example of what a TCP Server might look like that is
 * not actively using any form of security. 
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

void ProcessDataIn();

const int           DEFAULT_PORT = 11111;
/* Buffer to store data recieved from the client with a 
   max buffer size of 256 */
char                buff[256];

/* Identify and access the sockets */
int                 socketd;
int                 connd;
/* Server and Client socket address structures */
struct sockaddr_in  server_addr;
struct sockaddr_in  client_addr;


int main(int argc, char *argv[])
{
    /* Server and Client socket address structures */
    struct sockaddr_in server_addr, client_addr;

    /* Creates a socket that uses an internet IP address */
    /* Sets the type to be Stream based (TCP)            */
    /* 0 means choose the default protocol.              */
    socketd = socket(AF_INET, SOCK_STREAM, 0);

    /* If the socket descriptor (socketd) is a positive
       value then we know it is valid                    */
    if(socketd < 0)
    {
        printf("ERROR: failed to create the socket\n");
        /* Kill the server with exit status 1 */
        exit(1);
    }

    /* We now need to initialize the server address struct to zero */
    bzero((char *)&server_addr, sizeof(server_addr));

    /* Fill the server's address family */
    server_addr.sin_family              = AF_INET;
    server_addr.sin_addr.s_addr         = INADDR_ANY;
    /* Set the default port */
    server_addr.sin_port                = htons(DEFAULT_PORT);
    
    /* Now we need to attch the server socket to our port. Doing this enforces
       that it does not select a port randomly but instead uses our specified
       port. If we return a value less than 0, then we know it's invalid */
    if(bind(socketd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("ERROR: failed to bind\n");
        exit(1);
    }

    /* Now we will have the server start listening, it will halt at this point
       until it recieves a connection from a client. We will also allow it to 
       hold 5 client connection requests as pending while the server is
       processing another request */
    listen(socketd, 5);
    printf("Waiting for a connection...\n");

    ProcessDataIn();

    /* At this point the program is finished and you should now close all 
       open sockets that we used. */
    close(connd);
    close(socketd);
    return 0;

}
void ProcessDataIn()
{
    int     size = sizeof(client_addr);
    int     exit = 0; /* 0 means false, 1 means true */

    /* The server will wait at this point until a client tries to establish a
       connection. Once a connection is established it returns a new
       'connected socket descriptor' different from the one created earlier */
    connd = accept(socketd, (struct sockaddr *)&client_addr, &size);
    if(connd == -1)
    {
        printf("Failed to accept the connection\n");
    }
    else 
    {
        /* This new descriptor can now be read from or written to just like a 
            normal file descriptor. We can now process and print the data*/
        if(read(connd, buff, sizeof(buff)-1) > 0)
        {
            if(strcmp(buff,"exit")  != 0)
            {
                exit = 1;
                printf("Server shutting down...");
            }
            else
            {
                printf("Data Recieved: %s\n", buff);
                write(connd, buff, sizeof(buff)-1);
            }
            close(connd);
        }
        else
        {
            printf("Failed to recieve data, closing connection.\n");
            exit = 1;
        }
    }

    close(connd);
    if(exit == 0) /* if exit status is still false */
        ProcessDataIn();
}
