#include <stdio.h>
#include <stdlib.h>
#include <cassert>

#include "processor.h"
#include "../Stack/stack_structs.h"
#include "../Stack/stack_create.h"
#include "../Stack/stack_funcs.h"
#include "../Stack/verificator.h"

int processing(code_t* code, stack_t* stk) {
    assert(code != 0 || stk != 0);

    size_t IP = 0;

    code->IP = 0;
    const size_t MAX_IP = code->size - 1;
    
    //MAKE REGISTERS ARRAY:
    reg_t reg_1 = {NULL, 4};
    size_t REG_SIZE = reg_1.size;                                                   //reg_ctor
    reg_1.reg_arr = (stack_elem_t*) calloc(REG_SIZE, sizeof(stack_elem_t));
    
    //MAKE MEMORY ARRAY:
    mem_t mem_1 = {NULL, 0};                    //mem_ctor
    mem_1.size = 100;
    mem_1.mem_arr = (stack_elem_t*) calloc(mem_1.size, sizeof(stack_elem_t));

    int i = 0;

    while (IP <= MAX_IP) {
        i++;
        
        // if (i > 7) {
        //     break;
        // }

        int action = (int)code->code_arr[IP];

        if (IP > MAX_IP) {
            fprintf(stderr, "%s:%s, %s(): Error: code ended, but hlt was not detected.\n", __FILE__, __FILE__, __func__);  // придумать ошибку + придумать проверку
            action = HLT;
        }
  
        IP++;    
        
        switch (action) {

            case PUSH: {   
                
                int arg_type = (int)code->code_arr[IP];
                IP++;
                
                switch (arg_type) {
                    
                    case NUM: {               
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

            case POP: {
                
                int arg_type = (int)code->code_arr[IP];
                IP++;

                switch (arg_type) {
                    
                    case REG:
                        pop_r(reg_1.reg_arr, stk, (int)code->code_arr[IP]);
                        IP++;
                        break;
                    
                    case MEM_NUM:
                        pop_m(mem_1.mem_arr, stk,  (int)code->code_arr[IP]);
                        IP++;
                        break;

                    case MEM_REG:
                        pop_mr(mem_1.mem_arr, stk, reg_1.reg_arr, (int)code->code_arr[IP]);
                        IP++;
                        break;

                    case MEM_REG_NUM:
                        //TODO доделать
                        break;

                    default:
                        break;
                }
            
                break;    
            }

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
                reg_dump(&reg_1);   // mem dtor
                reg_dtor(&reg_1);
                stack_dump(stk);
                stack_dtor(stk);
                free(reg_1.reg_arr);
                free(mem_1.mem_arr);
                return 0;
            
            case JMP:
                IP = (size_t)code->code_arr[IP];
                break;

            case JB: {
                stack_elem_t a = 0;
                stack_elem_t b = 0;

                b = stack_pop(stk);
                a = stack_pop(stk);

                if (a < b) {
                    IP = (size_t)code->code_arr[IP];
                }

                else {
                    IP++;
                }

                break;
            }

            case JBE: {
                stack_elem_t a = 0;
                stack_elem_t b = 0;

                b = stack_pop(stk);
                a = stack_pop(stk);

                if (a <= b) {
                    IP = (size_t)code->code_arr[IP];
                }

                else {
                    IP++;
                }

                break;
            }

            case JA: {
                stack_elem_t a = 0;
                stack_elem_t b = 0;

                b = stack_pop(stk);
                a = stack_pop(stk);

                if (a > b) {
                    IP = (size_t)code->code_arr[IP];
                }

                else {
                    IP++;
                }

                break;
            }

            case JAE: {
                stack_elem_t a = 0;
                stack_elem_t b = 0;

                b = stack_pop(stk);
                a = stack_pop(stk);

                if (a >= b) {
                    IP = (size_t)code->code_arr[IP];
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