#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>

#include "assembler.h"

int first_pass(FILE* file_from, FILE* file_to, labels_t* labels) {

    size_t IP = 0;

    while (true) {

        char cmd[100] = "";
        int fscanf_result = 0;
        fscanf_result = fscanf(file_from, "%s", cmd);  //TODO обработать ошибку        
        
        if (fscanf_result == EOF) {
            break;
        }
        
        else if (strchr(cmd, 'j')) {
            fscanf(file_from, "%s", cmd);
        }
        
        else if (strchr(cmd, ':')) {
            int mark_num = 0;
            sscanf(cmd, "%d:", &mark_num);
            labels->label_arr[mark_num] = (int)IP;
            IP--;   // метки не считает
        }

        IP++;
    }
    
    fprintf(file_to, "%lu\n", IP);
    
    return 0;
}

int second_pass(FILE* file_from, FILE* file_to, labels_t* labels) {
    
    size_t IP = 0;

    fseek(file_from, 0, SEEK_SET);

    while (true) {

        char cmd[100] = "";
        int fscanf_result = 0;
        fscanf_result = fscanf(file_from, "%s", cmd);  //обработать ошибку
        size_t action = 0; 
        
        const char* commands[] = {"push", "push_r", "pop_r", "add", "sub", "mul", "div", "out", "hlt", "jmp", "jb", "jbe", "ja", "jae", "je", "jne"};
        //вынести все комманды в константы (push, push_r ... )
        
        static_assert(PUSH == 0);

        for(size_t i = PUSH; i < SIZE__ ; i++) {  
            
            if (strcasecmp(cmd, commands[i]) == 0) {
                action = i;                                           //TODO переименовать енамы
                break;
            }

            else if (strchr(cmd, ':')) {
                action = MARK;
            }
        }    
        
        if (fscanf_result == EOF) {
            break;
        }

        switch (action) {
        
            case PUSH: {
                double value = 0;
                fscanf(file_from, "%lg", &value);
                fprintf(file_to, "%lu %lg\n", action, value);      
                IP += 2;
                break;
            }
            // FIXME сделать бинарник

            case PUSH_R: 
            case POP_R: {
                char reg_num[100] = "";
                fscanf(file_from, "%s", reg_num);
                fprintf(file_to, "%lu %d\n", action, (reg_num[0] - 'a'));
                IP += 2;
                break;
            }

            case ADD:
            case SUB:
            case MUL:
            case DIV:
            case OUT:
            case HLT:
                fprintf(file_to, "%lu\n", action);
                IP++;
                break;

            case JMP: 
            case JB:
            case JBE:
            case JA:
            case JAE:
            case JE:
            case JNE: {    
                
                char jmp_value_str[100] = "";

                fscanf(file_from, "%s", jmp_value_str);
                
                if (strchr(jmp_value_str, ':')) {
                    int value = 0;
                    sscanf(jmp_value_str, "%d:", &value);
                    fprintf(file_to, "%lu %d\n", action, labels->label_arr[value]);
                }
                
                else {
                    int value = 0;
                    sscanf(jmp_value_str, "%d", &value);
                    fprintf(file_to, "%lu %d\n", action, value);  
                }
                
                IP += 2;
                break;
            }

            case MARK:
                break;

            
            default:
                break;
        }
    }
    
    fclose(file_from);
    fclose(file_to);
    
    return 0;
}

