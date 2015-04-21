#ifndef _CHUNK_H_
#define _CHUNK_H_
#include <stdio.h>
#include <inttypes.h>

#define CHUNK_SIZE (512 * 1024)

#define ascii2hex(ascii,len,buf) hex2binary((ascii),(len),(buf))
#define hex2ascii(buf,len,ascii) binary2hex((buf),(len),(ascii))

#ifdef __cplusplus
extern "C" {
#endif


    void md5_hash(uint8_t *chaine, int len, uint8_t *hash);

    /* return the md-5 hash of the string */
  

    /* converts hex string to ascii */
    void bin2hex(uint8_t* buf, int len, char* ascii);

    /* converts an ascii to hex */
    static uint8_t hex2bin(char hex);

    /* converts an ascii string to hex */
    void hex2binary(char *hex, int len, uint8_t*buf);

    int make_chunks(FILE *fp, uint8_t *chunk_hashes);

#ifdef __cplusplus
}
#endif

#endif /* _CHUNK_H_ */
