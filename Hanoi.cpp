#include <stdio.h>
int count1  = 0;
int count2  = 0;
int count3  = 0;
void hanoi(int n, char from, char tmp, char to) {       
    if(n==1){   
        // 어느 원반이 어느 기둥에서 어느 기둥으로 옮기는지 출력        
        printf("%d를 %c에서 %c로 옮기다 \n", n,from,to);
    } else {    
        // 마지막 원반을 제외한 n-1개 원반을 A에서 C를 이용해 B로 이동
        hanoi(n-1,from,to,tmp);                                             
        printf("%d를 %c에서 %c로 옮기다 \n", n,from,tmp);   
        //  n-1 원반을 B에서 A를 이용해 C로 이동
        hanoi(n-1,tmp,from,to);                         
    }
}

int main() {

    hanoi(4, 'A','B','C');
    return 0;
}