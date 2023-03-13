#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    printf("%d: hello world\n",getpid());
    int ret = fork();
    printf("%d: je suis ",getpid());
    if (ret){
        printf("le parent\n");
    } else {
        printf("l'enfant\n");
    }


    return EXIT_SUCCESS;
}
