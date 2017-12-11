// 
// Example for calling a timer from C/C++, and using it to time a function.
//
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

double getr(double *utime,
          double *stime,
          long counts[15]);


int main(int argc, char *argv[])
{
    double utime;
    double stime;
    double both;
    long counts[15];
    unsigned int sleepy_time = 2;
    int flag;


    both = getr(&utime, &stime, counts);
    flag  = sleep(sleepy_time);
    both = getr(&utime, &stime, counts);

    printf("utime = %24.17e seconds\n",  utime);
    printf("stime = %24.17e seconds\n",  stime);
    printf("both  = %24.17e seconds\n",  both);
    return 0;
};
