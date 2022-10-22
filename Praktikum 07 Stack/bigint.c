#include <stdio.h>
#include "stack.h"

int main()
{
	char c1[100]; scanf("%s", c1);
	char c2[100]; scanf("%s", c2);

	Stack s1; CreateEmpty(&s1);
	Stack s2; CreateEmpty(&s2);
	Stack s3; CreateEmpty(&s3);

	int l1 = 0;
	while (l1 < 100)
	{
		if (c1[l1] < 48 || c1[l1] > 57)
			break;
		l1++;
	}

	int l2 = 0;
	while (l2 < 100)
	{
		if (c2[l2] < 48 || c2[l2] > 57)
			break;
		l2++;
	}

	boolean isNeg = false;
	if (l1 < l2)
		isNeg = true;
	if (l1 == l2)
	{
		int i = 0;
		while (i < l1)
		{
			if (c1[i] > c2[i])
				break;
			if (c1[i] < c2[i])
				isNeg = true;
			i++;
		}
	}

	int i;

	if (isNeg)
	{
		for (i = 0; i < l1; i++)
			Push(&s2, c1[i]-48);
		for (i = 0; i < l2; i++)
			Push(&s1, c2[i]-48);
	}
	else
	{
		for (i = 0; i < l1; i++)
			Push(&s1, c1[i]-48);
		for (i = 0; i < l2; i++)
			Push(&s2, c2[i]-48);
	}	

	boolean isBor = false;
	int x, y;
	while (!IsEmpty(s1) && !IsEmpty(s2))
	{
		Pop(&s1, &x);
		Pop(&s2, &y);

		if (isBor)
		{
			if (x == 0)
			{
				x = 9;
			}
			else
			{
				x--;
				isBor = false;
			}
		}
		if (x-y < 0)
		{
			x += 10;
			isBor = true;
		}

		// printf("%d %d %d\n", x, y, x-y);

		Push(&s3, x-y);
	}

	while (!IsEmpty(s1))
	{
		Pop(&s1, &x);
		if (isBor)
		{
			if (x == 0)
			{
				x = 9;
			}
			else
			{
				x--;
				isBor = false;
			}
		}

		Push(&s3, x);
	}

	if (isNeg)
		printf("-");

	while (InfoTop(s3) == 0 && !IsEmpty(s3))
		Pop(&s3, &x);
	if (IsEmpty(s3))
		printf("0\n");
	
	else
	{
		while (!IsEmpty(s3))
		{
			Pop(&s3, &x);
			printf("%d", x);
		}

		printf("\n");
	}
}