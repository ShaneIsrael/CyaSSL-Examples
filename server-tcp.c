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

#define MAX_SIZE = 256
#define DEFAULT_PORT = 11111

int main(int argc, char *argv[])
{
    /* Identify and access the sockets */
    int socketd, connd;

    /* Server and Client socket address structures */
    struct sockaddr_in server_addr, client_addr;

    /* Buffer to store data recieved from the client */
    char buff[MAX_SIZE];

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
    server_addr.sin_port                = DEFAULT_PORT;
    
    /* Now we need to attch the server socket to our port. Doing this enforces
       that it does not select a port randomly but instead uses our specified
       port. If we return a value less than 0, then we know it's invalid */
    if(bind(socketd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        printf("ERROR: failed to bind\n");

    /* Now we will have the server start listening, it will halt at this point
       until it recieves a connection from a client. We will also allow it to 
       hold 5 client connection requests as pending while the server is
       processing another request */
    listen(socketd, 5);
    printf("Waitinf for a connection...\n");
    int size = sizeof(client_addr);
    
    /* The server will wait at this point until a client tries to establish a
       connection. Once a connection is established it returns a new
       'connected socket descriptor' different from the one created earlier */
    conn_desc = accept(socketd, (struct sockaddr *)&client_addr, &size);
    if(conn_desc == -1)
        printf("Failed to accept the connection\n");
    else
        printf("Connected Successfully!");

    /* This new descriptor can now be read from or written to just like a 
       normal file descriptor */
    if(read(conn_desc, buff, sizeof(buff)-1) > 0)
        printf("Data Recieved: %s", buff);
    else
        printf("Failed to recieve data\n");

    /* At this point the program is finished and you should now close all 
       open sockets that we used. */
    close(conn_desc);
    close(socketd);
    return 0;

}
