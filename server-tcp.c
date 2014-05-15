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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int                 sockfd, newsockfd, port, clilen;
    char                buffer[256];
    struct sockaddr_in  serv_addr, cli_addr;
    int                 n;

    /* Initialize the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    /* If the socket fails, throw an error and kill the server
     * with exit status 1 */
    if(sockfd < 0)
    {
        perror("ERROR opening the socket");
        exit(1);
    }

    /* Setup the socket */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    port                            = 11111;     /* set the default port */
    serv_addr.sin_family            = AF_INET;
    serv_addr.sin_addr.serv_addr    = INADDR_ANY;
    serv_addr.sin_port              = htons(port);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }

    /* Start listening for clients, the server will enter sleep mode and
     * wait for an incoming connection from the client */
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    /* Accept the connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    /* Just as above, if the accept connection fails, we throw an error and
     * kill the server with exit status 1 */
    if(newsockfd < 0)
    {
        perror("ERROR on accept");
        exit(1);
    }
    
    /* If the connection does not fail and is established then we can now
     * start communicating with the connected client */
    bzero(buffer, 256);
    
    /* read the data sent from the client */
    n = read(newsockfd, buffer, 255);

    
    if(n < 0)
    {
        perror("ERROR reading from the socket");
        exit(1);
    }

    /* print the data from the client to the console */
    printf("Client: %s\n", buffer);

    /* send a response back to the client */
    n = write(newsockfd, "TCP Server checking in!");
    if(n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }
    
    return 0;
}
