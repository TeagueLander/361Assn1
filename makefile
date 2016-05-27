assn1make: SimpServer.c SimpClient.c parseURI.c util.c
	gcc -w SimpServer.c parseURI.c util.c -o SimpServer
	gcc -w SimpClient.c parseURI.c util.c -o SimpClient
