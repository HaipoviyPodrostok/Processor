#include <stdio.h>
#include <assembler.h>

int main() {
    FILE* file_from = fopen("program.txt", "r");
    
    if (file_from == NULL) {
        printf("Error while opening file");
        return 1;
    }

    while (true) {
        
        char cmd[100] = "";
        fscanf(file_from, "%s", cmd);
        
        const int action = 0; 
        
        if (strcasecmp(cmd, "push")) {
            action = PUSH;
        }
        
        else if (strcasecmp(cmd, "add")) {
            action = ADD;
        } 

        else if (strcasecmp(cmd, "sub")) {
            action = SUB;
        }

        else if (strcasecmp(cmd, "mul")) {
            action = MUL;
        }  

        else if (strcasecmp(cmd, "div")) {
            action = DIV;
        }
        
        else if (strcasecmp(cmd, "out")) {
            action = OUT;
        }

        else if (strcasecmp(cmd, "hlt")) {
            action = HLT;
        })

        switch (action)) {
        
            case :
                break;
            
            default:
                break;
        }
    }
    return 0;
}

