/*
 * measureSystemCall.c
 *
 *  Created on: Feb 26, 2017
 *      Author: arvin
 */

#include <time.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

/* Your Answers Here
 *
 *1 a) brief description of the system 				: Running on ubuntu16.04 VM
 *1 b) total time measured 							: 2.0 ms
 *1 c) average overhead per pass through the loop 	: 2.0 ms / 1000 000 = 2 ns per pass
 *2 a) execute the function getpid() 1000000 times 	: 2.5 ms
 *2 b) average time per pass 						: 2.5 ms / 1000 000 = 2.5 ns per pass
 *3 a) measured total time for syscall(SYS_getpid)	: 52.3 ms
 *3 b) average time for syscall						: 52.3 ms / 1000 000 = 52.3 ns per pass
 *4 a) measured total time for fork() and wait()	: 54.2 ms
 *4 b) average time									: 54.2 ms / 1000 000 = 54.2 ns per pass
 *4 c) after every iteration the calling process forks a new child. the child then forks a new process too. this keeps going on until 2^<iterations> processes are created.
 *
 *
 */

double timespec_to_ms(struct timespec *ts)
{

	return ts->tv_sec * 1000.0 + ts->tv_nsec / 1000000.0;
}

int main()
{

	struct timespec start_time, end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);

	/* begin timing */

	int errorCount = 0;
	for (int i = 0; i < 1000; i++)
	{
//		getpid();
//		syscall(SYS_getpid);
		int pid = fork();
		if (pid == 0)
		{
			return 0;
		}
		if (pid < 0)
		{
			printf("ERROR: Fork failed.	n");
			errorCount++;
		}
		wait(0);
	}

	/* end timing */

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	printf("%f ms\n", timespec_to_ms(&end_time) - timespec_to_ms(&start_time));

}
