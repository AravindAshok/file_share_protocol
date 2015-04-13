/***************************************************************************
*Author-1: Kiran Kumar Lekkala
*Author-2: Aravind Ashok
*Date: 13 April 2015
*Filename: current_process.c
*Description: takes care of the current process it handles
***************************************************************************/

#include "current.h"



static const char *requests={"IndexGet RegEx",
                             "IndexGet ShortList",
                             "IndexGet Longlist",
                             "FileHash Verify",
                             "FileHash Check_All",
                             "FileDownload",
                             "FileUpload" };





int process_init(char* file, char* output){
    FILE*
}

void print_md5_hash(uint8_t *hash){

}

void print_data_pkt(data_packet_t* pkt){

}

int is_chunk_finished(chunk_t* chunk) {
    int cur_size = chunk->cur_size;
    float kb = cur_size / 1024;
    if (VERBOSE)
        fprintf(stderr, "check finished!!!\n");
    if (cur_size != CHUNK_SIZE) {
        if (VERBOSE)
            fprintf(stderr, "Not finished yet, cur_size = %.5f\n", kb);

        return 0;
    }
    uint8_t hash[SHA1_HASH_SIZE];
    // get hash code
    shahash((uint8_t*)chunk->data,cur_size,hash);
    // check hash code

    if( memcmp(hash,chunk->hash,SHA1_HASH_SIZE) == 0) {
        return 1;
    } else {
        return -1;

    }
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

void local2net(data_packet_t* pkt) {
    pkt->header.magicnum = htons(pkt->header.magicnum);
    pkt->header.header_len = htons(pkt->header.header_len);
    pkt->header.packet_len = htons(pkt->header.packet_len);
    pkt->header.seq_num = htonl(pkt->header.seq_num);
    pkt->header.ack_num = htonl(pkt->header.ack_num);
}


void net2local(data_packet_t* pkt) {
    pkt->header.magicnum = ntohs(pkt->header.magicnum);
    pkt->header.header_len = ntohs(pkt->header.header_len);
    pkt->header.packet_len = ntohs(pkt->header.packet_len);
    pkt->header.seq_num = ntohl(pkt->header.seq_num);
    pkt->header.ack_num = ntohl(pkt->header.ack_num);
}

void send_(){

}

data_packet_t *generate_packet(){

}

void print_pkt(data_packet_t* pkt) {
    if (VERBOSE != 1)
        return;
    header_t* hdr = &pkt->header;
    uint8_t* hash;
    int num;
    int i;
    fprintf(stderr, ">>>>>>>>>START<<<<<<<<<<<<<\n");
    fprintf(stderr, "magicnum:\t\t%d\n", hdr->magicnum);
    fprintf(stderr, "version:\t\t%d\n", hdr->version);
    fprintf(stderr, "packet_type:\t\t%d\n", hdr->packet_type);
    fprintf(stderr, "header_len:\t\t%d\n", hdr->header_len);
    fprintf(stderr, "packet_len:\t\t%d\n", hdr->packet_len);
    fprintf(stderr, "seq_num:\t\t%d\n", hdr->seq_num);
    fprintf(stderr, "ack_num:\t\t%d\n", hdr->ack_num);
    if (PKT_WHOHAS == hdr->packet_type || PKT_IHAVE == hdr->packet_type) {
        num = pkt->data[0];
        fprintf(stderr, "1st bytes data:\t\t%x\n", pkt->data[0]);
        hash = (uint8_t *)(pkt->data + 4);
        for (i = 0; i < num; i++) {
            print_hash(hash);
            hash += SHA1_HASH_SIZE;
        }
    }
    fprintf(stderr, ">>>>>>>>>END<<<<<<<<<<<<<\n");
}

