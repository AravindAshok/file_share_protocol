/***************************************************************************
 *Author:  Kiran Kumar Lekkala
 *Date:  15 April 2015
 *Filename: peer.c
 *Description: main program for file share protocol


 ***************************************************************************/

#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "queue.h"
#include "current_process.h"
#include "chunk.h"
#include "connection.h"

/* Function Prototypes */
void peer_run();
void freeJob(job_t* job);
void init_hasChunk(char* has_chunk_file);
void check_living();

/* Global variables */
job_t job;
config_t config;
queue_t* hasChunk;
upload_pool_t upload_pool;
download_pool_t download_pool;

uint32_t some_long = 10;
uint32_t some_short = 20;

int main(int argc, char **argv) {

    init(&config, argc, argv);
    printf("peer main beginning\n");   /* Debug info */

#ifdef TESTING
    config.identity = 1; // your group number here
    strcpy(config.chunk_file, "chunkfile");
    strcpy(config.has_chunk_file, "haschunks");
#endif
    
    printf("Peer initialized.... \nYou are good to go now !!!\n");
    peer_run(&config);
    return 0;
}

void process_user_input(){






}


void process_tcp(int sock) {
    int packet_type = -1;
    struct sockaddr_in from;
    socklen_t fromlen;
    char buf[PACKETLEN];
    upload_conn_t* upload_conn;
    download_conn_t* download_conn;
    void *ptr;
    int res;
    int finished = 0;
    data_packet_t* pkt;


    fromlen = sizeof(from);
    while ((res = TCP_recvfrom(sock, buf, PACKETLEN, 0, (struct sockaddr *) &from, &fromlen)) != -1) {
        // change to local format
        net2local((data_packet_t*)buf);
        // call packet_parser
        packet_type = packet_parser(buf);
        //get peer
        peer_t* peer = peer_get(&config,(struct sockaddr *)&from);
        //print_pkt((data_packet_t*)buf);
        // switch on packet type
        switch(packet_type) {

            case INDEXGET_SHORTLIST: {
                                         upload_conn = get_upload_conn(&upload_pool,peer);
                                         if(upload_conn == NULL) {
                                             // new connetion
                                             if(upload_pool.num >= 10) {
                                                 // sending pool full,construct denied pkt
                                                 data_packet_t* denied_pkt = DENIED_maker();
                                                 // send denied pkt
                                                 packet_sender(denied_pkt,(struct sockaddr*) &from);
                                             } else {
                                                 // get data pkt array
                                                 data_packet_t** data_pkt_array = DATA_pkt_array_maker((data_packet_t*)buf);
                                                 // create a new uploading connection
                                                 upload_conn = en_upload_pool(&upload_pool,peer,data_pkt_array);
                                                 if( upload_conn != NULL) {
                                                     // send first data
                                                     upload_conn_recur_send(upload_conn, (struct sockaddr*) &from);
                                                 }
                                             }
                                         } else {
                                             fprintf(stderr, "update!\n");
                                         }
                                         break;
                                     }

            case INDEXGET_LONGLIST: {
                                        upload_conn = get_upload_conn(&upload_pool,peer);
                                        if(upload_conn == NULL) {
                                            // new connection
                                            if(upload_pool.num >= 10) {
                                                // sending pool full,construct denied pkt
                                                data_packet_t* denied_pkt = DENIED_maker();
                                                // send denied pkt
                                                packet_sender(denied_pkt,(struct sockaddr*) &from);
                                            } else {
                                                // get data pkt array
                                                data_packet_t** data_pkt_array = DATA_pkt_array_maker((data_packet_t*)buf);
                                                // create a new uploading connection
                                                upload_conn = en_upload_pool(&upload_pool,peer,data_pkt_array);
                                                if( upload_conn != NULL) {
                                                    // send first data
                                                    upload_conn_recur_send(upload_conn, (struct sockaddr*) &from);
                                                }
                                            }
                                        } else {
                                            fprintf(stderr, "update!\n");
                                        }
                                        break;
                                    }

            case INDEXGET_REGEX: {
                                     upload_conn = get_upload_conn(&upload_pool,peer);
                                     if(upload_conn == NULL) {
                                         // new connetion
                                         if(upload_pool.num >= 10) {
                                             // sending pool full,construct denied pkt
                                             data_packet_t* denied_pkt = DENIED_maker();
                                             // send denied pkt
                                             packet_sender(denied_pkt,(struct sockaddr*) &from);
                                         } else {
                                             // get data pkt array
                                             data_packet_t** data_pkt_array = DATA_pkt_array_maker((data_packet_t*)buf);
                                             // create a new uploading connection
                                             upload_conn = en_upload_pool(&upload_pool,peer,data_pkt_array);
                                             if( upload_conn != NULL) {
                                                 // send first data
                                                 upload_conn_recur_send(upload_conn, (struct sockaddr*) &from);
                                             }
                                         }
                                     } else {
                                         fprintf(stderr, "update!\n");
                                     }
                                     break;
                                 }
            case FILEHASH_VERIFY_: {
                                       if(DEFAULT)
                                           fprintf();
                                       upload_conn = get_upload_connection(&upload_pool,peer);
                                       if(upload_connection == NULL){
                                           if(upload_pool < 10){
                                               data_packet_t* verify_pkt = VERIFY_maker();
                                               upload_connection = create_upload_pool(&upload_pool, peer, )// ************************* */;
                                               if(upload_connection != NULL)
                                                   packet_sender
                                                       // send verify pkt
                                                       packet_sender(verify_pkt, (struct sockaddr*) &from);
                                           }

                                           else{
                                               // sending pool full,construct denied pkt
                                               data_packet_t* denied_pkt = DENIED_maker();
                                               // send denied pkt
                                               packet_sender(denied_pkt,(struct sockaddr*) &from);

                                           }
                                       }

                                   }


            case FILEHASH_CHECKALL: {
                                        if(DEFAULT)
                                            fprintf();
                                        upload_conn = get_upload_connection(&upload_pool,peer);
                                        if(upload_connection == NULL){
                                            if(upload_pool < 10){
                                                data_packet_t* verify_pkt = VERIFY_maker();
                                                upload_connection = create_upload_pool(&upload_pool, peer, )// ************************* */;
                                                if(upload_connection != NULL)
                                                    packet_sender
                                                        // send verify pkt
                                                        packet_sender(verify_pkt, (struct sockaddr*) &from);
                                            }

                                            else{
                                                // sending pool full,construct denied pkt
                                                data_packet_t* denied_pkt = DENIED_maker();
                                                // send denied pkt
                                                packet_sender(denied_pkt,(struct sockaddr*) &from);

                                            }
                                        }

                                    }

            case FILEDOWNLOAD: {
                                   upload_conn = get_upload_conn(&upload_pool,peer);
                                   if(upload_conn == NULL) {
                                       // new connetion
                                       if(upload_pool.num >= 10) {
                                           // sending pool full,construct denied pkt
                                           data_packet_t* denied_pkt = DENIED_maker();
                                           // send denied pkt
                                           packet_sender(denied_pkt,(struct sockaddr*) &from);
                                       } else {
                                           // get data pkt array
                                           data_packet_t** data_pkt_array = DATA_pkt_array_maker((data_packet_t*)buf);
                                           // create a new uploading connection
                                           upload_conn = en_upload_pool(&upload_pool,peer,data_pkt_array);
                                           if( upload_conn != NULL) {
                                               // send first data
                                               upload_conn_recur_send(upload_conn, (struct sockaddr*) &from);
                                           }
                                       }
                                   } else {
                                       fprintf(stderr, "update!\n");
                                   }
                                   break;
                               }


            case FILEUPLOAD: {
                                 if(DEFAULT)
                                     fprintf(stderr, "receive data pkt,seq%d\n",
                                             ((data_packet_t*)buf)->header.seq_num);
                                 download_conn = get_download_conn(&download_pool,peer);
                                 // check ack number
                                 if(download_conn->next_pkt == ((data_packet_t*)buf)->header.seq_num) {
                                     // store data
                                     store_data((chunk_t*)(download_conn->chunks->head->data),
                                             (data_packet_t*)buf);
                                     // Construct ACK pkt
                                     data_packet_t* ack_pkt = ACK_maker(++(download_conn->next_pkt),
                                             (data_packet_t*)buf);
                                     // send ACK pkt
                                     packet_sender(ack_pkt,(struct sockaddr *) &from);
                                     // check if current chunk downloading finished

                                     if (1 == (finished = is_chunk_finished((chunk_t*)(download_conn->chunks->head->data)))) {


                                         fprintf(stderr, "finished!\n");
                                         job.num_need--;
                                         ptr = dequeue(download_conn->get_queue); // to do free
                                         //free(ptr);
                                         dequeue(download_conn->chunks); // to do free


                                         if(download_conn->get_queue->head != NULL) {
                                             fprintf(stderr, "send next get!\n");
                                             // update download_conn
                                             update_download_conn(download_conn,peer);
                                             // send out next GET packets
                                             packet_sender((data_packet_t*)download_conn->get_queue->head->data,(struct sockaddr*) &from);
                                         } else if( download_conn->get_queue->head == NULL) {
                                             // remove this download connection
                                             fprintf(stderr, "remove current download connection\n");
                                             de_download_pool(&download_pool,peer);
                                         }
                                         // check current downloading connection finished
                                         if(job.num_need == 0) {
                                             fprintf(stderr, "GOT %s\n",job.get_chunk_file);
                                             // all finished， cat all chunks into one file
                                             cat_chunks();
                                             // job finished
                                             if(is_job_finished()) {
                                                 clear_job();
                                             }
                                         }

                                     } else if (-1 == finished) {
                                         // hash wrong
                                         fprintf(stderr, "Hashed wrong, resend last get!\n");
                                         update_download_conn(download_conn,peer);
                                         packet_sender((data_packet_t*)download_conn->get_queue->head->data,(struct sockaddr*) &from);
                                     }

                                 } else {
                                     // wrong data packet!!!
                                     if(DEFAULT)
                                         fprintf(stderr, "got invalid data pkt\n");
                                     // Construct ACK pkt
                                     data_packet_t* ack_pkt = ACK_maker(download_conn->next_pkt,
                                             (data_packet_t*)buf);
                                     // send ACK pkt
                                     packet_sender(ack_pkt,(struct sockaddr *) &from);
                                 }
                                 gettimeofday(&(download_conn->last_time), NULL);  // update last alive time
                                 break;
                             }


            case FILE_UPLOAD_ALLOW: {
                                        if(DEFAULT)
                                            fprintf(stderr, "recieved ALLOW response. ALLOW response number is %d\n", ((data_packet_t*)buf)->header.ack_num);
                                        // continue send data pkt if not finished
                                        upload_conn = get_upload_conn(&upload_pool,peer);
                                        // check ACK
                                        if( ((data_packet_t*)buf)->header.ack_num == 512) {
                                            // downloading finished
                                            delete_upload_pool(&upload_pool,peer);
                                        }

                                        else if (upload_conn->l_ack+1 <= ((data_packet_t*)buf)->header.ack_num) {
                                            // valid ack
                                            upload_conn->duplicate = 1;
                                            upload_conn->l_ack = ((data_packet_t*)buf)->header.ack_num;
                                            if(DEFAULT)
                                                fprintf(stderr, "%dACKed!\n",upload_conn->l_ack);
                                            if( upload_conn->cwnd < upload_conn->ssthresh+0.0) {
                                                // slow start state
                                                upload_conn->cwnd += 1;
                                                print_cwnd(upload_conn);
                                                upload_conn_recur_send(upload_conn,(struct sockaddr*) &from);
                                            } else {
                                                // congestion avoidence state
                                                int old_cwnd = upload_conn->cwnd;
                                                upload_conn->cwnd += 1/upload_conn->cwnd;

                                                if((int)old_cwnd + 1 == (int)upload_conn->cwnd )
                                                    print_cwnd(upload_conn);

                                                upload_conn_recur_send(upload_conn,(struct sockaddr*) &from);
                                            }
                                        } else if( upload_conn->l_ack == ((data_packet_t*)buf)->header.ack_num) {
                                            // duplicate ack
                                            if (DEFAULT)
                                                fprintf(stderr, "got duplicate!:%d\n",upload_conn->duplicate+1 );
                                            upload_conn->duplicate++;
                                            if(upload_conn->duplicate >= 3) {
                                                upload_conn->ssthresh = upload_conn->cwnd/2>2?upload_conn->cwnd/2:2;
                                                int old_cwnd = upload_conn->cwnd;
                                                upload_conn->cwnd = 1;
                                                upload_conn->l_available = upload_conn->l_ack+1;
                                                upload_conn_recur_send(upload_conn,(struct sockaddr*) &from);
                                                upload_conn->duplicate = 0;
                                                if ((int)old_cwnd != upload_conn->cwnd)
                                                    print_cwnd(upload_conn);
                                            }
                                        }
                                        break;
                                    }

            case FILE_UPLOAD_DENY: {
                                       break;
                                   }

            default: {
                         // Label the packet as an invalid packet
                         fprintf(stderr,"Invalid Packet:%d!!!\n", packet_type);
                         break;
                     }
        }

        check_living();
    }
}

