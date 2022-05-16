/*
树状数组
*/
#include<stdio.h>

unsigned LowBit(int n){
    unsigned x;
    x = n & ((~n) + 1);
    return x;
}

unsigned Letter(unsigned x)
{
    /*
    x - 32bit 
    每4bit的 a = x3 & (x2 | x1)
    x3 x2 x1 x0 - hex
    0  0  1  0  &操作 取x1 - hex constant - 0x2
    */
    unsigned a; // a=1时 全字母
    unsigned x1 = x & 0x22222222;
    unsigned x2 = x & 0x44444444;
    unsigned x3 = x & 0x88888888;
    a = (x3 >> 3) & ((x2 >> 2) | (x1 >> 1));
    a = a & (a >> 32);
    a = a & (a >> 16);
    a = a & (a >>  8);
    a = a & (a >>  4);
    return a;
}

int main()
{
    printf("0x%x, is letter %u\n", 0xabcdefab, Letter(0xabcdefab));
    printf("0x%x, is letter %x\n", 0x11111111, Letter(0x11111111));
}

#if 0
int main()
{
    unsigned n = 9;

    //printf("0x%x\n", LowBit(0xa));
    printf("S[%u] = ", n);
    printf("T[%u]\n", n);
    n = n - LowBit(n);
    while(n != 0)
    {
        printf("+ T[%u]\n", n);
        n = n - LowBit(n);
    }
    printf("+ T[%u]\n", n);
 
    return 0;
}
#endif