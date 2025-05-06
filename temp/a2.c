#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct Node{
    struct Node* next;
    char val[100];
} Node;

typedef struct Queue{
    Node* head;
    Node* tail;
} Queue;

int isEmpty(Queue* q) {
    return q->head==NULL;
}
void enqueue(Queue* q, char* val){
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->next = NULL;
    strcpy(newNode->val, val);

    if(isEmpty(q)){
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}
char* dequeue(Queue* q){
    if(isEmpty(q)){
        return NULL;
    }

    Node* node = q->head;
    if(q->head == q->tail){
        q->head = q->tail = NULL;
    } else {
        q->head = q->head->next;
    }
    char* val = strdup(node->val);
    free(node);
    return val;
}
int isNumber(char* c){
    if(c[0] == '0') return 1;
    if(c[0] != '-'){
        return 0;
    }
    return 1;
}
void print(Queue* q){
    for(Node* cur = q->head; cur != NULL; cur = cur->next){
        printf("%s -> ", cur->val);
    }
}
int main(){
    Queue* oeste = (Queue*) malloc(sizeof(Queue));
    oeste->head = oeste->tail = NULL;
    Queue* norte = (Queue*) malloc(sizeof(Queue));
    norte->head = norte->tail = NULL;
    Queue* sul = (Queue*) malloc(sizeof(Queue));
    sul->head = sul->tail = NULL;
    Queue* leste = (Queue*) malloc(sizeof(Queue));
    leste->head = leste->tail = NULL;

    int fila = -4;

    char aviao[200] = "";

    while(fila != 0){
        scanf("%s", aviao);
        if(isNumber(aviao)){
            fila = atoi(aviao);
        } else {
            if(fila == -4){
                enqueue(leste, aviao);
            } else if(fila == -3){
                enqueue(norte, aviao);
            } else if(fila == -2) {
                enqueue(sul, aviao);
            } else {
                enqueue(oeste, aviao);
            }
        }
    }

    while(!isEmpty(oeste) || !isEmpty(norte) || !isEmpty(sul) || !isEmpty(leste)){
        if(!isEmpty(oeste)){
            printf("%s ", dequeue(oeste));
        }

        if(!isEmpty(norte)){
            printf("%s ", dequeue(norte));
        }

        if(!isEmpty(sul)){
            printf("%s ", dequeue(sul));
        }

        if(!isEmpty(leste)){
            printf("%s ", dequeue(leste));
        }
    }
    return 0;
}