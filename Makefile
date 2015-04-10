#####################################################################################
#Author: Kiran Kumar Lekkala
#Date: 13 April 2015
#Description: builds and compiles the necessary files
#####################################################################################

CC := gcc

SDIR = 

INCLUDEDIR = 
LIBDIR = 

timer:


peer:

md-5:


current_process:

chunk:

connection:


spiffy:
	$(CC) -c -Wall spiffy.c -o spiffy.o
	$(CC) test_server.c spiffy.o -o server
	$(CC) test_client.c spiffy.o -o client
	rm *.o

all: 
	$(CC) -o -Wall 
