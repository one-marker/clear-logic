#include "libs/arifm_mirea.h"
#include <iostream>

void processNewX(int len,
                unsigned int* pointX,
                unsigned int* pointX0,
                unsigned int* p,
                unsigned int* lambda,
                unsigned int* newX) {

    unsigned int* mulpLambda = new unsigned int[len];
    unsigned int* sumRes = new unsigned int [len * 2];

    mulp(len, lambda, lambda, p, mulpLambda);
    sum_mod(len, pointX, pointX0, p, sumRes);
    raz_mod(len, mulpLambda, sumRes, p, newX);
}


void processNewY(int len,
                 unsigned int* pointX,
                 unsigned int* pointY,
                 unsigned int* newX,
                 unsigned int* p,
                 unsigned int* lambda,
                 unsigned int* newY) {
    unsigned int* raz_modRes1 = new unsigned int[len];
    unsigned int* mulRes = new unsigned int [len * 2];


    raz_mod(len, pointX, newX, p, raz_modRes1);
    mulp(len, lambda, pointY, p, mulRes);
    raz_mod(len, mulRes, raz_modRes1, p, newY);

}

void lambdaForSameX(int len,
                    unsigned int* pointX,
                    unsigned int* pointY,
                    unsigned int*  a,
                    unsigned int* p,
                    unsigned int* lambda) {

    unsigned int* mulpRes1 = new unsigned int[len * 2];
    unsigned int* mulpRes2 = new unsigned int[len * 2];
    unsigned int* mulpRes3 = new unsigned int[len * 2];
    unsigned int* inverseRes = new unsigned int[len ];
    unsigned int* addRes = new unsigned int[len * 2];

    unsigned int* tmp = new unsigned int[len];
    tmp[0] = 0x3;

    mulp(len, pointX, pointX, p , mulpRes1);
    mulp(len, mulpRes1, tmp, reinterpret_cast<unsigned int *>(1), mulpRes2);
    sum_mod(len, mulpRes1, a, p, addRes);

    tmp[0] = 0x2;
    mulp(len, pointY, tmp, reinterpret_cast<unsigned int *>(1), mulpRes2);
    obr(len, mulpRes2, p, inverseRes);
    mulp(len, addRes , inverseRes, p, lambda);
}

void lambdaForDifferentX(int len,
                         unsigned int* pointX,
                         unsigned int* pointY,
                         unsigned int* pointX0,
                         unsigned int* pointY0,
                         unsigned int* p,
                         unsigned int* lambda) {
    unsigned int* raz_mod1 = new unsigned int[len];
    unsigned int* raz_mod2 = new unsigned int[len];
    unsigned int* obrRes = new unsigned int[len];


    raz_mod(len, pointY0, pointY, p , raz_mod1);
    raz_mod(len, pointX0, pointX, p , raz_mod2);
    obr(len, raz_mod1, p, obrRes);
    mulp(len, obrRes, raz_mod2, p, lambda);
}



int smartSum(int n,
               unsigned int* pointX,
               unsigned int* pointY,
               unsigned int* pointX0,
               unsigned int* pointY0,
               unsigned int* a,
               unsigned int* p,
               unsigned int* pointNewX,
               unsigned int* pointNewY) {

    unsigned int* lambda = new unsigned int[n];
    if (cmp(n, pointX, pointX0) == 0)
        lambdaForSameX(n, pointX, pointX0, a, p, lambda);
    else
        lambdaForDifferentX(n, pointX, pointY, pointX0, pointY0, p, lambda);

    processNewX(n, pointX, pointX0, p, lambda, pointNewX);
    processNewY(n, pointX, pointY, pointNewX, p, lambda, pointNewY);

    delete [] lambda;
}


int main() {

    //Евлентьев Максим КТСО-01-17. 5 Вариант

    //18446744073709551616 + 5 = 18446744073709551621
    //10000000000000000000000000000000000000000000000000000000000000101

    unsigned int k[8] = { 0x0000005,
                            0x00000000,
                            0x00000001,
                            0x00000000,
                            0x00000000,
                            0x00000000,
                            0x00000000,
                            0x00000000};

    int n = 256;

    unsigned int* p = new unsigned int[n]; //модуль эл.кривой
    unsigned int* a = new unsigned int[n]; //коэфициент a эл.кривой
    unsigned int* b = new unsigned int[n]; //коэфициент b эл.кривой
    unsigned int* q = new unsigned int[n]; //порядок циклической подгруппы
    unsigned int* xp = new unsigned int[n]; //коэфициент x точки эл.кривой
    unsigned int* yp = new unsigned int[n]; //коэфициент y точки эл.кривой

    unsigned int* xp_begin = xp;
    unsigned int* yp_begin = yp;
    unsigned int* xp_result = new unsigned int[n];
    unsigned int* yp_result = new unsigned int[n];

    for (int i = 256 - 1; i >= 0; i--) {
        smartSum(n, xp, yp,xp_begin, yp_begin, a ,p, xp_result, yp_result);
        unsigned int currentElementIndex = i / 32;
        unsigned char currentBit = (k[currentElementIndex] >> (i % (32))) & 1;
        if (currentBit)
            smartSum(n, xp, yp,xp_begin, yp_begin, a ,p, xp_result, yp_result);
    }

    delete [] p;
    delete [] a;
    delete [] b;
    delete [] q;
    delete [] xp;
    delete [] yp;
    delete [] xp_begin;
    delete [] yp_begin;
    delete [] xp_result;
    delete [] yp_result;

}

