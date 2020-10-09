#include <iostream>
#define max_queue_size 5
using namespace std;

// 큐에 들어갈 원소는 인트로 제한
typedef int element;
typedef struct {
    int front;
    int  rear;
    element data[max_queue_size];
} Qtype;

void error(char *message) {
    cout << 
}