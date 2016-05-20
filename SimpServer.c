/*------------------------------
* server.c
* Description: HTTP server program
* CSC 361
* Instructor: Kui Wu
-------------------------------*/

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>

#define MAX_STR_LEN 120		 /* maximum string length */
//#define SERVER_PORT_ID 9898	 /* server port number */
#define MAX_BACKLOG 10

void cleanExit();
int socketfd;

/*---------------------main() routine--------------------------*
 * tasks for main
 * generate socket and get socket id,
 * max number of connection is 3 (maximum length the queue of pending connections may grow to)
 * Accept request from client and generate new socket
 * Communicate with client and close new socket after done
 *---------------------------------------------------------------------------*/

main(int argc, char *argv[])
{
	//Declare variables and clear memory where necessary.
	int newsockid; /* return value of the accept() call */
	int my_port;
	char identifier[MAX_STR_LEN];

	struct sockaddr_in my_addr, client_addr;
	memset(&my_addr,'\0', sizeof(my_addr));
	memset(&client_addr, '\0', sizeof(client_addr));
	
	//Check that we have the proper arguments in the command line
	if (argc != 3) {
		printf("Error: Wrong number of arguments\nShould take the form 'SimpServer Port# Identifier'\n");
	}
	my_port = atoi(argv[1]);
	strcpy(identifier,argv[2]);

	//Open socket and bind.
	if ((socketfd = socket(AF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto)) < 0) {
		printf("Error opening socket");
		cleanExit();
	}

	//Setup my_addr
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htons(INADDR_ANY);
	my_addr.sin_port = htons(my_port);

	//
	bind(socketfd, (struct sockaddr*)&my_addr, sizeof(my_addr));
	
	listen(socketfd,MAX_BACKLOG);

	//TEMP LINES
	int comm_fd;  char str[100];
	comm_fd = accept(socketfd, (struct sockaddr*) NULL, NULL);
	printf("Received");

	while(1)
	    {
	 
		bzero( str, 100);
		read(comm_fd,str,100);
		printf("Echoing back - %s",str);
		write(comm_fd, str, strlen(str)+1);
	    }

	cleanExit();

}

/*---------------------------------------------------------------------------*
 *
 * cleans up opened sockets when killed by a signal.
 *
 *---------------------------------------------------------------------------*/

void cleanExit()
{
	close(socketfd);
	exit(0);
}

/*---------------------------------------------------------------------------*
 *
 * Accepts a request from "sockid" and sends a response to "sockid".
 *
 *---------------------------------------------------------------------------*/

perform_http(int sockid)
{

}










