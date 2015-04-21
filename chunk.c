/***************************************************************************
 *Author: Kiran Kumar Lekkala
 *Date:  11 April 2015
 *Filename: chunk.c
 *Description: Divides a file to chunks

 ***************************************************************************/
#include "chunk.h"

void md5_hash(uint8_t *chaine, int len, uint8_t *hash){
    struct md5_ctx ctx;
    unsigned char digest[16];

    //init the md5 process
    md5_init(&ctx);
    ctx.size = len ? len:strlen(chaine);
    strcpy(ctx.buf, chaine);
    md5_update(&ctx);
    md5_final(digest, &ctx);
    hash = digest;
}

void bin2hex(uint8_t* buf, int len, char* ascii){
    int i;
    for(i=0;i<len;i++){
        sprintf(ascii+(i*2), "%.2x", buf[i]);
    }
    ascii[len*2] = 0;
}

static uint8_t hex2bin(char hex)
{
    hex = toupper(hex);
    uint8_t c = ((hex <= '9') ? (hex - '0') : (hex - ('A' - 0x0A)));
    return c;
}


void hex2binary(char *hex, int len, uint8_t*buf) {
    int i = 0;
    for(i=0;i<len;i+=2) {
        buf[i/2] = hex2bin(hex[i]) << 4 | hex2bin(hex[i+1]);
    }
}


int make_chunks(FILE *fp, uint8_t *chunk_hashes){

    uint8_t *buffer = (uint8_t*) calloc(CHUNK_SIZE,0);
    int numchunks = 0;
    int numbytes = 0;

    while((numbytes = fread(buffer, sizeof(uint8_t), CHUNK_SIZE, fp)) > 0 ) {
        md5hash(buffer, numbytes, chunk_hashes[numchunks++]);
    }
    return numchunks;
}
