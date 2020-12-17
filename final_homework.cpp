#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

#define	MAX_CACHE_SIZE		8192

// 데이터 참조 스트림이 저장된 파일 
#define TRACE_FILE_NAME		"ref_stream.txt"

#define TABLE_SIZE 7 // 해싱테이블 크기는 소수

// 모듈러
int hash_func(int key) {
    return key % TABLE_SIZE;
}

// 이중연결리스트의 노드 타입
struct buffer {
	unsigned long blkno;    // 블록번호
	struct buffer* next, * prev;
    struct buffer* hash_next, * hash_prev;    
};

// 데이터를 저장할 공간을 한 번에 할당 받음
// 이후 추가적인 메모리 할당은 없음
// 할당 받은 노드들을 이용하여 LRU 리스트 또는 FIFO 리스트를 유지해야 함 
struct buffer cache_buffer[MAX_CACHE_SIZE];


// hash table
#define HASH_SIZE 6114
struct buffer *hash_table[HASH_SIZE];


// LRU 시뮬레이터 인 경우 lrulist 아니면 fifolist를 유지하기 위한 헤드 노드 선언
#if 1
struct buffer lrulist;
#else
struct buffer fifolist;
#endif

unsigned long curtime, hit, miss;

// lru insert: 헤드 다음에 넣기
void lruin(struct buffer* bp) { // bp가 dp의 next가 됨
    struct buffer* dp = *hash_table;   // hash_table head
    bp->hash_next = dp->hash_next;
    bp->hash_prev = dp;
    (dp->hash_next)->hash_prev = bp;
    dp->hash_next = bp;
};

// lru output: 빼왔으니깐 포인터 반납 가장 오래된 노드 빼기
struct buffer *lruout() {
    struct buffer* bp;
    bp = lrulist.prev;  // 리스트의 맨끝,가장 오래 전에 참조
    // 가장 오래 전에 참조된 bp를 반납
    (bp->prev)->next = bp->next;
    (bp->next)->prev = bp->prev;
    return bp;
}

void init(struct buffer* bp) {
    int i;
    struct buffer* bp = hash_table[0];
    bp->hash_next = bp->hash_prev = hash_table[0];
    for(i = 0; i < HASH_SIZE; i++) {
        cache_buffer[i].blkno = -0; // 블록 번호를 전부 1로 넣음
        cache_buffer[i].next = cache_buffer[i].prev = NULL;

        lruin(hash_table[i]);
    }
    return;
}

// 버퍼에 blkno 있는 지 찾기 -> O(n)
// 체이싱
// 많이 바꿔야 함
struct buffer *finblk(unsigned long blkno)
{
    struct  buffer* dp ,* bp;
    dp = &lrulist;
    // O(n) 검색하는 걸 해쉬테이블을 이용해 어떻게 줄일지
    for(bp = dp->next; bp != dp; bp = bp->next) {
        // 노드의 블록 번호와 인자로 받은 블록 번호가 같으면 노드의 포인터를 반환
        if(bp->blkno == blkno)
            return bp;
    }
    return NULL;
}

// 맨 끝으로 이동
void reorder(struct buffer* node, struct buffer *ht[], int hash_value) {
    // 이미 맨 끝이면 return
    if(node->hash_next == NULL) {
        return;
    }
    struct buffer* prev_node = node;
    for(node = ht[hash_value]; (node->hash_next) == NULL; node->hash_next) {
        if((node->hash_next) == NULL) {
            (prev_node->next) = ht[hash_value];
            ht[hash_value]->hash_next = (prev_node->next);
            node->hash_next = prev_node->hash_prev;
            prev_node->hash_prev = node->hash_next;
        }
    }
    // bp 반납하고 앞으로 이동
    // lruin(bp);
}

// 블록 번호가 한 번 참조 될 때마다
// 많이 바꿔야 함
void pgref(unsigned long blkno, struct buffer *ht[]) {
    struct buffer* bufp; // 버퍼 포인터
    int hash_value = hash_func(blkno);

    struct buffer *ptr;
    struct buffer *node_prev = NULL;
    struct buffer * node;

    for(node = ht[hash_value]; node; node_prev = node, node = node->hash_next) {
        (node->hash_next) = node_prev->hash_prev;
        (node->hash_prev) = node->hash_next;
        if(node->blkno == blkno) {
            fprintf(stderr, "already add\n");
            hit++;
            node_prev->hash_next = NULL;
            reorder(node_prev, ht, hash_value); // 맨 끝으로 보내기
            return;
        }
    }

    // 탐색키가 없을 시
    ptr = (struct buffer *)malloc(sizeof(struct buffer));
    ptr->blkno = blkno;
    ptr->next = NULL;
    // 링크 추가
    if(node_prev) { // 같은 버킷에 이미 키가 있다면 연결 리스트 맨 끝에 새로운 키를 포함하는 새로운 노드를 연결
        node_prev->hash_next = ptr;
        ptr->hash_prev = node_prev;
        printf("making next node: %d\n",ptr->blkno);
        miss++;
    }
    else {   // 버킷에 연결된 리스트가 없다면 해시테이블의 포인터에 새로운 노드 연결 
        ht[hash_value] = (ptr->hash_prev);
        printf("making new node: %d\n",ptr->blkno);
        miss++;
    }
}

int main(int argc, char* argv[]) {
    printf("1\n");
	int	ret;
	unsigned long blkno;
	FILE* fp = NULL;

	init(*hash_table);
    printf("2\n");
	if ((fp = fopen(TRACE_FILE_NAME, "r")) == NULL) {
		printf("%s trace file open fail.\n", TRACE_FILE_NAME);

		return 0;
	}
	else {
		printf("start simulation!\n");
	}

    // unsigned long %lu
	while (fscanf(fp,"%lu\n", &blkno) != EOF) {
        curtime++;
        blkno = hash_func(blkno);
        pgref(hash_func(blkno), hash_table);
    }
    
	fclose(fp);
    printf("total access: %lu, hit: %lu, miss: %lu \n", curtime, hit, miss);
    printf("hit ratio: %f \n",(float)hit/(float)curtime);
	return 0;
}
