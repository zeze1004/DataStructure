#include <iostream>
#include <time.h>
// clock은 초당 클럭 횟수로 측정, time은 초 단위 측정
int main() {
    // clock_t start, stop;
    time_t start, stop;
    double duration;
    // 측정시작
    // start = clock();
    start = clock();
    for ( int i = 0; i<1000000; i++) {
        // 측정 종료
        // stop = clock();
        stop = time(NULL);
    } 
    // duration = (double) (stop - start) / CLOCKS_PER_SEC;
    duration = (double)difftime(stop, start);
    printf("수행시간은 %f초 입니다 \n",duration);


    return 0;
}