// 다항식끼리 더해보자!
// 구조체, 배열 사용

#include <iostream>
using namespace std;
#define max 101;

typedef struct poliy {
    int arr[max][max]; //[차수][계수]
} poli;

// 일단 하나의 다항식 만드는 함수를 만들자
int input(int a, int b) {
    poli input, input2;
    for(int i = 0; i < a; i++) {
        cout << "차수입력 <<" "<< "계수입력" << '\n';
        cin >> a >> b >> '\n';
        input.arr[a][b];
        if(a == 0) {
            return input.arr[a][b];
        }    
    }
}

int main() {
    int a,b;
    
    cout << "차수입력" << " "<<"계수입력" << '\n';
    cin >> a >> b >> '\n';
    /*
    poli input, input2;     // 다항식 두 개 입력 받을 배열 선언
    input.arr[a][b];
    cout << "차수 입력 계수 입력" << '\n';
    cin >> a >> b >> '\n';
    input2.arr[a][b];
    */
    cout << input(a,b) <<'\n';





    return 0;
}