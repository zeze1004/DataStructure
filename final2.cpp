#ifdef _MSC_VER

#define _CRT_SECURE_NO_WARNINGS

#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CACHE_SIZE 8192


// 데이터 참조 스트림이 저장된 파일

#define TRACE_FILE_NAME "ref_stream.txt"

// 이중연결리스트의 노드 타입
struct buffer {
   unsigned long blkno;
   struct buffer *next, *prev;
   struct buffer *hash_next, *hash_prev;
};

// 데이터를 저장할 공간을 한 번에 할당 받음
// 이후 추가적인 메모리 할당은 없음
// 할당 받은 노드들을 이용하여 LRU 리스트 또는 FIFO 리스트를 유지해야 함

struct buffer cache_buffer[MAX_CACHE_SIZE];

// 해쉬 사이즈별로 시간 속도 차이남
// 3000으로 했을 때 0.7초로 가장 빠른 속도를 보임
#define HASH_SIZE 6144 // 전체 캐시 사이즈의 75%

struct buffer hash_table[HASH_SIZE];

// 주어진 값들을 모듈러 연산 후 버켓에 저장
unsigned long hash_function(unsigned long key) {
   return key % HASH_SIZE;
}

// LRU 시뮬레이터 인 경우 lrulist 아니면 fifolist를 유지하기 위한 헤드 노드 선언
#if 1
struct buffer lrulist;
#else
struct buffer fifolist;
#endif
unsigned long curtime, hit, miss;

// 해쉬테이블의 주소 저장
struct buffer *table_address(unsigned long blkno) {
   return &hash_table[hash_function(blkno)];
}

// lrulist 삽입 할 때 맨 앞에 넣기
// bp가 dp 앞에 삽입된다
void lruin(struct buffer *bp) {
   struct buffer *dp = &lrulist; // *dp = lrulist head
   bp->next = dp->next;
   bp->prev = dp;
   (dp->next)->prev = bp;
   dp->next = bp;
}

// 해시테이블에 추가하는 함수
void table_in(struct buffer *bp) {
   struct buffer *node = table_address(bp->blkno);
   bp->hash_next = node->hash_next;
   bp->hash_prev = node;
   (node->hash_next)->hash_prev = bp;
   node->hash_next = bp;
}

// lru output: 빼왔으니깐 포인터 반납 가장 오래된 노드 빼기
// 제일 오랫동안 참조되지 않은 값(lrulist 맨 마지막) lrulist에서 삭제
struct buffer *lruout() {
   struct buffer *bp = lrulist.prev;   // 첫 번째 노드의 이전 노드: 가장 마지막 노드
   (bp->prev)->next = bp->next;  // 가장 마지막 노드의 이전(뒤에서 두 번째 노드) 노드를 첫 번째 노드와 연결
   (bp->next)->prev = bp->prev;  // 첫 번째 노드의 이전 노드가 마지막 노드의 이전 노드(뒤에서 두 번째 노드)가 된다
   // lurlist에서 없애고 해시테이블에도 삭제한다
   (bp->hash_prev)->hash_next = bp->hash_next;
   (bp->hash_next)->hash_prev = bp->hash_prev;
   return bp;
}

//초기화
void init() {
   int i;
   // lrulist 초기화
   lrulist.next = lrulist.prev = &lrulist;
   for (i = 0; i < MAX_CACHE_SIZE; i++) {
      cache_buffer[i].blkno = -0; // 블록 번호를 전부 1로 넣음
      cache_buffer[i].next = cache_buffer[i].prev = NULL;
      cache_buffer[i].hash_next = cache_buffer[i].hash_prev = &cache_buffer[i];
      lruin(&cache_buffer[i]);
   }
   // 해시 테이블 초기화
   for (i = 0; i < HASH_SIZE; i++) {
      hash_table[i].hash_next = hash_table[i].hash_prev = &hash_table[i];
   }
   return;
}

// 테이블에 blkno 있는 지 찾기 -> O(1)
// 해쉬 테이블에 blkno있으면 해당 테이블의 주소 리턴 없으면 null
struct buffer *findblk(unsigned long blkno) {
   struct buffer *dp, *bp;
   // 해쉬테이블 저장 위치
   dp = table_address(blkno);
   // bp랑 dp 주소 같을 때까지 반복(더는 이동할 수 없을 때까지)
   for (bp = dp->hash_next; bp != dp; bp = bp->hash_next) {
      // 노드의 블록 번호와 인자로 받은 블록 번호가 같으면 노드의 포인터를 반환
      if (bp->blkno == blkno)
         return bp;
   }
   // blkno 없으면 널 리턴
   return NULL;
}

// 가장 최근에 참조된거를 lrulist 맨 앞으로 이동
// 해시테이블에서의 위치는 건드리지 않는다
void reorder(struct buffer *bp) {
   // ex.8=1=2 일 때 8과 2를 연결(=:이중연결리스트 표현)
   (bp->prev)->next = bp->next;
   (bp->next)->prev = bp->prev;
   // 1을 맨 앞으로 이동
   lruin(bp);
}

// 참조 알고리즘
// 블록 번호가 한 번 참조 될 때마다
void pgref(unsigned long blkno) {
   struct buffer *bufp;
   
   //HASHTABLE에서 데이터 있는지 검색
   bufp = findblk(blkno);
   
   // if exist in lrulist
   // blkno 있으면 lurlist 맨 앞으로 reorder
   if(bufp) {
      hit++;
      reorder(bufp);
   } 
   // blkno 없으면 lurlist 맨 뒤거 삭제한 후 맨 앞에 추가, 해시 테이블에 값 추가
   else {
      miss++;
      bufp = lruout();  // lrulist 가장 맨 뒤에 있는거 빼기
      bufp->blkno = blkno;
      lruin(bufp);      // 새로 받은 값 맨 앞에 넣기
      table_in(bufp);   // 해시 테이블에 값 추가
   }
}

int main(int argc, char *argv[]) {
   int ret;
   unsigned long blkno;
   FILE *fp = NULL;
   init();
   curtime = miss = hit = 0;
   clock_t start_time, end_time;

   if ((fp = fopen(TRACE_FILE_NAME, "r")) == NULL) {
      printf("%s trace file open fail.\n", TRACE_FILE_NAME);
      return 0;
   } else {
      printf("start simulation!\n");
      start_time = clock();
      printf("start_time: %d\n", start_time);
   }

   while ((ret = fscanf(fp, "%lu\n", &blkno)) != EOF) {
      curtime++;
      pgref(blkno);
   }
   // 참조 다 끝난 후 시간 체크
   end_time = clock();
   printf("end_time: %d\n", end_time);

   // 총 걸린 시간
   float time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
   printf("total_time: %f \n",time);

   fclose(fp);
   printf("hit ratio = %f, miss ratio = %f\n", (float)hit / (float)curtime, (float)miss / (float)curtime);
   return 0;
}