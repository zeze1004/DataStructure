#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CACHE_SIZE 8192

int hit = 0;

// 데이터 참조 스트림이 저장된 파일
#define TRACE_FILE_NAME "ref_stream.txt"

typedef int element;
// 이중연결리스트의 노드 타입
typedef struct node
{
    element data, time;
    unsigned int blkno; // 블랭크 넘버: 비워져있는 노드
    struct node *next, *prev;
} node;

// 데이터를 저장할 공간을 한 번에 할당 받음
// 이후 추가적인 메모리 할당은 없음
// 할당 받은 노드들을 이용하여 LRU 리스트 또는 FIFO 리스트를 유지해야 함
struct node cache_buffer[MAX_CACHE_SIZE];

// head 전역변수로 선언
node *head = NULL; // 캐쉬가 비어있다
void init(node *phead)
{
    phead->prev = phead; // 자기자신을 가르켜서 초기화시킴
    phead->next = phead;
}

// LRU 시뮬레이터 인 경우 lrulist 아니면 fifolist를 유지하기 위한 헤드 노드 선언
#if 1
struct node lrulist;
#else
struct buffer fifolist;
#endif

void insert(element data, element time)
{
    //printf("insert\n");
    // p는 새로 추가할 노드의 위치, tail_p: 새로 값을 추가할 마지막 노드를 가르키는 포인터
    node *p, *tail_p;
    int i = 0;
    // 빈 노드 찾기
    for (; i < MAX_CACHE_SIZE; i++)
    {
        p = &cache_buffer[i];
        if (p->prev == p && p->next == p)
        { // 노드가 비워져있다, 빈 노드를 찾았다
            break;
        }
    }
    // 노드가 다 찼을 경우, 노드 하나를 지워야 함
    if (i == MAX_CACHE_SIZE)
    {   
        //printf("first full\n");
        element min_time = 100000000;
        node *min_time_p;
        // 전체 노드 순환해서 time이 제일 적은 노드를 구함
        for(p = head; p != NULL; p = p->next) {
            if(p->time < min_time) {
                min_time = p->time;
                min_time_p = p;
                //printf("1\n");
            }
        }
        p = min_time_p;
        //printf("plz\n");
        if(p == head) {
            head = head->next;
            head ->prev = NULL;
            p->next = p;
            p->prev = p;
            //printf("2\n");
        }
        else if(p->next == NULL) {
            p->prev->next = NULL;
            p->prev = p;
            p->next = p;
            //printf("3\n");
        }
        else if(p->prev != NULL && p->next != NULL) {
            p->prev->next = p->next;
            p->next->prev = p->prev;
            p->next = p;
            p->prev = p;
            //printf("4\n");
        }
        else {
            //printf("why\n");
        }
    }
    // 비워있는 노드에 데이터 쓰기
    p->data = data;
    p->time = time;
    // p와 마지막 노드 연결
    // for(p = head; p->next != NULL; p = p->next); head가 null 경우 에러
    if (head == NULL)
    { // 캐쉬가 통째로 비워져 있을 떄
        head = p;
        // p는 이제 사용하는 노드이므로 next, prev가 자기자신을 가르키게 하지 않게 한다 NULL <- p -> NULL
        p->next = NULL;
        p->prev = NULL;
    }
    else // time 값이 작은 노드를 제거하므로 삽입할 위치는 중요하지 않음
    {
        for (tail_p = head; tail_p != NULL; tail_p = tail_p->next)
        {
            if (tail_p->next == NULL)
            {
                tail_p->next = p;
                p->prev = tail_p;
                p->next = NULL;
                //printf("5\n");
                break;
            }
        }
    }
}

node *search(element data, element time) // RLU에는 매개변수 INT TIME 추가
{
    node *p;
    for (p = head; p != NULL; p = p->next)
    {
        if (p->data == data)
        {
            p->time = time;
            return p; // 노드의 주소를 반환
        }
    }
    // 찾지 못했을 때
    return NULL;
}

int main(int argc, char *argv[])
{
    element data, time = 0;
    FILE *fp = fopen(TRACE_FILE_NAME, "r");
    char buffer[20]; // 파일을 읽을 때 사용할 임시 공간

    for (int i = 0; i < MAX_CACHE_SIZE; i++)
        init(&cache_buffer[i]);

    if ((fp = fopen(TRACE_FILE_NAME, "r")) == NULL)
    {
        printf("%s trace file open fail.\n", TRACE_FILE_NAME);

        return 0;
    }
    else
    {
        printf("start simulation!\n");
        while (!feof(fp))
        {
            fgets(buffer, sizeof(buffer), fp); // 한 문자열 씩 읽기, fgetc는 글씨개수만큼 읽기
            data = (element)atoi(buffer);
            if (search(data, time) != NULL)
            {
                //printf("Data %d Found\n", data);
                hit++;
            }
            else
            {
                //printf("Data %d Not Found\n", data);
                insert(data, time);
            }
            time++; 
        }
    }
    printf("HIT: %d\n", hit);

    ////////////////////////////////////////////////
    // 시뮬레이션 시작 및 결과 출력을 위한 코드
    ////////////////////////////////////////////////

    fclose(fp);

    return 0;
}
