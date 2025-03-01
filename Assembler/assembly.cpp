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
        fscanf(file_from, "%s", cmd);  //обработать ошибку
        
        if (feof(file_from)) {
            break;
        }
        
        int action = 0; 
        
        const char* commands[] = {"push", "pop", "add", "sub", "mul", "div", "out", "hlt", "jmp", "jb", "jbe", "ja", "jae", "je", "jne"};
        //вынести все команды в константы (push, push_r ... )
        
        static_assert(PUSH == 0);

        for(int i = PUSH; i < SIZE__ ; i++) {  
            
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
        
            case PUSH:
            case POP: {
                
                int push_action = 0;           
                char push_value_str[100] = "";
                
                fscanf(file_from, "%s", push_value_str);
                
                if (strchr(push_value_str, '[')) {
                    
                    if (strchr(push_value_str, 'x')) {
                        
                        if (strchr(push_value_str, '+')) {
                            push_action = MEM_REG_NUM;
                        }

                        else {
                            push_action = MEM_REG;
                        }
                    }

                    else {
                        push_action = MEM_NUM;
                    }
                }

                else if (strchr(push_value_str, 'x')) {
                    
                    if (strchr(push_value_str, '+')) {
                        push_action = REG_NUM;
                    } 

                    else {
                        push_action = REG;
                    }
                }
                
                else {
                    push_action = NUM;
                }

                switch (push_action) {

                    case NUM: {
                        double value = 0;
                        sscanf(push_value_str, "%lg", &value);
                        fprintf(file_to, "%d %d %lg\n", action, push_action, value);    
                        IP += 3;
                        break;
                    }

                    case REG: {
                        char reg_num[100] = "";
                        sscanf(push_value_str, "%s", reg_num);
                        fprintf(file_to, "%d %d %d\n", action, push_action, (reg_num[0] - 'a'));
                        IP += 3;
                        break;
                    }

                    case REG_NUM: {
                        double value = 0;
                        char reg_num[100] = "";
                        sscanf(push_value_str, "%s %lg", reg_num, &value);      //TODO обработать когда наоборот
                        fprintf(file_to, "%d %d %lg %d\n", action, push_action, value, (reg_num[0] - 'a'));   // сначала число, потом регистр
                        IP += 4;
                        break;
                    }

                    case MEM_NUM: {
                        double value = 0;
                        sscanf(push_value_str, "[%lg]", &value);
                        fprintf(file_to, "%d %d %lg\n", action, push_action, value);
                        IP += 3;
                        break;
                    }

                    case MEM_REG: {
                        char reg_num[100] = "";
                        sscanf(push_value_str, "[%s]", reg_num);
                        fprintf(file_to, "%d %d %d\n", action, push_action, (reg_num[0] - 'a'));
                        IP += 3;
                        break;
                    }
                    
                    case MEM_REG_NUM: {
                        double value = 0;
                        char reg_num[100] = "";
                        sscanf(push_value_str, "[%s %lg]", reg_num, &value);
                        fprintf(file_to, "%d %d %lg %d\n", action, push_action, value, (reg_num[0] - 'a'));
                        IP += 4;
                        break;
                    }

                    default:
                        break;    //TODO обработать
                }                  
                break;
            }
            // FIXME сделать бинарник

            case ADD:
            case SUB:
            case MUL:
            case DIV:
            case OUT:
            case HLT:
                fprintf(file_to, "%d\n", action);
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
                    fprintf(file_to, "%d %d\n", action, labels->label_arr[value]);
                }
                
                else {
                    int value = 0;
                    sscanf(jmp_value_str, "%d", &value);
                    fprintf(file_to, "%d %d\n", action, value);  
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

