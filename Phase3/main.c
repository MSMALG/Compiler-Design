#include <stdio.h>
#include <stdlib.h>
#include "global.h"


int main() {
    output = fopen("output.obj", "w");
    err = fopen("file.err", "w");
    input = fopen("file.exp", "r");  // Open user-provided input file

    if (!output) {
        perror("Error opening output file");
        return 1;
    }
    if (!err) {
        perror("Error opening error file");
        return 1;
    }
    if (!input) {
        perror("Error opening input file");
        return 1;
    }

    //printf("before\n");

    //Read the first character from the input file
    int t = getc(input);
    //printf("eee");
    
    if (t == EOF) {
        fprintf(err, "Error: Input file is empty or invalid\n");
        return 1;
    }
    
    //Push the character back to the stream
    ungetc(t, input);

    printf("Infix expression read from input file\n");

    init();
    parse();

    fclose(output);
    fclose(err);
    fclose(input);

    return 0;
}
