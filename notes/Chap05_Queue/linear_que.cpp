#include <iostream>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5
using namespace std;

typedef int element;
typedef struct que
{
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
};

// 오류 출력
void error(char *message) {
    fprintf(stderr, "%s/n", message); // fprintf(파일포인터, "출력인수", char *format)
    exit(1);
}

void init_que(que *q) {
    q->rear = -1;
    q->front = -1;
}

void print_que(que *q) {
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
        if (i <= q->front || i > q->rear)
            cout << " | ";
        else
            cout << q->data[i] << " | ";
    }
    cout << '\n';
}

int is_full(que *q) {
    if (q->rear == MAX_QUEUE_SIZE - 1)
        return 1;
    else
        return 0;
}

int main() {

    return 0;
}




