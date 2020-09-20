#include <iostream>

using namespace std;

int squal(int num) {
    int n = num;
    // 1 if문 안돌려도 됨
    if(num == 1) {
        return 1;
    }
    else {
        for(int i = 1; i<n; i ++) {
            num =n*num;
            cout << num << '\n';
        }
    }
    return num;
}

int main() {
    int num;
    cin >> num;
    int result = squal(num);
    cout << result << '\n';

    return 0;
}