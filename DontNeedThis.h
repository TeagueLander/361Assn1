/*------------------------------
* SimpClient.h
* Description: HTTP client program header file
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

main(int argc, char *argv);
parse_URI(char *uri, char *hostname, int *port, char *identifier);
perform_http(int sockid, char *identifier);
int open_connection(char *hostname, int port);