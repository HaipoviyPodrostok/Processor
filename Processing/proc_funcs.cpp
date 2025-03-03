#include <stdio.h>
#include <stdlib.h>
#include <cassert>

#include "processor.h"
#include "../Stack/stack_structs.h"
#include "../Stack/stack_create.h"
#include "../Stack/stack_funcs.h"
#include "../Stack/verificator.h"

int proc_push(code_t* code, stack_t* stk, reg_t* registers, mem_t* memory) {
    
    stk = NULL;
    
    assert((code && stk && registers && memory) != NULL);

    int arg_type = (int)code->code_arr[code->IP];
    code->IP++;
                
        switch (arg_type) {
            
            case NUM: {               
                stack_push(stk, code->code_arr[code->IP]);
                code->IP++;
                break;
            }    
            
            case REG: 
                push_r(registers->reg_arr, stk, (int)code->code_arr[code->IP]);
                code->IP++;
                break;
            
            case REG_NUM:
                push_r(registers->reg_arr, stk, (int)code->code_arr[code->IP]);
                code->IP++;
                stack_push(stk, code->code_arr[code->IP]);
                code->IP++;
                break; 

            case MEM_NUM:
                push_m(memory->mem_arr, stk,  (int)code->code_arr[code->IP]);
                code->IP++;
                break;

            case MEM_REG:
                push_mr(memory->mem_arr, stk, registers->reg_arr, (int)code->code_arr[code->IP]);
                code->IP++;
                break;

            case MEM_REG_NUM:  //TODO доделать

                break;

            default:
                break;
        }
    
    return 0;
} 