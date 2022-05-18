#include "memory/instruction.h"
#include "cpu/mmu.h"
#include "cpu/register.h"
#include "memory/dram.h"

#include <stdio.h>

static uint64_t decode_od(od_t od)
{
    if(od.type == IMM)
    {
        return od.imm;
    }
    else if(od.type == REG)
    {
        /*

        */
        return (uint64_t)od.reg1;  //reg存的是地址
    } 
    else
    {
        //mm
        uint64_t vaddr = 0;

        if (od.type == MM_IMM)
        {
            vaddr = *((uint64_t *)&od.imm);
        }
        else if (od.type == MM_REG)
        {
            vaddr = *(od.reg1);
        }
        else if (od.type == MM_IMM_REG)
        {
            vaddr = od.imm + *(od.reg1);
        }
        else if (od.type == MM_REG1_REG2)
        {
            vaddr = *(od.reg1) + *(od.reg2);
        }
        else if (od.type == MM_IMM_REG1_REG2)
        {
            vaddr = *(od.reg1) + *(od.reg2) + od.imm;
        }
        else if (od.type == MM_REG2_S)
        {
            vaddr = (*(od.reg2)) * od.scal;
        }
        else if (od.type == MM_IMM_REG2_S)
        {
            vaddr = od.imm + (*(od.reg2)) * od.scal;
        }
        else if (od.type == MM_REG1_REG2_S)
        {
            vaddr = *(od.reg1) + (*(od.reg2)) * od.scal;
        }
        else if (od.type == MM_IMM_REG1_REG2_S)
        {
            vaddr = od.imm + *(od.reg1) + (*(od.reg2)) * od.scal;
        }
        
        // uint64_t addr = MM_LEN + 0Xff;

        return va2pa(vaddr);
    }
}

void insruction_cycle()
{
    // 取址
    inst_t *instr = (inst_t *)reg.rip;

    // 译码
    uint64_t src = decode_od(instr->src);
    uint64_t dst = decode_od(instr->dst);

    // add rax, rbx
    // op = add_reg_reg = 3
    // handler_table[op] = handler_table[3] = add_reg_reg_handler
    handler_t handler = handler_table[instr->op];
    
    handler(src, dst);

    printf("    %s\n", instr->code);
}

void init_handler_table()
{
    handler_table[mov_reg_reg] = &mov_reg_reg_handler;
    handler_table[call] = &call_handler;
    handler_table[add_reg_reg] = &add_reg_reg_handler;
}

void mov_reg_reg_handler(uint64_t src, uint64_t dst)
{
    *(uint64_t *)dst = *(uint64_t *)src;
    reg.rip = reg.rip + sizeof(inst_t);
}

void call_handler(uint64_t src, uint64_t dst)
{
    // src: imm address of called function
    reg.rsp = reg.rsp - 8;

    // write return address to rsp memory
    write64bits_dram(
        va2pa(reg.rsp),
        reg.rip + sizeof(inst_t)
    );

    reg.rip = src;

}

void add_reg_reg_handler(uint64_t src, uint64_t dst)
{
    /*
    add_reg_reg_handler(src = &rax, dst = &rbx)
    */
    *(uint64_t *)dst = *(uint64_t *)dst + *(uint64_t *)src;
    reg.rip = reg.rip + sizeof(inst_t);
}

