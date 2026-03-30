#include <stdio.h>
#include <stdlib.h>


struct Node {
    void* val;
    int height;
    int balance;
    struct Node* left;
    struct Node* right;
};

struct Tree{
    struct Node* root;
    int (*compare)(void* arg1, void* arg2);
};


struct Node* createNode(void* val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    if(node){
    node->val = val;
    node->height = 1;
    node->balance=0;
    node->left = NULL;
    node->right = NULL;
    }
    return node;
}

struct Tree* createTree(int (*compare)(void* arg1, void* arg2)){
    struct Tree* tree = (struct Tree*)malloc(sizeof(struct Tree));

    if(tree){
        tree->root=NULL;
        tree->compare=compare;
    }
    return tree;
};

int findMaxHeight(int a,int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }

}

int getHeight(struct Node* root){
    if(root==NULL){
        return 0;
    }
    return root->height;

}

struct Node* rightRotate(struct Node* root){
    struct Node* leftNode = root->left;

    root->left=leftNode->right;
    leftNode->right=root;

    root->height = findMaxHeight(getHeight(root->left),getHeight(root->right)) + 1;
    leftNode->height = findMaxHeight(getHeight(leftNode->left),getHeight(leftNode->right)) + 1;

    return leftNode;
}

struct Node* leftRotate(struct Node* root){
    struct Node* rightNode = root->right;

    root->right =rightNode->left;
    rightNode->left = root;

    root->height = findMaxHeight(getHeight(root->left),getHeight(root->right)) + 1;
    rightNode->height = findMaxHeight(getHeight(rightNode->left),getHeight(rightNode->right)) + 1;

    return rightNode;
}

struct Node* InsertNode(struct Tree* tree, struct Node* root, struct Node* node){

    if(root==NULL){
        return node;
    }

    if(tree->compare(root->val,node->val) > 0){
        root->left = InsertNode(tree,root->left,node);
    }
    else if(tree->compare(root->val,node->val) < 0){
        root->right = InsertNode(tree,root->right,node);
    }
    else{
        return root;
    }

    root->height = findMaxHeight(getHeight(root->left),getHeight(root->right)) + 1;
    root->balance = (getHeight(root->left) - getHeight(root->right));

    int balance = root->balance;

    if(balance > 1 && tree->compare(node->val,root->left->val) < 0){   //!solun solu
        return rightRotate(root);
    }
    if(balance > 1 && tree->compare(node->val,root->left->val) > 0){  //!solun sagi
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && tree->compare(node->val,root->right->val) > 0){ //!sagin sagi
        return leftRotate(root);
    }
    if(balance < -1 && tree->compare(node->val,root->right->val) < 0){ //!sagin solu
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
   return root; //!
};

struct Node* findMin(struct Node* root){
    if(root==NULL){
        return NULL;
    }
    struct Node* temp = root;

    while(temp->left){
        temp=temp->left;
    }

    return temp;
};


struct Node* deleteNode(struct Tree* tree,struct Node* root,void* val){
    if(root==NULL){
        return root;
    }

    if(tree->compare(val,root->val) < 0){
        root->left= deleteNode(tree,root->left,val);
    }
    else if(tree->compare(val,root->val) > 0){
        root->right = deleteNode(tree,root->right,val);
    }
    else{
        if(root->right==NULL || root->left==NULL){

            struct Node* temp;

            if(root->right==NULL){
               temp  = root->left;
            }
            if(root->left==NULL){
                temp = root->right;
            }
            free(root);
            return temp;
        }
        else{
            struct Node* replaceNode = findMin(root->right);
            root->val=replaceNode->val;
            root->right = deleteNode(tree,root->right,replaceNode->val);
        }
    }

        if(root==NULL){
            return root;
        }

        root->height = findMaxHeight(getHeight(root->left),getHeight(root->right)) + 1;

        root->balance = (getHeight(root->left)-getHeight(root->right));

        int balance = root->balance;

        if(balance > 1){        //!agirlik solda
            int leftBalance = (getHeight(root->left->left)-getHeight(root->left->right));

            if(leftBalance > 0){    //!solun solu
                return rightRotate(root);
            }
            else{                   //!solun sagi
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }

        }

        if(balance < -1){        //!agirlik sagda
            int rightBalance = (getHeight(root->right->left)-getHeight(root->right->right));

            if(rightBalance < 0){   //!sagin sagi
                return leftRotate(root);
            }
            else{                   //!sagin solu
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        return root;
};







