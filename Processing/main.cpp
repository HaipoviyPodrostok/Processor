#include <stdio.h>
#include <stdlib.h>

#include "processor.h"
#include "../Stack/stack_structs.h"
#include "../Stack/stack_create.h"
#include "../Stack/stack_funcs.h"
#include "../Stack/verificator.h"

int main(int argc, char* argv[]) { 

    if (argc < 2) {
        fprintf(stderr, "There are not enough arguments in the command line");
        return TOO_FEW_ARGUMENTS;
    }

    else if (argc > 2) {
        fprintf(stderr, "Too much arguments in the command line");
        return TOO_FEW_ARGUMENTS;
    }
    
    FILE* file_from = fopen(argv[1], "r");

    if (file_from == NULL) {
        fprintf(stderr, "%s:%s, %s(): Error while opening file \"programs.txt\"\n", __FILE__, __FILE__, __func__);
        return FILE_OPENING_ERROR;
    }

    code_t code_1 = {NULL, 0, 0};
    
    stack_t stack_1 = {NULL, 0, 0};
    stack_ctor(&stack_1, 10);

    if (make_code(file_from, &code_1) != 0) {
        return 1;                   // TODO назвать ошибку
    }

    processing(&code_1, &stack_1);

    free(code_1.code_arr);
    fclose (file_from);

    return 0;
}

// int processing(stack_t* stk) {    // TODO сюда code 
    
//     stack_ctor(stk, 10);
    
//     verificator(stk);

//     stack_elem_t reg_array[4] = {};

    
        

//         // switch (action) {

//         //     case IN: {
//         //         stack_elem_t value = 0;
//         //         fscanf(file_from, "%lg", &value);          
//         //         stack_push(stk, value);
                
//         //         code[IP] = IN;
//         //         IP++;
//         //         code[IP] = value;
//         //         IP++;
                
//         //         break;
//         //     }    
                      
//         //     case ADD:
//         //         a = stack_pop(stk);
//         //         b = stack_pop(stk);
//         //         stack_push(stk, a + b); 
                
//         //         code[IP] = ADD;
//         //         IP++;               
//         //         code[IP] = 0;
//         //         IP++;

//         //         break;

//         //     case SUB:          
//         //         a = stack_pop(stk);
//         //         b = stack_pop(stk);
//         //         stack_push(stk, b - a);
                
//         //         code[IP] = SUB;
//         //         IP++;
//         //         code[IP] = 0;
//         //         IP++;

//         //         break;

//         //     case MUL:
//         //         a = stack_pop(stk);
//         //         b = stack_pop(stk);
//         //         stack_push(stk, a * b);
                
//         //         code[IP] = MUL;
//         //         IP++;
//         //         code[IP] = 0;
//         //         IP++;

//         //         break;
            
//         //     case DIV:
//         //         a = stack_pop(stk);                
//         //         b = stack_pop(stk);
//         //         stack_push(stk, a / b);

//         //         code[IP] = DIV;
//         //         IP++;
//         //         code[IP] = 0;
//         //         IP++;

//         //         break;

//         //     case OUT:
//         //         printf("%lg\n", stack_pop(stk));   
                
//         //         code[IP] = OUT;
//         //         IP++;
//         //         code[IP] = 0;
//         //         IP++;

//         //         break;

//         //     case HLT:
//         //         stack_dump(stk);
//         //         stack_dtor(stk);  

//         //         code[IP] = HLT;
//         //         IP++;
//         //         code[IP] = 0;
//         //         IP++;

//         //         return 0;

//         //     case JMP:
//         //         code[IP] = 

//         //     default:
//         //         ;                // TODO придумать при дефолте че делать
//         // }
//     }
    
//     return 0;
// }