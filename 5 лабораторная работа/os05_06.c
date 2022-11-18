#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/resource.h>
#include <sched.h>


int main(int argc, char **argv) 
{
	for(int i = 0; i < 100000000000000; i++)
	{
		printf("%ld\n", (long)getpid());
		sleep(1);
	}
}
