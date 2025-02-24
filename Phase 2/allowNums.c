#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#define NUM 256

int lookahead;
int tokenval;
int nbrline = 1;

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
        if ((t == ' ')|(t == '\t')); //meaning -> do nothing 
        else if(t == '\n') //Calc num of lines/elems
        {
          nbrline++;
        }
        else
            if (isdigit(t))
            {  
                              //eg: 125, scanf will read 25 only cuz first on is read already
                ungetc(t, stdin); //we use ungetc to read first elem 1
                scanf("%d", &tokenval); //reads from second elem, so we have whole num 125
                return NUM;
            }
            return t; //Get the ASCII Code if it is not a digit, just first elem.
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
    if (lookahead == NUM)
    {
        if(IL)
            printf("push %d\n", tokenval); //we used %c instead of d cuz lookahead is a char since we read its ascii int code using getchar
        else
            printf("%d",tokenval);
            match(lookahead);  
    }
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
