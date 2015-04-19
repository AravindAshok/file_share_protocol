/***************************************************************************
*Author: Kiran Kumar Lekkala
*Date:  14 April 2015
*Filename: connection.c
*Description: Initializing connections and configuring pools for 
Downloading/Uploading connections.

***************************************************************************/

#include "connection.h"
#include "current_process.h"

void init_upload_connection(up_connection_t** conn, peer_t* receiver, data_packet_t** pkt_array) {
	(*conn) = (up_connection_t*)malloc(sizeof(up_connection_t));
	(*conn)->receiver = receiver;
	(*conn)->pkt_array = pkt_array;
	(*conn)->l_ack = 0;
	(*conn)->l_available = 1;
	(*conn)->duplicate = 1;
	(*conn)->cwnd = INIT_CWND;
	(*conn)->ssthresh = INIT_SSTHRESH;
}

void init_download_connection(download_connection_t** connection, peer_t* provider, queue_t* chunk, queue_t* get_queue) {
	(*conn) = (download_connection_t*)malloc(sizeof(download_connection_t));
	(*conn)->provider = provider;
	(*conn)->chunks = chunk;
	(*conn)->get_queue = get_queue;
	(*conn)->next_pkt = 1;
	gettimeofday(&((*conn)->last_time), NULL); // initial timestamp
}

void init_download_pool(download_pool_t* pool) {
	int i = 0 ;
	int max = config.max_connection;
	pool->flag = (int*)malloc(sizeof(int)*max);
	pool->connection = (download_connection_t**)malloc(sizeof(download_connection_t*)*max);
	int* flags = pool->flag;
	while(i < max) {
		flags[i++] = 0;
	}
}


void init_upload_pool(up_pool_t* pool) {
	int i = 0 ;
	int max = config.max_connection;

	pool->flag = (int*)malloc(sizeof(int)*max);
	pool->connection = (upload_connection_t**)malloc(sizeof(upload_connection_t));
	int* flags = pool->flag;
	while(i < max) {
		flags[i++] = 0;
	}
}

void delete_upload_pool(upload_pool_t* pool,peer_t* peer) {
	int i = 0;
	up_connection_t** conns = pool->connection;
	while( i < config.max_conn ) {
		if( pool->flag[i] == 1 && conns[i]->receiver->id == peer->id) {
			conns[i]->receiver = NULL;
			free(conns[i]->pkt_array);
			conns[i]->pkt_array = NULL;
			conns[i]->l_ack = 0;
			conns[i]->l_available = 1;
			conns[i]->duplicate = 0;
			conns[i]->cwnd = INIT_CWND;
			conns[i]->ssthresh = INIT_SSTHRESH;
			pool->flag[i] = 0;
			(pool->num)--;
			break;
		}
		i++;
	}
}

void delete_download_pool(download_pool_t* pool,peer_t* peer) {
	int i = 0;
	download_connection_t** conns = pool->connection;
	while( i < config.max_conn ) {
		if(pool->flag[i] == 1 && conns[i]->provider->id == peer->id) {
			if(dequeue(conns[i]->get_queue) != NULL ) {
				// This should never happen!
				fprintf(stderr, "downloading connection pool error!\n");
			}
			conns[i]->provider = NULL;
			conns[i]->chunks = NULL;
			conns[i]->get_queue = NULL;
			pool->flag[i] = 0;
			pool->num--;
			break;
		}
		i++;
	}
}

download_connection_t* get_download_connection(download_pool_t* pool, peer_t* peer) {
	int i = 0; 
	download_connection_t** conns = pool->connection;
	while( i<= config.max_conn) {
		if( pool->flag[i] == 1 && conns[i]->provider->id == peer->id) {
			return conns[i];	
		}
		i++;
	}
	return NULL;
}


upload_connection_t* get_upload_connection(upload_pool_t* pool, peer_t* peer) {
	int i = 0; 
	up_connection_t** conns = pool->connection;
	while( i<= config.max_conn) {
		if( pool->flag[i] == 1 && conns[i]->receiver->id == peer->id) {
			return conns[i];	
		}
		i++;
	}
	return NULL;
}


void update_upload_connection(up_connection_t* conn, peer_t* peer, data_packet_t* get_pkt) {
	// construct new data pkt array
	data_packet_t** data_pkt_array = DATA_pkt_array_maker(get_pkt);
	conn->receiver = peer;
	conn->pkt_array = data_pkt_array;
	conn->l_ack = 0;
	conn->l_available = 1;
	conn->duplicate = 1;
	conn->cwnd = INIT_CWND;
	conn->ssthresh = INIT_SSTHRESH;
}

void update_download_connection( download_connection_t* conn, peer_t* peer) {
	// removed finished GET request
	conn->next_pkt = 1;
}

