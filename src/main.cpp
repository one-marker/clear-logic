#include "libs/arifm_mirea.h"
#include <iostream>




using namespace std;

int xp_count(int len, unsigned int* lambda, unsigned int* xp_cur, unsigned int* xp_first, unsigned int* p, unsigned int* xp_res);
int yp_count(int len, unsigned int* lambda, unsigned int* xp_cur, unsigned int* xp, unsigned int* yp_cur, unsigned int* p, unsigned int* yp_res);
int numerator_count(int len, unsigned int* xp_cur, unsigned int* a, unsigned int* numerator, unsigned int* p);
int denominator_count(int len, unsigned int* yp_cur, unsigned int* denominator);
int simple_sum(int n, unsigned int* x_left, unsigned int* y_left,
               unsigned int* x_right, unsigned int* y_right, unsigned int* x_result, unsigned int* y_result, int lambda_type,
               unsigned int* p, unsigned int* a, unsigned int* b);

int main()
{
    //Евлентьев Максим КТСО-01-17. 5 Вариант

    //18446744073709551616 + 5 = 18446744073709551621
    //10000000000000000000000000000000000000000000000000000000000000101
    int k_bin[64] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,01,0,1};
    int n = 16;

    unsigned int* p = new unsigned int[n]; //модуль эл.кривой
    unsigned int* a = new unsigned int[n]; //коэфициент a эл.кривой
    unsigned int* b = new unsigned int[n]; //коэфициент b эл.кривой
    unsigned int* q = new unsigned int[n]; //порядок циклической подгруппы
    unsigned int* xp = new unsigned int[n]; //коэфициент x точки эл.кривой
    unsigned int* yp = new unsigned int[n]; //коэфициент y точки эл.кривой
    unsigned int* k = new unsigned int[n]; //порядок кратной точки

    unsigned int* xp_begin = xp;
    unsigned int* yp_begin = yp;
    unsigned int* xp_result = new unsigned int[n];
    unsigned int* yp_result = new unsigned int[n];

    for (int i = 1 ; i < 65; i++) {
        simple_sum(n, xp, yp, xp, yp, xp_result, yp_result, 0, p, a, b);
        xp = xp_result;
        yp = yp_result;
        if (k_bin[i] == 1) {
            simple_sum(n, xp, yp, xp_begin, yp_begin, xp_result, yp_result, 1, p, a, b);
            xp = xp_result;
            yp = yp_result;
        }
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
    delete [] k;


}


int simple_sum(int n, unsigned int* x_left, unsigned int* y_left,
               unsigned int* x_right, unsigned int* y_right, unsigned int* x_result, unsigned int* y_result, int lambda_type,
               unsigned int* p, unsigned int* a, unsigned int* b)
{

    //x_left = xp
    //y_left = yp
    //x_right = xq
    //y_right = yq

    unsigned int* lambda = new unsigned int[n];
    unsigned int* numerator; //числитель при расчете lambda
    unsigned int* denominator; //знаменатель при расчете lambda

    if (lambda_type == 0) {
        //складываем точку саму с собой P + P
        numerator_count(n, x_left, a, numerator, p);
        denominator_count(n, y_left, denominator);
        div(n, numerator, denominator, lambda);
        obr(n, lambda, p, lambda);
    } else {
        //складывем точку с самой начальной точкой P + Q
        raz(n, y_right, y_left, numerator);
        raz(n, x_right, x_left, denominator);
        div(n, numerator, denominator, lambda);
        obr(n, lambda, p, lambda);
    }
    unsigned int* x_res = new unsigned int[n];
    unsigned int* y_res = new unsigned int[n];

    // ( lambda^2 – x1 – x2 ) mod p
    xp_count(n, lambda, x_left, x_right,  p, x_res); //коэфициент x точки эл.кривой
    unsigned int* xp_cur = x_res;
    // ( lambda ( x1 – x3 ) – y1 ) mod p
    yp_count(n, lambda, x_left, xp_cur, y_left, p, y_res); //коэфициент y точки эл.кривой
    unsigned int* yp_cur = y_res;

    x_left = xp_cur;
    y_left = yp_cur;

    delete[] numerator;
    delete[] denominator;
    delete[] x_res;
    delete[] y_res;
    delete[] xp_cur;
    delete[] yp_cur;
    delete[] lambda;
}

int xp_count(int len, unsigned int* lambda, unsigned int* xp_cur, unsigned int* xp_first, unsigned int* p, unsigned int* xp_res)
{
    //(lambda * lambda - xp_cur - xp_first) % p

    mulp(len, lambda, lambda, p, xp_res);
    change_sign(len, xp_cur);
    change_sign(len, xp_first);
    sum(len, xp_cur, xp_first, xp_cur);
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

