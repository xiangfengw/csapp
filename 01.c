#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdint.h>

uint32_t uint2float(uint32_t u) // unsingned int 32bit type
{
    // 32 zeros
    if(u == 0)
    {
        return 0;
    }
    
    uint32_t s = u & 0x80000000;
    uint32_t f;
    uint32_t e;
    u = u & 0x7fffffff;
    // printf("%x\n", s);
    // u doesn't have sign bit 
    // must exist highest 1
    int n = 0;
    uint32_t temp = u;
    for (int i = 1; i <= 32; ++i)
    {
        u = u>>1;
        if(u == 0x1)
        {
            n = i + 1;
            // printf("%d\n", n);
            break;
        }
    }
    // printf("%d\n", n);
    if (n <= 23)
    {
        // no near 
        f = (0xffffffff >> (33-n)) & temp; // temp - u
        e = n + 126;
        return s | (e << 23) | f;
    }
}

#if 0
uint32_t uint2float2(uint32_t u)
{
    if (u == 0x00000000)
    {
        return 0x00000000;
    }
    // must be NORMALIZED
    // counting the position of highest 1: u[n]
    int n = 31;
    while (0 <= n && (((u >> n) & 0x1) == 0x0))
    {
        n = n - 1;
    }
    uint32_t e, f;
    //    seee eeee efff ffff ffff ffff ffff ffff
    // <= 0000 0000 1111 1111 1111 1111 1111 1111
    if (u <= 0x00ffffff)
    {
        // no need rounding
        uint32_t mask = 0xffffffff >> (32 - n);
        f = (u & mask) << (23 - n);
        e = n + 127;
        return (e << 23) | f;
    }
    // >= 0000 0001 0000 0000 0000 0000 0000 0000
    else
    {
        // need rounding
        // expand to 64 bit for situations like 0xffffffff
        uint64_t a = 0;
        a += u;
        // compute g, r, s
        uint32_t g = (a >> (n - 23)) & 0x1;     // Guard bit, the lowest bit of the result
        uint32_t r = (a >> (n - 24)) & 0x1;     // Round bit, the highest bit to be removed
        uint32_t s = 0x0;                       // Sticky bit, the OR of remaining bits in the removed part (low)
        for (int j = 0; j < n - 24; ++ j)
        {
            s = s | ((u >> j) & 0x1);
        }
        // compute carry
        a = a >> (n - 23);
        // 0    1    ?    ... ?
        // [24] [23] [22] ... [0]
        /* Rounding Rules
            +-------+-------+-------+-------+
            |   G   |   R   |   S   |       |
            +-------+-------+-------+-------+
            |   0   |   0   |   0   |   +0  | round down
            |   0   |   0   |   1   |   +0  | round down
            |   0   |   1   |   0   |   +0  | round down
            |   0   |   1   |   1   |   +1  | round up
            |   1   |   0   |   0   |   +0  | round down
            |   1   |   0   |   1   |   +0  | round down
            |   1   |   1   |   0   |   +1  | round up
            |   1   |   1   |   1   |   +1  | round up
            +-------+-------+-------+-------+
        carry = R & (G | S) by K-Map
        */
        if ((r & (g | s)) == 0x1)
        {
            a = a + 1;
        }
        // check carry
        if ((a >> 23) == 0x1)
        {
            // 0    1    ?    ... ?
            // [24] [23] [22] ... [0]
            f = a & 0x007fffff;
            e = n + 127;
            return (e << 23) | f;
        }
        else if ((a >> 23) == 0x2)
        {
            // 1    0    0    ... 0
            // [24] [23] [22] ... [0]
            e = n + 1 + 127;
            return (e << 23);
        }
    }
    // inf as default error
    return 0x7f800000;
}
#endif

int main()
{
    uint32_t u = 0x00407200;
    uint32_t a = uint2float(u);
    printf("%x\n", a);

    return 0;
}