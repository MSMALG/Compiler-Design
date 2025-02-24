#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int lookahead;

bool IL = true;

void expr(void);
void term(void);
void match(int);
void error(void);

int main(void)
{
  lookahead = getchar();
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
            putchar('+');
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
    lookahead = getchar();
  else
    error();
}

void error(void)
{
  printf("syntax error\n"); /* print error message */
  exit(1); /* then halt */
}
