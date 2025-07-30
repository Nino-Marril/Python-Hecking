#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10
typedef struct {
    int data;
    int link;
}nodeType;

typedef struct node{
    nodeType heap[SIZE];
    int availList;
}*VHeap;

typedef struct {
    VHeap VH;
    int elemPtr;
}cursorList;


void initCursor(cursorList* L);
void insertCursor(cursorList* L, int num);
void deleteCursor(cursorList* L, int delElem);
cursorList getEven(cursorList* L);
void displayCursor(cursorList L);
int main() {
    cursorList C;
    initCursor(&C);
    int data[] = {2,4,6,8,10, 9};
    int x;
    for(x = 0; x < sizeof(data)/sizeof(data[0]);x++) {
        insertCursor(&C, data[x]);
        printf("\ninserts values %d\n", data[x]);
    }
    displayCursor(C);

    printf("\n**********EVEN LIST**********\n");
    cursorList D = getEven(&C);
    displayCursor(C);
    displayCursor(D);

    printf("\n*********Delete one Element*********\n");
    deleteCursor(&D, 4);
    displayCursor(D);
    return 0;
}

void initCursor(cursorList* L) {
    
    L->VH = (VHeap)malloc(sizeof(struct node));
    if(L->VH != NULL) {
    int x;
    L->VH->availList = SIZE-1;
    L->elemPtr = -1;
    for(x = SIZE-1; x > 0; x--) {
        L->VH->heap[x].link = x-1;
        printf("link value of [%d] is %d\n\n", x, L->VH->heap[x].link);
    }
    L->VH->heap[x].link = -1;
    printf("Successfully initialized\n");
    }
}

void insertCursor(cursorList* L, int num) {
//without using allocspace or dealloc

    int temp = L->VH->availList;
    if(temp != -1) {
    L->VH->availList = L->VH->heap[temp].link; //----------------             
    L->VH->heap[temp].data = num;                             //|
    L->VH->heap[temp].link = L->elemPtr;                      //--------inserting//allocating data
    L->elemPtr = temp;                                        //|
    }                                          //----------------

}

void deleteCursor(cursorList* L, int delElem) {

    printf("\nTo be deleted: %d\n\n", delElem);
    if(L->elemPtr != -1) {
        int* x, temp;
        for(x = &L->elemPtr; *x != -1 && L->VH->heap[*x].data != delElem; x = &L->VH->heap[*x].link){}
        if(*x != -1) {
            temp = *x;
            *x = L->VH->heap[temp].link;
            L->VH->heap[temp].link = L->VH->availList;
            L->VH->availList = temp;
        }

    }
}

void displayCursor(cursorList L) {
    int x;
    printf("\n");
    for(x = L.elemPtr; x != -1; x = L.VH->heap[x].link) {
        printf("%d ->%d  ", L.VH->heap[x].data, L.VH->heap[x].link);
    }
    printf("\n\n");
}

cursorList getEven(cursorList* L) {
    cursorList newL;
    newL.elemPtr = -1;
    newL.VH = L->VH;
    int* trav, temp;
    for(trav = &L->elemPtr; *trav != -1; ) {
        if(L->VH->heap[*trav].data % 2 == 0) {
            temp = *trav;
            *trav = newL.VH->heap[temp].link;
            newL.VH->heap[temp].link = newL.elemPtr;
            newL.elemPtr = temp;
        }else {
            trav = &newL.VH->heap[*trav].link;
        }
    }
    return newL;
}