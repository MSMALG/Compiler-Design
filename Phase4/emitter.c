#include "global.h"

extern struct entry symtable[];

void emit(int t, int tval)
{
	switch(t) {
	//case '+': printf("\npush r1\npop r2\nadd r2, r1\npush r2"); break;
	//or 
	case '+': fprintf(output,"\npop r1\npop r2\nadd r2, r1\npush r2\n"); break; //do it to other cases as well.
    case '-': fprintf(output,"\npop r1\npop r2\nsub r2, r1\npush r2\n"); break;
    case '*': fprintf(output,"\npop r1\npop r2\nmult r2, r1\npush r2\n"); break;
    case '/': fprintf(output,"\npop r1\npop r2\ndiv r2, r1\npush r2\n"); break;
	//	printf("%c", t); 
		//break;
	case DIV:
		//printf("DIV");
		fprintf(output,"\npop r1\npop r2\ndiv r2, r1\npush r2\n"); break;
		break;

	case MOD:
        fprintf(output,"\npop r1\npop r2\nmod r2, r1\npush r2\n"); break;
		break;
	case NUM:
		//printf("%d", tval);
		fprintf(output, "push %d\n", tval); //in all cases replace with fprintf
		break;
	case ID:
		fprintf(output, "push %s\n", symtable[tval].lexptr);
		break;
	default:
		fprintf(output,"token %d, tokenval %d\n", t, tval);
	}
}
