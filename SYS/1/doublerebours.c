#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int ret = fork();
    char* reboursLength = (ret==0 ? "4" : "2");
    execl("./rebours","./rebours",reboursLength,NULL);
    return EXIT_SUCCESS;
}
