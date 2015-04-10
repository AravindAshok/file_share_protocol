#####################################################################################
#Author: Kiran Kumar Lekkala
#Date: 13 April 2015
#Description: builds and compiles the necessary files
#####################################################################################

CFLAGS        = -g -Wall -DDEBUG -03
CC            = gcc
LDFLAGS       = 
OBJS          = peer.o debug.o input_buffer.o chunk.o md5.o timer.o current_process.o connection.o
MK_CHUNK_OBJS = make_chunks 
SDIR = 

INCLUDEDIR = 
LIBDIR = 

timer:


peer:

md-5:


current_process:

chunk:

connection:


all: 
	$(CC) -o -Wall 
