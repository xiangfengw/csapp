#include<stdio.h>
#include<stdint.h>

#include "cpu/register.h"
#include "disk/elf.h"
#include "cpu/mmu.h"
#include "memory/dram.h"

int main()
{
    init_handler_table();

    // init
    reg.rax = 0x12340000;
    reg.rbx = 0x555555555190;
    reg.rcx = 0x555555555190;
    reg.rdx = 0xabcd;
    reg.rsi = 0x7fffffffe158;
    reg.rdi = 0x1;
    reg.rbp = 0x7fffffffe060;
    reg.rsp = 0x7fffffffe040;
    reg.rip = (uint64_t)&program[11];

    mm[va2pa(0x7fffffffe040)] = 0x00; // rsp 栈顶
    mm[va2pa(0x7fffffffe04f)] = 0x12340000;
    mm[va2pa(0x7fffffffe050)] = 0xabcd;
    mm[va2pa(0x7fffffffe05f)] = 0x0;
    mm[va2pa(0x7fffffffe060)] = 0x0; // rbp

    // run inst
    for(int i = 0; i < 15; i++)
    {
        insruction_cycle(); // 指令周期
    }

    // verify
    int match = 1;

    match = match && (reg.rax == 0x1234abcd);
    match = match && (reg.rbx == 0x555555555190);
    match = match && (reg.rcx == 0x555555555190);
    match = match && (reg.rdx == 0x12340000);
    match = match && (reg.rsi == 0xabcd);
    match = match && (reg.rdi == 0x12340000);
    match = match && (reg.rbp == 0x7fffffffe060);
    match = match && (reg.rsp == 0x7fffffffe040);

    if(match == 1)
    {
        printf("register match\n");
    }
    else
    {
        printf("register not match\n");
    }

    match = match && (mm[va2pa(0x7fffffffe040)] == 0x0);
    match = match && (mm[va2pa(0x7fffffffe04f)] == 0x12340000);
    match = match && (mm[va2pa(0x7fffffffe050)] == 0xabcd);
    match = match && (mm[va2pa(0x7fffffffe05f)] == 0x1234abcd);
    match = match && (mm[va2pa(0x7fffffffe060)] == 0x0);

    if(match == 1)
    {
        printf("memory match\n");
    }
    else
    {
        printf("memory not match\n");
    }

    return 0;
} 