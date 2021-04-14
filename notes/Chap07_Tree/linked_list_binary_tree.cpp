#include <iostream>
#include <stdlib.h>
#include <memory.h>
using namespace std;

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} node;

/*
    n1
    |\
  n2 n3
*/

int main() {
    node *n1, *n2, *n3;
    n1 = (node *)malloc(sizeof(node));
    n2 = (node *)malloc(sizeof(node));
    n3 = (node *)malloc(sizeof(node));

    // 첫 번째 노드 설정
    n1->data = 10; 
    n1->left = n2;
    n1->right = n3;
    // 두 번째 노드 설정
    n2->data = 20; 
    n1->left = NULL;
    n1->right = NULL;
    // 세 번째 노드 설정
    n1->data = 30; 
    n1->left = NULL;
    n1->right = NULL;
    
    free(n1); free(n2); free(n3);

    return 0;
}