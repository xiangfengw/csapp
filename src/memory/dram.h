/*
    DRAM 动态随机存取存储器
    虚拟内存、cache
*/

#include<stdint.h>

#define MM_LEN 1000

uint32_t mm[MM_LEN]; //physical memory

//virtual address 在mmu中实现翻译