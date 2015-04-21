#ifndef _CHUNK_H_
#define _CHUNK_H_
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "md5.h"

#define CHUNK_SIZE (512 * 1024)

#ifdef __cplusplus
extern "C" {
#endif

    void md5_hash(uint8_t *chaine, int len, uint8_t *hash);

    /* return the md-5 hash of the string */
    void md5_hash(uint8_t *chr, int len, uint8_t *t);

    /* converts hex string to ascii */
    void bin2hex(uint8_t* buf, int len, char* ascii);

    /* converts an ascii to hex */
    void hex2bin(char *ascii, int len, uint8_t *buf);

    /* converts an ascii string to hex */
    void hex2binary(char *hex, int len, uint8_t*buf)

#ifdef __cplusplus
}
#endif

#endif /* _CHUNK_H_ */
