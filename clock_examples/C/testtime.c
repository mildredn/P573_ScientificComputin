#include <unistd.h>
#include <stdio.h>
#include <time.h>
int main(int argc, char **argv)
{
//--------------------------------------------------------------------------------
//
// Simple test driver for the elapsedtime() function, which in turn is a
// wrapper for one of the many system clocks.
//
// This will use sleep() or nanosleep() to make sure some time has passed
// on the clock between the two calls to elapsedtime(). The delay time is
// sleepytime for sleep() and nsleepytime for nanosleep().
//
// First try calling this without a sleep interval; just comment out both of
// the lines starting with "flag = "
//
//----------------
// Randall Bramley
// Department of Computer Science
// Indiana University, Bloomington
//----------------
// Last Modified: Mon 28 Aug 2017, 07:48 AM
//--------------------------------------------------------------------------------
    double time_used, time_start, time_end;
    double elapsedtime();
    unsigned int flag, sleepytime;
    struct timespec nsleepytime;

    nsleepytime.tv_sec  = 0;
    nsleepytime.tv_nsec = 123;
    sleepytime = 1;

    time_start = elapsedtime();
    //-------------------------------------------------------------------------
    // Block of code to be timed goes here. If the block is repeatedly called
    // in a loop, the loop should be considered part of the block. Here a
    // sleep delay is used to simulate a more interesting timing block. Use
    // sleep() if nanosleep() is not available
    //-------------------------------------------------------------------------
    flag       = nanosleep(&nsleepytime, NULL);
    // flag       = sleep(sleepytime);
    time_end   = elapsedtime();
    time_used  = time_end - time_start;

    // printf("time_start = %.17e\n", time_start);
    // printf("time_end   = %.17e\n", time_end);
    printf("time_used  = %.17e\n", time_used);

return 0;

}
