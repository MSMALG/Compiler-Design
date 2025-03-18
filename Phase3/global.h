#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BSIZE  128
#define NONE   -1
#define EOS    '\0'

#define NUM    256
#define DIV    257
#define MOD    258
#define ID     259
#define DONE   260

int tokenval;
int lexan();
void parse();
void expr();
void term();
void factor();
void match(int t);
void emit(int t, int tval);
void init();
void error(char* m);
int lookup(char s[]);
int insert(char s[], int tok);

int lineno;
int lookahead;
FILE *output, *err, *input;

struct entry {
   char *lexptr;
   int token;
   };

#endif
