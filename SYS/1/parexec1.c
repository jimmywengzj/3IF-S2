#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    assert(argc>=3);
    int N = argc - 2;
    char* prog = argv[1];
    int i;
    int ret;
    for (i=0;i<N;i++){
        ret = fork();
        if (ret == 0){
            execl(prog,prog,argv[2+i],NULL);
        }
    }
    for (i=0;i<N;i++){
        wait(NULL);
    }
    return EXIT_SUCCESS;
}