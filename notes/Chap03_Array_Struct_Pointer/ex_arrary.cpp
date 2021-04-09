#include <iostream>
// 배열의 응용: 다향식
// 배열을 사용한 2가지 방법
// 1) 다항식 모든 항을 배열에 저장
// 2) 다항식 0이 아닌 항만을 배열에 저장

// 10x^5 + 6x + 3
// 5  4 3 2 1 0
// 10 0 0 0 6 3

#define max_degree 101// 다항식 최대차수 + 1
typedef struct 
{
    int degree; // 최대 차수
    float coef[max_degree];
}ploynomial;

ploynomial a = {5, {10,0,0,0,6,3}};

