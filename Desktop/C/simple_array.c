#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int* getListEven(int nums[], int size);
//malloc is needed here :]
bool isEven(int num);
void display(int list[], int size);



int main() {
    int lotto[] = {22,55,68,90,45,83,42,11,56,53};
    int size = sizeof(lotto)/sizeof(lotto[0]);
    int* Even = getListEven(lotto, size);
    int nsize = sizeof(Even)/sizeof(Even[0]);
    display(Even, nsize);
    //printf("%s\n", isEven(lotto[9]) ?  "true" : "false");
    free(Even);
    return 0;
}

//still trying to figure out why this doesnt work on vscode :( until my internet is back)
int* getListEven(int nums[], int size) {
    int x, count;
    count = 0;
    x = 0;
    while(x < size){
        if(nums[x] % 2 == 0) {
            count++;
        }
        x++;
    }
    int* EvenList = (int*)malloc(sizeof(int)*count);
    if(EvenList != NULL) {
        x = 0;
        while(x < size) {
        if(isEven(nums[x]) == true) {
            EvenList[x] = nums[x];
          }
        x++;
        }
    }
    return EvenList;
}


bool isEven(int num) {
    return (num % 2 == 0) ? true : false;
}
void display(int list[], int size) {
    int x;
    for(x = 0; x < size; x++) {
        if(x < size-1) {
            printf("%d, ", list[x]);
        }else {
            printf(" %d", list[x]);
        }
    }
}