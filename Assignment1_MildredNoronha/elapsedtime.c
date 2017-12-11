//--------------------------------------------------------------------------------
//
// Read all the warnings in the comments about nonstandard or nonportable usages.
// Actually, read all the comments in any case.
// 
// This set of example timers is for use from within C/C++. This has multiple
// versions but only needs one. This cannot be used without thought; it has
// parameters and cpp parameters that must be set correctly for the platform used.
// Some of the timers do not require any special configuration, but they generally
// are low resolution. Ultra-high resolution clocks are more finicky and require
// more careful consideration. Do not use this without reading the entire file.
//
// In particular, before compiling this needs to have
//
//      1. version set to whichever clock is going to be used, as in the line
//          int version = 1;
//      2. gotassembler to indicate if asm (or gsm or nasm or ...) is available
//      3. cps, currently set in a declaration as 1000000
//      4. cpurate for version 5 must be set according to the platform used.
//          The values here correspond to some of my machines (behemoth, coris, ...)
//          and so are only useful on those machines.
// 
// Version 2 uses the function gettimeofday(), which is on all systems. Generally a
// high resolution clock is a better choice if one is available. The resolution of
// different clocks on a single machine can vary by a ratio of 10^6 or 10^7. So
// it can be the difference between waiting one second for a timing, or 3.8 months.
//
// The convention used is that a negative number (-17.0) is returned in case the 
// clock_gettime() call fails, instead of the error flag from that function. 
// 
// The makefile may link in librt, but it is not needed for all of the timers
// here. Modify the makefile and pick one of the timers that don't need
// the real-time library if it is not found. Because the prototype is simple and
// always the same, no elapsedtime.h file is provided.
//
// Originally the different timers were in different files, then glommed together
// by commenting out all but the chosen timer. That was shifted to use a case switch
// system in May 2015, which is why so many variables are defined at the start.
//
// The glory of the C programming language is sticking something simple like clock
// into multiple include files in different places. So this file includes time.h,
// sys/time.h, and sys/times.h. Disgusting.
//
// 2^-36 = eps(10^5) = 1.455191522836685e-11
//
//----------------
// Randall Bramley
// Department of Computer Science
// Indiana University, Bloomington
//----------------
// Last Modified: Mon 28 Aug 2017, 07:48 AM
//--------------------------------------------------------------------------------

#include <time.h>
#include <sys/time.h>   // Lovely: got both time.h and times.h in sys
#include <sys/times.h>  // For both times() and struct tms definitions
#include <unistd.h>     // Defines _SC_CLK_TCK
#include <stdio.h>      // The usual irritant needed for printf, etc.

#define gotassembler 0
// asm (or nasm or gasm or other assemblers) is not always available on a platform.
// The readtsc() function is needed for version 5 of the timers below. Set
// gotassembler to 1 if it is not available. This reads the tsc counter, which is
// normally recommended against - especially on multi-core or multi-cpu systems. If
// the constant_tsc flag is present in the CPU capability list, that avoids issues
// with the system entering power saving states or C* states. It still requires
// knowing the tsc rate, which varies from platform to platform. That makes it
// un-portable, and hence something to avoid in general.
#ifdef gotassembler
 unsigned long long int readtsc(void) {
    unsigned long long int val;
    do {
        unsigned int a, d;
        asm volatile("rdtsc" : "=a" (a), "=d" (d));
        (val) = ((long long)a) | (((long long)d)<<32);
    } while(0);
    return(val);
 }
#endif

// Just set the version below to whichever one you want.
int version = 1;

