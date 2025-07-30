#include <stdio.h>
#include <stdlib.h>
#define MAX 5
typedef struct node{
    int vertex; // if matrix, add a source index
    int weight;
    struct node* next;
}*Node;

typedef Node ADJACENT[MAX];

void initGraph(ADJACENT T);
void createAdjacentEdge(ADJACENT T, int src, int dest, int weight);
Node convertToLinkedList(ADJACENT T);


void displayAdjacent(ADJACENT T);
void displayList(Node N);
int main() {
    ADJACENT adj;
    initGraph(adj);
    createAdjacentEdge(adj, 0, 3, 20);
    createAdjacentEdge(adj, 2, 1, 18);
    createAdjacentEdge(adj, 1, 0, 24);
    createAdjacentEdge(adj, 3, 2, 18);
    createAdjacentEdge(adj, 2, 5, 27);

    displayAdjacent(adj);
    Node List = convertToLinkedList(adj);
    displayList(List);
    return 0;
}
void initGraph(ADJACENT T) {
    int x;
    for(x = 0; x < MAX; x++) {
        T[x] = NULL;
    }
}

void createAdjacentEdge(ADJACENT T, int src, int dest, int weight) {
    Node temp = (Node)malloc(sizeof(struct node));
    if(temp != NULL) {
        temp->vertex = dest;
        temp->weight = weight;
        temp->next = T[src];
        T[src] = temp;
    }
}

void displayAdjacent(ADJACENT T) {
    int x;
    for(x = 0; x < MAX; x++) {
        printf("[%d]: ", x);
        Node trav = T[x];
        while(trav != NULL) {
            printf("vertex(%d) weight {%d} -> ", trav->vertex, trav->weight);
            trav = trav->next;
        }if(trav == NULL ) {
            printf("%s", "NULL");
        }
        printf("\n");
    }
}

Node convertToLinkedList(ADJACENT T) {
    Node converted = NULL; //converted[x] = NULL;
    Node* trav, temp;
    int x;
    for(x = 0; x < MAX; x++) {
        while(T[x] != NULL) { //list != NULL
            temp = T[x]; // temp = list; if the conversion is from linked list to adjacency list
            T[x] = T[x]->next; //list = temp->next;
            
            //trav = &converted; trav = &converted[temp->vertex]; *trav != NULL && similar stuff
            for(trav = &converted; *trav != NULL && (*trav)->weight < temp->weight; trav = &(*trav)->next){}
            temp->next = *trav;
            *trav = temp;
        }
    }
    return converted;
}

void displayList(Node N) {
    Node trav = N;
    printf("\n\n\nLinked List\n\n");
    while(trav != NULL) {
        printf(" %d -> ", trav->weight);
        trav = trav->next;
    }
    if(trav == NULL) {
        printf("NULL");
    }
}