#include "queue.h"
#include <stdio.h>

int main()
{
	Queue q; CreateQueue(&q);
	int c; scanf("%d", &c);
	int amt = 0;
	int min = -1; 
	int max = -1;
	float sum = 0;

	int v;
	while (c != 0)
	{
		if (c == 1)
		{
			if (isFull(q))
				printf("Queue penuh\n");
			else
			{
				scanf("%d", &v);
				enqueue(&q, v);	
			}
		}
		else if (c == 2)
		{
			if (isEmpty(q))
				printf("Queue kosong\n");
			else
			{
				dequeue(&q, &v);
				amt++;
				sum += v;
				if (min == -1 && max == -1)
				{
					max = v;
					min = v;
				}
				else
				{
					if (v > max)
						max = v;
					if (v < min)
						min = v;
				}
			}
		}

		scanf("%d", &c);
	}

	printf("%d\n", amt);
	if (amt == 0)
	{
		printf("Tidak bisa dihitung\n");
		printf("Tidak bisa dihitung\n");
		printf("Tidak bisa dihitung\n");
	}
	else
	{
		printf("%d\n", min);
		printf("%d\n", max);
		printf("%.2f\n", sum/amt);
	}
}