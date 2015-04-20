#ifndef _JOB_H
#define _JOB_H

#include "md5.h"
#include "queue.h"
#include "chunk.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <assert.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "timer.h"

#define PACKETLEN       1500
#define HEADERLEN       16
#define DATALEN         PACKETLEN - HEADERLEN
#define MAX_CHUNK		74   //Max number of chunk in a single whohas pkt
#define BUF_SIZE                60
#define INDEXGET_SHORTLIST 	0
#define INDEXGET_LONGLIST       1
#define INDEXGET_REGEX		2
#define FILEHASH_VERIFY		3
#define FILEHASH_CHECKALL	4
#define FILEDOWNLOAD		5
#define FILEUPLOAD		6

#define FILEUPLOAD_ALLOW 	7
#define FILEUPLOAD_DENY		8      
#define CHUNK_SIZE      	(1 << 19)  //size of a single chunk in Bytes
#define DEFAULT         	0

#ifndef _PARSE_H_
#define _PARSE_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <stdio.h>

#define FILENAME_LEN 255
#define MAX_PEERS 1024

typedef struct peer {
  short  id;
  struct sockaddr_in addr;
  struct peer *next;
} peer_t;

typedef struct config {
  char  chunk_file[FILENAME_LEN];
  char  has_chunk_file[FILENAME_LEN];
  char  output_file[FILENAME_LEN];
  char  peer_list_file[FILENAME_LEN];
  int   max_conn;
  short identity;
  unsigned short myport;
  struct timeval start_time;
  FILE *cwnd;
  int sock;
  int argc; 
  char **argv;
  peer_t *peers;
}config_t;

typedef struct chunk {
	int id;
	uint8_t hash[MD5_HASH_SIZE];
	char *data;
    	int cur_size;
	int num_p;
	peer_t *pvd; /* providers */
} chunk_t
 
/* chunk_size = 512 * 1024 */
// num_chunk * 512 * 1024 = file_size;max num_chunk = 4095
// largest file supports is 2GB - 512KB


typedef struct file {
    int num_chunk;   
    int num_need;
    int num_living;
    chunk_t* chunks;
    short living_flags;
    char get_chunk_file[FILENAME_LEN];
} file_t;


typedef struct header {
    short magicnum;
    char version;
    char packet_type;
    short header_len;
    short packet_len; 
    u_int seq_num;
    u_int ack_num;
} header_t;  

typedef struct data_packet {
    header_t header;
    char data[DATALEN];
} data_packet_t;

//Initializing jobs
int init_job(char* chunkFile, char* output_file);

/* Finders, Senders and Makers */
int packet_finder(char* buf);
void packet_sender(data_packet_t* pkt, struct sockaddr* to);
queue_t* GET_maker(data_packet_t *pkt,peer_t* peer, queue_t* chunk_queue);
data_packet_t* ACK_maker(int ack, data_packet_t* pkt);
data_packet_t* DENIED_maker();
data_packet_t** DATA_pkt_array_maker(data_packet_t* pkt);
data_packet_t *packet_maker(int type, short pkg_len, u_int seq, u_int ack, char *data);

/* Helper functions */
void store_data(chunk_t* chunk, data_packet_t* pkt);
int chunk_download_done(chunk_t* chunk);
void packet_free(data_packet_t *pkg);
void local2net(data_packet_t* pkt);
void net2local(data_packet_t* pkt);
void clear_job();

/* Printing stuff in the intermediate process. Helpful in debugging !! */
void cat_chunks();
void print_md5_hash();
void print_pkt(data_packet_t* pkt);

#endif

