#ifndef _PEER_H
#define _PEER_H

#include "md5.h"
#include "parse.h"


typedef struct job_s {
	int num_chunk;
	chunk_t chunks;
} job_t;

typedef struct chunk {
	int id;
	char hash[SHA1_HASH_SIZE*2+1];
	char *data;
	int num_p;
	bt_peer_t *p;
} chunk_t;


#endif /* _PEER_H */
