#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h>
#define SEED 35791246

void startTime(void);
void stopTime(void);

int main(int argc, char* argv[])
{
    long niter = 10000;
    int myid;                       //holds process's rank id
    double x,y;                     //x,y value for the random coordinate
    int i, count=0;                 //Count holds all the number of how many good coordinates
    double z;                       //Used to check if x^2+y^2<=1
    double pi;                      //holds approx value of pi
    int nodenum;


    startTime(); //Prints starting time


    MPI_Init(&argc, &argv);                 //Start MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);           //get rank of node's process
    MPI_Comm_size(MPI_COMM_WORLD, &nodenum);
    int recieved[nodenum];
    long recvniter[nodenum];
    srand(SEED);                        //Give rand() a seed value

    if(myid != 0)
    {
        for (i=0; i<niter; ++i)                  //main loop
        {
            x= ((double)rand())/RAND_MAX;           //gets a random x coordinate
            y =((double)rand())/RAND_MAX;           //gets a random y coordinate
            z = sqrt(x*x+y*y);                  //Checks to see if number in inside unit circle
            if (z<=1)
            {
                count++;                //if it is, consider it a valid random point
            }
        }
        for(i=0; i<nodenum; ++i)
        {
            MPI_Send(&count,
                                 1,
                                 MPI_INT,
                                 0,
                                 myid,
                                 MPI_COMM_WORLD);
            MPI_Send(&niter,
                                 1,
                                 MPI_LONG,
                                 0,
                                 myid,
                                 MPI_COMM_WORLD);
        }
    }
    else if (myid == 0)
    {
        for(i=0; i<nodenum; ++i)
        {
            MPI_Recv(&recieved[i],
                                 nodenum,
                                 MPI_INT,
                                 MPI_ANY_SOURCE,
                                 MPI_ANY_TAG,
                                 MPI_COMM_WORLD,
                                 MPI_STATUS_IGNORE);
            MPI_Recv(&recvniter[i],
                                 nodenum,
                                 MPI_LONG,
                                 MPI_ANY_SOURCE,
                                 MPI_ANY_TAG,
                                 MPI_COMM_WORLD,
                                 MPI_STATUS_IGNORE);
        }
    }

    if (myid == 0)                      //if root process
    {
        int finalcount = 0;
        long finalniter = 0;
        for(i = 0; i<nodenum; ++i)
        {
            finalcount += recieved[i];
            finalniter += recvniter[i];
        }

        pi = ((double)finalcount/(double)finalniter)*4.0;               //p = 4(m/n)
        printf("Pi: %f\n", pi);             //Print the calculated value of pi

    }

    MPI_Finalize();                     //Close the MPI instance

    stopTime();				//Prints Final time at stop

    return 0;
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

