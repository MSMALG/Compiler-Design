#include "global.h"

int lookahead;

void parse()
{
    //printf("Before lexan: %d\n", lookahead);
    lookahead = lexan();
    //printf("After lexan: %d\n", lookahead);
    while (lookahead != DONE) {
        expr(); match(';');
    }
    //printf("Parsing started...\n"); 
    //printf("Lookahead: %d\n", lookahead);
}

void expr()
{
    int t;
    term();
    while(1)
        switch (lookahead) {
            case '+': case '-':
                t = lookahead;
                match(lookahead); term(); emit(t, NONE);
                continue;
            default:
                return;
        }
}

void term()
{
    int t;
    factor();
    while(1)
        switch (lookahead) {
            case '*': case '/': case DIV: case MOD:
                t = lookahead;
                match(lookahead); factor(); emit(t, NONE);
                continue;
            default:
                return;
        }
}

void match(int t)
{
    if (lookahead == t)
    {
        lookahead = lexan();
        printf("Matching token: %d\n", t);
    }
    else 
        fprintf(err, "line %d: Syntax error!", lineno);
}

void factor()
{
    switch (lookahead) {
        case '(':
            match('('); expr(); match(')'); break;
        case NUM:
            emit(NUM, tokenval);
            match(NUM); break;
        case ID:
            emit(ID, tokenval); 
            match(ID); 
            break;
        default:
            error("syntax error");
            fprintf(err, "line %d: Syntax error!", lineno);
    }
}

