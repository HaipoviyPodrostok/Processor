#ifndef ASSEMBLER_H
#define ASSEMBLER_H


enum Programs {
    PUSH = 0,
    PUSH_R = 1,
    POP_R = 2,
    ADD = 3,
    SUB = 4,
    MUL = 5,
    DIV = 6,
    OUT = 7,
    HLT = 8, 
    JMP = 9,
    JB = 10,
    JBE = 11,
    JA = 12,
    JAE = 13,
    JE = 14,
    JNE = 15,
    SIZE__ = 16,
    MARK = 17,
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