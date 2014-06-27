/* server-tls.c
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
 * might look like. This server can also resume the session if a client 
 * nadvertantly disconnects. 
 */

/* include the CyaSSL library for our TLS 1.2 security */
#include <cyassl/options.h>
#include <cyassl/test.h>

#define DEFAULT_PORT 11111

int main()
{
    int         ret, socketfd, clientfd;
    char        buff[80];
    CYASSL*     ssl;
    char        reply[] = "I hear ya fa shizzle!";
    CYASSL_CTX* ctx = CyaSSL_CTX_new(CyaSSLv23_server_method());

    if (ctx == NULL)
        err_sys("ctx error");
    if (CyaSSL_CTX_use_certificate_file(ctx, "certs/server-cert.pem",
        SSL_FILETYPE_PEM) != SSL_SUCCESS) {
        err_sys("Error loading server-cert.pem");
        return EXIT_FAILURE;
    }
    if (CyaSSL_CTX_use_PrivateKey_file(ctx, "certs/server-key.pem",
        SSL_FILETYPE_PEM) != SSL_SUCCESS) {
        err_sys("Error loading server-key.pem");
        return EXIT_FAILURE;
    }

    printf("Waiting for a connection...\n");

    tcp_accept(&socketfd, &clientfd, NULL, DEFAULT_PORT, 0, 0);
    if ((ssl = CyaSSL_new(ctx)) == NULL) {
        err_sys("Error create ssl");
    }
    if (CyaSSL_set_fd(ssl, clientfd) != SSL_SUCCESS) {
        err_sys("Error setting socketfd");
    }
    if ((ret = CyaSSL_read(ssl, buff, sizeof(buff)-1)) > 0) {
        buff[ret] = '\0';
        printf("Client: %s\n", buff);
    }
    else
        err_sys("CyaSSL_read error");

    if (CyaSSL_write(ssl, reply, sizeof(reply)-1) < 0) {
        err_sys("CyaSSL_write error");
    }

    CyaSSL_free(ssl);
    CyaSSL_CTX_free(ctx);
    close(socketfd);
    close(clientfd);

    return EXIT_SUCCESS;
}