void process_get(char *chunkfile, char *outputfile) {
    printf("PROCESS GET SKELETON CODE CALLED.  Fill me in!  (%s, %s)\n", chunkfile, outputfile);
    /* Create a Job */
    init_job(chunkfile,outputfile);

    /* call whohasmaker */
    queue_t* whoHasQueue = WhoHas_maker();
    /* send out all whohas packets */
    data_packet_t* cur_pkt = NULL;
    while((cur_pkt = (data_packet_t *)dequeue(whoHasQueue)) != NULL) {
        //fprintf(stderr, "here\n");
        send_WhoHas(cur_pkt);
        packet_free(cur_pkt);
    }

    /* free current job content */
    //freeJob(job);

}
/******* Note: This is the main underlying sockets part of this protocol *********/

void peer_run() {
    int sock;
    struct sockaddr_in myaddr;
    fd_set readfds;
    struct user_iobuf *userbuf;
    int yes = 1;
    struct timeval tv;

/** Small note about the IPPROTO_IP macro. This constant has the value 0. It's actually an automatic choice depending on socket type and family.
If you use it, and if the socket type is SOCK_STREAM and the family is AF_INET, then the protocol will automatically be TCP (exactly the same as if you'd used IPPROTO_TCP). Buf if you use IPPROTO_IP together with AF_INET and SOCK_RAW, you will have an error, because the kernel cannot choose a protocol automatically in this case.*****/

    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) == -1) {
        perror("peer could not create socket");
        exit(-1);
    }

    // Removing insane errors like "address already in use"
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    fcntl(sock, F_SETFL, O_NONBLOCK);
    bzero(&myaddr, sizeof(myaddr));
    myaddr.sin_family = AF_INET;

    //myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_aton("127.0.0.1", (struct in_addr *)&myaddr.sin_addr.s_addr);
    myaddr.sin_port = htons(config.myport);

    if (bind(sock, (struct sockaddr *) &myaddr, sizeof(myaddr)) == -1) {
        perror("peer_run could not bind socket");
        exit(-1);
    }

    server_init()
    config.sock = sock;
    /* load my local chunk file list */
    init_hasChunk(config.has_chunk_file);

    /* Initialize download and upload connections */
    init_download_pool(&download_pool);
    init_upload_pool(&upload_pool);

    /* Select statement to process user input and incomming requests */
    while (1) {
        int nfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(sock, &readfds);
        
        tv.tv_sec = 10; /* Wait up to 10 seconds. */
        tv.tv_usec = 0;

        if (DEFAULT)
            fprintf(stderr, "New Select with%ld, %d\n", tv.tv_sec, tv.tv_usec);

        nfds = select(sock+1, &readfds, NULL, NULL, &tv);
        if (nfds > 0) {
            if (FD_ISSET(sock, &readfds)) {
                 process_tcp(sock);
            }
            if (FD_ISSET(STDIN_FILENO, &readfds)) {
                process_user_input(STDIN_FILENO, userbuf, handle_user_input,
                 "Currently unused");
            }
        } 
    }
}
void init_hasChunk(char* chunk_file) {

    FILE* file = fopen(chunk_file,"r");
    char read_buffer[BUF_SIZE];
    char hash_buffer[MD5_HASH_SIZE*2];

    hasChunk = queue_init();

    while (fgets(read_buffer,BUF_SIZE,file)) {
        chunk_t* chunk = calloc(sizeof(chunk_t),0);
        sscanf(read_buffer,"%d %s",&(chunk->id),hash_buffer); /****************Small doubt here ************/

        /* convert ascii to binary hash code */
        hex2binary(hash_buffer,MD5_HASH_SIZE*2,chunk->hash);
        //fprintf(stderr, "ID: %d\n", chunk->id);
        //print_hash((uint8_t *)chunk->hash);
        enqueue(hasChunk, (void *)chunk);

	// Resetting the buffer
        memset(read_buffer,0,BUF_SIZE);
        memset(hash_buffer,0,MD5_HASH_SIZE*2);
    }
    fclose(file);

}

void connection_check(){
}
