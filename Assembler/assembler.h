#ifndef ASSEMBLER_H
#define ASSEMBLER_H

enum Programs {
    IN = 1,
    ADD = 2,
    SUB = 3,
    MUL = 4,
    DIV = 5,
    OUT = 6,
    HLT = 7, 
};

enum Errors {
    ERROR_WHILE_OPENING_FILE = 1,
};

#endif //ASSEMBLER_H