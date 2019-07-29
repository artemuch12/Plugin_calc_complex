#include <stdlib.h>
#include <stdio.h>

struct complex
{
        int real;
        int im;
};

void division(struct complex *n1, struct complex *n2, struct complex *result)
{
	int denominator;
	denominator = (n2->real) * (n2->real) + (n2->im) * (n2->im);
	result->real = (((n1->real) * (n2->real)) + ((n1->im) * (n2->im)))/(denominator);
	result->im = (((n1->im) * (n2->real)) - ((n1->real) * (n2->im)))/(denominator);
}
