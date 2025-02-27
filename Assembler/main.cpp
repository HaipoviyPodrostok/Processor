#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "assembler.h"

int main(int argc, char* argv[]) {
    
    if (argc < 3) {
        fprintf(stderr, "There are not enough arguments in the command line");
        return TOO_FEW_ARGUMENTS;
    }

    else if (argc > 3) {
        fprintf(stderr, "Too much arguments in the command line");
        return TOO_FEW_ARGUMENTS;
    }
    
    FILE* file_from = fopen(argv[1], "r");   //"../ProgramFiles/programs.txt"
    if (file_from == NULL) {
        fprintf(stderr, "%s:%s, %s(): Error while opening file \"programs.txt\"", __FILE__, __FILE__, __func__);
        return ERROR_WHILE_OPENING_FILE;
    }
    
    FILE* file_to = fopen(argv[2], "w");   //"../ProgramFiles/programs_v2.txt"
    if (file_to == NULL) {
        printf("%s:%s, %s(): Error while opening file \"programs_v2.txt\"", __FILE__, __FILE__, __func__);
        return ERROR_WHILE_OPENING_FILE;
    }

    labels_t labels_1 = {NULL, 20, 0};
    
    
    labels_1.label_arr = (int*) calloc(labels_1.size, sizeof(int));
    
    first_pass(file_from, file_to, &labels_1);
    second_pass(file_from, file_to, &labels_1);

    free(labels_1.label_arr);
    return 0;
}
