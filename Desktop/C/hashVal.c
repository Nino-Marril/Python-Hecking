#include <stdio.h>

int hashBitValue(int data);

int main() {
    int n = 255;
    int hash = hashBitValue(n);
    printf(" the amount of 1s in here is %d", hash);
    return 0;
}

int hashBitValue(int data) {
    unsigned int mask = 1;
    int cnt = 0;
    for(;mask != 0; mask<<=1) { 
        if((mask&data) == 1) {
            cnt++;
        }
    }

    return cnt;
}