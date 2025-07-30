#include <stdio.h>
#include <math.h> // Required for sqrt() function

// Function to check if a number is prime
int isPrime(int number) {

    int retVal;
    // Check for divisibility from 2 up to the square root of the number
    if(number > 1) {
        int primeN = number*number;
        for (int i = 2; i <= primeN; i++) {
            if (number % i == 0) {
                retVal =  0; // If divisible, it's not prime
            }else {
                retVal = 1;
            }
        }
    }
    return retVal;
}

int main() {
    int num;

    printf("Enter an integer: ");
    scanf("%d", &num);

    if (isPrime(num)) {
        printf("%d is a prime number.\n", num);
    } else {
        printf("%d is not a prime number.\n", num);
    }

    return 0;
}