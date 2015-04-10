/***************************************************************************
*Author: Kiran Kumar Lekkala
*Date:  11 April 2015
*Filename: chunk.c
*Description: Divides a file to packets


***************************************************************************/

void md5_hash(uint8_t *str, int len, uint8_t *hash){



int make_chunks(FILE *fp, uint8_t *chunk_hashes){

    uint8_t *buffer = (uint8_t*) malloc(BT_CHUNK_SIZE);
    int numchunks = 0;
    int numbytes = 0;

    /* read the bytes from the file and fill in the chunk hashes */
    while((numbytes = fread(buffer)))
}
}

int main(int argc, char *argv[]){
    uint8_t *test = "test";
    uint8_t hash1[MD5_HASH_SIZE], hash2[MD5_HASH_SIZE];
    char ascii[MD5_HASH_SIZE*2 + 1];

    md5_hash(test, 4, hash);

    binary2
}