double elapsedtime(void) {

    int flag;
    struct timespec tp;
    double timing;
    struct timeval t;
    struct timezone whocares;
    double total;
    double sec, msec;     /* seconds */
    double usec;          /* microseconds */
    struct tms p;
    static long cps = 1000000;
    clock_t now = clock();
    static clockid_t cid = CLOCK_REALTIME; 
    // Do not use CLOCK_MONOTONE for resolution tests, as in
    //      static clockid_t cid = CLOCK_MONOTONIC;
    // Especially for systems running the NTP protocol it will include small drifts
    // meant to bring a clock back to "correct" time as indicated by the protocol.
    // That means the clock quantum tau is being changed. Even w/o the NTP system,
    // the clock can be shifted slowly by other software or hardware.
    long sumpun;
    clock_t ret;

    unsigned long long int val;
    double retval;

    static double cpurate = 1.8e9;  // if you use this, you did not read the instructions
    // static double cpurate = 3.201e9;  // coris
    // static double cpurate = 2.801e9;  // charis
    // static double cpurate = 3.301e9;  // behemoth std rate
    // static double cpurate = 5.7e9;    // behemoth max rate
    // static double cpurate = 1.700e9;  // toshita

switch(version) {
case 1:
    //-------------------------------------
    // Version 1: using clock_gettime()
    //-------------------------------------
    
    flag = clock_gettime(cid, &tp);
    if (flag == 0) 
        timing = (double)tp.tv_sec + ((double)1.0e-9)*(double)tp.tv_nsec;
    else 
        timing = -17.0;  // If timer failed, return non-valid time
    
    return(timing);
break;

case 2:
    //--------------------------------------------------------------
    // Version 2: using gettimeofday(), which is a wall clock timer
    //--------------------------------------------------------------
    gettimeofday(&t, &whocares);

    msec = (double) (t.tv_sec);
    usec = 1.0e-6*(double) (t.tv_usec);
    total = msec + usec;
    if (total < 0) 
        return(-17.0);
    else
        return(total);
break;

case 3:
    //---------------------------------------------------------------------------
    // Version 3: using times(). This uses sysconf() to get ticks per second.
    // Returns a double that gives the sum of user and system time. Beware: this 
    // has poor resolution generally, so it may require gazillions of timing 
    // samples and/or large number of adds before it shows anything nonzero when
    // using resol.c
    //---------------------------------------------------------------------------
    // tms is defined as
    // struct tms {
    //     clock_t tms_utime;  /* user time */
    //     clock_t tms_stime;  /* system time */
    //     clock_t tms_cutime; /* user time of children */
    //     clock_t tms_cstime; /* system time of children */
    // };
    sumpun = sysconf(_SC_CLK_TCK);
    ret = times(&p);
    return( (double) (p.tms_utime + p.tms_stime)/(double) sumpun );
break;

case 4:
    //------------------------------------------------------------------------------
    // Version 4: using the cpu timer clock()
    // This will not count sleep time, so testing this needs to do actual CPU work.
    // Beware: POSIX requires that CLOCKS_PER_SEC equals 1000000 independent of 
    // the actual resolution. So cps = sysconf(_SC_CLK_TCK) is not correct.
    // Also note this is an approximation of processor time used by the process,
    // and may not include any system time (which include important operations 
    // like I/O.)
    //------------------------------------------------------------------------------
    return ((double) now)/(double) cps;
break;

case 5:
    //------------------------------------------------------------------------------
    // Version 5: using a high resolution non-standard clock.
    // Beware: this hardcodes in the CPU Ghertz rate, which is specific to a single
    // machine. On systems with the proc filesystem, rate can be obtained from 
    //    cat /proc/cpuinfo
    // but if powersaving states are enabled in the CPU, that can vary dynamically.
    // Grep for constant_tsc in the CPU flags to see if a constant rate is used.
    // Another, more accurate way is
    //    cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_max_freq 
    // which will give the speed in units of khertz
    //------------------------------------------------------------------------------
#ifdef gotassembler
        val = readtsc();
        retval = (double) val/cpurate;
        if (retval < 0.0)
            return(-17.0);
        else
            return(retval);
#else
        printf("Trying to use asm version, but it is not around.\n");
        return(-17.0);
#endif
break;

default:
    printf("Whoa, cowbowy. No version found in elapsedtime().\n");
    return(-17.0);
break;
}

};
