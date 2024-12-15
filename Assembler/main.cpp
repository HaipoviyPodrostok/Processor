#include <stdio.h>
#include <strings.h>
#include <cstdlib>
#include "assembler.h"

int main() {
    FILE* file_from = fopen("../ProgramFiles/programs.txt", "r");
    
    if (file_from == NULL) {
        printf("%s:%s, %s(): Error while opening file \"programs.txt\"", __FILE__, __FILE__, __func__);
        return 1;
    }

    FILE* file_to = fopen("../ProgramFiles/programs_v2.txt", "w");

    if (file_from == NULL) {
        printf("%s:%s, %s(): Error while opening file \"programs_v2.txt\"", __FILE__, __FILE__, __func__);
        return 1;
    }

    while (true) {
        
        char cmd[100] = "";
        int fscanf_result = 0;
        fscanf_result = fscanf(file_from, "%s", cmd);
        
        int action = 0; 
        
        if (strcasecmp(cmd, "push") == 0) {
            action = PUSH;
        }
        
        else if (strcasecmp(cmd, "add") == 0) {
            action = ADD;
        } 

        else if (strcasecmp(cmd, "sub") == 0) {
            action = SUB;
        }

        else if (strcasecmp(cmd, "mul") == 0) {
            action = MUL;
        }  

        else if (strcasecmp(cmd, "div") == 0) {
            action = DIV;
        }
        
        else if (strcasecmp(cmd, "out") == 0) {
            action = OUT;
        }

        else if (strcasecmp(cmd, "hlt") == 0) {
            action = HLT;
        }
        
        else if (fscanf_result == EOF) {
            break;
        }

        double value = 0;
        
        fscanf(file_from, "%lg", &value);

        switch (action) {
        
            case PUSH:
                fprintf(file_to, "1 %lg\n", value);
                break;

            case ADD:
                fprintf(file_to, "2 \n");
                break;
            
            case SUB:
                fprintf(file_to, "3 \n");
                break;
            
            case MUL:
                fprintf(file_to, "4 \n");
                break;

            case DIV:
                fprintf(file_to, "5 \n");
                break;

            case OUT:
                fprintf(file_to, "6 \n");
                break;
            
            case HLT:
                fprintf(file_to, "7 \n");
                break;

            default:
                break;
        }
    }

    fclose(file_from);
    fclose(file_to);
    
    return 0;
}

