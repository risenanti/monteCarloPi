#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>


#define SEED 35791246
void startTime(void);
void stopTime(void);

int main(int argc, char** argv)
{
	startTime();

    double x,y, z;
    long int i,count=0; /* # of points in the 1st quadrant of unit circle */
    double pi;

    long int nIterations = 100000000;
    /* initialize random numbers */
    srand(SEED);
    count=0;
    for ( i=0; i<nIterations; i++)
    {
       x = (double)rand()/RAND_MAX;
       y = (double)rand()/RAND_MAX;
       z = sqrt(x*x+y*y);
       if (z<=1) count++;
    }

    pi = (double)count/nIterations*4.0;

    printf("count is %ld \n", count);
    printf("# of trials= %ld , Serial estimate of pi is %6.6f \n",nIterations,pi);

    stopTime();
}

void startTime(void)
{
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ( "Current start time and date: %s", asctime (timeinfo) );
}

void stopTime(void)
{
    time_t rawtime;
    struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf ( "Top time and date: %s", asctime (timeinfo) );
}
