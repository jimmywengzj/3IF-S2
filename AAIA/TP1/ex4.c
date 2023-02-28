#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct{
    int n; // number of vertices in the graph
    int* nbSucc; // for each 0<=i<n, nbSucc[i] = number of successors of i
    int** succ; // for each 0<=i<n and each 0<=j<nbSucc[i], succ[i][j]=jth successor of i
} DIGRAPH;


DIGRAPH* readDigraph(FILE *fp){
    // return the DIGRAPH contained in file fp
    DIGRAPH *g = (DIGRAPH*)malloc(sizeof(DIGRAPH));
    if (fscanf(fp, "%d\n", &(g->n)) != 1 || g->n <= 0){
        printf("erreur de lecture du fichier\n");
        exit(1);
    }
    g->nbSucc = (int*)malloc(g->n*sizeof(int));
    g->succ = (int**)malloc(g->n*sizeof(int*));
    int succ[g->n];
    for (int i=0; i<g->n; i++){
        g->nbSucc[i] = 0;
        while (1){
            if (fscanf(fp, "%d", &(succ[g->nbSucc[i]])) != 1 || succ[g->nbSucc[i]] >= g->n){
                printf("erreur de lecture du fichier\n");
                exit(1);
            }
            if (succ[g->nbSucc[i]]<0) break;
            g->nbSucc[i]++;
        };
        g->succ[i] = (int*)malloc(g->nbSucc[i]*sizeof(int));
        memcpy(g->succ[i], succ, g->nbSucc[i]*sizeof(int));
    }
    return g;
}

void printDigraph(DIGRAPH *g){
    // For each vertex of g, display the list of its successors
    for (int i=0; i<g->n; i++){
        printf("Vertex %d has %d successors: ", i, g->nbSucc[i]);
        for (int j=0; j<g->nbSucc[i]; j++)
            printf("%d ", g->succ[i][j]);
        printf("\n");
    }
}

void it(double **ptr, DIGRAPH *g){
    // return s(k+1) from s(k)
    double *s = *ptr;
    double *res = (double*)malloc(g->n * sizeof(double));
    double q = 0.0;
    for (int i = 0; i < g->n; i++) {
        if(g->nbSucc[i] == 0) {
            q += s[i];
        }
    }
    q /= g->n;

    for (int i = 0; i < g->n; i++) {
        res[i] = q;
    }
    
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->nbSucc[i]; j++) {
            res[g->succ[i][j]] += 1.0 * s[i] / g->nbSucc[i];
        }
    }
    
    *ptr = res;
}

int main(){
    FILE* fp  = fopen("exemple2.txt", "r");
    DIGRAPH* g = readDigraph(fp);
    fclose(fp);
    double *s = (double*)malloc(g->n * sizeof(double));

    printf("s0 = ");
    for (int i = 0; i < g->n; i++) {
        s[i] = 1.0 / g->n;
        printf("%lf  ", s[i]);
    }
    printf("\n");

    for (int t = 1; t <= 4; t++) {
        it(&s, g);
        printf("s%d = ", t);
        for (int i = 0; i < g->n; i++) {
            printf("%lf  ", s[i]);
        }  
        printf("\n");
    }
    return 0;
}
