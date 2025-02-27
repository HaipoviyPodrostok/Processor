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
    PUSH_R = 2,
    POP_R = 3,
    ADD = 4,
    SUB = 5,
    MUL = 6,
    DIV = 7,
    OUT = 8,
    HLT = 9, 
    JMP = 10,
    JB = 11,
    JBE = 12,
    JA = 13,
    JAE = 14,
    JE = 15,
    JNE = 16,
};

enum RegisterNums {
    RAX = 100,
    RBX = 101,
    RCX = 102,
    RDX = 103,
};

typedef struct Code {
    stack_elem_t* code_arr;
    size_t size;
    int ERROR;
} code_t;

typedef struct Registers {
    stack_elem_t* reg_arr;
    size_t size;
    int ERROR;
} reg_t;

FILE* open_file(const char* file_name);
int pop_r(stack_elem_t* reg_array, stack_t* stk, int reg_num);
int push_r(stack_elem_t* reg_array, stack_t* stk, int reg_num);
int make_code(FILE* file_from, code_t* code_arr);
int processing(code_t* code, stack_t* stk);
int reg_dump(stack_elem_t* reg_array, size_t reg_size);
int reg_dtor(stack_elem_t* reg_array, size_t reg_size);

#endif //PROCESSOR_H
