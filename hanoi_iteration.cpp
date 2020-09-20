#include <iostream>
#include <stack>
using namespace std;

void hanoi(int n, char from, char tmp, char to) {
    // int형 stack 호출
    stack<int> s; 
    while (1)
    {
        while(n>1) {     // N= 3,2 , 반복문 두 번 돈다 
			/*
			C
			B
			A
			4
			*/
            s.push(n), 
            s.push(from),
			s.push(tmp),
            s.push(to);
			// 2
            n = n - 1;                   
        }
		// 원반 
        cout << "원반 " << n << "을 " << from << "에서 " << tmp <<" 로 이동시킨다." << '\n';
        
		if (s.size()) {
            to = s.top(),
			     s.pop();

			from = s.top(),
			       s.pop();
			
			n = s.top(),
			    s.pop();
            
            cout << "원반 " << n << "을 " << from << "에서 " << to <<" 로 이동시킨다." << '\n'; 
            n = n-1;
		}
		else {
			break;
		}
    }
}

int main() {
   hanoi(4, 'A','B','C');
    return 0;
}