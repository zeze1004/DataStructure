#include <stdio.h>
#include <math.h>

int for_pow(int x, int n) {
    int result = 1;
    for(int i = 0; i < n; i++) 
        result = result * x;
    return result;
}

int recursive_pow(int x, int n) {
    if(n==0) {    
        return 1;
    }
    else if (n%2 == 0) {
        printf("%d\n",pow(x*x,n/2));
        return pow(x*x,n/2);
    }
    else{
        printf("%d\n",pow(x*x,n/2));
        return pow(x*x,(n-1)/2);      
    }  
}
int main() {
    int x,n;
    scanf("%d %d",&x, &n);
    recursive_pow(x,n);

    return 0;
}
