#include <stdio.h>
#include <stdlib.h>

#define MAX 8
typedef struct {
    char data;
    int next;
}nodeType;

typedef struct {
    nodeType nodes[MAX];
    int Avail;
}VirtualHeap; //VERSION 1.0
typedef int List;
void initHeap(VirtualHeap* heap);
void initList(List* L);
int alloc(VirtualHeap* heap);
void dealloc(VirtualHeap* V, int ndx);
void insertFirst(VirtualHeap* V, char x, List* L);
void displayList(VirtualHeap V, List L);
void deleteFirst(VirtualHeap* V, List* L);
int main() {
    VirtualHeap heap;
    List L;
    initHeap(&heap);
    initList(&L);
    printf("*****INSERTING DATA*****\n");
    insertFirst(&heap, 'A', &L);
    insertFirst(&heap, 'B', &L);
    insertFirst(&heap, 'C', &L);
    insertFirst(&heap, 'D', &L);

    printf("*****DISPLAYING DATA*****\n");
    displayList(heap, L);

    // Deallocate nodeS
    deleteFirst(&heap, &L);
    displayList(heap, L);
    return 0;
}
void initHeap(VirtualHeap* heap) {
    heap->Avail = 0; // Start with the first node available
    for (int i = 0; i < MAX - 1; i++) {
        heap->nodes[i].next = i + 1;
    }
    heap->nodes[MAX - 1].next = -1; // Last node points to NULL
    
}

void initList(List* L) {
    *L = -1; // Initialize the list to empty
}

int alloc(VirtualHeap* heap) {
    int retVal = heap->Avail;
    if (retVal != -1) {
        heap->Avail = heap->nodes[retVal].next; // Move to the next 
    }
    return retVal;
}

void dealloc(VirtualHeap* V, int ndx) {
    if(ndx >=0 && ndx < MAX) {
        V->nodes[ndx].next = V->Avail; 
        V->Avail = ndx;
    }
}

void insertFirst(VirtualHeap* V, char x, List* L) {
    int temp = alloc(V);
    if (temp != -1) {
        V->nodes[temp].data = x;
        V->nodes[temp].next = *L; // Point to the current first node
        *L = temp; // Update the list head to the new node
    }
}

void displayList(VirtualHeap V, List L) {
    int trav = L;
    printf("INSERTED DATA: \n");
    while (trav != -1) {
        printf("%c ", V.nodes[trav].data);
        trav = V.nodes[trav].next; // Move to the next node
    }
    printf("\n");
}

void deleteFirst(VirtualHeap* V, List* L) {
    if (*L != -1) {
        int temp = *L; // Get the first node index
        *L = V->nodes[temp].next; // Update the list head to the next node
        dealloc(V, temp); // Deallocate the node
    }
}