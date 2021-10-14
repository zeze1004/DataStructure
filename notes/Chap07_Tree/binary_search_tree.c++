#include <iostream>
#include <stdlib.h>

typedef struct NodeStruct
{
    int value;
    struct NodeStruct* leftChild;
    struct NodeStruct* rightChild;
}Node;

Node* root = NULL;

Node* BST_insert(Node* root, int value)
{
    BST_search(root, value);
        
    
    if(root == NULL)
    {
        root = (Node*)malloc(sizeof(Node));
        root->leftChild = root->rightChild = NULL;
        root->value = value;
        printf("root == NULL: %d \n", root->value);
        return root;
    }
    else
    {
        printf("??\n");
        if(root->value > value)
            root->leftChild = BST_insert(root->leftChild, value);
        else
            root->rightChild = BST_insert(root->rightChild, value);
    }
    printf("root: %d \n", root->value);
    
    return root;
}

Node* BST_search(Node* root, int value)
{
    if(root == NULL)
        return NULL;

    if(root->value == value)
        return root;
    else if(root->value > value)
        return BST_search(root->leftChild, value);
    else
        return BST_search(root->rightChild, value);
}

void BST_print(Node* root)
{
    if(root == NULL)
        return;

    printf("%d ", root->value);
    BST_print(root->leftChild);
    BST_print(root->rightChild);
}


int main()
{
    root = BST_insert(root, 5);
    root = BST_insert(root, 3);
    // root = BST_insert(root, 1);
    // root = BST_insert(root, 9);
    // root = BST_insert(root, 6);

    BST_print(root);
}