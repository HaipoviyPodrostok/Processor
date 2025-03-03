#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>

#include "assembler.h"

int pack_byte(u_int8_t command, u_int8_t arg_type, FILE* file_to) {
    
    u_int8_t command_byte = (u_int8_t)((command & 0x1F) << 3 | (arg_type & 0x07));               // 0x1F = 00011111    0x07 = 00000111
    
    if (fwrite(&command_byte, sizeof(command_byte), 1, file_to) != 1) {
        fprintf(stderr, "%s:%s, %s(): ERROR: command byte writing error.\n", __FILE__, __FILE__, __func__);
        return COMMAND_BYTE_WRITING_ERROR;
    }

    return 0;
}

int first_pass(FILE* file_from, FILE* file_to, labels_t* labels) {

    size_t instruction_num = 0;

    while (true) {

        char cmd[100] = "";
        fscanf(file_from, "%s", cmd);  //TODO обработать ошибку        
        
        if (feof(file_from)) {
            break;
        }
        
        if ((strcasecmp(cmd, "push") * strcasecmp(cmd, "pop")) == 0) {
            instruction_num++;
        }

        else if (strchr(cmd, 'j')) {
            fscanf(file_from, "%s", cmd);
            instruction_num++;
        }
        
        else if (strchr(cmd, ':')) {
            int mark_num = 0;
            sscanf(cmd, "%d:", &mark_num);
            labels->label_arr[mark_num] = (int)instruction_num;
            instruction_num--;   // метки не считает
        }
        
        instruction_num++;
    }
    
    fwrite(&instruction_num, sizeof(instruction_num), 1, file_to);
   
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
        
        int command = 0; 
        
        const char* commands[] = {"push", "pop", "add", "sub", "mul", "div", "out", "hlt", "jmp", "jb", "jbe", "ja", "jae", "je", "jne"};
        //вынести все команды в константы (push, push_r ... )
        
        static_assert(PUSH == 0); // спросить у вовы

        for(int i = PUSH; i < SIZE__ ; i++) {  
            
            if (strcasecmp(cmd, commands[i]) == 0) {
                command = i;                                           //TODO переименовать енамы
                break;
            }

            else if (strchr(cmd, ':')) {
                command = MARK;
            }
        }    
        
        if (fscanf_result == EOF) {
            break;
        }

        int push_action = 0;      

        switch (command) {
        
            case PUSH:
            case POP: {
                     
                char value_str[100] = "";
                
                fscanf(file_from, "%s", value_str);
                
                if (strchr(value_str, '[')) {
                    
                    if (strchr(value_str, 'x')) {
                        
                        if (strchr(value_str, '+')) {
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

                else if (strchr(value_str, 'x')) {
                    
                    if (strchr(value_str, '+')) {
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
                        
                        //PACKING (COMMAND + ARG_TYPE) BYTE:
                        pack_byte((u_int8_t)command, (u_int8_t)push_action, file_to);
                        
                        //PACKING REG_NUM BYTE:                      
                        double value = 0;
                        sscanf(value_str, "%lg", &value);
                        fwrite(&value, sizeof(value), 1, file_to);
                        
                        IP += 3;
                        break;
                    }

                    case REG: {
                        
                        //PACKING (COMMAND + ARG_TYPE) BYTE:
                        pack_byte((u_int8_t)command, (u_int8_t)push_action, file_to);
                        
                        //PACKING REG_NUM BYTE:
                        char reg_str[10] = "";
                        sscanf(value_str, "%s", reg_str);                        
                        u_int8_t reg_num = (u_int8_t)(reg_str[0] - 'a');
                        fwrite(&reg_num, sizeof(reg_num), 1, file_to);
                        
                        IP += 3;
                        break;
                    }

                    case REG_NUM: {
                        
                        //PACKING (COMMAND + ARG_TYPE) BYTE:
                        pack_byte((u_int8_t)command, (u_int8_t)push_action, file_to);

                        double value = 0;
                        char reg_str[10] = "";
                                               
                        if (sscanf(value_str, "%lg + %s", &value, reg_str) != 2) {                            
                            if (sscanf(value_str, "%s + %lg", reg_str, &value) != 2) {                               
                                fprintf(stderr, "%s:%s, %s(): ERROR: reding error.\n", __FILE__, __FILE__, __func__);
                                return READING_ERROR;
                            }
                        }
                        
                        //PACKING VALUE:                                         
                        fwrite(&value, sizeof(value), 1, file_to);                        
                        
                        //PACKING REG_NUM:
                        u_int8_t reg_num = (u_int8_t)(reg_str[0] - 'a');
                        fwrite(&reg_num, sizeof(reg_num), 1, file_to);
                        
                        IP += 4;
                        break;
                    }

                    case MEM_NUM: {
                        
                        //PACKING (COMMAND + ARG_TYPE) BYTE:
                        pack_byte((u_int8_t)command, (u_int8_t)push_action, file_to);

                        //PACKING VALUE: 
                        double value = 0;
                        sscanf(value_str, "[%lg]", &value);
                        fwrite(&value, sizeof(value), 1, file_to);
                        
                        IP += 3;
                        break;
                    }

                    case MEM_REG: {
                        
                        //PACKING (COMMAND + ARG_TYPE) BYTE:
                        pack_byte((u_int8_t)command, (u_int8_t)push_action, file_to);
                        
                        //PACKING REG_NUM BYTE:
                        char reg_str[10] = "";
                        sscanf(value_str, "[%s]", reg_str);                        
                        u_int8_t reg_num = (u_int8_t)(reg_str[0] - 'a');
                        fwrite(&reg_num, sizeof(reg_num), 1, file_to);

                        IP += 3;
                        break;
                    }
                    
                    case MEM_REG_NUM: {
                        
                        //PACKING (COMMAND + ARG_TYPE) BYTE:
                        pack_byte((u_int8_t)command, (u_int8_t)push_action, file_to);

                        //PACKING VALUE AND REG_NUM:
                        double value = 0;
                        char reg_str[10] = "";
                        
                        if ((sscanf(value_str, "[%lg + %s]", &value, reg_str) != 2) || (sscanf(value_str, "[%lg+%s]", &value, reg_str) != 2)) {              
                            if ((sscanf(value_str, "[%lg + %s]", &value, reg_str) != 2) || (sscanf(value_str, "[%lg+%s]", &value, reg_str) != 2)) {                               
                                fprintf(stderr, "%s:%s, %s(): ERROR: reding error.\n", __FILE__, __FILE__, __func__);
                                return READING_ERROR;
                            }
                        }

                        fwrite(&value, sizeof(value), 1, file_to);
                        
                        u_int8_t reg_num = (u_int8_t)(reg_str[0] - 'a');
                        fwrite(&reg_num, sizeof(reg_num), 1, file_to);
                        
                        IP += 4;
                        break;
                    }

                    default:
                        break;    //TODO обработать
                }                  
                break;
            }

            case ADD:
            case SUB:
            case MUL:
            case DIV:
            case OUT:
            case HLT:
                pack_byte((u_int8_t)command, (u_int8_t)push_action, file_to);
                IP++;
                break;

            case JMP: 
            case JB:
            case JBE:
            case JA:
            case JAE:
            case JE:
            case JNE: {    
                
                //PACKING COMMAND BYTE:
                pack_byte((u_int8_t)command, (u_int8_t)push_action, file_to);
                
                //PACKING JMP_ADR BYTE:
                char jmp_value_str[100] = "";
                fscanf(file_from, "%s", jmp_value_str);
                
                if (strchr(jmp_value_str, ':')) {
                    int label_num = 0;
                    sscanf(jmp_value_str, "%d:", &label_num);
                    u_int8_t jmp_adr = (u_int8_t)labels->label_arr[label_num]; 
                    fwrite(&jmp_adr, sizeof(jmp_adr), 1, file_to);
                }
                
                else {
                    int value = 0;
                    sscanf(jmp_value_str, "%d", &value);
                    u_int8_t jmp_adr = (u_int8_t)value; 
                    fwrite(&jmp_adr, sizeof(jmp_adr), 1, file_to);  
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
    
    return 0;
}

