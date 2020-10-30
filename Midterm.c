#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define   MAX_CACHE_SIZE      8192
int index = 0, hit = 0;

// 데이터 참조 스트림이 저장된 파일 
#define TRACE_FILE_NAME      "ref_stream.txt"


typedef long element;
// 이중연결리스트의 노드 타입
typedef struct node {
	element data;
   	unsigned long blkno;	// 블랭크 넘버
   	struct node* next, * prev;
} node;

// 데이터를 저장할 공간을 한 번에 할당 받음
// 이후 추가적인 메모리 할당은 없음
// 할당 받은 노드들을 이용하여 LRU 리스트 또는 FIFO 리스트를 유지해야 함 
struct node cache_buffer[MAX_CACHE_SIZE];

// head 전역변수로 선언
node *head = &cache_buffer[0];
void init(node* phead) {
    phead->prev = phead;    // 자기자신을 가르켜서 초기화시킴
    phead->next = phead;
}

// LRU 시뮬레이터 인 경우 lrulist 아니면 fifolist를 유지하기 위한 헤드 노드 선언
#if 1
struct node lrulist;
#else 
struct buffer fifolist;
#endif 


// 메모리 할당 위해 노드를 배열에 하나 씩 추가
int memory(node* newnode, element data) {
	if (index != MAX_CACHE_SIZE) {
	index++; 
	newnode = &cache_buffer[index];
	}
	// 버퍼가 꽉 찾을 시
	else {
		// fifo 삭제, 삽입
		deque(&cache_buffer[index]);
		insert(newnode, data);
	}
}

void insert(head, element data) {
    node* newnode; // 새로운 노드를 위한 포인터 선언
    // search에서 같은 값 있으면 함수 리턴
	if(search(head, element data) == 1) {
		hit++; 
		return;
	}
	newnode = memory(newnode);
	
    // 4개의 포인터 조작
    // 1. 새로 삽입될 노드의 두 포인터 변경
    newnode->data = data;
    newnode->prev = head; 
    newnode->next = head->next; 
    // 2. 새로 삽일되는 노드를 가리키는 두 개의 포인터 변경
    head->next->prev = newnode; // 비포의 다음 노드의 이전노드를 뉴노드로 바꿈
    head->next = newnode;
}

node* search(node *head, element data) {
    node* p;
    for(p = head -> next; p!=head; p=p->next) {
        if(p->data == data)
            return 1;
        // 찾지 못했을 때
        return NULL;
    }    
}
// 가장 먼저 들어온 꼬리 삭제
void deque(node *tail) {
	node *tmp = tail;
	tail = tail->prev;
	tmp->data = NULL; // 꼬리 데이터 삭제
}
void enque(node *newnode)

int main(int argc, char* argv[])
{
    int   ret;
    unsigned long blkno;
    node* head;
    FILE* fp = fopen(TRACE_FILE_NAME, "r");
    char buffer[20]; // 파일을 읽을 때 사용할 임시 공간 
    
    
    init(head);

    if ((fp = fopen(TRACE_FILE_NAME, "r")) == NULL) {
        printf("%s trace file open fail.\n", TRACE_FILE_NAME);

        return 0;
    }
    else {
        printf("start simulation!\n");
        fgets(buffer, sizeof(buffer), fp);

    }

    ////////////////////////////////////////////////
    // 시뮬레이션 시작 및 결과 출력을 위한 코드
    ////////////////////////////////////////////////
        
    fclose(fp);

    return 0;
}
