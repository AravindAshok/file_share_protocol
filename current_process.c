/***************************************************************************
*Author-1: Kiran Kumar Lekkala
*Author-2: Aravind Ashok
*Date: 13 April 2015
*Filename: current_process.c
*Description: takes care of the current process it handles
***************************************************************************/

#include "current.h"



static const char *requests={"IndexGet",
                             "ShortList",
                             "Longlist",
                             "RegEx",
                             "Verify",
                             "Check_All",
                             "FileDownload",
                             "FileUpload" };





int process_init(char* file, char* output){
    FILE*
}

void print_md5_hash(uint8_t *hash){

}

void print_data_pkt(data_packet_t* pkt){

}

int is_chunk_finished(chunk_t* chunk){

}

void cat_chunks(){

}

void store_data(){


}


queue_t* GET_maker(data_packet_t *ihave_pkt, bt_peer_t* provider,
                                             queue_t* chunk_queue) {
    assert(ihave_pkt->header.packet_type == PKT_IHAVE);
    int num = ihave_pkt->data[0]; // num of chunk that peer has
    //int num_match = 0;
    int i;
    int match_idx;
    chunk_t* chk = job.chunks;  // the needed chunk here
    queue_t *q;      // the queue of GET request
    data_packet_t* pkt; // GET packet
    uint8_t *hash;   // the incoming hash waiting to match my needs
    if (0 == num)
        return NULL;

    q = queue_init();
    hash = (uint8_t *)(ihave_pkt->data + 4); // the start of hash
    for (i = 0; i < num; i++) {
        match_idx = match_need(hash);
        if (-1 != match_idx) {
            chk[match_idx].pvd = provider;
            chk[match_idx].num_p = 1;
            job.num_living |= (1 << match_idx);   // this chunks is living
            pkt = packet_maker(PKT_GET,
                               HEADERLEN + SHA1_HASH_SIZE,
                               0, 0, (char *)hash);
            enqueue(q, (void *)pkt);
            enqueue(chunk_queue,(void*)(chk+match_idx));
            if (config.peers->next->next != NULL)
                return q;
        }
        hash += SHA1_HASH_SIZE;
    }
    return q;
}


/**********--------------*/
void packet_sender(data_packet_t* pkt, struct sockaddr* to) {
    int pkt_size = pkt->header.packet_len;
    int type = pkt->header.packet_type;
    if (VERBOSE)
        fprintf(stderr, "send %s pkt!*********\n", type2str[type]);
    print_pkt(pkt);
    hostToNet(pkt);
    spiffy_sendto(config.sock, pkt, pkt_size, 0, to, sizeof(*to));
    netToHost(pkt);
}


void send_(){

}

data_packet_t *generate_packet(){

}


