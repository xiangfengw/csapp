#include<stdio.h>
#include<stdint.h>

#include "cpu/register.h"
#include "disk/elf.h"
#include "cpu/mmu.h"
#include "memory/dram.h"
#include "memory/instruction.h"

int main()
{
    init_handler_table();

    // init
    reg.rax = 0x12340000;
    reg.rbx = 0x555555555190;
    reg.rcx = 0x555555555190;
    reg.rdx = 0xabcd;
    reg.rsi = 0x7fffffffe178;
    reg.rdi = 0x1;
    reg.rbp = 0x7fffffffe080;
    reg.rsp = 0x7fffffffe060;
    reg.rip = (uint64_t)&program[11];

    write64bits_dram(va2pa(0x7fffffffe060), 0x00); // rsp 栈顶
    write64bits_dram(va2pa(0x7fffffffe068), 0x12340000);
    write64bits_dram(va2pa(0x7fffffffe070), 0xabcd);
    write64bits_dram(va2pa(0x7fffffffe078), 0x00);
    write64bits_dram(va2pa(0x7fffffffe080), 0x00); // rbp


    print_register();
    print_stack();

    // uint64_t pa = va2pa(0x7fffffffe068);
    // printf("%16lx\n",
    //     *((uint64_t *)(&mm[pa])));
    // printf("%lx\n", read64bits_dram(va2pa(0x7fffffffe068)));


    // run inst
    for(int i = 0; i < 3; i++)
    {
        insruction_cycle(); // 指令周期

        print_register();
        print_stack();
    }

    // verify
    int match = 1;

    match = match && (reg.rax == 0x1234abcd);
    match = match && (reg.rbx == 0x555555555190);
    match = match && (reg.rcx == 0x555555555190);
    match = match && (reg.rdx == 0x12340000);
    match = match && (reg.rsi == 0xabcd);
    match = match && (reg.rdi == 0x12340000);
    match = match && (reg.rbp == 0x7fffffffe080);
    match = match && (reg.rsp == 0x7fffffffe060);

    if(match == 1)
    {
        printf("register match\n");
    }
    else
    {
        printf("register not match\n");
    }

    match = match && (read64bits_dram(va2pa(0x7fffffffe060)) == 0x0);
    match = match && (read64bits_dram(va2pa(0x7fffffffe068)) == 0x12340000);
    match = match && (read64bits_dram(va2pa(0x7fffffffe070)) == 0xabcd);
    match = match && (read64bits_dram(va2pa(0x7fffffffe078)) == 0x1234abcd);
    match = match && (read64bits_dram(va2pa(0x7fffffffe080)) == 0x0);

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