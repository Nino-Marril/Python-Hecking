#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node {
    char* elemPtr;
    int count;
} LIST;

void initList(LIST *L);
void insertLast(LIST *L, char data);

int main() {
    LIST letters;

    printf("*****INITIALIZING LIST*****\n");
    initList(&letters);

    if (letters.elemPtr != NULL) {  // Proceed only if allocation succeeded
        printf("*****CREATING LETTERS*****\n");
        insertLast(&letters, 'L');
        insertLast(&letters, 'E');
        insertLast(&letters, 'T');
        insertLast(&letters, 'T');
        insertLast(&letters, 'E');
        insertLast(&letters, 'R');

        printf("*****DISPLAYING LETTERS*****\n");
        for (int x = 0; x < letters.count; x++) {
            printf("%c", letters.elemPtr[x]);
        }
        printf("\n");

        free(letters.elemPtr);
    } else {
        printf("Memory allocation failed. List not initialized.\n");
    }

    return 0;
}

void initList(LIST *L) {
    L->elemPtr = (char*)malloc(sizeof(char) * MAX);
    if (L->elemPtr != NULL) {
        L->count = 0;
    }
}

void insertLast(LIST *L, char data) {
    if (L->elemPtr != NULL && L->count < MAX) {
        L->elemPtr[L->count] = data;
        L->count++;
    }
}
