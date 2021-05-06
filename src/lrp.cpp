
void print(unsigned short* a, unsigned int size) {
    for (int i = size - 1; i >= 0; i--)
        printf("%d ", a[i]);
    printf("\n");
}

void lrp(unsigned short* a, unsigned short f_x, unsigned int t, unsigned short size, unsigned int count){

    for (int i = 0; i < count; i++) {
        unsigned short b = a[0];
        unsigned int tmp = a[t] << 1;

        if ((tmp & 0x100))
            tmp ^= f_x;

        b ^= tmp;
        for (int i = 0; i < size - 1; i++)
            a[i] = a[i + 1];

        a[size - 1] = b;
    }
}

