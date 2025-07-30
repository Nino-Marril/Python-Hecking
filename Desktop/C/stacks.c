//Stacks in array, Linked List, and Cursor-Based Implementations
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    char ELem[MAX];
    int top;
}Stack; //Version 1 structure variable


typedef struct node {
    char data;
    struct node* top;
}*Node; //Version 2 structure variable

typedef struct {
    char data;
    int link;
}nodeType;

typedef struct {
    nodeType stack[MAX];
    int top;
    int Avail; //index of the first available node
}VirtualHeap;

//Array-based stack implementation
void initStack(Stack* S); //Array-based stack initialization
void push(Stack* S, char data); //Array-based stack push operation
void pop(Stack* S); //Array-based stack pop operation
int isEmpty(Stack S); //Array-based stack check if empty
int isFull(Stack S);


//Linked list-based stack implementation
void initList(Node* N);
void pushList(Node* N, char data); //Linked list stack push operation
void popList(Node* N); //Linked list stack pop operation
int isEmptyList(Node N); //Linked list stack check if empty

//Cursor-based stack implementation
void initVirtualHeap(VirtualHeap* VH);
int alloc(VirtualHeap* V);
void dealloc(VirtualHeap* V, int index);
void pushCursor(VirtualHeap* V, char data);
void popCursor(VirtualHeap* V);
void displayCursor(VirtualHeap* V);
int main() {
    VirtualHeap VH;
    initVirtualHeap(&VH);   
    pushCursor(&VH, 'A');
    pushCursor(&VH, 'B');
    pushCursor(&VH, 'C');
    printf("Cursor Stack: ");
    displayCursor(&VH);

    // Node L;
    // initList(&L);
    // pushList(&L, 'A');
    // pushList(&L, 'B'); 
    // pushList(&L, 'C');
    // printf("Linked List Stack: ");
    // while (!isEmptyList(L)) {
    //     printf("%c ", L->data);
    //     popList(&L);
    // }
    // printf("\n");   
    return 0;
}

void initStack(Stack* S) {
    S->top = -1;
}
void push(Stack* S, char data) {
    if (S->top < MAX - 1) { // Check if stack is not full
        S->top++;
        S->ELem[S->top] = data;
    }
}
void pop(Stack* S) {
    if (S->top >= 0) { // Check if stack is not empty
        S->top--;
    }
}
int isEmpty(Stack S) {
    return (S.top == -1) ? 1 : 0;
}
int isFull(Stack S) {
    return (S.top == MAX - 1) ? 1 : 0;
}


void initList(Node* N) {
    *N = NULL;
}
void pushList(Node* N, char data) {
    Node temp = (Node)malloc(sizeof(struct node));
    if (temp != NULL) {
        temp->data = data;
        temp->top = *N;
        *N = temp;
    }
}
void popList(Node* N) {
    if (*N != NULL) { // Check if stack is not empty
        Node temp = *N;
        *N = temp->top; // Move top pointer to the next node
        free(temp); // Free the popped node
    }
}
int isEmptyList(Node N) {
    return (N == NULL) ? 1 : 0;
}



void initVirtualHeap(VirtualHeap* VH) {
    VH->top = -1;
    VH->Avail = 0;
    for (int i = 0; i < MAX; i++) {
        VH->stack[i].link = i + 1;
    }
    VH->stack[MAX - 1].link = -1;
}
int alloc(VirtualHeap* V) {
    int retVal = V->Avail; // Get the index of the first available node
    if (retVal != -1) {
        V->Avail = V->stack[retVal].link; // Update the first available node
    }
    return retVal;
}
void dealloc(VirtualHeap* V, int index) {
    if(index >= 0 && index < MAX) {
        V->stack[index].link = V->Avail;
        V->Avail = index;
    }
}

void pushCursor(VirtualHeap* V, char data) {
    int temp = alloc(V); // Get an available index
    if (temp != -1) {
        V->stack[temp].data = data;
        V->stack[temp].link = V->top; // Link to the previous top node
        V->top = temp;
    }
}

void popCursor(VirtualHeap* V) {
    if (V->top != -1) { // Check if stack is not empty
        int temp = V->top; // Get the index of the top node
        V->top = V->stack[temp].link; // Move top pointer to the next node
        dealloc(V, temp); // Deallocate the popped node
    }
}

void displayCursor(VirtualHeap* V) {
    int current = V->top;
    while (V->top != -1) {
        printf("%c ", V->stack[V->top].data);
        //current = V->stack[current].link; // Move to the next node
        popCursor(V);
    }
    V->top = current;
    printf("\n");
}