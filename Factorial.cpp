#include <iostream>
using namespace std;

int factorial(int num) {
    if (num <= 1)
        return 1;
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