#include <stdio.h>
#include <stdlib.h>


#define MAX 10
typedef struct {
    char FName[16];
    char LName[24];
    char Mi;
}nameType;

typedef struct {
    nameType name;
    char course[8];
    int year;
}studType;

// typedef struct {
//     studType* stud;
//     int count;
//     int arrSize;
// }List;

typedef struct {
    studType* data;
    int front;
    int rear;
}Queue; //Queue Version 3

typedef struct {
    studType stud[MAX];
    int Top;
}*Stack;



int main() {
    return 0;
}