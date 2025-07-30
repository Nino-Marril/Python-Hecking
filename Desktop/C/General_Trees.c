#include <stdio.h>
#include <stdlib.h>
#define M 10
typedef struct {
    int Parent[M];
    int root;
}Parent;


void initTree(Parent* P);
void initRoot(Parent* P,int r);
void insertParent(Parent* P, int val, int Parent);
void displayTree(Parent P);
int LeftMostChild(Parent P, int parent);
int main() {
    Parent T;
    printf("\n**********Initializing*********");
    initTree(&T);
    initRoot(&T, 2);


    printf("\n**********Inserting*********\n");
    insertParent(&T, 0, 2);
    insertParent(&T, 3, 2);
    insertParent(&T, 1, 3);
    insertParent(&T, 4, 1);
    insertParent(&T, 6, 3);
    insertParent(&T, 7, 6);
    //T.Parent[0] = 2;


    printf("\n**********Displaying*********\n");
    //printf("%d %d",0, T.Parent[0]);
    displayTree(T);

    printf("\n**********Left most child*********\n");
    printf("The left-most child is %-10d ", LeftMostChild(T, 6));
    return 0;
}

void initTree(Parent* P) {
    int x;
    for(x = 0;x < M; x++) {
        P->Parent[x] = -2;
    }
    printf("Successfully Initialized\n");
}

void initRoot(Parent* P, int r) {
    P->root = r;
    P->Parent[P->root] = -1;
} 

void insertParent(Parent* P, int val,int Parent) {
        printf("\n Inserting Now\n");
        P->Parent[val] = Parent;
}

void displayTree(Parent P) {
    int x;
    for(x = 0; x < M; x++) {
        printf("P%5d C%5d\n", x,P.Parent[x]);
    }
}

int LeftMostChild(Parent P, int parent) {
    int x;
    int LeftP = 0;
    for(x = 0; x < M && P.Parent[x] != parent; x++) {}

    return (x < M)? x : -2;
}