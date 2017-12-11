// 
// Example for calling a timer from C/C++, and using it to time a function. In
// this case it just calls sleep().
//
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

double elapsedtime(void); // Dumb to have a .h file just for this one line

int main(int argc, char *argv[])
{
    double time1 , time2;
    unsigned int sleepy_time = 1;
    int flag;

    time1 = elapsedtime();
    flag  = sleep(sleepy_time);
    time2 = elapsedtime() - time1;

    // The time printed should be slightly more than sleepy_time
    printf("Elapsed time = %24.17e seconds\n", time2);
    return 0;
};
