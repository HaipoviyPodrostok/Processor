#include <stdio.h>
#include <stdlib.h>

#include "processor.h"
#include "../Stack/stack_structs.h"
#include "../Stack/stack_create.h"
#include "../Stack/stack_funcs.h"
#include "../Stack/verificator.h"

int processing(code_t* code, stack_t* stk) {
    // FIXME assert
    size_t IP = 0;

    stack_elem_t* code_arr_proc = 0;
    code_arr_proc = code->code_arr;
    const size_t MAX_IP = code->size - 1;

    reg_t reg_1 = {NULL,4,0};
    size_t REG_SIZE = reg_1.size;
    stack_elem_t* reg_array = NULL;
    reg_array = (stack_elem_t*) calloc(REG_SIZE, sizeof(stack_elem_t));
    
    
    while (IP <= MAX_IP) {
        
        int action = (int)code_arr_proc[IP];

        IP++;
        
        if (IP > MAX_IP) {
            action = HLT;          // придумать ошибку + придумать проверку
        }

        switch (action) {

            case PUSH: 
                stack_push(stk, code_arr_proc[IP]);
                verificator(stk);
                IP++;
                break;

            case PUSH_R:
                push_r(reg_array, stk, (int)code_arr_proc[IP]);
                IP++;
                break;

            case POP_R:
                pop_r(reg_array, stk, (int)code_arr_proc[IP]);
                IP++;
                break;

            case ADD:
                stack_push(stk, stack_pop(stk) + stack_pop(stk)); 
                break;

            case SUB: {
                stack_elem_t a = 0;
                stack_elem_t b = 0;

                a = stack_pop(stk);
                b = stack_pop(stk);

                stack_push(stk, b - a); 
                
                break; 
            }
                
            case MUL:
                stack_push(stk, stack_pop(stk) * stack_pop(stk)); 
                break;

            case DIV: {
                stack_elem_t a = 0;
                stack_elem_t b = 0;

                a = stack_pop(stk);
                b = stack_pop(stk);
                
                stack_push(stk, a / b);

                break;    
            }

            case OUT:    
                printf("%s:%s, %s(): stack_peak = %f\n", __FILE__, __FILE__, __func__, stack_pop(stk));
                break;
            
            case HLT:
                stack_dump(stk);
                stack_dtor(stk);
                reg_dump(reg_array, REG_SIZE);
                reg_dtor(reg_array, REG_SIZE);
                return 0;
            
            case JMP:
                IP = (size_t)code_arr_proc[IP];
                break;

            case JB: {
                stack_elem_t a = 0;
                stack_elem_t b = 0;

                b = stack_pop(stk);
                a = stack_pop(stk);

                if (a < b) {
                    IP = (size_t)code_arr_proc[IP];
                }

                else {
                    IP++;
                }

                break;
            }

            default:
                ; // FIXME обработать как ошибку
        }
    }
    return 0;
}