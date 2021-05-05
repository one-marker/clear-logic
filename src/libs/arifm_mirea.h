#ifndef ARIFM_MIREA_H
#define ARIFM_MIREA_H

#define MAXLEN 6
#define BIT_INT 32

void umn(int n, unsigned int *a, unsigned int *b, unsigned int *c);
int first_bit(int n, unsigned int *a);
int cmp(int n, unsigned int *a, unsigned int *b);
void sum(int n, unsigned int *a, unsigned int *b, unsigned int *c);
void raz(int len, unsigned int * a, unsigned int * b, unsigned int * c);
void sum_mod(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c);
void raz_mod(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c);
void mod_p(unsigned int * a, int n1, unsigned int * p, int n2);
void mulp(int len, unsigned int * a, unsigned int * b, unsigned int * p, unsigned int * c);
void step_mod(unsigned int * p, unsigned int * a, int n1, unsigned int * b, int n2, unsigned int * c);
void shift_l(int n, int k, unsigned int * a, unsigned int * c);
void shift_r(int n, int k, unsigned int * a, unsigned int * c);
int obr(int len, unsigned int * a, unsigned int * N, unsigned int * c);
int div(int len, unsigned int * a, unsigned int * b, unsigned int * c);
void change_sign(int len, unsigned int * c);

#endif
