#include <stdio.h>
#include <stdlib.h>

#define M 10
#define EMPTY -999
#define DELETED -998

typedef int Dictionary[M];
typedef int node;
typedef struct {
    Dictionary Dict;
    int count;
}CLOSED_HASH;

void initDictionary(CLOSED_HASH* D);

int hashVal(int data);

void insertDictionary(CLOSED_HASH* D, node n);

void deleteDictionary(CLOSED_HASH* D, node n);

void displayDictionary(CLOSED_HASH D);

int main() {
    CLOSED_HASH H;
    initDictionary(&H);
    int data[] = {235, 148, 190, 219, 127};
    int x;
    for(x =0; x <sizeof(data)/sizeof(data[0]);x++) {
        insertDictionary(&H,data[x]);
    }
    displayDictionary(H);

    printf("\n\nDelete A value\n\n");
    deleteDictionary(&H,190);
    displayDictionary(H);
    return 0;
}

void initDictionary(CLOSED_HASH* D) {
    D->count = 0;
    int x;
    for(x = D->count; x < M; x++) {
        D->Dict[x] = EMPTY;
    }
}

int hashVal(int data) {
    return ((data * data) - data) % M;
}

void insertDictionary(CLOSED_HASH* D, node n) {
    int hash =hashVal(n);
    printf("\n%d hash value is %d\n", n, hash);
    if(D->Dict[hash] != n) {
        int x;
    for(x = hash; D->Dict[x] != n && D->Dict[x] != EMPTY && D->Dict[x] != DELETED;x = (x + 1) % M){}
        D->Dict[x] = n;
    }
}

void deleteDictionary(CLOSED_HASH* D, node n) {
    printf("\n\nValue to be deleted: %d\n\n", n);
    int hash = hashVal(n);
    if(D->Dict[hash] != n) {
        int x;
        for(x = hash+1; D->Dict[x] != n && D->Dict[x] != EMPTY && D->Dict[x] != DELETED; x = (x+1) % M){}
        D->Dict[x] = DELETED;
    }
}

void displayDictionary(CLOSED_HASH D) {
    int x;
    for(x = 0; x < M; x++) {
        printf("\n[%d] ", x);
        if(D.Dict[x] != EMPTY || D.Dict[x] != DELETED) {
            printf("%d", D.Dict[x]);
        }else if(D.Dict[x] == EMPTY){
            printf("%d", EMPTY);
        }else {
            printf("%d", DELETED);
        }
        printf("\n");
    }
}