#include <stdio.h>
#include <stdlib.h>
#include "global.h"



int main() {
    output = fopen("file.obj", "w");
    err = fopen("file.err", "w");
    input = fopen("file.exp", "r");  

    //printf("before\n");
    
    int t = getc(input);  //Read the first character from the input file
    //printf("eee");
    
    ungetc(t, input);    //Push the character back to the stream

    init();
    parse();

    fclose(output);
    fclose(err);
    fclose(input);

    return 0;
}


