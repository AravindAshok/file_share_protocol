
#ifndef _CONN_H
#define _CONN_H

#include "queue.h"
#include "chunk.h"
#include "md5.h"
#include "current_process.h"
#include "timer.h"

#define INIT_CWND     8   // initial window size   
#define INIT_SSTHRESH 64  // initial thresh size

typedef struct download_connection {
	bt_peer_t* provider;
	queue_t* chunks;
	queue_t* get_queue;
	struct timeval last_time;
	int next_pkt; // next expected pkt number
}download_connection_t;


typedef struct upload_connection {
	bt_peer_t* receiver;
	data_packet_t** pkt_array;
	int l_ack;
	int l_available;
	int duplicate;
	float cwnd;
	int ssthresh;
}upload_connection_t;

typedef struct download_pool {
	down_conn_t** connection;
	int* flag;
	int num;
}download_pool_t;

typedef struct upload_pool {
	up_conn_t** connection;
	int* flag;
	int num;	
}upload_pool_t;

//Initialization handlers
void init_download_pool(download_pool_t* pool);
void init_upload_pool(upload_pool_t* pool);
void init_download_connection(download_connection_t** conn, peer_t* provider, queue_t* chunk, queue_t* get_queue);
void init_upload_connection(upload_connection_t** conn, bt_peer_t* receiver, data_packet_t** pkt_array);

//Adding the respective connections to the pool
download_connection_t* add_download_pool(download_pool_t* pool, peer_t* provider, queue_t* chunk, queue_t* get_queue);
upload_connection_t* add_upload_pool(upload_pool_t* pool, peer_t* receiver, data_packet_t** pkt_array);

//Deleting pools
void delete_download_pool(download_pool_t* pool, peer_t* peer);
void delete_upload_pool(upload_pool_t* pool, peer_t* peer);

//Get the pointers to get download connection
download_connection_t* get_download_connection(download_pool_t* pool, peer_t* peer);
upload_connection_t* get_update_connection(upload_pool_t* pool, peer_t* peer);
void up_conn_recur_send(up_conn_t* conn, struct sockaddr* to);
void update_download_connection( down_conn_t* conn, bt_peer_t* peer);
void update_upload_connection(upload_connection_t* conn, peer_t* peer, data_packet_t* get_pkt);

#endif

