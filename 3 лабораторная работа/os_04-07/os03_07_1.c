#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
 	printf("SYSTEM\n");
	system("./os03_05_1");
	printf("SYSTEM end\n");
	printf("EXEC\n");
	char* argv[] = { NULL };
	execv("./os03_04", argv);
	printf("EXEC end\n");
	
}
