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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  * USA
 * =============================================================================
 *
 * This is a super basic example of what a TCP Server secured with TLS 1.2
 * might look like.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>

/* include the cyassl library for our TLS 1.2 security */
#include <cyassl/ssl.h>

void AcceptAndRead();

const int   DEFAULT_PORT = 11111;

int         socketd;    /* Identify and access the sockets */
int         connd;      /* Identify and access the clients connection */

/* Server and Client socket address structures */
struct sockaddr_in server_addr, client_addr;

/* Create a ctx pointer for our ssl */
CYASSL_CTX* ctx;

void AcceptAndRead()
{
    int exit_status = 0; /* 0 = false, 1 = true */

    /* Continuously accept connects while not currently in an active connection
       or told to quit */
    while (exit_status == 0)
    {
        /* listen for a new connection, allow 5 pending connections */
        listen(socketd, 5);

        printf("Waiting for a connection...\n");

        int     size = sizeof(client_addr);
        CYASSL* ssl;

        /* Wait until a client connects */
        connd = accept(socketd, (struct sockaddr *)&client_addr, &size);

        /* If fails to connect, loop back up and wait for a new connection */
        if(connd == -1)
        {
            printf("failed to accept the connection..\n");
        }
        /* If it connects, read in and reply to the client */
        else
        {
            printf("Client connected successfully\n");

            if( (ssl = CyaSSL_new(ctx)) == NULL)
            {
                fprintf(stderr, "CyaSSL_new error.\n");
                exit(EXIT_FAILURE);
            }

            /* direct our ssl to our clients connection */
            CyaSSL_set_fd(ssl, connd);

            for ( ; ; )
            {
                char    buff[256];

                /* Clear the buffer memory for anything  possibly left over */
                bzero(&buff, sizeof(buff));

                /* Read the client data into our buff array */
                if(CyaSSL_read(ssl, buff, sizeof(buff)-1) > 0)
                {
                    /* Print any data the client sends to the console */
                    printf("Client: %s\n", buff);

                    /* Create our reply message */
                    char reply[] = "I hear ya fa shizzle!\n";
                    
                    /* Reply back to the client */
                    CyaSSL_write(ssl, reply, sizeof(reply)-1);

                    continue;
                }
                /* if the client disconnects break the loop */
                else
                    break;
            }
        }
        CyaSSL_set_fd(ssl, connd);  
        CyaSSL_free(ssl);           /* Free the CYASSL object */
        close(connd);               /* close the connected socket */
    }
}

int main(int argc, char *argv[])
{
    /* initialize CyaSSL */
    CyaSSL_Init();

    /* create and initialize CYASSL_CTX structure */
    if((ctx = CyaSSL_CTX_new(CyaTLSv1_2_server_method())) == NULL)
    {
        fprintf(stderr, "CyaSSL_CTX_new error.\n");
        exit(EXIT_FAILURE);
    }

    /* Load server certificate into CYASSL_CTX */
    if(CyaSSL_CTX_use_certificate_file(ctx, "certs/server-cert.pem", 
                SSL_FILETYPE_PEM) != SSL_SUCCESS)
    {
        fprintf(stderr, "Error loading certs/server-cert.pem, please check"
                "the file.\n");
        exit(EXIT_FAILURE);
    }

    /* Load server key into CYASSL_CTX */
    if(CyaSSL_CTX_use_PrivateKey_file(ctx, "certs/server-key.pem", 
                SSL_FILETYPE_PEM) != SSL_SUCCESS)
    {
        fprintf(stderr, "Error loading certs/server-key.pem, please check"
                "the file.\n");
        exit(EXIT_FAILURE);
    }

    /* 
     * Creates a socket that uses an internet IP address,
     * Sets the type to be Stream based (TCP),
     * 0 means choose the default protocol.
     */
    socketd = socket(AF_INET, SOCK_STREAM, 0);

    /* If positive value, the socket is valid */
    if(socketd < 0)
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
    if(bind(socketd, (struct sockaddr *)&server_addr, sizeof(server_addr))
        < 0)
    {
        printf("ERROR: failed to bind\n");
        exit(1);
    }

    /* Accept client connections and read from them */
    AcceptAndRead();

    CyaSSL_CTX_free(ctx);   /* Free CYASSL_CTX */
    CyaSSL_Cleanup();       /* Free CyaSSL */
    exit(EXIT_SUCCESS);
}
