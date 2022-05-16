/*
    汇编代码模拟器
*/

#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>

typedef struct REG_STRUCT
{
    union
    {
        struct
        {
            uint8_t al;
            uint8_t ah;
        };
        uint16_t ax;
        uint32_t eax;
        uint64_t rax;
    };
    union
    {
        struct
        {
            uint8_t bl;
            uint8_t bh;
        };
        uint16_t bx;
        uint32_t ebx;
        uint64_t rbx;
    };
    union
    {
        struct
        {
            uint8_t cl;
            uint8_t ch;
        };
        uint16_t cx;
        uint32_t ecx;
        uint64_t rcx;
    };
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    union
    {
        struct
        {
            uint8_t spl;
            uint8_t sph;  //小端模式，从低到高
        };
        uint16_t sp;
        uint32_t esp;
        uint64_t rsp;
    };
    uint64_t rip;  // PC

}reg_t;

reg_t reg;


