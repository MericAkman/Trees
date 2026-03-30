#include<stdio.h>
#include<stdlib.h>

struct treeNode{
    struct treeNode* left;
    struct treeNode* right;
    void* val;
};

struct Tree{
    int count;
    int (*compare)(void* arg1, void* arg2);
    struct treeNode* root;
};

struct treeNode* nodeCreator(void* val){
    struct treeNode* node = (struct treeNode*)malloc(sizeof(treeNode));

    if(node){
        node->left=NULL;
        node->right=NULL;
        node->val=val;
    }

    return node;
};

struct Tree* treeCreator(int(*compare)(void* arg1,void* arg2)){
    struct Tree* tree = (struct Tree*)malloc(sizeof(struct Tree));

    if(tree){
        tree->count=0;
        tree->root=NULL;
        tree->compare=compare;
    }

    return tree;
};

struct treeNode* InsertNode(struct Tree* tree,struct treeNode* root,struct treeNode* node){

    if(root==NULL){
        return node;
    }

    if(tree->compare(root->val,node->val) > 0){
        root->left = InsertNode(tree,root->left,node);
    }
    if(tree->compare(root->val,node->val) < 0){
        root->right = InsertNode(tree,root->right,node);
    }

    return root;
};

void InsertToTree(struct Tree* tree,void* val){

    struct treeNode* node = nodeCreator(val);

    if(tree->root==NULL){
        tree->root=node;
        return;
    }

    InsertNode(tree,tree->root,node);

    (tree->count)++; //!
}

struct treeNode* findMin(struct treeNode* root){

    struct treeNode* temp = root;

    while(temp->left){
        temp=temp->left;
    }

    return temp;
};

struct treeNode* deleteNode(struct Tree* tree,struct treeNode* root,void* val){

    if(root==NULL){
        return root;
    }


    if(tree->compare(root->val,val) > 0){
        root->left = deleteNode(tree,root->left,val);
    }
    else if(tree->compare(root->val,val) < 0){
        root->right = deleteNode(tree,root->right,val);
    }
    else{
        if(root->left==NULL || root->right==NULL){
            struct treeNode* temp;
            if(root->left==NULL){
                temp = root->right;
            }
            else{
                temp = root->left;
            }
            free(root);
            return temp;
        }
        else{
            struct treeNode* replaceNode = findMin(root->right);
            root->val = replaceNode->val;
            root->right=deleteNode(tree,root->right,replaceNode->val);
        }
    }
    return root;    //!
};






