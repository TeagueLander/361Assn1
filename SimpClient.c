/*------------------------------
* SimpClient.c
* Description: HTTP client program
* CSC 361
* Instructor: Kui Wu
* Adapted from client.c by Teague Lander
-------------------------------*/
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

/* define maximal string and reply length, this is just an example.*/
/* MAX_RES_LEN should be defined larger (e.g. 4096) in real testing. */
#define MAX_STR_LEN 120
#define MAX_RES_LEN 120

/* Constants */
#define DEFAULT_PORT 80


/* --------- Main() routine ------------
 * three main task will be excuted:
 * accept the input URI and parse it into fragments for further operation
 * open socket connection with specified sockid ID
 * use the socket id to connect sopecified server
 * don't forget to handle errors
 */

main(int argc, char *argv)
{
	char uri[MAX_STR_LEN];
	char hostname[MAX_STR_LEN];
	char identifier[MAX_STR_LEN];
	int sockid, port;

	printf("Open URI:  ");
	scanf("%s", uri);
	//strcpy(uri,"http://www.google.com/index.html");
	
	parse_URI(uri, hostname, &port, identifier);
	printf("hostname = \"%s\"\n", hostname);
	printf("port = \"%d\"\n", port);
	printf("identifier = \"%s\"\n", identifier);

	sockid = open_connection(hostname, port);
	perform_http(sockid, identifier);
}

/*------ Parse an "uri" into "hostname" and resource "identifier" --------*/

parse_URI(char *uri, char *hostname, int *port, char *identifier)
{
	printf("parsing URI\n"); //REMOVE THIS
	
	//Set default port
	*port = DEFAULT_PORT;
	
	//CHECK IF WE ARE CONNECTING USING PROPER HTTP PROTOCOL
	char host_and_port[MAX_STR_LEN];
	sscanf(uri, "http://%120[^/]/%120[^\n]", host_and_port, identifier);
	sscanf(host_and_port, "%120[^:]:%120d", hostname, port);
	
	printf("returning parsed URI\n"); //REMOVE THIS
	return;
}

/*------------------------------------*
* connect to a HTTP server using hostname and port,
* and get the resource specified by identifier
*--------------------------------------*/
perform_http(int sockid, char *identifier)
{
	/* connect to server and retrieve response */
	char recvBuff[MAX_RES_LEN]; memset(recvBuff, '0', sizeof(recvBuff));
	char *query_get = sprintf(recvBuff, "GET /%s HTTP/1.0\r\n\r\n", identifier);
	int query_len = strlen(&query_get);

	int total_sent_len = 0;
	int sent_len;
	
	int n = write(sockid, query_get, query_len);
	printf("Wrote in\n");
	int o = read(sockid, &recvBuff, MAX_RES_LEN);

	/*while (total_sent_len < query_len) {
		sent_len = send(sockid, query_get+total_sent_len, query_len-total_sent_len, 0);
		if (sent_len == -1) {
			perror("Can't send query");
			exit(1);
		}
		total_sent_len += sent_len;
	}

	int recv_len;
	while((recv_len = recv(sockid, recvBuff, MAX_RES_LEN, 0)) > 0) {
		
	}*/


	printf("%s\n",recvBuff);

	close(sockid);
}

/*---------------------------------------------------------------------------*
 *
 * open_conn() routine. It connects to a remote server on a specified port.
 *
 *---------------------------------------------------------------------------*/

int open_connection(char *hostname, int port)
{
	int sockfd;
	/* generate socket
	 * connect socket to the host address
	 */
	
	//Get IP address if the hostname is a character string
	struct sockaddr_in server_addr; memset(&server_addr, '0', sizeof(server_addr));
	struct hostent *server_ent = NULL; 

	printf("Getting hostname\n");
	if ( (server_ent = gethostbyname(hostname)) == NULL ) {
		printf("Error requesting host ip\n");
		exit(1);
	}
	memcpy(&(server_addr.sin_addr), server_ent->h_addr, server_ent->h_length);
	printf("Copied memory successfully\n");
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	printf("Creating socket\n");
	if ((sockfd = socket(PF_INET,SOCK_STREAM,getprotobyname("tcp")->p_proto)) < 0 ) {
		printf("Error creating socket\n");
		exit(1);
	}
	//WE WILL NEED TO BIND THIS LATER?

	//Convert IP Address and Print it
	char ip4[15];
	inet_ntop(AF_INET, &(server_addr.sin_addr), ip4, 15);
	printf("The ip address of the hostname is %s\n",ip4);
	printf("The port we are connecting to is %d\n",ntohs(server_addr.sin_port));

	printf("Attempting to connect\n");
	if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		printf("Error with connect()\n");
		exit(1);
	}

	printf("Connected, returning socket\n");

	

	return sockfd;
}
