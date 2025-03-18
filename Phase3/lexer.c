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
                        fprintf(err, "line %d: Compiler error: Lexeme too long\n", lineno);
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
                           fprintf(err, "line %d: Unexpected character '%c' (ASCII: %d)\n", lineno, t, t);
                           return t;
                           }
                    }
                }
