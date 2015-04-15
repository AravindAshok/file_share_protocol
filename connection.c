/***************************************************************************
*Author: Kiran Kumar Lekkala
*Date:  14 April 2015
*Filename: connection.c
*Description: Initializing connections for Downloading/Uploading


***************************************************************************/

#include "connection.h"
#include 
void init_upload_connection(up_connection_t** connection, bt_peer_t* receiver,  
	data_packet_t** pkt_array) {
	(*connection) = (up_connection_t*)malloc(sizeof(up_connection_t));
	(*connection)->receiver = receiver;
	(*connection)->pkt_array = pkt_array;
	(*connection)->l_ack = 0;
	(*connection)->l_available = 1;
	(*connection)->duplicate = 1;
	(*connection)->cwnd = INIT_CWND;
	(*connection)->ssthresh = INIT_SSTHRESH;
}

void init_download_connection(down_connection_t** connection, bt_peer_t* provider, 
	queue_t* chunk, queue_t* get_queue) {
	(*connection) = (down_connection_t*)malloc(sizeof(down_connection_t));
	(*connection)->provider = provider;
	(*connection)->chunks = chunk;
	(*connection)->get_queue = get_queue;
	(*connection)->next_pkt = 1;
	gettimeofday(&((*connection)->last_time), NULL); // initial time
}

void init_down_pool(down_pool_t* pool) {
	int i = 0 ;
	int max = config.max_connection;
	pool->flag = (int*)malloc(sizeof(int)*max);
	pool->connectionection = (down_connection_t**)malloc(sizeof(down_connection_t*)*max);
	int* flags = pool->flag;
	while(i < max) {
		flags[i++] = 0;
	}
}


void init_up_pool(up_pool_t* pool) {
	int i = 0 ;
	int max = config.max_connection;

	pool->flag = (int*)malloc(sizeof(int)*max);
	pool->connection = (up_connection_t**)malloc(sizeof(up_connection_t));
	int* flags = pool->flag;
	while(i < max) {
		flags[i++] = 0;
	}
	//fprintf(stderr, "%f\n", job.cwnd);
}
