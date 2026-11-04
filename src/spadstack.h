#ifndef SPADSTACK_H
#define SPADSTACK_H

/* Run a call on a stack in the scratchpad: the old $sp is pushed at addr and $sp moved below it.
   Only for calls that take their arguments in registers. */
#define SPAD_STACK_ADDR 0x1F8003FC

#define SetSpadStack(addr)                                                     \
    {                                                                          \
        __asm__ volatile("move $8,%0" ::"r"(addr) : "$8", "memory");           \
        __asm__ volatile("sw $29,0($8)" ::: "$8", "memory");                   \
        __asm__ volatile("addiu $8,$8,-4" ::: "$8", "memory");                 \
        __asm__ volatile("move $29,$8" ::: "$8", "memory");                    \
    }

#define ResetSpadStack()                                                       \
    {                                                                          \
        __asm__ volatile("addiu $29,$29,4" ::: "$29", "memory");               \
        __asm__ volatile("lw $29,0($29)" ::: "$29", "memory");                 \
    }

#endif
