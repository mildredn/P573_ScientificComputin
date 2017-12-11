
#include <sys/times.h>
#include <sys/types.h>
#include <sys/resource.h>

double getr(double *utime,
            double *stime,
            long counts[15])
{
/*---------------------------------------------------------------------
>> Read the system time and resource usage from getrusage(),
>> and return it in a format suitable for using in other languages
>> The fields in the array named "resources" have the
>> interpretations that match the corresponding ones in the
>> structure rusage in /sys/resource.h:
>>        maxrss	=   maximum resident size so far
>>        ixrss		=   integral shared memory size 
>>        idrss		=   integral unshared data 
>>        isrss		=   integral unshared stack
>>        minflt	=   page reclaims 
>>        majflt	=   page faults 
>>        nswap		=   swaps 
>>        inblock	=   block input operations 
>>        oublock	=   block output operations 
>>        msgsnd	=   IPC messages sent 
>>        msgrcv	=   IPC messages received 
>>        nsignals	=   signals received 
>>        nvcsw		=   voluntary context switches 
>>        nivcsw	=   involuntary context switches 
-------------------------------------------------------------*/
     struct rusage resources;
     struct timeval rutime;
     struct timeval rstime;
     // int who = RUSAGE_SELF;
     int who = RUSAGE_CHILDREN;
     int ierr;
     int i;

     ierr = getrusage (who, &resources);

/* ---------------------------------------- */
/* In case of error, return garbage values: */
/* ---------------------------------------- */
     if (ierr != 0) 
      { *utime = -1.0;
        *stime = -1.0;
        for (i = 0; i < 15; i++) counts[i] = -1;
        return -34.0; }

/* ----------------------------------- */
/* Unpack structure to return as array */
/* ----------------------------------- */
      *utime = (double) resources.ru_utime.tv_sec
               + 1.0e-6 * (double) resources.ru_utime.tv_usec;
      *stime = (double) resources.ru_stime.tv_sec
               + 1.0e-6 * (double) resources.ru_stime.tv_usec;
      counts[0]  = resources.ru_maxrss;     /* maximum resident set size */
      counts[1]  = resources.ru_ixrss;      /* integral shared memory size */
      counts[2]  = resources.ru_idrss;      /* integral unshared data size */
      counts[3]  = resources.ru_isrss;      /* integral unshared stack size  */
      counts[4]  = resources.ru_minflt;     /* page reclaims */
      counts[5]  = resources.ru_majflt;     /* page faults */
      counts[6]  = resources.ru_nswap;      /* swaps */
      counts[7]  = resources.ru_inblock;    /* block input operations */
      counts[8]  = resources.ru_oublock;    /* block output operations */
      counts[9]  = resources.ru_msgsnd;     /* messages sent */
      counts[10] = resources.ru_msgrcv;     /* messages received */
      counts[11] = resources.ru_nsignals;   /* signals received */
      counts[12] = resources.ru_nvcsw;      /* voluntary context switches */
      counts[13] = resources.ru_nivcsw;     /* involuntary context switches */
      return (*utime + *stime); }
