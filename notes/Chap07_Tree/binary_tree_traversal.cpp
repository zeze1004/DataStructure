#include <iostream>
#include <stdlib.h>
#include <memory.h>
using namespace std;

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} node;

// 전위순회
void preorder(node *root) {
    if (root != NULL) {
        cout << root->data << ' ';     // 노드 방문
        preorder(root->left);           // 왼쪽 서브트리 순회
        preorder(root->right);          // 오른쪽 서브트리 순회
    }
}

// 중위순회
void inorder(node *root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << ' ';
        inorder(root->right);
    }
}

// 후위순회
void postorder(node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << ' ';   
    }
}

// malloc을 사용하지 않고 정적으로 이진트리 생성, 실제로는 사용x

/*
            15
        4       20
     1       16   25
*/
node n1 = {1, NULL, NULL};
node n2 = {4, &n1, NULL};
node n3 = {16, NULL, NULL};
node n4 = {25, NULL, NULL};
node n5 = {20, &n3, &n4};
node n6 = {15, &n2, &n5};
node *root = &n6;

int main() {
    cout << "전위 순회 = ";
    preorder(root);
    cout << '\n';

    cout << "중위 순회 = ";
    inorder(root);
    cout << '\n';

    cout << "후위 순회 = ";
    postorder(root);
    cout << '\n';

    return 0;
}