#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


void cycle(char* s)
{
    pid_t pid = getpid();
    for (int i = 1; i < 100; i++)
    {
        sleep(1);
        printf("%d-%d,  prosses %s, \n", pid, i, s);
    }
};
void cycle_c(char* s)
{
    pid_t pid = getpid();
    for (int i = 1; i < 50; i++)
    {
        sleep(1);
        printf("%d-%d,  prosses %s, \n", pid, i, s);
    }
};

int main()
{
    pid_t pid;
    switch (pid = fork())
    {
    case -1: 
        perror("fork error"); 
        exit(1);
    case 0: 
        cycle_c("child");
        exit(0);
    default: 
        cycle("main"); 
        wait(0);
    }
    exit(0);
}
