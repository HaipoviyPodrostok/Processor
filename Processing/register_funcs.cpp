#include <stdio.h>

#include "processor.h"
#include "../Stack/stack_structs.h"
#include "../Stack/stack_create.h"
#include "../Stack/stack_funcs.h"
#include "../Stack/verificator.h"

// int reg_ctor(reg_t* registers, size_t size) {

// }

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

int reg_dump(reg_t* Registers) {       //переделать

    printf("\n+--------------------------------------+\n");
    printf("|              REGISTER DUMP           |\n");
    printf("+-------------------+------------------+\n");
    printf("| reg_array         | %-16p |\n", Registers->reg_arr);
    printf("| reg_size          | %-16lu |\n", Registers->size);
    printf("+-------------------+------------------+\n\n");

    return 0;
}

int reg_dtor(reg_t* Registers) {
    for (size_t i = 0; i <= Registers->size - 1; i++) {
        Registers->reg_arr[i] = 0;
    }
    return 0;
}

