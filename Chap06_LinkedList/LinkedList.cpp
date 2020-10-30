#include <iostream>
#include <stdlib.h>
using namespace std;

typedef int element;
typedef struct node {
    element data;
    struct node* next; // 다음노드가 저장된 메모리 주소를 저장하는 포인터 변수
}node;


void error(char* message) {
    printf("%s\n",message);
    exit(1); // 프로그램 종료
}

node* insert_first(node* head,element data) {
    node* p = (node*)malloc(sizeof(node));
            // (어떤 타입으로 할당될 것인가?)malloc
    p->data = data;
    p->next = head;
    head = p;   // 새로 삽입된 포인터가 head가 됨
    return head;
}

node* insert(node* head, node* pre, element data) {
    node* p = (node*)malloc(sizeof(node));
    p->data = data;
    p->next = pre->next;
    pre->next = p;

    return head;
}

node* delete_first(node* head) {
    if(head == NULL) 
        return NULL;
    node *removed; // 링크가 끊어지지 않게 삭제될 노드를 백업해야함
    removed = head; // removed는 head가 가르키는 노드
    head = removed->next; // 삭제할 노드의 다음 노드를 헤드 포인트가 가르킴
    free(removed);

    return head;
}
// pre 다음 노드를 제거
node* ddelete(node* head, node* pre) {
    node *removed;
    removed = pre->next;
    pre->next = removed->next;
    free(removed);

    return head;
}

void print(node *head) {
    node *p;
    // head부터 null 전인 노드 끝까지 순회
    for(p = head; p != NULL; p = p->next) {
        printf("%d-> ", p->data);    
    }
    printf("NULL\n");
}

// 오름차순으로 정렬
node *insert_sort(node* head, element data) {
    node *p = (node*)malloc(sizeof(node));
    node *cur; // head 부터 순회하면서 값 비교
    p->data = data; // 초기화
    p->next = NULL; // 초기화

    if(head = NULL) {
        head = p;
        return head;
    }
    cur = head;
    // cur이 null이 아니고, cur의 다음 데이터가 현재 데이터보다 작으면 루프 탈출
    while(cur->next != NULL && cur->next->data < p->data) {
        cur = cur->next; // head부터 시작
    }
    p->next = cur->next;
    cur->next = p;

    return head;
}

int main() {
    node* head = NULL;
    for(int i = 0; i < 5; i++) {
        head = insert_first(head, i);
        print(head);
    }
    head = insert_sort(head, 8);
    head = insert_sort(head, 7);
    head = insert_sort(head, 6);
    print(head);
    for(int i = 0; i < 5; i++) {
        head = delete_first(head);
        print(head);
    }
    return 0;
}