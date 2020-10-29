#include <iostream>
#include <stdlib.h>
using namespace std;

// 노드 타입
typedef int element;
typedef struct node {
    element data;
    struct node* prev;
    struct node* next;
} node;

// 리스트 초기화 
void init(node* phead) {
    phead->prev = phead;    // 자기자신을 가르켜서 초기화시킴
    phead->next = phead;
}

void insert(node* before, element data) {
    node* newnode; // 새로운 노드를 위한 포인터 선언
    newnode = (node *)malloc(sizeof(node));
    // 4개의 포인터 조작
    // 1. 새로 삽입될 노드의 두 포인터 변경
    newnode->data = data;
    newnode->prev = before; 
    newnode->next = before->next; 
    // 2. 새로 삽일되는 노드를 가리키는 두 개의 포인터 변경
    before->next->prev = newnode; // 비포의 다음 노드의 이전노드를 뉴노드로 바꿈
    before->next = newnode;
}

void deleted(node *phead, node *removed) {
    if(removed == phead)
        return;
    // 삭제될 노드를 가리키고 있던 두 개의 포인터를 변경
    removed->prev->next = removed->next;
    removed->next->prev = removed->prev;
    free(removed);
}

// 특정값을 가지고 있는 노드를 검색해서 그 노드의 포인터를 반환하는 함수
node* search(node* phead, element data) {
    node* p;
    for(p = phead -> next; p!=phead; p=p->next) {
        if(p->data == data)
            return p;
        // 찾지 못했을 때
        return NULL;
    }    
}
void print(node *phead) {
    node* p; // 임시 포인터 선언
    // 오른쪽으로 순회(next)
    // 헤드포인터부터 next 노드로 이동
    // p가 다시 phead로 오기 전까지 반복
    for(p = phead -> next; p!=phead; p=p->next) {
        printf("<- %d -> ", p->data);
    }
    /* while문 버전
    p=phead->next
    while(p != phead) {
        printf("<- %d ->", p->data)
        p=p->next;
    }
    */
    printf("\n");
}

int main() {
    node* head;
    element data;
    head = (node*)malloc(sizeof(node));
    init(head);

    insert(head,1);
    insert(head,2);
    insert(head,3);
    print(head);

    printf("write down the number you want to find: \n");
    scanf("%d", &data);
    if(search(head, data) != NULL) {
        printf("in list\n");
    } else {
        printf("%d is not in list\n", data);
        insert(head,data);
        print(head);
    }    



    return 0;
}