#ifndef _TIMER_H
#define _TIMER_H

#include <sys/time.h>

#include "queue.h"
#include "chunk.h"
#include "md5.h"
#include "current_process.h"

int get_time_diff(struct timeval* start);

#endif


