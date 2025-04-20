#include "global.h"
#define SYMMAX 100

//start function
int lookahead;
struct entry symtable[SYMMAX];

void func1()
{
    printf("%s:\n",symtable[tokenval].lexptr);
}

void func2()
{
    printf("ret\n");
}

void func3(int tok)
{
    printf("call %s:\n",symtable[tok].lexptr);
}

void main1()
{
    printf("main:\n");
}

void main2()
{
    printf("exit\n");     
}

void funcdec()
{
    match(FUNCTION);
    func1();
    match(ID);
    match('(');
    match(')');
    match(BEGIN);
    CS();
    match(END);
    func2();
}

void dec()
{
    //do a loop to recursively call the fn dec again
    // we call the fn dec when we need to call mainfunction next. When mainfunction runs dec stops 
    // mainfunction runs when we call the fun main
    while (lookahead != MAIN)
    { 
        funcdec();
        match(';');
    }
}

void mainfun()
{
    match(MAIN);
    main1();
    match('(');
    match(')');
    match(BEGIN);
    CS();
    match(END);
    main2();

}

void rest(int t)
{
    switch (lookahead)
    {
    case '=':
         match('=');
         expr();
         fprintf(output, "pop %s\n", symtable[t].lexptr);
         break;
     case '(':
         match('(');
         match(')');
         func3(t);
         break;
    default: printf("syntax error");
    }
    //we can also use switch which would be better
    /*if (lookahead == '=')
    {
        match('=');
        expr();
        fprintf(output, "pop %s\n", symtable[tokenval].lexptr);
    }
    else if (lookahead == '(')
    {
        match('(');
        match(')');
        func3();
    }*/
}

void stmt()
{
    int tok = tokenval;
    //rule: id = expr | if (expr) then stmt carry on with the rest of the code.
    switch(lookahead)
    {
        case ID:
            match(ID);
            rest(tok);
            break;
        case IF: //we need to test if expr is true or not. If T then don stmt if not skip the stmt 
            match(IF);                          
            match('(');
            expr();
            fprintf(output, "pop r2\ncomp r2,0\nbe else\n");
            match(')');
            match(THEN);
            stmt(); 
            fprintf(output, "else:\n");
            break;
        case WHILE:
            match(WHILE);
            fprintf(output, "while:\n");            
            match('(');
            expr();
            fprintf(output, "pop r2\ncomp r2,0\nbe end while\n");
            match(')');
            match(DO);
            stmt();
            fprintf(output, "b while\nend while:\n");
            break;
        case BEGIN:
            match(BEGIN);
            fprintf(output, "begin:\n");
            CS();
            match(END);
            fprintf(output, "end\n");
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

void start()
{
    dec();
    mainfun();
    match(DONE);
}

void parse() //start fn 
{
    lookahead = lexan();
    stmt();
    start();
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

