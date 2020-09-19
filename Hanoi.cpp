#include <stdio.h>

void hanoi(int n, char from, char tmp, char to) {
    if(n==1){
        printf("%d를 %c에서 %c로 옮기다 \n", n,from,to);
    } else {
        hanoi(n-1,from,to,tmp);
        printf("%d를 %c에서 %c로 옮기다 \n", n,from,tmp);
        hanoi(n-1,tmp,from,to);
    }
}

int main() {

    hanoi(4, 'A','B','C');
    return 0;
}