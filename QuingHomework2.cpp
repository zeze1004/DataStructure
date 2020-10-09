#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define max_que_size 20

// typedef int element; // 고객 정보를 받아야 하므로 구조체로 변경
typedef struct {
    int id;
    int arrival_time;
    int service_time;
}element;

typedef struct {
    element data[max_que_size];
    // 저장된 값이 배열의 요소를 가르킨다는 의미로 포인터라는 용어 사용?
    int front, rear;
}queType;

void error(char *msg) {
    printf("%d\n", &msg);
    exit(1);
}

void init_que(queType *q) {
    q->front = q->rear = 0;
}

// front와 rear가 같으면 비워져 있는 것
int is_empty(queType *q) {
    if(q->front == q->rear)
        return 1;
    else 
        return 0;
}

// 
int is_full(queType *q) {
    return ((q->rear+1) % max_que_size == q->front);
}


// 큐에 추가
void enque(queType *q, element item) {
    // 큐가 꽉 찾는지 보기
    if(is_full(q)) {
        error("que full\n");
    }
    q->rear = (q->rear + 1) % max_que_size;
    q->data[q->rear] = item;
}

element deque(queType* q) {
    if(is_empty(q)) {
        error("que empty\n");
    }
    q->front = (q->front+1) % max_que_size;
    return q->data[q->front];
}

int main() {
    int minutes = 60;
    int total_wait = 0;
    int total_customer = 0;
    int service_time = 0;
    int service_customer;
    queType que;

    init_que(&que);

    for(int clock = 0; clock < minutes; clock++) {
        printf("current time: %d\n",clock);
        // in
        if((rand()%10) < 3) {   // rand()%10 = 0~9
            element customer;
            customer.id = total_customer++;
            customer.arrival_time = clock;
            customer.service_time = rand() % 3 + 1;
            enque(&que, customer);

            printf("customer: %d, time: %d, service time: %d\n",
                customer.id, customer.arrival_time, customer.service_time);
        }
        // service
        if(service_time > 0) {
            printf("servicing customer: %d\n", service_customer);
            service_time--;
        } 
        // free 창구에서 은행원 쉬는 중
        else
        {
            if(!is_empty(&que)) {
                element customer = deque(&que);
                service_customer = customer.id;
                service_time = customer.service_time;
                printf("customer %d, start time: %d, wait time: %d\n",
                    customer.id, clock, clock - customer.arrival_time);

                total_wait += clock - customer.arrival_time;
            }
        }
    }
    printf("total wait time = %d\n", total_wait);
    return 0;
}