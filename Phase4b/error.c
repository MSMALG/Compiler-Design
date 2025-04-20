#include "global.h"


void error(char* m)
{
	//fprintf(stderr, "line %d: %s\n", lineno, m);
	fprintf(err, "line %d: %s\n", lineno, m);
	exit(1);
}
