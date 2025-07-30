#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char FName[16];
    char LName[24];
    char Mi;
}nameType;

typedef struct {
    nameType name;
    char course[8];
    int age;
}studType;

typedef struct node{
    studType studs;
    struct node* next;
}*Stack;

void initStack(Stack* S);
void sortStack(Stack* S);
void push(Stack* S, studType data);
void display(Stack* S);
int main() {
    Stack A;
    initStack(&A);
    studType students[] = {
        {{"John", "Doe", 'A'}, "CS101", 20},
        {{"Jane", "Smith", 'B'}, "CS102", 22},
        {{"Alice", "Johnson", 'C'}, "CS103", 19},
        {{"Bob", "Brown", 'D'}, "CS101", 21}
    };
    int i;
    for(i = 0; i < 4; i++) {
        push(&A, students[i]);
    }

    display(&A);

    printf("\nSorting stack...\n");
    sortStack(&A);
    //display(&A);
}
void initStack(Stack* S) {
    *S = NULL;
}

void push(Stack* S, studType data) {
    Stack temp = (Stack)malloc(sizeof(struct node));
    if(temp != NULL) {
        temp->studs = data;
        temp->next = *S;
        *S = temp;
    }
}

void display(Stack* S) {
    Stack current;
    while(*S != NULL) {
        printf("Name: %s %s, Course: %s, Age: %d\n", 
               (*S)->studs.name.FName, 
               (*S)->studs.name.LName, 
               (*S)->studs.course, 
            (*S)->studs.age);
        //current = current->next;
            current = *S;
        *S = current->next;
        if(current != NULL) {
            current->next = *S;
        }
    }

    while(current != NULL) {
        *S = current;
        current = current->next;
    }
}

void sortStack(Stack* S) {
    Stack stack1, stack2;
    stack1 = NULL;
    stack2 = NULL;
    char temp[8];
    strcpy(temp, (*S)->studs.course);
    printf("Initial course: %s\n", temp);
    while(*S != NULL) {
        if(strcmp((*S)->studs.course, temp) > 0) {
            strcpy(temp, (*S)->studs.course);
            
            push(&stack1, (*S)->studs);
            printf("Course changed to: %s\n", temp);
        }else {
            push(&stack2, (*S)->studs);
        }
        *S = (*S)->next;
    }

    while(stack1 != NULL) {
        if(strcmp(stack1->studs.course, temp) == 0) {
            push(S, stack1->studs);
        }
        *S = stack1;
        stack1 = (*S)->next;
        printf("value shifted");
    }

    printf("I give up, I still have an exam to study for.\n");
}