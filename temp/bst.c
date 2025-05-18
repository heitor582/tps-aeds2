#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    struct TreeNode* left;
    struct TreeNode* right;
    int value;
} TreeNode;

typedef struct BST{
    TreeNode* root;
} BST;

typedef struct Node{
    struct Node* next;
    TreeNode* val;
} Node;

typedef struct Queue{
    Node* head;
    Node* tail;
} Queue;

int isEmpty(Queue* q) {
    return q->head==NULL;
}
void enqueue(Queue* q, TreeNode* root){
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->val = root;

    if(isEmpty(q)){
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}
TreeNode* dequeue(Queue* q){
    if(isEmpty(q)){
        return NULL;
    }

    Node* node = q->head;
    if(q->head == q->tail){
        q->head = q->tail = NULL;
    } else {
        q->head = q->head->next;
    }
    TreeNode* val = node->val;
    free(node);
    return val;
}

void preOrder(TreeNode* root){
    if(root == NULL) return;
    printf("%d", root->value);
    preOrder(root->left);
    preOrder(root->right);
}
void inOrder(TreeNode* root){
    if(root == NULL) return;
    inOrder(root->left);
    printf("%d", root->value);
    inOrder(root->right);
}
void posOrder(TreeNode* root){
    if(root == NULL) return;
    posOrder(root->left);
    posOrder(root->right);
    printf("%d", root->value);
}
void levelOrder(TreeNode* root){
    if(root == NULL) return;
    Queue* q = (Queue*) malloc(sizeof(Queue));
    enqueue(q,root);
    while(!isEmpty(q)){
        TreeNode* cur = dequeue(q);
        if(cur->left != NULL){
            enqueue(q,cur->left);
        }
        if(cur->right != NULL){
            enqueue(q,cur->right);
        }
        printf("%d", cur->value);
    }
}
void deleteTreeNode(TreeNode* root){
    if(root == NULL) return;
    deleteTreeNode(root->left);
    deleteTreeNode(root->right);
    free(root);
}
void deleteBST(BST* bst){
    deleteTreeNode(bst->root);
    free(bst);
}
TreeNode* createNode(int value) {
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}
TreeNode* insertTreeNode(TreeNode* node, int value){
    if(node == NULL){
       node = createNode(value);
    } else if(value < node->value){
        node->left = insertTreeNode(node->left, value);
    } else if(value > node->value){
        node->right = insertTreeNode(node->right, value);
    }
    return node;
}
void insert(BST* bst, int value){
    bst->root = insertTreeNode(bst->root, value);
}
TreeNode* invertTree(TreeNode* node){
    if(node == NULL) return node;
    TreeNode* left = invertTree(node->left);
    TreeNode* right = invertTree(node->right);

    node->left = right;
    node->right = left;

    return node;
}
int sameTree(TreeNode* node, TreeNode* node2){
    if((node == NULL && node2 != NULL) || (node != NULL && node2 == NULL)) return 0;
    int isSame = 1;
    if(node != NULL && node2 != NULL) {
        if(node->value != node2->value) {
            isSame = 0;
        } else {
            isSame = isSame && sameTree(node->left, node2->left);
            isSame = isSame && sameTree(node->right, node2->right);
        }
    }

    return isSame;
}
int symmetricTree(TreeNode* node, TreeNode* node2){
    if((node == NULL && node2 != NULL) || (node != NULL && node2 == NULL)) return 0;
    int isSame = 1;
    if(node != NULL && node2 != NULL) {
        if(node->value != node2->value) {
            isSame = 0;
        } else {
            isSame = isSame && sameTree(node->left, node2->right);
            isSame = isSame && sameTree(node->right, node2->left);
        }
    }

    return isSame;
}
TreeNode* search(TreeNode* root, int value){
    TreeNode* result = NULL;
    if(root == NULL) result = NULL;
    else if(root->value == value) result = root;
    else if(value < root->value) result =search(root->left, value);
    else if(value > root->value) result = search(root->right, value);
    return result;
}
TreeNode* minimumNode(TreeNode* root){
    if(root->left == NULL) return root;
    return minimumNode(root->left);
}
TreeNode* deleteNode(TreeNode* root, int value){
    if(root == NULL) return NULL;
    if(root->value > value) {
        root->left = deleteNode(root->left, value);
    } else if(root->value < value){
        root->right = deleteNode(root->right, value);
    } else {
        //2 children i change my curr for the right less value for mantain the rule of bst
        //2 filhos eu troco meu atual pelo menor valor a direita para manter a regra do bst e depois deleto ele
        if(root->left != NULL && root->right != NULL){
            TreeNode* minRightNode = minimumNode(root->right);
            root->value = minRightNode->value;
            root->right = deleteNode(root->right, minRightNode->value);
        } else if(root->left != NULL){ //1 child i just substitute the curr for the son and free the memory // 1 filho eu so substituo o atual pelo filho e libero a memoria
            TreeNode* temp = root;
            root = root->left;
            free(temp);
        } else if(root->right != NULL){
            TreeNode* temp = root;
            root = root->right;
            free(temp);
        } else { //Without a son i just free the memory and set the root null // nenhum filho eu libero a memoria e seto para null
            free(root);
            root = NULL;
        }
    }
    return root;
}
int main(void) {
    BST* tree = (BST*) malloc(sizeof(BST));
    tree->root = NULL;

    // Inserindo elementos na árvore
    insert(tree, 5);
    insert(tree, 3);
    insert(tree, 7);
    insert(tree, 2);
    insert(tree, 4);

    // Mostrando a árvore antes da inversão
    printf("Árvore original:\n");
    printf("Pré-ordem: ");
    preOrder(tree->root);
    printf("\nEm ordem: ");
    inOrder(tree->root);
    printf("\nPós-ordem: ");
    posOrder(tree->root);
    printf("\n");

    // Invertendo a árvore
    invertTree(tree->root);

    // Mostrando a árvore invertida
    printf("\nÁrvore invertida:\n");
    printf("Pré-ordem: ");
    preOrder(tree->root);
    printf("\nEm ordem: ");
    inOrder(tree->root);
    printf("\nPós-ordem: ");
    posOrder(tree->root);
    printf("\n");

    // Limpando memória
    deleteBST(tree);

    tree = (BST*) malloc(sizeof(BST));
    tree->root = NULL;

    // Inserindo elementos na árvore
    insert(tree, 5);
    insert(tree, 3);
    insert(tree, 7);
    insert(tree, 2);
    insert(tree, 4);

    // Criar uma cópia da árvore original e comparar com ela mesma
    BST* tree2 = (BST*) malloc(sizeof(BST));
    tree2->root = NULL;
    insert(tree2, 5);
    insert(tree2, 3);
    insert(tree2, 7);
    insert(tree2, 2);
    insert(tree2, 4);

    printf("\nSão iguais? %s\n", sameTree(tree->root, tree2->root) ? "Sim" : "Não");
    printf("\nSão simetricas? %s\n", symmetricTree(tree->root, tree2->root) ? "Sim" : "Não");

    int val = 4;
    TreeNode* found = search(tree->root, val);
    if (found != NULL)
        printf("Valor %d encontrado na árvore.\n", val);
    else
        printf("Valor %d NÃO encontrado na árvore.\n", val);

    levelOrder(tree->root);
    return 0;
}
