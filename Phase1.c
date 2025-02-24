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

//Expr and rest functions
void expr(void)
{
  term();
  while (1) {
    if (lookahead == '+') {
      match('+');
      term();
      putchar('+');
    }
    else if (lookahead == '-') {
      match('-');
      term();
      putchar('-');
    }
    else
      break;
  }
}

//Term function
void term(void)
{
  if (isdigit(lookahead)) {
    putchar(lookahead);
    match(lookahead);  }
  else
    error();
}

//Match Function
void match(int t)
{
  if (lookahead == t)
    lookahead = getchar();
  else
    error();
}

//Error Function
void error(void)
{
  printf("syntax error\n"); /* print error message */
  //exit(1); /* then halt */
}
