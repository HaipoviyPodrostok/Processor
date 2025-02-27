#include <stdio.h>
#include <stdlib.h>

#include "processor.h"

FILE* open_file(const char* file_name) {
    // FIXME assert
    FILE* file_from = fopen(file_name, "r");

    if (file_from == NULL) {
        fprintf(stderr, "%s:%s, %s(): Error while opening file \"programs.txt\"\n", __FILE__, __FILE__, __func__);
    }

    return file_from;
}

int make_code(FILE* file_from, code_t* code_arr) {
    
    size_t NUMBER_OF_INSTRUCTIONS = 0;
    
    fscanf(file_from, "%lu", &NUMBER_OF_INSTRUCTIONS);
    
    stack_elem_t* code = (stack_elem_t*) calloc(NUMBER_OF_INSTRUCTIONS, sizeof(stack_elem_t));   // TODO добавлять при переполнении
    
    size_t IP = 0;

    while (IP <= NUMBER_OF_INSTRUCTIONS - 1) {

        int cmd = 0;
        int action = 0;
        int command_number = 0;

        fscanf(file_from, "%d", &cmd);
        
        if (feof(file_from)) {
            break;         
        }

        else {
            fprintf(stderr, "%s:%s, %s(): Comand %d: No such command\n", __FILE__, __FILE__, __func__, command_number);
        }

        command_number++;

        switch (cmd) {
            
            case PUSH: {
                stack_elem_t value = 0;
                fscanf(file_from, "%lg", &value);               //TODO проверка IP
                
                code[IP] = PUSH;
                IP++;
                code[IP] = value;
                IP++;
                
                break;
            }    
                    
            case PUSH_R: {
                int reg_num = 0;
                fscanf(file_from, "%d", &reg_num);

                code[IP] = PUSH_R;
                IP++;
                code[IP] = reg_num;
                IP++;

                break;
            }
            
            case POP_R: {
                int reg_num = 0;
                fscanf(file_from, "%d", &reg_num);

                code[IP] = POP_R;
                IP++;
                code[IP] = reg_num;
                IP++;

                break;
            }

            case ADD:
                code[IP] = ADD;
                IP++;               
                break;

            case SUB:          
                code[IP] = SUB;
                IP++;
                break;

            case MUL:
                code[IP] = MUL;
                IP++;
                break;
            
            case DIV:
                code[IP] = DIV;
                IP++;
                break;

            case OUT:
                code[IP] = OUT;
                IP++;
                break;

            case HLT:
                code[IP] = HLT;
                IP++;
                break;

            case JMP: {
                stack_elem_t value = 0;
                fscanf(file_from, "%lg", &value);
                
                code[IP] = JMP;
                IP++;
                code[IP] = value;
                IP++;

                break;
            }

            case JB: {
                stack_elem_t value = 0;
                fscanf(file_from, "%lg", &value);
                
                code[IP] = JB;
                IP++;
                code[IP] = value;
                IP++;

                break;
            }

            case JBE: {
                stack_elem_t value = 0;
                fscanf(file_from, "%lg", &value);
                
                code[IP] = JBE;
                IP++;
                code[IP] = value;
                IP++;

                break;
            }

            case JA: {
                stack_elem_t value = 0;
                fscanf(file_from, "%lg", &value);
                
                code[IP] = JA;
                IP++;
                code[IP] = value;
                IP++;

                break;
            }

            case JAE: {
                stack_elem_t value = 0;
                fscanf(file_from, "%lg", &value);
                
                code[IP] = JAE;
                IP++;
                code[IP] = value;
                IP++;

                break;
            }

            case JE: {
                stack_elem_t value = 0;
                fscanf(file_from, "%lg", &value);
                
                code[IP] = JE;
                IP++;
                code[IP] = value;
                IP++;

                break;
            }

            case JNE: {
                stack_elem_t value = 0;
                fscanf(file_from, "%lg", &value);
                
                code[IP] = JNE;
                IP++;
                code[IP] = value;
                IP++;

                break;
            }

            default: 
                fprintf(stderr, "%s:%s, %s(): Comand %d: No such command\n", __FILE__, __FILE__, __func__, command_number);    
                break;                // TODO придумать при дефолте че делать
        }
    }

    code_arr->code_arr = code;
    code_arr->size = NUMBER_OF_INSTRUCTIONS;

    return 0;
}