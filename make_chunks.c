/***************************************************************************
*Author: Kiran Kumar Lekkala
*Date: 10 April 2015
*Filename: make_chunks.c
*Description: Driver program to make chunks from a file


***************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>

#include "md-5.h"
#include "chunk.h"

static int num_chunks();

int main(int argc, char *argv){

    if(argc<2){
        fprintf(stderr, "usage: error", argv[0]);
        exit(-1);
    }

    char *input_file = argv[1];
    FILE *fp = fopen(input_file, "r");
    int numchunks = find_numchunks(input_file);

    //sanity testing
    if (numchunks < 0 || fp == NULL){
        fprintf(stderr, "file error for %s: %s", input_file, strerror(errno));
        exit(-1);
    }

    uint8_t **hashes = (uint8_t **)calloc(sizeof(uint8_t*), numchunks);
    if(hashes == NULL){
        fprintf(stderr, "Out of memory !!!");
        exit(-1);
    }

    for(i=0;i<numchunks;i++){
    hashes[i] = calloc(sizeof(uint8_t), (MD5_HASH_SIZE))

    if(hashes[i] == NULL){
        fprintf(stderr, "Out of memory !!");
        exit(-1);
    }
    }

    int chunks = make_chunks(fp, hashes);
    char ascii[MD5_HASH_SIZE*2+1]; //This is the ascii string

    for(i=0;i<chunks;i++){
        hex2ascii(hashes[i], MD5_HASH_SIZE, ascii);
        printf("%d %s\n", i, ascii);
        free(hashes[i]);
    }

    //free the memory
    free(hashes);
    fclose(fp);

    return 0;
}

int find_numchunks(char *filename){
    struct stat file;

    //the stat returned the file.
    if( !stat(filename, &file)) {

        double size_file = (double) file.st_size;
        return ceil(length/ CHUNK_SIZE);
    }
    else{
        //return error
        return -1
    }
}
