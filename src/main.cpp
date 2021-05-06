#include <iostream>
#include "lrp.cpp"


void testLrp() {

    //t = 5; Евлентьев Максим КТСО-01-17
    //0x100B -> x^16+x^12+x^3+x+1
    unsigned short a[32], f_x = 0x100B, t = 5;

    //init
    for (int i = 0; i < 32; i++)
        a[i] = i + t;

    lrp(a,f_x, t, 32, 64);

    for (int i = 64; i < 96; i++) {
        lrp(a,f_x, t, 32, 1);
        print(a, 32);
    }

}

int main() {
    testLrp();

    return 0;
}
