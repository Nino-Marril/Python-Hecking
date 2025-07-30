#define MAX 0xA
#define VH_MAX 0xFF
typedef struct {
    char FN[24], LN[24];
    char Mi;
}nameType;

typedef struct {
    unsigned int ID;
    nameType name;
    char course[8];
    int yearLevel;
}studRec;

typedef struct cell {
    studRec studs[MAX];
    int ctr; //element count
}*ArrayList;


typedef struct {
    studRec stud;
    int link;
}CBnode;

typedef struct {
    CBnode heap[VH_MAX];
    int Avail; //index of the first available node
}*Vheap;

typedef struct {
    int elemPtr; //ndx of 1st elem in the list
    Vheap VH;
}cursorList;

typedef struct {
    ArrayList A;
    cursorList B;
}ComboList;

typedef enum {
    TRUE, FALSE
}boolean;

/*Given a combo list, write the code of the function isSubset(). The function will return true if list A of the combo list is a subset of list B of the combo list. 
Assume that the elements in the lists are unique . Note: Only efficient code will get full credit and there should be ONE  return statement ONLY. no break or exit statement*/

int main() {

    return 0;
}