#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <time.h>

#define	MAX_CACHE_SIZE		8192

// 데이터 참조 스트림이 저장된 파일 
#define TRACE_FILE_NAME		"ref_stream.txt"


// 이중연결리스트의 노드 타입
struct buffer {
	unsigned long blkno;    // 블록번호
	struct buffer* next, * prev;
};


// 데이터를 저장할 공간을 한 번에 할당 받음
// 이후 추가적인 메모리 할당은 없음
// 할당 받은 노드들을 이용하여 LRU 리스트 또는 FIFO 리스트를 유지해야 함 
struct buffer cache_buffer[MAX_CACHE_SIZE];


// LRU 시뮬레이터 인 경우 lrulist 아니면 fifolist를 유지하기 위한 헤드 노드 선언
#if 1
struct buffer lrulist;
#else
struct buffer fifolist;
#endif

unsigned long curtime, hit, miss;

// lru insert: 헤드 다음에 넣기
void lruin(struct buffer* bp) { // bp가 dp의 next가 됨
    struct buffer* dp = &lrulist;   // lrulist head
    bp->next = dp->next;
    bp->prev = dp;
    (dp->next)->prev = bp;
    dp->next = bp;
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

void init() {
    int i;
    lrulist.next = lrulist.prev = &lrulist;
    for(i = 0; i < MAX_CACHE_SIZE; i++) {
        cache_buffer[i].blkno = -0; // 블록 번호를 전부 1로 넣음
        cache_buffer[i].next = cache_buffer[i].prev = NULL;

        lruin(&cache_buffer[i]);
    }
    return;
}

// 버퍼에 blkno 있는 지 찾기 -> O(n)
struct buffer *finblk(unsigned long blkno)
{
    struct  buffer* dp ,* bp;
    dp = &lrulist;
    for(bp = dp->next; bp != dp; bp = bp->next) {
        // 노드의 블록 번호와 인자로 받은 블록 번호가 같으면 노드의 포인터를 반환
        if(bp->blkno == blkno)
            return bp;
    }
    return NULL;
}

// 현재 위치에서 빼서 rluin() 하면 맨 앞으로 이동
void reorder(struct buffer* bp)
{
    (bp->prev)->next = bp->next;
    (bp->next)->prev = bp->prev;
    // bp 반납하고 앞으로 이동
    lruin(bp);
}

// 블록 번호가 한 번 참조 될 때마다
void pgref(unsigned long blkno) {
    struct buffer* bufp; // 버퍼 포인터
    
    bufp = finblk(blkno);
    // if exist in lrulist
    if(bufp) { // bufp가 있으면 hit
        hit++; 
        // hit 됐으니깐 lrulist의 맨 앞으로 보냄
        reorder(bufp);
    }
    // else
    else {
        miss++;
        bufp = lruout();
        bufp->blkno = blkno;
        lruin(bufp);
    }
}

int main(int argc, char* argv[])
{
	int	ret;
	unsigned long blkno;
	FILE* fp = NULL;

	init();
    clock_t start_time, end_time;

	if ((fp = fopen(TRACE_FILE_NAME, "r")) == NULL) {
		printf("%s trace file open fail.\n", TRACE_FILE_NAME);

		return 0;
	}
	else {
		printf("start simulation!\n");
        start_time = clock();
        printf("start_time: %d\n", start_time);
	}

    // unsigned long %lu
	while (fscanf(fp,"%lu\n", &blkno) != EOF)
    {
        curtime++;
        pgref(blkno);
    }
    end_time = clock();
    printf("end_time: %d\n", end_time);

    float time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
    printf("total_time: %f \n",time);
        
	fclose(fp);
    printf("hit ratio: %f \n",(float)hit/(float)curtime);
	return 0;
}
