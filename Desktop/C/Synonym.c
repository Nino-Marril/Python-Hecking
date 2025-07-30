#include <stdio.h>
#include <stdlib.h>

#define M 50
#define EMPTY -999
#define DELETED -2

typedef int CLOSED_DICT[M * 2];

typedef struct {
    CLOSED_DICT Dict;
    int Bit_Vector[M * 2];
    //Add packing density later
    int last; // next available index for synonyms (starts at 10)
} CLOSEDH;

int hash(int data);
void initClosedDict(CLOSEDH* D);
void insertClosedDict(CLOSEDH* D, int elem);
void displayClosedHash(CLOSEDH D);


void insertPrime(CLOSEDH* H, int number);
int isPrime(int number); //for checking a hash value is a prime;


// Main program (Closed Hashing only)
int main() {
    CLOSEDH closedDict;
    int data[] = {4,6,8,9,22,12,46,33,103,145};

    initClosedDict(&closedDict);
    for (int i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
        insertPrime(&closedDict, data[i]);
    }

    displayClosedHash(closedDict);
    return 0;
}


// Hash function: digit sum AND data, then mod M
int hash(int data) {
    int H = 0, temp = data;
    while (temp != 0) {
        H += temp % 10;
        temp /= 10;
    }
    return (H & data) % M;
}



// Initialize Closed Hash Table
void initClosedDict(CLOSEDH* D) {
    for (int i = 0; i < M * 2; i++) {
        D->Dict[i] = EMPTY;
        D->Bit_Vector[i] = 0;
    }
    D->last = M; // synonyms start at index 10
}



// Insert into Closed Hash Table
void insertClosedDict(CLOSEDH* D, int elem) {
    int key = hash(elem);
    printf("Inserting %d → hash = %d\n", elem, key);

    if (D->Dict[key] == EMPTY || D->Dict[key] == DELETED) {
        D->Dict[key] = elem;
        D->Bit_Vector[key] = 1;
        printf("  → Placed at D[%d]\n", key);
    } else {
        if (D->last < M * 2) {
            D->Dict[D->last] = elem;
            D->Bit_Vector[D->last] = 1;
            printf("  → Collision! Placed at synonym D[%d]\n", D->last);
            D->last++;
        } else {
            printf("  → ERROR: Table full! Cannot insert %d\n", elem);
        }
    }
}



// Display the contents of the hash table
void displayClosedHash(CLOSEDH D) {
    for (int i = 0; i < M; i++) {
        if (D.Dict[i] != EMPTY && D.Dict[i] != DELETED)
            printf("D[%d] -> %d\n", i, D.Dict[i]);
        else
            printf("D[%d] -> EMPTY\n", i);
    }

    if (D.last > M) {
        printf("\nSynonyms Area (10 to %d):\n", D.last - 1);
        for (int i = M; i < D.last; i++) {
            if (D.Dict[i] != EMPTY && D.Dict[i] != DELETED)
                printf("D[%d] -> %d\n", i, D.Dict[i]);
            else
                printf("D[%d] -> EMPTY\n", i);
        }
    } else {
        printf("\nSynonyms Area is empty.\n");
    }
}



void insertPrime(CLOSEDH* H, int number) {
    int Hval = hash(number);

    printf("Inserting %d → hash = %d\n", number, Hval);
    if(isPrime(Hval) == 1) {
        if(H->Dict[Hval] == EMPTY || H->Dict[Hval] == DELETED) {
            H->Dict[Hval] = number;
            H->Bit_Vector[Hval] = 1;
        }
    }else {
            H->Dict[H->last] = number;
            H->Bit_Vector[H->last] = 1;
            H->last++;
    }
}

int isPrime(int number) {
    int retVal = 0;  // Assume prime by default

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