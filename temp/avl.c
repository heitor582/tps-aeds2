#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    struct TreeNode* left;
    struct TreeNode* right;
    int value;
    int height;
} TreeNode;

typedef struct AVL{
    TreeNode* root;
} AVL;

AVL* newAVL(void){
    AVL* avl = (AVL*) malloc(sizeof(AVL));
    avl->root = NULL;

    return avl;
}
void deleteAllNodes(TreeNode* root){
    if(root == NULL) return;
    deleteAllNodes(root->left);
    deleteAllNodes(root->right);
    free(root);
}
void deleteAVL(AVL* avl){
    deleteAllNodes(avl->root);
    free(avl);
}
TreeNode* createNode(int value, int height) {
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    node->value = value;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}
int getHeight(TreeNode* node){
    if(node == NULL) return 0;
    return node->height;
}
int getBalance(TreeNode* node){
    if(node == NULL) return 0;

    return getHeight(node->left) - getHeight(node->right);
}

//insertion
// Left Right case = Transform to Left Left ( Left Rotation ) and do a right rotation
// Left Left case = right rotation
// Right Left case = transform into Right Right ( Right Rotation ) case and do a left rotation
// Right Right case = left rotation
TreeNode* rightRotation(TreeNode* node){
    TreeNode* newRoot = node->left;
    node->left = node->left->right;
    newRoot->right = node;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
    return newRoot;
}
TreeNode* leftRotation(TreeNode* node){
    TreeNode* newRoot = node->right;
    node->right = node->right->left;
    newRoot->left = node;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
    return newRoot;
}
TreeNode* insertNode(TreeNode* node, int value){
    if(node == NULL){
        node = createNode(value, 1);
    } else if(value < node->value){
        node->left = insertNode(node->left, value);
    } else if(value > node->value){
        node->right = insertNode(node->right, value);
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if(balance > 1 && value < node->left->value){
        node = rightRotation(node);
    } else if(balance > 1 && value > node->left->value){
        node->left = leftRotation(node->left);
        node = rightRotation(node);
    }else if(balance < -1 && value > node->right->value){
        node = leftRotation(node);
    } else if(balance < -1 && value < node->right->value){
        node->right = rightRotation(node->right);
        node = leftRotation(node);
    }

    return node;
}
void insert(AVL* avl, int value){
    avl->root = insertNode(avl->root, value);
}

TreeNode* minimumNode(TreeNode* node){
    if(node->left == NULL) return node;

    return minimumNode(node->left);
}
TreeNode* deleteNode(TreeNode* node, int value){
    if(node == NULL) return NULL;
    else if(value < node->value) node->left = deleteNode(node->left, value);
    else if(value > node->value) node->right = deleteNode(node->right, value);
    else {
        if(node->left != NULL && node->right != NULL){
            TreeNode* minNode = minimumNode(node->right);
            node->value = minNode->value;
            node->right = deleteNode(node->right, minNode->value);
        } else if(node->left != NULL) {
            TreeNode* temp = node;
            node = node->left;
            free(temp);
        } else if(node->right != NULL){
            TreeNode* temp = node;
            node = node->right;
            free(temp);
        } else {
            free(node);
            node = NULL;
        }
    }

    int balance = getBalance(node);
    // LL
    if(balance > 1 && getBalance(node->left) >= 0){
        node = rightRotation(node);
    } else if(balance > 1 && getBalance(node->left) < 0){ // LR
        node->left = leftRotation(node->left);
        node = rightRotation(node);
    }else if(balance < -1 && getBalance(node->right) <= 0){ // RR
        node = leftRotation(node);
    } else if(balance < -1 && getBalance(node->right) > 0){ // RL
        node->right = rightRotation(node->right);
        node = leftRotation(node);
    }

    return node;
}
void delete(AVL* avl, int value){
    avl->root = deleteNode(avl->root, value);
}

void main(void){

    return (0);
}