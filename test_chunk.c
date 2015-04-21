/***************************************************************************
 *Author:  Kiran Kumar Lekkala
 *Date:  15 April 2015
 *Filename: test_chunk.c
 *Description: driver program for making chunks


 ***************************************************************************/

#include "chunk.h"

int main(int argc, char *argv[]){
	uint8_t *test = "test";
	uint8_t hash1[MD5_HASH_SIZE], hash2[MD5_HASH_SIZE];
	char ascii[MD5_HASH_SIZE*2 + 1];

	printf("Testing a character string..\n");
	md5_hash(test, 4, hash1);

	bin2hex(hash1,MD5_HASH_SIZE,ascii);
	printf("%s\n",ascii);

	assert(strlen(ascii)==32);

	hex2binary(ascii, strlen(ascii), hash2);

	bin2hex(hash2, MD5_HASH_SIZE,ascii);
	printf("%s\n", ascii);
	return 0;
}

