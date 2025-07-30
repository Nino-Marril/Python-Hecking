#include <stdio.h>
#include <stdlib.h>

#define MAX 8
typedef struct {
    char FN[24], LN[16];
    char Mi;
}nameType;

typedef struct cell{
    nameType* name;
    int count;
    int ArrSize;//for realloc purposes
}*ArrayList;

void initList(ArrayList *L);
void insertFirst(ArrayList *L, nameType data);
void displayList(ArrayList L);
int main() {

    ArrayList Students;
    nameType student1 = {"John", "Doe", 'A'};
    nameType student2 = {"Jane", "Smith", 'B'};
    nameType student3 = {"Alice", "Johnson", 'C'};

    printf("*****INITIALIZING LIST*****\n\n");
    initList(&Students);
    if (Students != NULL && Students->name != NULL) {  // Proceed only if allocation succeeded
        printf("*****INSERTING STUDENTS*****\n\n");
        insertFirst(&Students, student1);
        insertFirst(&Students, student2);
        insertFirst(&Students, student3);

        printf("*****DISPLAYING STUDENTS*****\n\n");
        displayList(Students);

        // Free allocated memory
        free(Students->name);
        free(Students);
    }


    return 0;
}


void initList(ArrayList *L) {
    *L = (ArrayList)malloc(sizeof(struct cell));
    if (*L != NULL) {
        (*L)->name = (nameType*)malloc(sizeof(nameType)*MAX);
        if((*L)->name != NULL) {
            (*L)->count = 0;
            (*L)->ArrSize = 0;
        }
    }
}
void insertFirst(ArrayList *L, nameType data) {
    if((*L)->count < MAX) {
        int i;
        if((*L)->count == (*L)->ArrSize) {
            (*L)->ArrSize += MAX; // Increase size for realloc
            (*L)->name = (nameType*)realloc((*L)->name, sizeof(nameType) * (*L)->ArrSize);
        }
        if((*L)->name != NULL) {
            for(i = (*L)->count; i > 0; i--) {
                (*L)->name[i] = (*L)->name[i - 1]; // Shift elements to the right
            }
            (*L)->name[0] = data; // Insert new element at the beginning
            (*L)->count++;
        }
    }
}

void displayList(ArrayList L) {
    if (L != NULL && L->name != NULL) {
        printf("\t\t\t%-5ss %-5s", "First Name", "Last Name\n");
        for (int i = 0; i < L->count; i++) {
            printf("Student %-10d: %-10s %-10s, Middle Initial: %5c\n", i + 1, L->name[i].FN, L->name[i].LN, L->name[i].Mi);
        }
    } else {
        printf("List is empty or not initialized.\n");
    }
}