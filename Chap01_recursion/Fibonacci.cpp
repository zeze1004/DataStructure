#include <iostream>

int fib(int n) {
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    int pp = 0;
    int p = 1;
    int result = 0;

    for(int i = 2; i <= n; i++) {
        result = p + pp;
        pp = p;
        p = result;
    }
    return result;
}

int main() {




    return 0;
}