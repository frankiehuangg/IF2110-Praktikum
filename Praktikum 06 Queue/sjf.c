#include <stdio.h>
#include "prioqueuetime.h"

int main()
{
	int p; scanf("%d", &p);
	PrioQueueTime pq; MakeEmpty(&pq, p);
	
	int time; char info; infotype it; 
	infotype val;

	boolean isRunning = false;
	int currTime = 0, doneTime;
	
	int i = 0;
	while (i < p)
	{
		scanf("%d %c", &time, &info);
		Time(it) = time; Info(it) = info;
		Enqueue(&pq, it);

		if (i == doneTime)
		{
			currTime = doneTime;
			isRunning = false;
		}

		if (!isRunning)
		{
			Dequeue(&pq, &val);
			printf("%d %c\n", currTime, Info(val));
			doneTime = currTime + Time(val);
			isRunning = true;
		}

		i++;
	}
	
	currTime = doneTime;

	while (!IsEmpty(pq))
	{
		Dequeue(&pq, &val);
		printf("%d %c\n", currTime, Info(val));
		currTime += Time(val);
	}
}