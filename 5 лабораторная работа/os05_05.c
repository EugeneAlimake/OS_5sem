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
	nice(-20); 
	for(int i = 0; i < 100000000000000; i++)
	{
		printf("%ld\n", (long)getpid());
	}
}

sudo ./OSSP_05b