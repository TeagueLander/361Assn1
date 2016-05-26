assn1make: SimpServer.c SimpClient.c util.c
	gcc -w SimpServer.c util.c -o SimpServer
	gcc -w SimpClient.c util.c -o SimpClient
