#include <stdlib.h>
#include <stdio.h>

struct complex
{
        int real;
        int im;
};

void multi(struct complex *n1, struct complex *n2, struct complex *result)
{
	result->real = ((n1->real) * (n2->real)) - ((n1->im) * (n2->im));
	result->im = ((n1->real) * (n2->im)) + ((n1->im) * (n2->real));
}
