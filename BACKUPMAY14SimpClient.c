/*------------------------------
* SimpClient.c
* Description: HTTP client program
* CSC 361
* Instructor: Kui Wu
* Adapted from client.c by Teague Lander
-------------------------------*/
#include <stdio.h>
#include <string.h>

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

    parse_URI(uri, hostname, &port, identifier);
    /*sockid = open_connection(hostname, port);
    perform_http(sockid, identifier);*/
}

/*------ Parse an "uri" into "hostname" and resource "identifier" --------*/

parse_URI(char *uri, char *hostname, int *port, char *identifier)
{
	printf("parsing URI\n"); //REMOVE THIS
	
	//CHECK IF WE ARE CONNECTING USING HTTP PROTOCOL
	char protocol[7];
	strncpy(protocol,uri,7);
	int test_protocol = strcmp(protocol,"http://");
	if (test_protocol != 0)
	{
		printf("This client only supports the http protocol\n");
	}
	else
	{
		printf("HTTP Request.\n");
	}
	//Get the hostname
	int hn_str_pos = strlen(protocol);
	for(int i = 0; i < MAX_STR_LEN-hn_str_pos; i++)
	{
		char next_char = uri[hn_str_pos+i]
		if (next_char != '\0') {
			hostname[i] = next_char;
			break;
		}
		else if (next_char != ':')
		{
			
		}else if (next_char == '/' ) {
			
		}else {
			hostname[i] = next_char;
		}
			
	}
	

	printf("%s\n",hostname);
	printf("hello\n");
	
	
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
  return sockfd;
}
