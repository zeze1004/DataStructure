#include <iostream>
using namespace std;

int factorial(int num) {
    // 순환을 멈추는 부분
    if (num <= 1)
        return 1;
    // 순환 호출하는 부분
    else return (num * factorial(num - 1));
}


int main() {
    int num,result;
    cout << "수를 입력하시오: " << '\n';
    cin >> num;
    result = factorial(num);
    cout << result << '\n';

    return 0;
}