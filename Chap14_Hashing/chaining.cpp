#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 7 // 해싱테이블 크기는 소수
#define SIZE 5

typedef struct {
    int key;
} element;

struct list {
    element item;
    struct list *next;
};

struct list *hash_table[TABLE_SIZE];

// 모듈러
int hash_func(int key) {
    return key % TABLE_SIZE;
}

// 체인법을 이용해 테이블에 키 삽입
void add(element item, struct list *ht[]) {
    int hash_value = hash_func(item.key);   // struct list 포인터 변수가 매개변수로 들어오니깐 struct list -> item -> key로 접근
    struct list *ptr;
    struct list *prev = NULL;
    // node가 ht[hash_value]의 head, hash_value = 탐색키
    struct list *node;  
    /*  
    if(node == ht[hash_value]) {
        printf("node: %d ht: %d\n",node, ht[hash_value]);
    }
    */
    // printf("node's item.key: %d\n",node->item.key); // 웨 출력 안되징
    for(node = ht[hash_value]; node; prev = node, node = node->next) {
        if(node->item.key == item.key) {
            fprintf(stderr, "already add\n");
            return;
        }
    }
    // 탐색키가 없을 시
    ptr = (struct list *)malloc(sizeof(struct list));
    ptr->item = item;
    ptr->next = NULL;
    // 링크 추가
    if(prev) { // 같은 버킷에 이미 키가 있다면 연결 리스트 맨 끝에 새로운 키를 포함하는 새로운 노드를 연결
        prev->next = ptr;
        // prev->item.key = ptr->item.key; 이전 값이 다음에 들어오는 키값으로 저장 
        printf("making next node: %d\n",ptr->item.key);
    }
    else {   // 버킷에 연결된 리스트가 없다면 해시테이블의 포인터에 새로운 노드 연결 
        ht[hash_value] = ptr;
        printf("making new node: %d\n",ptr->item.key);
    }

}

// 체인법을 이용해 테이블에 저장된 키 탐색
void search(element item, struct list *ht[]) {
    struct list *node;
    int hash_value = hash_func(item.key);
    // list의 헤더 부터 다음 next 있는 지 검색
    for(node = ht[hash_value]; node; node = node->next) {
        if(node->item.key == item.key) {
            fprintf(stderr, "search: %d success \n", item.key);
            return;
        }
    }
    printf("no find key\n");
}

void print(struct list *ht[]) {
    struct list * node;
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]->", i);
        for(node = ht[i]; node; node = node->next) {
            printf("%d->", node->item.key);
        }
        printf("\n");
    }    
}

int main() {
    int data[SIZE] = {8, 8, 9, 6, 13};
    element e;

    for(int i = 0; i < SIZE; i++) {
        e.key = data[i];
        add(e, hash_table);
        print(hash_table);
    }
    for(int i = 0; i < SIZE; i++) {
        e.key = data[i];
        search(e, hash_table);
    }
    return 0;
}