#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "../Stack/stack_structs.h"

enum ProcessorErrors {
    FILE_OPENING_ERROR = 2,
    SYNTAX_ERROR = 3,
    UNDEFINED_BEHAVIOR_ERROR = 4,
    TOO_FEW_ARGUMENTS = 5
};

enum Programs {
    PUSH,
    POP,
    ADD, 
    SUB, 
    MUL, 
    DIV, 
    OUT, 
    HLT, 
    JMP, 
    JB, 
    JBE, 
    JA, 
    JAE, 
    JE, 
    JNE,
    SIZE__,
};

enum RegisterNums {
    RAX,
    RBX,
    RCX,
    RDX,
};

enum ArgumentTypes {
    NUM = 1, 
    REG = 2,
    REG_NUM = 3,
    MEM_NUM = 5,
    MEM_REG = 6,
    MEM_REG_NUM = 7,
};

enum AdditionalActions {
    ABORT = 16,
};

typedef struct Code {
    stack_elem_t* code_arr;
    size_t size;
} code_t;

typedef struct Registers {
    stack_elem_t* reg_arr;
    size_t size;
} reg_t;

typedef struct Memory {
    stack_elem_t* mem_arr;
    size_t size;
} mem_t;

int pop_r(stack_elem_t* reg_array, stack_t* stk, int reg_num);
int push_r(stack_elem_t* reg_array, stack_t* stk, int reg_num);
int make_code(FILE* file_from, code_t* code_arr);
int processing(code_t* code, stack_t* stk);
int reg_dump(stack_elem_t* reg_array, size_t reg_size);
int reg_dtor(stack_elem_t* reg_array, size_t reg_size);
int push_m(stack_elem_t* mem_array, stack_t* stk, int mem_num);
int pop_m(stack_elem_t* mem_array, stack_t* stk, int mem_num);
int push_mr(stack_elem_t* mem_array, stack_t* stk, stack_elem_t* reg_array, int reg_num);
int pop_mr(stack_elem_t* mem_array, stack_t* stk, stack_elem_t* reg_array, int reg_num);


#endif //PROCESSOR_H
