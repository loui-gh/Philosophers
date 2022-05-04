#include <stdio.h>
#include <sys/time.h>

int main (int argc, char** argv) {
    struct timeval tval_start, tval_now;  // removed comma

    gettimeofday (&tval_start, NULL);
    int i =0;
    while ( i < 10000) {
        i ++;
    }

    gettimeofday (&tval_now, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
    return 0;
}