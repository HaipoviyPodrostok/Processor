#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "../Stack/stack_structs.h"

enum ProcessorErrors {
    FILE_OPENING_ERROR = 2,
    SYNTAX_ERROR = 3,
    UNDEFINED_BEHAVIOR_ERROR = 4,
};

enum Programs {
    IN = 1,
    ADD = 2,
    SUB = 3,
    MUL = 4,
    DIV = 5,
    OUT = 6,
    HLT = 7, 
};

FILE* reading_from_file();
int processing(stack_t* stk, FILE* file_from);

#endif //PROCESSOR_H