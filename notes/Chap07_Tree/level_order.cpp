#include <iostream>
#include <memory.h>
using namespace std;

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;  // 구조체 변수 선언
} tree_node;

// 원형큐 코드
#define MAX_QUE_SIZE 100
typedef tree_node * element;
typedef struct QueType {
    element que_data[MAX_QUE_SIZE];     // 구조체 변수 선언
    int front, rear;
} que_type;

// 오류 함수
void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 초기화
void init_que(que_type *q) {
    q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(que_type *q) {
    return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(que_type *q) {
    return ((q->rear + 1) % MAX_QUE_SIZE == q->front);
}

// 삽입 함수
void enque(que_type *q, element item) {
    if (is_full(q))
        error("que is empty");
    q->rear = (q->rear + 1) % MAX_QUE_SIZE;
    q->que_data[q->front];
}

// 삭제 함수
element deque(que_type *q) {
    if (is_empty(q))
        error("que is empty");
    q->front = (q->front + 1) % MAX_QUE_SIZE;
    return q->que_data[q->front];
}

void level_order(tree_node *ptr) {
    que_type q;
    init_que(&q); // 큐 초기화

    if (ptr == NULL) return;
    enque(&q, ptr);
    while (!is_empty(&q)) {
        ptr = deque(&q); 
        cout << ptr->data << " ";
    
    }
    
}