#ifndef ASSEMBLER_H
#define ASSEMBLER_H


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
    MARK,
};

enum ArgumentTypes {
    NUM = 1, 
    REG = 2,
    REG_NUM = 3,
    MEM_NUM = 4,
    MEM_REG = 6,
    MEM_REG_NUM = 7,
};

enum Errors {
    ERROR_WHILE_OPENING_FILE = 1,
    TOO_FEW_ARGUMENTS = 2,
};

typedef struct Labels {
    int* label_arr;
    size_t size;
    int ERROR;
} labels_t;

int first_pass(FILE* file_from, FILE* file_to, labels_t*);
int second_pass(FILE* file_from, FILE* file_to, labels_t* labels);


#endif //ASSEMBLER_H