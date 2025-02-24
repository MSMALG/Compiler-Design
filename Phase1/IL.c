#include <stdio.h>
#include <ctype.h>

int lookahead;

void expr(void);
//void rest(void);
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
      printf("pop r1\npop r2\nadd r2, r1\npush r2");
    }
    else if (lookahead == '-') {
      match('-');
      term();
      printf("pop r1\npop r2\nsub r2, r1\npush r2");
    }
    else
      break;
  }
}

void term(void)
{
  if (isdigit(lookahead)) {
    //putchar(lookahead);
    printf("push %c\n", lookahead); //we used %c instead of d cuz lookahead is a char since we read its ascii int code using getchar
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
