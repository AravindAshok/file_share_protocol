
#ifndef _CHUNK_H_
#define _CHUNK_H_
#include <stdio.h>
#include <inttypes.h>

#define CHUNK_SIZE (512 * 1024)

#define ascii2hex(ascii, len, buf) hex2binary((ascii), (len), (buf))


#ifdef __cplusplus
extern "C"
