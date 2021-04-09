#include <iostream>
#include <string.h>

struct studentA
{
    char name[10];
    int age;
    double gpa;
};

typedef struct studentB {
    char name[10];
    int age;
    double gpa;
} student;

// student라는 타입의 변수 s 선언
student s; 

// 초기화
student s = {"kim",20, 4.3};

struct studentA s1;
strcpy(s1.name,"kim");
s1.age = 20;
s1.gpa = 4.3;