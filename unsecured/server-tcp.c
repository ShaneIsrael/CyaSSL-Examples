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
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>

void AcceptAndRead();

const int   DEFAULT_PORT = 11111;

int         sockfd;     /* Identify and access the sockets */
int         connd;      /* Identify and access the clients connection */

/* Server and Client socket address structures */
struct sockaddr_in server_addr, client_addr;

void AcceptAndRead()
{
    int exit = 0; /* 0 = false, 1 = true */

    /* Continuously accept connects while not currently in an active connection or told to quit */
    while (exit == 0)
    {
        /* listen for a new connection, allow 5 pending connections */
        listen(sockfd, 5);
        printf("Waiting for a connection...\n");

        int size = sizeof(client_addr);

        /* Wait until a client connects */
        connd = accept(sockfd, (struct sockaddr *)&client_addr, &size);

        /* If fails to connect, loop back up and wait for a new connection */
        if(connd == -1)
        {
            printf("failed to accept the connection..\n");
        }
        /* If it connects, read in and reply to the client */
        else
        {
            printf("Client connected successfully\n");

            for ( ; ; )
            {
                char buff[256];

                /* Clear the buffer memory for anything  possibly left over */
                bzero(&buff, sizeof(buff));
                
                /* Read the client data into our buff array */
                if(read(connd, buff, sizeof(buff)-1) > 0)
                {
                    /* Print any data the client sends to the console */
                    printf("Client: %s\n", buff);

                    /* Create our reply message */
                    char reply[] = "I hear ya fa shizzle!\n";
                    
                    /* Reply back to the client */
                    write(connd, reply, sizeof(reply)-1);

                    continue;
                }
                /* if the client disconnects break the loop */
                else
                    break;
            }
        }
    }

}

int main(int argc, char *argv[])
{
    /* 
     * Creates a socket that uses an internet IP address,
     * Sets the type to be Stream based (TCP),
     * 0 means choose the default protocol.
     */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* If positive value, the socket is valid */
    if(sockfd < 0)
    {
        printf("ERROR: failed to create the socket\n");
        exit(1);        /* Kill the server with exit status 1 */        
    }

    /* Initialize the server address struct to zero */
    bzero((char *)&server_addr, sizeof(server_addr)); 

    /* Fill the server's address family */
    server_addr.sin_family          = AF_INET;
    server_addr.sin_addr.s_addr     = INADDR_ANY;
    server_addr.sin_port            = htons(DEFAULT_PORT);

    /* Attach the server socket to our port */
    if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("ERROR: failed to bind\n");
        exit(1);
    }

    /* Accept client connections and read from them */
    AcceptAndRead();

    /* Close the open sockets */
    close(connd);
    close(sockfd);
    return 0;

}
