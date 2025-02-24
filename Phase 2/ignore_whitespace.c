#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int lookahead;

bool IL = false;

void expr(void);
void term(void);
void match(int);
void error(void);

int lexem() //fn to ignore whitespace 
{
    int t;
    while(1)
   {
        t = getchar();
        if ((t == ' ')|(t == '\n')|(t == '\t')); //meaning -> do nothing 
        else
            return (t);
    }
}

int main(void)
{
  lookahead = lexem();
  expr();
  putchar('\n'); /* adds trailing newline character */
}
void expr(void)
{
  term();
  while (1) {
    if (lookahead == '+') {
      match('+');
      term();
      if(IL)
            printf("pop r1\npop r2\nadd r2, r1\npush r2");
      else
            putchar('+');   //Putchar is not working, check why
    }
    else if (lookahead == '-') {
      match('-');
      term();
      if(IL)
            printf("pop r1\npop r2\nsub r2, r1\npush r2");
       else
            putchar('-'); //check
    }
    else
      break;
  }
}

void term(void)
{
  if (isdigit(lookahead)) {
    if(IL)
        printf("push %c\n", lookahead); //we used %c instead of d cuz lookahead is a char since we read its ascii int code using getchar
    else
        putchar(lookahead);
        match(lookahead);  }
  else
    error();
}

void match(int t)
{
  if (lookahead == t)
    lookahead = lexem();
  else
    error();
}

void error(void)
{
  printf("syntax error\n"); /* print error message */
  exit(1); /* then halt */
}