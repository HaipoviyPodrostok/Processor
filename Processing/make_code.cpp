#include <stdio.h>
#include <stdlib.h>

#include "processor.h"

int make_code(FILE* file_from, code_t* code) {
    
    size_t NUMBER_OF_INSTRUCTIONS = 0;
    
    fscanf(file_from, "%lu", &NUMBER_OF_INSTRUCTIONS);
    
    code->code_arr = (stack_elem_t*) calloc(NUMBER_OF_INSTRUCTIONS, sizeof(stack_elem_t));   // TODO добавлять при переполнении

    size_t IP = 0;

    while (IP <= NUMBER_OF_INSTRUCTIONS - 1) {

        int action = 0;
        int command_number = 0;

        fscanf(file_from, "%d", &action);
        
        if (feof(file_from)) {
            break;         
        }

        command_number++;

        switch (action) {
            
            case PUSH: 
            case POP: {
                int arg_type = 0;
                fscanf(file_from, "%d", &arg_type);               //TODO проверка IP

                code->code_arr[IP] = action;
                IP++;
                code->code_arr[IP] = arg_type;
                IP++;

                switch(arg_type) {

                    case NUM: 
                    case MEM_NUM: {
                        stack_elem_t value = 0;
                        fscanf(file_from, "%lg", &value);
                        code->code_arr[IP] = value;
                        IP++;
                        break;
                    }

                    case REG: 
                    case MEM_REG: {
                        int reg_num = 0;
                        fscanf(file_from, "%d", &reg_num);
                        code->code_arr[IP] = reg_num;
                        IP++;
                        break;
                    }
                    
                    case REG_NUM:
                    case MEM_REG_NUM: {
                        stack_elem_t value = 0;
                        int reg_num = 0;
                        fscanf(file_from, "%lg %d", &value, &reg_num);
                        code->code_arr[IP] = value;
                        IP++;
                        code->code_arr[IP] = value;
                        IP++;
                        break;
                    }

                    default:
                        break;
                }
                
                break;
            }    

            case ADD:
            case SUB:          
            case MUL:
            case DIV:
            case OUT:
            case HLT:
                code->code_arr[IP] = action;
                IP++;
                break;

            case JMP: 
            case JB:             
            case JBE: 
            case JA: 
            case JAE: 
            case JE: 
            case JNE: {
                stack_elem_t value = 0;
                fscanf(file_from, "%lg", &value);
                
                code->code_arr[IP] = action;
                IP++;
                code->code_arr[IP] = value;
                IP++;

                break;
            }

            default: 
                fprintf(stderr, "%s:%s, %s(): Comand %d: No such command\n", __FILE__, __FILE__, __func__, command_number);    
                break;                // TODO придумать при дефолте че делать
        }
    }

    code->size = NUMBER_OF_INSTRUCTIONS;

    return 0;
}