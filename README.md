CyaSSL-Examples
===============

a very basic client and server example using the CyaSSL API. Complete code 
explanations of both the unsecured and secured server are available below.

## NOTE
For the most up-to-date version of CyaSSL-Examples please go to: https://github.com/wolfSSL/wolfssl-examples

Getting Started - Linux Systems
---------------------------------
The following instructions will work for both the `secured` and `unsecured` servers. Depending on which you want to setup and run, please navigate to the corresponding `secured` or `unsecured` folder before continueing...

Before you can begin, you will need to have `make` and `gcc` installed on your
system. To do this, open up a terminal and type:

    sudo apt-get install make

Once that finishes install `gcc` by typing into the terminal:

    sudo apt-get install gcc

Great! Next you will need to build and install the CyaSSL library, you only need to configure and install this library if you plan on running the secured versions of the client/server. To do this, download and extract the CyaSSL package from http://wolfssl.com/yaSSL/Products-cyassl.html

Once the CyaSSL package is downloaded and extracted, navigate to the root of the extracted files. Once there type:

	./configure

this will configure CyaSSL and prepare it to be installed on your system. Once that finished type:
	
	make

to compile the CyaSSL library. Now all that's left is to install it. You can do this by typing:
	
	make install

some users may need to have superuser permissions to install, if that's the case then type:

	sudo make install

That's it. You now have CyaSSL installed on your machine and can now compile and run the TLS secured examples.

Server Startup - Linux Systems
------------------------------

Once you have gone through the **Getting Started** section above, all thats left to do is to compile and run the `server-tcp.c` file, to do this
navigate to the unsecured folder containing `server-tcp.c` and `Makefile` which should
be located in the root of your CyaSSL examples folder that you downloaded.

Now run the `make` command from your terminal by typing:

    make

You should now have an executable file `server-tcp`. Running this executeable
will start up the server and begin listening on port `11111`. To execute this
file type:

    ./server-tcp

and hit enter.

Congratulations, you now have a basic tcp server listening on port `11111` ready for a client to connect.


