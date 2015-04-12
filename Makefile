#####################################################################################
#Author: Kiran Kumar Lekkala
#Date: 13 April 2015
#Description: builds and compiles the necessary files
#####################################################################################

CFLAGS        = -g -Wall -DDEBUG -03
CC            = gcc
LDFLAGS       = 
OBJS          = peer.o debug.o input_buffer.o chunk.o md5.o timer.o current_process.o connection.o
MK_CHUNK_OBJS = make_chunks.o chunk.o md5.o

BINS          = peer make_chunks
TESTBINS      = test_input.o

INCLUDEDIR = 
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
	$(CC) $(c)

md-5:


current_process:


all: 
	$(CC) -o -Wall 
