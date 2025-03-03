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
    NUM = 1, //001
    REG = 2, //010
    REG_NUM = 3, //011
    MEM_NUM = 5, //101
    MEM_REG = 6, //110
    MEM_REG_NUM = 7, //111
};

enum Errors {
    ERROR_WHILE_OPENING_FILE = 1,
    TOO_FEW_ARGUMENTS = 2,
    COMMAND_BYTE_WRITING_ERROR = 3,
    READING_ERROR = 4,
};

typedef struct Labels {
    int* label_arr;
    size_t size;
    int ERROR;
} labels_t;

int first_pass(FILE* file_from, FILE* file_to, labels_t*);
int second_pass(FILE* file_from, FILE* file_to, labels_t* labels);
int pack_byte(u_int8_t command, u_int8_t arg_type, FILE* file_to);

#endif //ASSEMBLER_H