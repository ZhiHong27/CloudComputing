#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

static double second(void)
{
    return ((double)((double)clock()/(double)CLOCKS_PER_SEC));
}

long child_node(long sPoint, long ePoint);
pid_t wpid;

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("\n Not accurate arguments passed!!! start value and end value needed \n");
		return 0;
	}
	double time;
	time = second();

	long start = strtol(argv[1], NULL, 10);
	long end = strtol(argv[2], NULL, 10);
	long res;

	res = child_node(start, end);
	printf("\n*******the sum from %li to %li is %li ********  \n",start, end, res);

  	time = second() - time;
  	printf("%.5f\n", time);

	return 0;	
}

long child_node(long sPoint, long ePoint)
{
	long num = ePoint-sPoint+1;
	long leftVal;
	long rightVal;
	int status = 0;

	int fdLeft[2];
	int fdRight[2];
	if (pipe(fdLeft) == -1) 
	{
  		sleep(5);
		fprintf(stderr, "pipe failed\n");
		printf("Pipe failed: My parent is dealing %li -- %li\n",sPoint,ePoint);
	}

	if (pipe(fdRight) == -1) 
	{
  		sleep(5);
		fprintf(stderr, "pipe failed\n");
		printf("Pipe failed: My parent is dealing %li -- %li\n",sPoint,ePoint);
	}

	if(num != 1)
	{
		pid_t left,right;
		left = right = getpid();

		left = fork();
	  	while (left < 0) 
	  	{
	  		sleep(5);
			fprintf(stderr, "fork failed\n");
			printf("Left: My parent is dealing %li -- %li\n",sPoint,ePoint);
			left = fork();
		}

		if(left > 0)  /**in the parent process**/
		{
			right = fork();
			while (right<0)
			{
				sleep(5);
				fprintf(stderr, "fork failed\n");
				printf("Right: My parent is dealing %li -- %li\n",sPoint,ePoint);				
				right = fork();
			}
		}

		if(left == 0) /**left child**/
		{
			leftVal = child_node(sPoint,sPoint + num/2-1);

  			close(fdLeft[0]);
			write(fdLeft[1], &leftVal, sizeof(long));
			close(fdLeft[1]);
			exit(0);
		}

		if(right == 0) /**right child**/
		{
			rightVal = child_node(sPoint + num/2, ePoint);

			close(fdRight[0]);
			write(fdRight[1], &rightVal, sizeof(long));
			close(fdRight[1]);
			exit(0);
		}		

		if(left>0 &&right>0) /** parent thread**/
		{
			close(fdRight[1]);
			close(fdLeft[1]);
			while((wpid = wait(&status)) > 0) {} /**wait until the end of 2 children threads**/
			read(fdLeft[0], &leftVal, sizeof(long));
			read(fdRight[0], &rightVal, sizeof(long));
			close(fdRight[0]);
			close(fdLeft[0]);
			return leftVal+rightVal;
		}

	}
	else
	{
		return ePoint;
	}
	return 0;
}
