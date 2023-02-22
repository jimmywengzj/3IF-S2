#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    assert(argc == 2);
    int duree = atoi(argv[1]);
    assert(duree > 0);

    //printf("Bonjour je suis '%s'\n",argv[0]);
    printf("%d: debut\n", getpid());
    while(duree > 0) {
        printf("%d: %d\n", getpid(), duree);
        sleep(1);
        duree--;
    }
    printf("%d: fin\n", getpid());

    return EXIT_SUCCESS;
}
