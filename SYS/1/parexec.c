#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    assert(argc>=4);
    int N = argc - 3;
    char* prog = argv[1];
    int maxProcess = atoi(argv[2]);
    int i;
    int ret;
    for (i=0;i<N;i++){
        if (i>=maxProcess){
            wait(NULL);
        }
        ret = fork();
        if (ret == 0){
            execl(prog,prog,argv[3+i],NULL);
        }
    }
    for (i=0;i<maxProcess;i++){
        wait(NULL);
    }
    return EXIT_SUCCESS;
}