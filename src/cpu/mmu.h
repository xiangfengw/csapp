/*
    memory management unit 内存管理单元
    ch9.va到pa的翻译
*/
#ifndef mmu_guard
#define mmu_guard

#include<stdint.h>

uint64_t va2pa(uint64_t vaddr);

#endif