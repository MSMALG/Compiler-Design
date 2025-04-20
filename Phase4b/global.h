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
#define IF 261
#define THEN 262
#define WHILE 263   //carry on with the rest of the grammar
#define DO 264
#define BEGIN 265
#define END 266
#define FUNCTION 267
#define MAIN 268

int tokenval;
int lexan();
void stmt();
void CS();
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
