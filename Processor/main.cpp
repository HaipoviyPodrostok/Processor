#include <stdio.h>
#include "processor.h"
#include "../Stack/stack_structs.h"
#include "../Stack/stack_create.h"
#include "../Stack/stack_funcs.h"
#include "../Stack/verificator.h"

int main() {

    FILE* file_from = NULL;
    file_from = reading_from_file();

    if (file_from == NULL) {
        return FILE_OPENING_ERROR;
    }

    stack_t stack_1 = {NULL, 0, 0};

    int proc_completion = processing(&stack_1, file_from);
    
    fclose (file_from);

    return proc_completion;
}

FILE* reading_from_file() {
    
    FILE* file_from = fopen("../ProgramFiles/programs_v2.txt", "r");

    if (file_from == NULL) {
        fprintf(stderr, "%s:%s, %s(): Error while opening file \"programs.txt\"", __FILE__, __FILE__, __func__);
    }

    return file_from;
}

int processing(stack_t* stk, FILE* file_from) {
    
    stack_ctor(stk, 10);
    
    verificator(stk);

    while (true) {

        int cmd = 0;
        int action = 0;
        stack_elem_t a = 0;
        stack_elem_t b = 0;

        fscanf(file_from, "%d", &cmd);

        if (cmd == 1) {
            action = IN;
        } 

        else if (cmd == 2) {
            action = ADD; 
        }
        
        else if (cmd == 3) {
            action = SUB;
        }

        else if (cmd == 4) {
            action = MUL;
        }

        else if (cmd == 5) {
            action = DIV;
        }

        else if (cmd == 6) {
            action = OUT;
        }

        else if (cmd == 7) {
            action = HLT;
        }

        else if (cmd == EOF) {
            fprintf(stderr, "%s:%s, %s(): Warning: Reached the end of input file, but processor still working", __FILE__, __FILE__, __func__);
            return UNDEFINED_BEHAVIOR_ERROR;           
        }

        else {
            fprintf(stderr, "%s:%s, %s(): Error: No such command or program file is empty", __FILE__, __FILE__, __func__);
            return SYNTAX_ERROR;
        }

        switch (action) {

            case IN: {
                stack_elem_t value = 0;
                fscanf(file_from, "%lg", &value);
                
                stack_push(stk, value);                                                                                                                                        
                verificator(stk);

                break;
            }    
                      
            case ADD:
                a = stack_pop(stk);
                verificator(stk);
                
                b = stack_pop(stk);
                verificator(stk);
                
                stack_push(stk, a + b);
                verificator(stk);
                
                break;

            case SUB:          
                a = stack_pop(stk);
                verificator(stk);
                
                b = stack_pop(stk);
                verificator(stk);
                
                stack_push(stk, b - a);
                verificator(stk);

                break;

            case MUL:
                a = stack_pop(stk);
                verificator(stk);
                
                b = stack_pop(stk);
                verificator(stk);
                
                stack_push(stk, a * b);
                verificator(stk);

                break;
            
            case DIV:
                a = stack_pop(stk);
                verificator(stk);
                
                b = stack_pop(stk);
                verificator(stk);
                
                stack_push(stk, a / b);
                verificator(stk);

                break;

            case OUT:
                printf("%lg\n", stack_pop(stk));
                verificator(stk);
                
                break;

            case HLT:
                stack_dump(stk);
                stack_dtor(stk);  

                return 0;

            default:
                ;                
        }
    }
    
    return 0;
}