// 
// Example timer for use from C++. 
// 
// This calls clock_gettime(). Use gettimeofday() if clock_gettime() is not
// available - use the man pages to see how to use gettimeofday(). 
//
// Also note the convention used here: a negative number is returned in case the
// clock_gettime() call fails, instead of the error flag from that function.
//
//----------------
// Randall Bramley
// Department of Computer Science
// Indiana University, Bloomington
//----------------
// Started change tracking: Fri 28 Sep 2007, 06:38 PM
// Modified: Tue 01 Sep 2009, 04:40 PM to add comments
// Last Modified: Mon 28 Aug 2017, 07:50 AM
//------------------------------------------------------

#include <time.h>

double elapsedtime (void)
{
    int flag;
    clockid_t cid = CLOCK_REALTIME;
    // CLOCK_MONOTONE might be better in some cases
    timespec tp;
    double timing;

    flag = clock_gettime(cid, &tp);
    if (flag == 0) timing = tp.tv_sec + 1.0e-9*tp.tv_nsec;
    else           timing = -17.0; // If timer failed, return non-valid time
    
    return(timing);
};

