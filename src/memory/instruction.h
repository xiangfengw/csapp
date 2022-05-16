#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>

#define NUM_INSTRTYPE 30

// enum枚举中的元素本质上是0、1、2...(int)
typedef enum OP
{
    mov_reg_reg, // 0 
    mov_reg_mem, // 1
    mov_mem_reg, // 2
    push_reg,    // 3
    pop_reg,     // 4
    call,        // 5
    ret,         // 6
    add_reg_reg, // 7
}op_t;

typedef enum OD_TYPE
{
    // csapp 3.4.1
    EMPTY,
    IMM, REG,                    //立即数和寄存器
    MM_IMM, MM_REG, MM_IMM_REG,  //MM 内存
    MM_REG1_REG2, MM_IMM_REG1_REG2, 
    MM_REG2_S, MM_IMM_REG2_S, 
    MM_REG1_REG2_S, MM_IMM_REG1_REG2_S
}od_type_t;

typedef struct OD
{
    od_type_t type;

    int64_t imm;    //立即数，可能是负数
    int64_t scal;   //scale
    uint64_t *reg1;  //寄存器，存地址 
    uint64_t *reg2;
}od_t;

typedef struct INSTRUCT_STRUCT
{
    op_t op;
    od_t src;
    od_t dst;
    char code[100];
}inst_t;

// pointer pointing to the function
// function_t func = function_table[instr->op];
// func(src, dst);

typedef void (*handler_t)(uint64_t, uint64_t);

void mov_reg_reg_handler(uint64_t, uint64_t);

void add_reg_reg_handler(uint64_t, uint64_t);

handler_t handler_table[NUM_INSTRTYPE];

void init_handler_table();

void insruction_cycle();

