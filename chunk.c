/***************************************************************************
*Author: Kiran Kumar Lekkala
*Date:  11 April 2015
*Filename: chunk.c
*Description: Divides a file to packets


***************************************************************************/



int make_chunks(FILE *fp, uint8_t **chunk_hashes);


/* return the md-5 hash of the string */
void md-5_hash(uint8_t *chr, int len, uint8_t *t);

/* converts hex string to ascii */
void bin2hex(uint8_t *buf, int len, char *ascii);

/* converts an ascii to hex */
void ascii2hex(char *ascii, int len, uint8_t *buf);
