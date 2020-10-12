#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#define max_que_size 20

// typedef int element; // 고객 정보를 받아야 하므로 구조체로 변경
typedef struct {
    int id;             // 고객 id
    int arrival_time;   // 고객이 들어온 시간
    int service_time;   // 고객이 요청한 일을 은행원이 처리하는 시간
}element;

typedef struct {
    // 고객 정보를 넣을 수 있는 구조체 배열 선언 
    element data[max_que_size];
    // 저장된 값이 배열의 요소를 가르킨다는 의미로 포인터라는 용어 사용?
    int front, rear;
}queType;

void error(char *msg) {
    fprintf(stderr,"%s\n", &msg);
    exit(1);
}
// 초기화
void init_que(queType *q) {
    q->front = q->rear = 0;
}

// front와 rear가 같으면 비워져 있는 것
int is_empty(queType *q) {
    return (q->front == q->rear);
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
    // 60번 반복
    int minutes = 5;
    // 평균을 나타나기 위해 고객이 기다린 전체 시간
    int total_wait = 0;
    // 평균을 나타나기 위해 고객의 총 수 
    int total_customer = 0;
    int server1_customer = 0, server2_customer = 0;
    bool server1 = true, server2 = true;
    // 은행원 2명의 서비스 시간
    int server1_service_time = 0, server2_service_time = 0;
    // 모든 고객에게 서비스하는 시간의 총 합
    int total_service_time = 0;
    // 현재 서비스 받고 있는 고객 수
    int service_customer;
    // 구조체 선언
    queType que;
    // 큐 초기화
    init_que(&que);

    srand(time(NULL));
    // 60번 반복
    for(int clock = 0; clock < minutes; clock++) {
        // 현재 시간 출력
        printf("[current time: %d]\n",clock);
        // in(고객이 들어오는 경우
        if((rand()%10) < 3) {   // rand()%10 = 0~9, 3보다 낮으면 고객이 들어왔다고 판단
            // element 구조체 변수인 customer 선언
            total_customer++;
            element customer;
            
            customer.id = total_customer; // 전체 고객 수 1 증가
            customer.arrival_time = clock;  // 고객 도착 시간
            customer.service_time = rand() % 3 + 1; // 대기시간: 1 || 2 || 3
            enque(&que, customer);
            // 고객 id, 고객이 들어온 시간, 업무처리 시간
            printf("customer: %d, time: %d, service time: %d\n",
                customer.id, customer.arrival_time, customer.service_time);

            if(server1_service_time == 0) {
                server1_customer = customer.id;
                server1_service_time = customer.service_time;
            } else if (server1_service_time > 0 && server1_service_time == 0) {
                server2_customer = customer.id;
                server2_service_time = customer.service_time;
            }
        }
         // server1,2의 서비스 시간이 비어있으면 서비스 타임 할당
        // service(은행원1이 고객에게 업무 중)
        if(server1_service_time > 0) {
            printf("server1 servicing customer: %d\n", server1_customer);
            server1_service_time--; // 랜덤으로 받은 서비스 시간(3||2||1을 하나씩 줄인다)
        } else if(server1_service_time == 0) {
            printf("server1 servicing customer: %d\n", server1_customer);
            server1_service_time--; // 랜덤으로 받은 서비스 시간(3||2||1을 하나씩 줄인다)
            if(!is_empty(&que)) {   // 비어있지 않으면 customer 구조체 변수 큐에 추가
                element customer = deque(&que);
                server1_customer = customer.id; // server1이 서비스하고 있는 고객
                server1_service_time = customer.service_time;
                //total_service_time = customer.service_time;
                printf("server1: customer %d, start time: %d, wait time: %d\n",
                    // 대기시간: 현재 시간 - 고객이 들어온 시간
                    server1_customer, clock, clock - customer.arrival_time);
                total_wait += clock - customer.arrival_time;
            }
        }
        if(server2_service_time > 0) {
                printf("server2 servicing customer: %d\n", server2_customer);
                    server2_service_time--; // 랜덤으로 받은 서비스 시간(3||2||1을 하나씩 줄인다)
            } else if(server2_service_time == 0){
                //server1 = true; 
                if(!is_empty(&que)) {   // 비어있지 않으면 customer 구조체 변수 큐에 추가
                    element customer = deque(&que);
                    server2_customer = customer.id; // server1이 서비스하고 있는 고객
                    server2_service_time = customer.service_time;
                    printf("server2: customer %d, start time: %d, wait time: %d\n",
                        // 대기시간: 현재 시간 - 고객이 들어온 시간
                        server2_customer, clock, clock - customer.arrival_time);
                    total_wait += clock - customer.arrival_time;
                }
            }
    }

    printf("total wait time = %d\n", total_wait);
    return 0;
}