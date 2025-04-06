#include "global.h"
#define SYMMAX 100

//start function
int lookahead;
struct entry symtable[SYMMAX];


void stmt()
{
    int tok = tokenval;
    //rule: id = expr | if (expr) then stmt carry on with the rest of the code.
    switch(lookahead)
    {
        case ID:
            match(ID);
            match('=');
            expr(); 
            fprintf(output, "pop %s\n", symtable[tok].lexptr);
            break;
        case IF:
            match(IF);
            match('(');
            expr();
            match(')');
            match(THEN);
            stmt(); 
            break;
        case WHILE:
            match(WHILE);
            match('(');
            expr();
            match(')');
            match(DO);
            stmt();
            break;
        case BEGIN:
            match(BEGIN);
            CS();
            match(END);
            break;
        default: 
            printf("syntax error");
    }
}


void CS()
{
    if(lookahead == ID || lookahead == IF ||lookahead == WHILE || lookahead == BEGIN)
    {
        stmt();
        match(';');
        CS();
    }
}

void parse()
{
    lookahead = lexan();
    stmt();
    match(DONE);
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
    }
    else 
        error("Syntax error!");
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
            //fprintf(err, "line %d: Syntax error!", lineno);
    }
}

