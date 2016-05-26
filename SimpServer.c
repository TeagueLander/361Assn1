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

#define MAX_REC_LEN 120		 /* maximum receive message length */
#define MAX_SEND_LEN 120	/* maximum send message length */
//#define SERVER_PORT_ID 9898	 /* server port number */  We will take this as a cl argument
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
	char identifier[MAX_REC_LEN];

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
		printf("Error opening socket\n");
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
	while (1) {
		printf("Listening for new connection\n");
		int comm_fd;	
		if ((comm_fd = accept(socketfd, (struct sockaddr*) NULL, NULL)) < 0) {
			printf("Error accepting socket\n");
		}	
		printf("Received\n");
		perform_http(comm_fd);
		close(comm_fd);
	}

	cleanExit();

}

/*---------------------------------------------------------------------------*
 *
 * cleans up opened sockets when killed by a signal.
 *
 *---------------------------------------------------------------------------*/

void cleanExit() {
	close(socketfd);
	exit(0);
}

/*---------------------------------------------------------------------------*
 *
 * Accepts a request from "sockid" and sends a response to "sockid".
 *
 *---------------------------------------------------------------------------*/

perform_http(int sockid) {

	char str_rec_buff[MAX_REC_LEN]; bzero( str_rec_buff, MAX_REC_LEN);
	char str_send_buff[MAX_SEND_LEN]; bzero( str_send_buff, MAX_SEND_LEN);
	FILE *file_to_send;
	
	read(sockid,str_rec_buff,100);
	printf("Echoing back - %s",str_rec_buff);


	if ((file_to_send = fopen("web/index.html","r")) != NULL) {
		fread(str_send_buff, 1, MAX_SEND_LEN, (FILE*)file_to_send);
		write(sockid, str_send_buff, MAX_SEND_LEN);
		fclose(file_to_send);
	}else {
		printf("File does not exist or could not be opened\n");
	}


}











