/* ------------
* util.h: used by client.c and server.c 
* ---------------*/

/* write "size" bytes of "ptr" to "sd" */

writen(int sd, char *ptr, int size);

/* read "size bytes from "sd" to "ptr" */

readn(int sd, char *ptr, int size);
