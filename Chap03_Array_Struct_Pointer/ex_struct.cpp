#include <iostream>
#include <string>

struct student
{
    char name[10];
    int age;
    double gpa;
};

typedef struct student {
    char name[10];
    int age;
    double gpa;
} student;

// student라는 타입의 변수 s 선언
student s; 
// int 타입의 배열 변수인 arr 선언
int arr[10];

// 초기화
student s = {"kim",20, 4.3};

struct student s1;
strcpy(s1.name,"kim");
s1.age = 20;
s1.gpa = 4.3;