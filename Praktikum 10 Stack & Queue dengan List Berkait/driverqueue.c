#include <stdio.h>
#include "queuelinked.h"

int main()
{
	Queue q; CreateQueue(&q);

	printf("%d\n", isEmpty(q));
	printf("%d\n", length(q));

	DisplayQueue(q); printf("\n");
	for (int i = 0; i < 10; i++)
	{
		enqueue(&q, i);
		printf("Queue %d: ", i); DisplayQueue(q); printf("\n");
	}

	int val;
	for (int i = 0; i < 10; i++)
	{
		dequeue(&q, &val);
		printf("Value %d: ", val); DisplayQueue(q); printf("\n");
	}
}