CSC 361 Assignment 1
Web Client and Web Server
Teague Lander
V00710026
May 27 2016



Compiling the C files
----------------------------

- SimpServer.c and SimpClient.c and other C file compilation is done 
  using the included makefile.
  
- To run the makefile ensure you are in the assignment directory in your
  terminal window and run the simple command "make".
  
- Example of running the code: 
    ~/Assn1$ make

------------------------------------------------------------------------------------


Using SimpClient.c
----------------------------

- SimpClient.c is an HTTP Client which is able to send a simple HTTP 'GET'
  request to a server and print out the returned HTTP header and body.
  
- After the file has been been compiled it can be run from the terminal
  window.  This program takes 1 command line argument which is a Uniform
  Resource Identifier (URI) of the form "protocol://host[:port]/filepath".
  The 'protocol' must be of type 'http' or the URI will not be accepted.
  
- Examples of running the code: 
    ~/Assn1 ./SimpClient http://10.10.1.100:2000/index.html
    ~/Assn1 ./SimpClient http://www.csc.uvic.ca/index.htm
    
------------------------------------------------------------------------------------



