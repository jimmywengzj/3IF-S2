#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const double epsilon = 1e-10;

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

int it(double **ptr, DIGRAPH *g, double alpha){
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
        res[i] = alpha * q;
    }

    for (int i = 0; i < g->n; i++) {
        res[i] += (1.0 - alpha) / g->n;
    }
    
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->nbSucc[i]; j++) {
            res[g->succ[i][j]] += alpha * s[i] / g->nbSucc[i];
        }
    }
    
    int converge = 1;
    for (int i = 0; i < g->n; i++) {
        if (res[i] - s[i] > epsilon || res[i] - s[i] < -epsilon ) {
            converge = 0;
            break;
        }
    }

    *ptr = res;
    free(s);

    return converge;
}

int main(){    
    FILE* fp  = fopen("genetic.txt", "r");
    DIGRAPH* g = readDigraph(fp);
    fclose(fp);
    double *s = (double*)malloc(g->n * sizeof(double));
    double alpha = 0.9;

//    printf("s0 = ");
    for (int i = 0; i < g->n; i++) {
        s[i] = 1.0 / g->n;
//        printf("%lf  ", s[i]);
    }
//    printf("\n");

    int t = 0;
    int converge = 0;
    while(!converge) {
        converge = it(&s, g, alpha);
        t++;
//        printf("s%d = ", t);
        for (int i = 0; i < g->n; i++) {
//            printf("%lf  ", s[i]);
        }  
//        printf("\n");
    }

    printf("Les pages plus consultes : \n");
    //selection sort
    int *sorted = (int*)malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; i++) {
        sorted[i] = 0;
    }
    for (int i = 0; i < (5 < g->n ? 5 : g->n); i++) {
        int pos = 0;
        double mini = -1;
        for (int j = 0; j < g->n; j++) {
            if (!sorted[j] && s[j] > mini) {
                mini = s[j];
                pos = j;
            }
        }
        sorted[pos] = 1;
        printf("%d  ", pos);
    }
    printf("\n");

    return 0;
}
