/*I want to find a number, and search them in an order*/
#include <stdio.h>
#define M 10

typedef struct {
    int numbers[M];
    int count;
}BinaryS;

void initList(BinaryS* B);
void insertSorted(BinaryS* B, int data);
int binarySearch(BinaryS B, int number); 
void display(BinaryS B);

int main() {
    BinaryS Bin;
    initList(&Bin);
    int x;
    int numbers[] = {2,4,9,10,15};
    for(x = 0; x < sizeof(numbers)/sizeof(numbers[0]);x++) {
    insertSorted(&Bin, numbers[x]);
    }
    display(Bin);
    int bin = binarySearch(Bin,10);
    ("value is at %d",bin);
    return 0;
}

void initList(BinaryS* B) {
    B->count = -1;
}
void insertSorted(BinaryS* B, int data) {

    if(B->count < M){
        B->count++;
        B->numbers[B->count] = data;
    }
}
int binarySearch(BinaryS B, int number) {
    int low = 0;
    int res = -1;
    int high = M-1;
    while(low <= high && res == -1) {
        int mid = low + (low - high) / 2;
        if(B.numbers[mid] == number) {
            res = mid;
        }else if(B.numbers[mid] > number) {
                high = mid - 1;
        }else {
                low = mid + 1;
        }
    }
    return res;
}
void display(BinaryS B) {
    int x;
    for(x = 0; x <= B.count; x++) {
        printf("%d ", B.numbers[x]);
    }
    printf("\n");
}