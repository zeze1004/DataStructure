#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

#define MAX_DEGREE 101

typedef struct { 
	int degree; // 최대차항
	int coef[MAX_DEGREE + 1];
} polynomial;

polynomial A, B;

// sum two polynomial
polynomial add(polynomial max, polynomial min) {
    int max_degree = max.degree;
    int min_degree = min.degree;
    
    for (int i = max_degree - min_degree, count = 0; i <= max_degree; i++, count++) {
        max.coef[i] += min.coef[count];
    }
    for (int i = 0; i <= max_degree; i++) {
        cout << max.coef[i] << " ";
    }
    return max;
}

int main() {
    int degreeA, degreeB;
    int coef;
    cin >> degreeA >> degreeB;
    A.degree = degreeA;
    B.degree = degreeB;
    // input A's coef
    for (int i = 0; i <= degreeA; i++) {
        cin >> coef;
        A.coef[i] = coef;
    }
    // input B's coef
    for (int i = 0; i <= degreeB; i++) {
        cin >> coef;
        B.coef[i] = coef;
    }
    // choose max degree & input add method's parameter
    if (degreeA >= degreeB) {
        add(A, B);
    } else {
        add(B, A);
    }

    return 0;
}
