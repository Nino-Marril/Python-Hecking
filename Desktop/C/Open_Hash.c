#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 10
#define EMPTY -1
#define DELETED -2
typedef struct link {
    int data;
    struct link* next;
}*list;
typedef list Dictionary[M];
typedef struct {
    Dictionary Dict;
    int Bit_Vector[M*2];
    int cnt; /*counting how many variables that are inserted*/
}OPENH;

typedef int CLOSED_DICT[M*2];

typedef struct {
    CLOSED_DICT Dict;
    int Bit_Vector[M];
    int last; /*counting how many variables that are inserted*/
}CLOSEDH;

// Function prototypes OPEN HASHING
void initDict(OPENH* D);
void insertDict(OPENH* D,int data); /*Acts like insertFirst*/
int hash(int data);
void display(OPENH D);


// Closed Hashing
void initCLosedDict(CLOSEDH* D);
void insertClosedDict(CLOSEDH* D, int elem); /*Linear Hashing version 2. Synonym ahh*/
void displayClosedHash(CLOSEDH D);


void EvenAtTop(OPENH* D);

int main() {
    int datas[] = {4,5,7,22,12,23,46};
    OPENH dict;
    printf("*********Initialize List*********\n");
    initDict(&dict);
    int x;
    for(x = 0; x < sizeof(datas)/sizeof(datas[0]); x++) {
        insertDict(&dict, datas[x]);
    }

    display(dict);

    printf("\n*********Even Numbers at Top*********\n");
    EvenAtTop(&dict);
    display(dict);

    // printf("\n*********Closed Hashing*********\n");
    // CLOSEDH closedDict;
    // int closedDatas[] = {4,6,8,9,22,12,46,33,103,145};
    // initCLosedDict(&closedDict);
    // for(x = 0; x < sizeof(closedDatas)/sizeof(closedDatas[0]); x++) {
    //     insertClosedDict(&closedDict, closedDatas[x]);
    // }
    
    // displayClosedHash(closedDict);
    printf("\n\n*********End of Program*********\n");
    // Free allocated memory for open hashing
    for (x = 0; x < M; x++) {
        list trav = dict.Dict[x];
        while (trav != NULL) {
            list temp = trav;
            trav = trav->next;
            free(temp);
        }
    }
    return 0;
}


//EITHER OPEN HASHING OR CLOSED HASHING
int hash(int data) {
    int H = 0, temp = data;
    while (temp != 0) {
        H += temp % 10;
        temp /= 10;
    }
    return (H & data) % M;
}



//OPEN HASHING STUFF
void initDict(OPENH* D) {
    int x;
    D->cnt = 0;
    for(x = 0; x < M; x++) {
        D->Dict[x] = NULL;
        D->Bit_Vector[x] = 0;
    }
}


void insertDict(OPENH* D,int data) {
    int key = hash(data);
    printf("\n\n hash value %d\n\n*********Insert Values*********\n", key);
    list temp;
    temp = (list)malloc(sizeof(struct link));
    if(temp != NULL) {
        temp->data = data;
        temp->next = D->Dict[key];
        D->Dict[key] = temp;
        D->cnt++;
        D->Bit_Vector[key] = 1;
    }


}



void display(OPENH D) {
    int x;
    list trav;
    int max = M-1;
    for(x = 0; x <= max; x++) {
        printf("D[%d] -> ", x);
        for(trav = D.Dict[x]; trav != NULL; trav = trav->next){
            printf("%d -> ", trav->data);
        }
        printf("\n");
    }


    printf("\nInserted Values for Bit Vector: \n");
    for(x = 0; x <= max; x++) {
        printf("[%d]%d ",x,D.Bit_Vector[x]);
    }
    printf("\n");
}



void EvenAtTop(OPENH* D) {
    int x;
    list trav, temp;

    for (x = 1; x < M; x++) {
        if (D->Bit_Vector[x] == 1) {
            trav = D->Dict[x];
            while (trav != NULL) {
                if (trav->data % 2 == 0) {
                    temp = (list)malloc(sizeof(struct link));
                    if (temp != NULL) {
                        temp->data = trav->data;
                        
                        if(D->Dict[0] != NULL) {
                            temp->next = D->Dict[0];
                            temp->next = D->Dict[0]; // Insert at the front of bucket 0
                            D->Dict[0] = temp;
                            D->Bit_Vector[0] = 1;
                        } else {
                            temp->next = NULL; // If bucket 0 is empty
                        }
                    }
                }
                trav = trav->next; // Move to next node (MUST be outside if)
            }
        }
    }
}

















//CLOSED HASHING STUFF
void initCLosedDict(CLOSEDH* D) {
    int x;
    int closeM = M * 2;
    D->last = M;
    for(x = 0; x < closeM ;x++) {
            D->Dict[x] = EMPTY;
            D->Bit_Vector[x] = 0;
    }
     // Initialize last to 10 as I want the synonyms to be inserted here
}


void insertClosedDict(CLOSEDH* D, int elem) {
    int key = hash(elem);
    printf("%d\n",D->last);
    if (D->Dict[key] == EMPTY || D->Dict[key] == DELETED) {
        // No collision; insert directly
        D->Dict[key] = elem;
        D->Bit_Vector[key] = 1;
    } else {
        // Collision — insert into overflow area
        if (D->last < M * 2) {
            D->Dict[D->last] = elem;
            D->Bit_Vector[D->last] = 1;
            D->last++;
        } else {
            printf("ERROR: Hash table overflow! Cannot insert %d\n", elem);
        }
    }
}



void displayClosedHash(CLOSEDH D) {
    printf("Main Area (0 to 9):\n");
    for (int i = 0; i < M; i++) {
        if (D.Dict[i] != EMPTY && D.Dict[i] != DELETED) {
            printf("D[%d] -> %d\n", i, D.Dict[i]);
        } else {
            printf("D[%d] -> EMPTY\n", i);
        }
    }

    // Only show synonym area if D.last moved beyond M
    if (D.last < M) {
        printf("\nSynonyms Area (10 to %d):\n", D.last - 1);
        for (int i = M; i < D.last; i++) {
            if (D.Dict[i] != EMPTY && D.Dict[i] != DELETED) {
                printf("D[%d] -> %d\n", i, D.Dict[i]);
            } else {
                printf("D[%d] -> EMPTY\n", i);
            }
        }
    } else {
        printf("\nSynonyms Area is empty.\n");
    }
}
