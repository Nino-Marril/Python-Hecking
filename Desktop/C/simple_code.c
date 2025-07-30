#include <stdio.h>

void swap(int* x, int* y);

int main() {

    int num1 = 55;
    int num2 = 66;
    printf("Numbers: num1 %d num2 %d", num1, num2);
    swap(&num1, &num2);
    printf("\nSwapped: num1 %d  num2 %d\n", num1, num2);
    return 0;
}


void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}