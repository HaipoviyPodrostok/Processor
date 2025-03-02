#include <stdio.h>
#include <stdlib.h>
#include <cassert>

#include "processor.h"
#include "../Stack/stack_structs.h"
#include "../Stack/stack_create.h"
#include "../Stack/stack_funcs.h"
#include "../Stack/verificator.h"

int proc_push(code_t* code, stack_t* stk, reg_t* registers, mem_t* memory) {
    int arg_type = (int)code->code_arr[IP];
    IP++;
                
        switch (arg_type) {
            
            case NUM: {               
                stack_push(stk, code->code_arr[IP]);
                double stack_peak = stack_pop(stk);
                printf("%lg\n", stack_peak);
                stack_push(stk, code->code_arr[IP]);
                IP++;
                break;
            }    
            
            case REG: 
                push_r(reg_1.reg_arr, stk, (int)code->code_arr[IP]);
                IP++;
                break;
            
            case REG_NUM:
                push_r(reg_1.reg_arr, stk, (int)code->code_arr[IP]);
                IP++;
                stack_push(stk, code->code_arr[IP]);
                IP++;
                break; 

            case MEM_NUM:
                push_m(mem_1.mem_arr, stk,  (int)code->code_arr[IP]);
                IP++;
                break;

            case MEM_REG:
                push_mr(mem_1.mem_arr, stk, reg_1.reg_arr, (int)code->code_arr[IP]);
                IP++;
                break;

            case MEM_REG_NUM:  //TODO доделать
                break;

            default:
                break;
        }
    
    break;
} 