#include<string.h>
#include"ll.c"


int mod(int number, int size){
    return  number % size;
}
int modASCII(char* word, int size){
    int total = 0;
    for(int i = 0; i < strlen(word); i++){
        total += word[i];
    }
    return total % size;
}

typedef struct DirectChaining {
    LinkedList** hashTable;
    int size; // actual size of hashtable
    int maxSize; // max size of hash table
    int maxChainSize; // max size of itens on linked list
}  DirectChaining;
DirectChaining* createDC(int maxSize, int maxChainSize){
    DirectChaining* dc = (DirectChaining*) malloc(sizeof(DirectChaining));
    LinkedList** hashTable = (LinkedList**) malloc(maxSize * sizeof(LinkedList*));
    dc->hashTable = hashTable;
    dc->maxChainSize = maxChainSize;
    dc->maxSize = maxSize;
    dc->size = 0;
    return dc;
}
void insertHashTableDC(DirectChaining* dc, int value){
    int newIndex = mod(value, dc->maxSize);
    if(dc->hashTable[newIndex] == NULL){
        dc->hashTable[newIndex] = createLL();
        dc->size++;
    }
    if(dc->hashTable[newIndex]->length < dc->maxChainSize){
        insertOnTail(dc->hashTable[newIndex], value);
    } 
}
int searchHashTableDC(DirectChaining* dc, int value){
    int index = mod(value, dc->maxSize);
    if(dc->hashTable[index] == NULL) return 0;
    return searchLL(dc->hashTable[index], value);
}
void printDirectChaining(DirectChaining* dc){
    printf("Hash Table\n");
    for(int i = 0; i<dc->size; i++){
        print(dc->hashTable[i]);
    }
}
void deleteDirectChainingKey(DirectChaining* dc, int key){
    int index = mod(key, dc->maxSize);
    if(dc->hashTable[index] == NULL) return;
    deleteByValue(dc->hashTable[index], key);
}

typedef struct OpenAddrLinearProbing{
    int* hashTable;
    int maxSize;
    int size;
} OpenAddrLinearProbing;
OpenAddrLinearProbing* createLinearProbing(int maxSize){
    int* hashTable = (int*) malloc(maxSize*sizeof(int));
    OpenAddrLinearProbing* oalp = (OpenAddrLinearProbing*) malloc(sizeof(OpenAddrLinearProbing));
    oalp->hashTable = hashTable;
    oalp->maxSize = maxSize;
    oalp->size = 0;

    for (int i = 0; i < maxSize; i++) {
        hashTable[i] = -1; 
    }
    return oalp;
}
double getLoadFactor(OpenAddrLinearProbing* oalp) {
    return oalp->size * 1.00/oalp->maxSize;
}
void rehashKeys(OpenAddrLinearProbing* oalp){
    int newMaxSize = 2 * oalp->maxSize;
    int* newTable = (int*) malloc(newMaxSize * sizeof(int));
    
    for(int i = 0; i < newMaxSize; i++){
        newTable[i] = -1;
    }

    for(int i = 0; i < oalp->maxSize; i++){
        if(oalp->hashTable[i] != -1){
            int value = oalp->hashTable[i];
            int index = mod(value, newMaxSize);
            while(newTable[index] != -1){
                index = (index + 1) % newMaxSize;
            }
            newTable[index] = value;
        }
    }
    free(oalp->hashTable); 
    oalp->hashTable = newTable;
    oalp->maxSize = newMaxSize;
}
void insertIntoLinearProbing(OpenAddrLinearProbing* oalp, int value){
    if(getLoadFactor(oalp) >= 0.75){
        rehashKeys(oalp);
    }
    int newIndex = mod(value, oalp->maxSize);
    while(oalp->hashTable[newIndex] != -1){
        newIndex = (newIndex + 1) % oalp->maxSize;
    }
    oalp->hashTable[newIndex] = value;
    oalp->size++;
}

int main(void){
    //DirectChaining
    DirectChaining* dc = createDC(5,5);
    insertHashTableDC(dc, 1);
    insertHashTableDC(dc, 2);
    insertHashTableDC(dc, 3);
    insertHashTableDC(dc, 4);
    insertHashTableDC(dc, 5);
    insertHashTableDC(dc, 6);
    printDirectChaining(dc);
    deleteDirectChainingKey(dc, 6);
    deleteDirectChainingKey(dc, 5);
    printDirectChaining(dc);


    return (0);
}