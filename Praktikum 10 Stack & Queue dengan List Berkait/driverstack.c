#include <stdio.h>
#include "stacklinked.h"

int main()
{
	Stack s; CreateStack(&s);

	printf("%d\n", isEmpty(s));
	printf("%d\n", length(s));

	DisplayStack(s); printf("\n");
	for (int i = 0; i < 10; i++)
	{
		push(&s, i);
		printf("Stack %d: ", i); DisplayStack(s); printf("\n");
	}

	int val;
	for (int i = 0; i < 10; i++)
	{
		pop(&s, &val);
		printf("Value %d: ", val); DisplayStack(s); printf("\n");
	}
}