#include <stdio.h>

#include "processor.h"
#include "../Stack/stack_structs.h"
#include "../Stack/stack_create.h"
#include "../Stack/stack_funcs.h"
#include "../Stack/verificator.h"

int push_r(stack_elem_t* reg_array, stack_t* stk, int reg_num) {

    stack_push(stk, reg_array[reg_num]);

    return 0;
}

int pop_r(stack_elem_t* reg_array, stack_t* stk, int reg_num) {
    
    stack_elem_t stack_peak = 0;
    stack_peak = stack_pop(stk);

    reg_array[reg_num] = stack_peak;

    return 0;
}

int reg_dump(stack_elem_t* reg_array, size_t reg_size) {

    printf("\n+--------------------------------------+\n");
    printf("|              REGISTER DUMP           |\n");
    printf("+-------------------+------------------+\n");
    printf("| reg_array         | %-16p |\n", reg_array);
    printf("| reg_size          | %-16lu |\n", reg_size);
    printf("+-------------------+------------------+\n\n");

    return 0;
}

int reg_dtor(stack_elem_t* reg_array, size_t reg_size) {
    for (size_t i = 0; i <= reg_size - 1; i++) {
        reg_array[i] = 0;
    }
    return 0;
}

