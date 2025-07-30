#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char Elems;
    struct node* next;
}*LList;

void initList(LList* L);
void insertFirst(LList* L, char x);
void displayList(LList L);
char getLastElem(LList L);
int main() {
    LList C;
     initList(&C);
     insertFirst(&C, 'A');
     insertFirst(&C, 'B');
     insertFirst(&C, 'C');
     insertFirst(&C, 'D');
    displayList(C);
    char data = getLastElem(C);
    printf("\nThe last element is %c \n", data);
    return 0;
}
void initList(LList* L) {
    *L = NULL;
}
void insertFirst(LList* L, char x) {
    LList temp = (LList)malloc(sizeof(struct node));
    if(temp != NULL) {
        temp->Elems = x;
        temp->next = *L;
        *L = temp;
    }
}

void displayList(LList L) {
    LList trav;
    printf("INSERTED DATA: \n");
    for(trav = L; trav != NULL;) {
        printf("%c ", trav->Elems);
        trav = trav->next;
    }
}

// char getLastElem(LList L) {
//     char temp = ';';
//     LList trav;
//     if(L != NULL) {
//     for(trav = L; trav->next != NULL; trav = trav->next){}
//     if(trav->next == NULL) {
//       temp = trav->Elems;
//         }
//     }
//     return temp;
// }

// char getLastElem(LList L) {
//     char result = ';';  // Default value for empty list

//     while (L != NULL) {
//         result = L->Elems;
//         L = L->next;
//     }

//     return result;
// }

char getLastElem(LList L) {
    char temp = ';';
    LList trav;

    for(trav = L; trav != NULL;) {
        if(trav->next == NULL) {
            temp = trav->Elems;
            printf("\ndata %c \n", temp);
        }
        trav = trav->next;  // Always advance
    }

    return temp;
}

