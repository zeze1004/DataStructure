#include <stdio.h>

int factorial(int n) {
    if(n <= 1)  
        return 1;
    else {
        
        return (n*factorial(n-1));
    } 
}

int main() {
    int input;
    scanf("%d",&input);
    printf("%d",factorial(input));
    int v = 1;
    // 모든 재귀함수는 반복문으로 표현 가능
    for(int i = 1; i <= input; i++) {
        v*=i;
        printf("%d\n",v);
    }

    return 0;
}