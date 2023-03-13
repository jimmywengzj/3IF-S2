#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    fork();
    if(fork()){
        fork();
    }
    printf("PID: %d, Parent PID:%d\n",getpid(),getppid());
    return EXIT_SUCCESS;
}