/*
    内存
    DRAM 动态随机存取存储器
    虚拟内存、cache
*/
#ifndef dram_guard
#define dram_guard

#include<stdint.h>

#define MM_LEN 1000

uint8_t mm[MM_LEN]; //physical memory

//virtual address 在mmu中实现翻译

uint64_t read64bits_dram(uint64_t paddr);
void write64bits_dram(uint64_t paddr, uint64_t data);

void print_register();
void print_stack();

#endif