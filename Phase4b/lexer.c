#include "global.h"

char lexbuf[BSIZE];
int lineno = 1;
int tokenval = NONE;
extern struct entry symtable[];

int lexan()
{
	int t;

	while(1) {
		t = getc(input);
		if (t == ' ' || t == '\t');
		else if (t == '\n')
		          lineno = lineno + 1;
		        else if (isdigit (t)) {
		           ungetc(t, input);
		           fscanf(input,"%d", &tokenval);
		           return NUM;
		        }
                else if (isalpha(t)) {
                    int p, b = 0;
                    while (isalnum(t)) {
                        lexbuf[b] = t;
                        t = getc(input);
                        b = b + 1;
                        if (b >= BSIZE)
                        error("Compiler Error\n"); //show in error file the error mssg
                    }
                
                    lexbuf[b] = EOS;
                    if (t != EOF)
                        ungetc(t, input);
                    p = lookup(lexbuf);
                    if(p == 0)
                        p = insert(lexbuf, ID);
                    tokenval = p;
                    return symtable[p].token;
                    }
                    else if (t == EOF)
                        return DONE;
                        else {
                           tokenval = NONE;
                           //error("Unexpected character\n"); //if an undefined char is read show this error in the error file err
                           return t;
                           }
                    }
                }