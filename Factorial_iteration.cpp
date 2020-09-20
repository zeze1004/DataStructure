#include <iostream>
using namespace std;

int factorial(int num) {
    int result=1;
    for(int i = 1; i <= num; i++) {
        result=result*i;
    }
    return result;
}

int main() {
    int num;
    cout << "수 입력하세요" << '\n';
    cin >> num;
    int result = factorial(num);
    cout << result << '\n';

    return 0;
}