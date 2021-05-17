#include "libs/arifm_mirea.h"
#include <iostream>

using namespace std;

int xp_count(int len, unsigned int* lambda, unsigned int* xp_cur, unsigned int* p, unsigned int* xp_res);
int yp_count(int len, unsigned int* lambda, unsigned int* xp_cur, unsigned int* xp, unsigned int* yp_cur, unsigned int* p, unsigned int* yp_res);
int numerator_count(int len, unsigned int* xp_cur, unsigned int* a, unsigned int* numerator, unsigned int* p);
int denominator_count(int len, unsigned int* yp_cur, unsigned int* denominator);

int main() {
    int n = 16;
    unsigned int* p = new unsigned int[n]; //модуль эл.кривой
    unsigned int* a = new unsigned int[n]; //коэфициент a эл.кривой
    unsigned int* b = new unsigned int[n]; //коэфициент b эл.кривой
    unsigned int* q = new unsigned int[n]; //порядок циклической подгруппы  
    unsigned int* xp = new unsigned int[n]; //коэфициент x точки эл.кривой
    unsigned int* yp = new unsigned int[n]; //коэфициент y точки эл.кривой
    unsigned int* k = new unsigned int[n]; //порядок кратной точки
    
    unsigned int* lambda = new unsigned int[n];
    unsigned int* xp_cur = xp;
    unsigned int* yp_cur = yp;

    for (unsigned int* i = 0; i < k; ) {
        
        unsigned int* x_res = new unsigned int[n];
        unsigned int* y_res = new unsigned int[n];

        unsigned int* numerator; //числитель при расчете lambda
        numerator_count(n, xp_cur, a, numerator, p);
        unsigned int* denominator; //знаменатель при расчете lambda
        denominator_count(n, yp_cur, denominator);
       
        div(n, numerator, denominator, lambda);
        obr(n, lambda, p, lambda);

        xp_count(n, lambda, xp_cur, p, x_res); //коэфициент x точки эл.кривой
        xp_cur = x_res;
        yp_count(n, lambda, xp_cur, xp, yp_cur, p, y_res); //коэфициент y точки эл.кривой
        yp_cur = y_res;

        unsigned int* iter = new unsigned int[n];
        iter[0] = 1;

        sum(n, i, iter, i);

        delete [] numerator;
        delete [] denominator;
        delete [] x_res;
        delete [] y_res;
        delete [] iter;

    }



}


int xp_count(int len, unsigned int* lambda, unsigned int* xp_cur, unsigned int* p, unsigned int* xp_res)
{
    //(lambda * lambda - xp_cur - xp_cur) % p
    
    mulp(len, lambda, lambda, p, xp_res);
    sum(len, xp_cur, xp_cur, xp_cur);
    change_sign(len, xp_cur);
    sum_mod(len, xp_res, xp_cur, p, xp_res);

    return 0;
}

int yp_count(int len, unsigned int* lambda, unsigned int* xp_cur, unsigned int* xp, unsigned int* yp_cur, unsigned int* p, unsigned int* yp_res)
{
    //(lambda * (xp_cur - xp) - yp_cur) % p
    change_sign(len, xp);
    sum(len, xp_cur, xp, xp_cur);
    change_sign(len, xp);
    mulp(len, lambda, xp_cur, p, yp_res);
    change_sign(len, yp_cur);
    sum_mod(len, yp_res, yp_cur, p, yp_res);

    return 0;

}

int numerator_count(int len, unsigned int* xp_cur, unsigned int* a, unsigned int* numerator, unsigned int* p)
{
    //3 * xp_cur * xp_cur + a
    unsigned int* r = new unsigned int[len];
    r[0] = 0x3;
    mulp(len, xp_cur, xp_cur, p, numerator);
    mulp(len, numerator, r, p, numerator);
    sum(len, numerator, a, numerator);

    delete [] r;
    return 0;

}

int denominator_count(int len, unsigned int* yp_cur, unsigned int* denominator)
{
    //2 * yp_cur
    sum(len, yp_cur, yp_cur, denominator);

    return 0;

}