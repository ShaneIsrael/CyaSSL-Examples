CyaSSL-Examples
===============

a very basic client and server example using the CyaSSL API. Complete code 
explanations of both the unsecured and secured server are available below.

Setup - Linux Systems
---------------------------------
The following instructions will work for both the `secured` and `unsecured` servers. Depending on which you want to setup and run, please navigate to the corresponding `secured` or `unsecured` folder before continueing...

Before you can begin, you will need to have `make` and `gcc` installed on your
system. To do this, open up a terminal and type:

    sudo apt-get install make

Once that finishes install `gcc` by typing into the terminal:

    sudo apt-get install gcc

Great! Now all that is left to do is compile the `server-tcp.c` file, to do this
navigate to the unsecured folder containing `server-tcp.c` and `Makefile` which should
be located in the root of your CyaSSL examples folder that you downloaded.

Now run the `make` command from your terminal by typing:

    make

You should now have an executable file `server`. Running this executeable
will start up the server and begin listening on port `11111`. To execute this
file type:

    ./server

and hit enter.

Congratulations, you now have a basic tcp server listening on port `11111` ready
for a client to connect. However this is an unsecured TCP server.

Setup (Secured with CyaSSL TLS) - Linux Systems
-----------------------------------------------

Please refer to the above instruction, but instead of using `server-tcp.c` you
will instead compile the `server-tcp-tls.c` file. 

After doing that you will then have an executable file named `tcp-server-tls`
that you can run by typing:
    
    ./tcp-server-tls

Congratulations, you now have a basic tcp server secured with a TLS layer
listening on port `11111`.

tcp-server.c Explained
----------------------

tcp-server-tls.c Explained
--------------------------


