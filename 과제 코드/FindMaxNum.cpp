#include <iostream>
#include <vector>
using namespace std;

// vector 함수 매개변수 설명: https://www.acmicpc.net/board/view/38804 
// vector 함수 매개변수로 받을 때 vector<type> &vector 변수명 
int maxNum(int num, vector<int> &scanfNum) {
    int max = scanfNum[0];
    for (int i =0; i<num; i++) {
        if(scanfNum[i] > max)
            max = scanfNum[i];
    }
    return max;
}

int main() {
    
    vector <int> scanfNum;
    int num = 0;
    int scanf = 0;
    cout << "put num" <<'\n';
    cin >> num;
    for(int i =0; i<num; i++) {
        cin >> scanf;
        scanfNum.push_back(scanf);
    }
    // vector 매개변수로 넘길 때 그냥 변수명만 넣기
    int max = maxNum(num, scanfNum);
    cout << "최댓값: " <<max << '\n';

    return 0;
}