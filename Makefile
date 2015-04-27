##############################################################################################
#Author: Kiran Kumar Lekkala
#Date: 13 April 2015
#Description: Makefile to build and compile the necessary files for generating peer executable
##############################################################################################

CFLAGS        = -g -Wall -DDEBUG -03
CC            = gcc
LDFLAGS       = -lm
OBJS          = peer.o debug.o input_buffer.o chunk.o md5.o timer.o current_process.o connection.o
MK_CHUNK_OBJS = make_chunks.o chunk.o md5.o

BINS          = peer make_chunks  
TESTBINS      = test_input

LIBDIR = 

.c.o:
	$(CC) $(TEST) -c $(CFLAGS) $<

all: ${BINS} ${TESTBINS}

run: peer_run

test: peer_test
	./peer_test

timer: timer.c timer.h
	$(CC) timer.c ${INCLUDES} ${CFLAGS} -c -

clean:
	rm -f *.o $(BINS) $(TESTBINS)

peer: $(OBJS)
	$(CC) 

## debugging utility code for this project

debug-text:



all: 
	$(CC) -o -Wall 
