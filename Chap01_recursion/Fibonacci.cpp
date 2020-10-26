#include <iostream>

int fib(int n) {
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    int pp = 0; // (n-2)
    int p = 1;  // (n-1)
    int result = 0;

    for(int i = 2; i <= n; i++) {
        result = p + pp; // (n-2) + (n-1)
        pp = p;
        p = result;
    }
    return result;
}

int main() {
    int x;
    scanf("%d",&x);
    printf("%d",fib(x));


    return 0;
}