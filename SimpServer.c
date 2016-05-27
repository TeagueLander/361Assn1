/*------------------------------
* SimpServer.c
* Description: HTTP server program
* CSC 361
* Instructor: Kui Wu
* Adapted from server.c by Teague Lander
-------------------------------*/

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/utsname.h>
#include <time.h>
#include "util.h"

#define MAX_REC_LEN 120		 /* maximum receive message length */
#define MAX_SEND_LEN 4096	/* maximum send message length */
#define MAX_BACKLOG 10

void cleanExit();

int socketfd; //Make global so it can be cleaned up by cleanExit();
char directory[MAX_REC_LEN]; //The directory of the files we will host

/*---------------------main() routine--------------------------*
 * tasks for main
 * generate socket and get socket id,
 * Accept request from client and generate new socket
 * Communicate with client and close new socket after done
 *---------------------------------------------------------------------------*/
main(int argc, char *argv[]) {
	//Declare variables and clear memory where necessary.
	int newsockid; /* return value of the accept() call */
	int my_port;

	struct sockaddr_in my_addr, client_addr;
	memset(&my_addr,'\0', sizeof(my_addr));
	memset(&client_addr, '\0', sizeof(client_addr));
	
	//Check that we have the proper arguments in the command line
	if (argc != 3) {
		printf("Error: Wrong number of arguments\nShould take the form 'SimpServer Port# Directory'\n");
	}
	my_port = atoi(argv[1]);
	strcpy(directory,argv[2]);

	//Open socket and bind.
	if ((socketfd = socket(AF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto)) < 0) {
		printf("Error opening socket\n");
		cleanExit();
	}

	//Setup my_addr
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = htons(INADDR_ANY);
	my_addr.sin_port = htons(my_port);

	//Bind the socket to our IP
	if ((bind(socketfd, (struct sockaddr*)&my_addr, sizeof(my_addr))) < 0) {
		printf("Error binding socket to port\n");
		cleanExit();
	}
	
	if ((listen(socketfd,MAX_BACKLOG)) < 0 ) {
		printf("Error listening on port %d",my_port);
	}

	//Wait until there is a connection request to perform HTTP
	while (1) {
		int comm_fd;	
		if ((comm_fd = accept(socketfd, (struct sockaddr*) NULL, NULL)) < 0) {
			printf("Error accepting socket\n");
		}else {
		 perform_http(comm_fd);
		}
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
	
	//Read from the socket
	if ((readn(sockid,str_rec_buff,MAX_REC_LEN)) < 0){
		printf("Error reading TCP stream from client\n");
		close(sockid);
		cleanExit();
	}

	//Parse received string;
	char method[MAX_REC_LEN];
	char request_URI[MAX_REC_LEN];
	char http_version[MAX_REC_LEN];
	sscanf(str_rec_buff, "%s %s %s\r\n", method, request_URI, http_version);
	
	//Parse the URI for the requested file
	char hostname[MAX_REC_LEN];
	char identifier[MAX_REC_LEN];
	int port;
	parse_URI(request_URI, hostname, &port, identifier, MAX_REC_LEN);
	
	//Ensure the GET method is the one being asked for
	if ((strcmp(method,"GET") != 0) || (strcmp(http_version,"HTTP/1.0")) ){
		writen(sockid, "HTTP/1.0 501 Not Implemented\r\n\r\n", MAX_SEND_LEN);
		return;
	}

	//Get System Information
	struct utsname unameData;
	uname(&unameData);
	//Get System Time
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	
	//Setup the strings that gives us the file location and the system info
	char file_location[2*MAX_REC_LEN];
	snprintf(file_location, MAX_REC_LEN*2, "%s/%s",directory,identifier);
	char server_info[MAX_SEND_LEN];
	snprintf(server_info, MAX_REC_LEN, "Date: %sServer: %s %s %s\r\n", asctime(timeinfo), unameData.sysname, unameData.nodename, unameData.release);

	//HTTP Header is built and sent here if file is found
	if ((file_to_send = fopen(file_location,"r")) != NULL) {
		strcpy(str_send_buff, "HTTP/1.0 200 OK\r\n");
		strcat(str_send_buff, server_info);
		strcat(str_send_buff, "\r\n");
		int http_len = strlen(str_send_buff);
		fread(str_send_buff+http_len, 1, MAX_SEND_LEN-http_len, (FILE*)file_to_send);
		writen(sockid, str_send_buff, MAX_SEND_LEN);
		fclose(file_to_send);
	}else {
		strcpy(str_send_buff, "HTTP/1.0 404 Not Found");
		strcat(str_send_buff, "\r\n\r\n");
		writen(sockid, str_send_buff, MAX_SEND_LEN);
		return;
	}

}











