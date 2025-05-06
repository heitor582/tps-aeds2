#include <stdio.h>
#include<stdlib.h>
typedef struct Node {
    int val;
    struct Node* next;
} Node;
typedef struct LinkedList {
    Node* head;
    Node* tail;
    int length;
} LinkedList;

void print(LinkedList* ll){
    for(Node* cur = ll->head; cur != NULL; cur = cur->next){
        printf("%d", cur->val);
        if(cur->next != NULL){
            printf(" -> ");
        }
    }
    printf("\n");
}
void insertOnHead(LinkedList* ll, int val){
    Node* node = (Node*) malloc(1*sizeof(Node));
    node->val = val;
    node->next = ll->head;
    if(ll->head == NULL){
        ll->tail = node;
    }
    ll->head = node;
    ll->length++;
}
void insertOnTail(LinkedList* ll, int val){
    Node* node = (Node*) malloc(1*sizeof(Node));
    node->val = val;
    if(ll->tail == NULL){
        ll->head = node;
    }else {
        ll->tail->next = node;
    }
    ll->tail = node;
    ll->length++;
}
void insert(LinkedList* ll, int val, int position){
    if(position == 1){
        insertOnHead(ll,val);
        return;
    }
    if(position == ll->length+1){
        insertOnTail(ll,val);
        return;
    }
    int pos = 1;
    Node* cur;
    for( cur = ll->head; cur != NULL && pos < position-1; cur = cur->next, pos++);
    
    if(cur == NULL){
        return;
    }
    
    Node* node = (Node*) malloc(1*sizeof(Node));
    node->val = val;
    Node* next = cur->next;
    cur->next = node;
    node->next = next;
    ll->length++;
}
int deleteOnHead(LinkedList* ll){
    if(ll->head == NULL){
        return -1;
    }
    Node* temp = ll->head;
    int val = temp->val;
    
    ll->head = ll->head->next;
    if(ll->head == NULL){
        ll->tail=NULL;
    }
    
    free(temp);
    ll->length--;
    return val;
}
int deleteOnTail(LinkedList* ll){
    if(ll->tail == NULL){
        return -1;
    }
    
    if(ll->tail == ll->head){
        int val = ll->head->val;
        free(ll->tail);
        ll->head = NULL;
        ll->tail = NULL;
        ll->length--;
        return val;
    }
    Node* cur;
    for( cur = ll->head; cur->next != NULL && cur->next!=ll->tail; cur=cur->next);
    int val = ll->tail->val;
    free(ll->tail);
    
    ll->tail = cur;
    ll->tail->next = NULL;
    ll->length--;
    return val;
}
int delete(LinkedList* ll, int position){
    if(ll->head == NULL){
        return -1;
    }
    if(position == 1){
        return deleteOnHead(ll);
    }
    if(position == ll->length){
        return deleteOnTail(ll);
    }
    int pos = 1;
    Node* cur, *prev;
    for( cur = ll->head; cur != NULL && pos < position; cur = cur->next, pos++){
        prev = cur;
    }
    
    int val = cur->val;
    prev->next = cur->next;
    cur->next = NULL;
    free(cur);
    return val;
}

Node* split(Node* head){
    Node* fast = head;
    Node* slow = head;
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        if(fast != NULL){
            slow = slow->next;
        }
    }
    Node* temp = slow->next;
    slow->next = NULL;
    return temp;
}
Node* merge(Node* first, Node* second){
    if(first == NULL) return second;
    if(second == NULL) return first;
    if(first->val < second->val){
        first->next = merge(first->next, second);
        return first;
    } else {
        second->next = merge(first, second->next);
        return second;
    }
}
Node* mergeSort(Node* head){
    if(head == NULL || head->next == NULL) return head;
    Node* second = split(head);
    head = mergeSort(head);
    second = mergeSort(second);
    return merge(head, second);
}

int main(){
    LinkedList* ll = (LinkedList*) malloc(1*sizeof(LinkedList));
    insertOnHead(ll, 1);
    insertOnTail(ll, 3);
    insert(ll, 2,2);
    print(ll);
    printf("%d\n", deleteOnTail(ll));
    printf("%d\n", deleteOnHead(ll));
    insertOnHead(ll, 1);
    insertOnTail(ll, 3);
    print(ll);
    
    printf("%d\n", delete(ll,2));
    print(ll);
    insertOnTail(ll, 2);
    print(ll);
    mergeSort(ll->head);
    print(ll);
    return 0;
}