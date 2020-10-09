#include <iostream>
#include <vector>
#define max_que_size 5

using namespace std;

// int를 element라는 이름으로도 선언할 수 있게 rename
// 이렇게 하는 이유는 element로 선언한 변수들이 여러 개일 시, element의 자료형만 바꾸면 싹 다 바꿀 수 있기에 편하다
typedef int element;
typedef struct {
    element data[max_que_size];
    int front, rear;
} QueType;

// 오류함수
void error(char *message) {
    fprintf(stderr, "%s\n",message);
    exit(1);
}



int main() {



    return 0;
}