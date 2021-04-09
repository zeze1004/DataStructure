#include <iostream>
using namespace std;

void hanoi(int n, char from, char tmp, char to) {       
    if(n==1){   
        // 어느 원반이 어느 기둥에서 어느 기둥으로 옮기는지 출력        
        cout << n << " :" <<from <<"->" << to <<'\n';
    } else {    
        // 마지막 원반을 제외한 n-1개 원반을 A에서 C를 이용해 B로 이동
        hanoi(n-1,from,to,tmp);                                             
        cout << n << " :" <<from <<"->" << to <<'\n';
          
        //  n-1 원반을 B에서 A를 이용해 C로 이동
        hanoi(n-1,tmp,from,to);                         
    }
}

int main() {

    hanoi(4, 'A','B','C');
    return 0;
}