#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

void afficher(char* crible, int n)
{
    // TODO: afficher les nombres premiers plus petits que n
}

void rayer_multiples(char* crible, int n, int k)
{
    // TODO: rayer (i.e. passer à zéro) tous les multiples de k qui sont plus petits que n
}


int main(int argc, char **argv)
{
    int n=1000;
    if(argc>1)
    {
        n = atoi(argv[1]);
        assert( n > 0 );
    }

    char buffer[1000];
    assert(n <= 1000);
    
    char * crible = (char*)&buffer ;

    for(int i=0; i<n; i++)
    {
        crible[i] = 1;//par défaut: pas encore barré
    }
    
    for(int k=2; k<n; k++)
    {
        rayer_multiples(crible, n, k);
    }

    afficher(crible, n);
    
    return 0;
}
