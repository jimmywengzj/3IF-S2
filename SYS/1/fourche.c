#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    printf("Bonjour je suis '%s'\n",argv[0]);

    return EXIT_SUCCESS;
}