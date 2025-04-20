#include "global.h"

struct entry keywords[] = {
	"div", DIV, 
	"mod", MOD,
	"if", IF,
	"while", WHILE, //carry on with the rest of the grammar 
	"do", DO,
	"then", THEN,
	"begin", BEGIN,
	"end", END,
	"function", FUNCTION,
	"main", MAIN,
	0, 0
};


void init()
{
	struct entry *p;
	for (p = keywords; p->token; p++)
		insert(p->lexptr, p->token);
}
