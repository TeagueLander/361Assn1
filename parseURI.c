/* ------------
* parse_URI.c: used by SimpClient.c and SimpServer.c 
* Adapted from code in client.c
* ---------------*/

/*------------------------------------*
* parse the passed in URI and save the hostname,
* port, and identifier.  
*--------------------------------------*/
//Parse the passed in URI and save the hostname, port and identifier
parse_URI(char *uri, char *hostname, int *port, char *identifier, int max_len) {
	
	//In case no port is found
	*port = -1;
	//CHECK IF WE ARE CONNECTING USING PROPER HTTP PROTOCOL
	char host_and_port[max_len];
	char scan_uri_string[max_len];
	snprintf(scan_uri_string, max_len, "http://\%s%d[^/]/\%s%d[^\n]", "%", max_len, "%", max_len);
	sscanf(uri, scan_uri_string, host_and_port, identifier);
	snprintf(scan_uri_string, max_len, "%s%d[^:]:%s%dd", "%", max_len, "%", max_len);
	sscanf(host_and_port, scan_uri_string, hostname, port);
	
	//printf("returning parsed URI\n"); //REMOVE THIS
	return;
}
