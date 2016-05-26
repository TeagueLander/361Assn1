/*------------------------------
* server.h
* Description: HTTP server program
* CSC 361
* Instructor: Kui Wu
* Adapted from server.c by Teague Lander
-------------------------------*/

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>

#define MAX_REC_LEN 120		 /* maximum receive message length */
#define MAX_SEND_LEN 4096	/* maximum send message length */
#define MAX_BACKLOG 10

void cleanExit();
int socketfd;
char directory[MAX_REC_LEN];

main(int argc, char *argv[]);

void cleanExit();

perform_http(int sockid);
