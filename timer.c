/***************************************************************************
*Author:  Nagarjuna Chidara                                                                 
*Date:  12 April 2015                                                                  
*Filename: timer.c                                                                 
*Description: Helper function for timing                                                             
                                                                           
                                                                           
***************************************************************************/

#include "timer.h"

int time_diff(struct timeval* start) {
	struct timeval curr;
	double t1 = start->tv_sec+(start->tv_usec/1000000.0);
	double t2;
	gettimeofday(&curr,NULL);
	t2=curr.tv_sec+(curr.tv_usec/1000000.0);
	return (int)((t2 - t1)*1000);
}
