#include <stdio.h>
#include <stdlib.h>
#define max_que_size 5

using namespace std;

// int를 element라는 이름으로도 선언할 수 있게 rename
// 이렇게 하는 이유는 element로 선언한 변수들이 여러 개일 시, element의 자료형만 바꾸면 싹 다 바꿀 수 있기에 편하다
typedef int element;
typedef struct {
    element data[max_que_size]; // data라는 배열 선언
    int front, rear;
} QueType;

// ******오류함수 존나 모임?
void error(char *message) {
    // 문자열 입력 받을 거 웨 fprintf임?
    fprintf(stderr, "%s\n",message);
    exit(1);
}

// 공백 상태 검출 함수
void init_que(QueType *q) { // 화살표 연산자로 구조체 멤버에 접근하여 값 할당
    q->front = q->rear = 0;
}
/*
막간 struct pointer 변수로 화살표 연산자 사용법

typedef struct {
    char name[20];  // 구조체 멤버들
    int age;
    char address[100];
} person; // person이라는 구조체 선언

int main() {
    // 구조체 포인터 선언, 메모리 할당
    person *p = malloc(sizeof(struct person));
    strcpy(p ->name, "zeze");   // strcpy(): 문자열 복사
    p->age = 27;
    cout >> p->name >> p->age ; // zeze27
    free(p);
    return 0; 
}
*/
// C 언어는 bool 타입이 없어서 int로 1(true), 0(false) 결정
// 공백 상태 검출 함수
int is_empty(QueType *q) {
    return (q->front == q->front);
}

// 포화 상태 검출 함수
int is_full(QueType *q) {
    // front는 모듈러 안해줘도 되지만
    // rear는 인덱스를 뛰어넘을 수 있어서 모듈러 연산 필요
   return((q->rear+1) % max_que_size == q->front); 
}

// 원형큐 출력 함수
void que_print(QueType *q) {
    printf( "Que: front = %d, rear = %d", q->front, q->rear);
    // que가 비어있지 않으면 if문 실행
    if(!is_empty(&q)) {
        int i = q->front;
        do {
            i = (i + 1) % max_que_size;
            printf(q->data[i]);
            // i가 rear까지 갔으면 다 출력한거이므로 break
            if(i == q->rear)
                break;
        } while (i != q->front);
    } 
    printf("\n");
}

void enque(QueType *q, element item) {
    if(is_full(q))
        error("큐가 포화상태입니다");
    q->front = (q->front + 1) % max_que_size;
    return q->data[q->front];
}

element deque(QueType *q) {
    if(is_empty(&q))
        error("큐가 공백상태입니다");
    q->front = (q->front+1) % max_que_size;
    return q->data[q->front];
}

int main() {
    QueType que;
    int element;
    init_que(&que);
    cout << "데이터 추가 단계" << '\n';
    while (!is_full(&que)) {
        cout << "정수를 입력하시오: ";
        cin >> element;
        enque(&que, element);
        que_print(&que);
    }
    cout << "큐는 포화상태입니다" << '\n\n';

    cout << "데이터 삭제 단계" << '\n';
    while(!is_empty(&que)) {
        element = deque(&que);
        cout << "꺼내진 정수: " << element << '\n';
        que_print(&que);
    }
    cout << "큐는 공백상태입니다" << '\n';
    return 0;
}