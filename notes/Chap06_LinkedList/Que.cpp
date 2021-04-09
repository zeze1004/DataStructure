#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX_CACHE_SIZE 100

typedef int element;
// 큐의 노드 타입
typedef struct node {
    element data;
    struct node *next;
} node;

struct node cache_buffer[MAX_CACHE_SIZE];

// 큐 ADT 구현
typedef struct {
    node *front, *rear;
} queNode;

// 초기화
void init(queNode *q) {
    q->front = q->rear;
}

// 삽입함수
void enque(queNode *q, element data) {
    queNode *tmp = cache_buffer[MAX_CACHE_SIZE];
}

int main() {

    return 0;
}