#include <stdio.h>

#include "processor.h"
#include "../Stack/stack_structs.h"
#include "../Stack/stack_create.h"
#include "../Stack/stack_funcs.h"
#include "../Stack/verificator.h"

int push_m(stack_elem_t* mem_array, stack_t* stk, int mem_num) {
    stack_push(stk, mem_array[mem_num]);
    return 0;
}

int push_mr(stack_elem_t* mem_array, stack_t* stk, stack_elem_t* reg_array, int reg_num) {
    
    push_r(reg_array, stk, reg_num);
    
    int stack_peak = 0;
    stack_peak = (int)stack_pop(stk);
    
    push_m(mem_array, stk, stack_peak);
    
    return 0;
}

int pop_m(stack_elem_t* mem_array, stack_t* stk, int mem_num) {
    
    stack_elem_t stack_peak = 0;
    stack_peak = stack_pop(stk);

    mem_array[mem_num] = stack_peak;

    return 0;
}

int pop_mr(stack_elem_t* mem_array, stack_t* stk, stack_elem_t* reg_array, int reg_num) {
    push_r(reg_array, stk, reg_num);
    
    int stack_peak = 0;
    stack_peak = (int)stack_pop(stk);
    
    pop_m(mem_array, stk, stack_peak);
    
    return 0;
}

// mem_dtor