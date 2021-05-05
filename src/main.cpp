#include <iostream>
#include "libs/arifm_mirea.h"


int main() {
    int n = 2;
    unsigned int *a = new unsigned int[n];
    unsigned int *b = new unsigned int[n];
    unsigned int *c = new unsigned int[n];

    //12
    a[0] = 1;
    a[1] = 2;

    //23
    b[0] = 2;
    b[1] = 3;


    sum(n, a, b, c);

    //35
    for (int i = 0; i < n; i++) {
        std::cout << c[i];
    }

    return 0;
}
