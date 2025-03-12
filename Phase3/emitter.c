#include "global.h"

extern struct entry symtable[];

void emit(int t, int tval)
{
	switch(t) {
	case '+': printf("\npush r1\npop r2\nadd r2, r1\npush r2"); break;
    case '-': printf("\npush r1\npop r2\nsub r2, r1\npush r2"); break;
    case '*': printf("\npush r1\npop r2\nmult r2, r1\npush r2"); break;
    case '/': printf("\npush r1\npop r2\ndiv r2, r1\npush r2"); break;
	//	printf("%c", t); 
		break;
	case DIV:
		printf("DIV");
		break;

	case MOD:
		printf("MOD"); 
		break;
	case NUM:
		printf("%d", tval);
		break;
	case ID:
		printf("%s", symtable[tval].lexptr); 
		break;
	default:
		printf("token %d, tokenval %d\n", t, tval);
	}
}

