#include <stdio.h>
#include <stdlib.h>
#define max_que_size 100


typedef int element;
element data[max_que_size];
int front;
int rear;

void error(char* str) {
    printf("%s", &str);
    exit(1);
}

void init_que() {front = rear = 0;}
int is_empty() {return front == rear;}
int is_full() {return front == (rear + 1) % max_que_size;}
int size() {return (rear - front + max_que_size) % max_que_size;}

void enque(element val) {
    if(is_full())
        error("포화상태");
    rear = (rear + 1) % max_que_size;
    scanf("%d", &val);
    data[rear] = val;
}

element deq() {
    if(is_empty()) {
        error("큐 공백 에러");
    front = (front + 1) % max_que_size;
    return data[front];
    }
}

element peek() {
    if(is_empty()) 
        error("큐 공백 에러");
    return data[(front+1) % max_que_size];
}

void print_que(char msg[]) {
    int max = rear;
    if(front >= rear)
        max += max_que_size;
    printf("%s[%2d]= ", msg, size());
    for(int i = front + 1; i <= max; i++) {
        printf("%2d ", data[i % max_que_size]);
    }
    printf("\n");
}


int main() {
    init_que();
    element que;
    char msg[100];
    for(int i = 0; i < max_que_size; i++) {
        enque(i);
    }
    print_que("aaaa");
    return 0;
    
}