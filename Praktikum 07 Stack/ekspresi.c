#include <stdio.h>
#include <math.h>
#include "stack.h"
#include "wordmachine.h"

int op(int a, int b, char c)
{
	if (c == '+')
		return a+b;
	if (c == '-')
		return a-b;
	if (c == '*')
		return a*b;
	if (c == '/')
		return a/b;
	return pow(a,b);
}

int w2i(Word w)
{
	int sum = 0;

	int i;
	for (i = 0; i < w.Length; i++)
	{
		sum *= 10;
		sum += w.TabWord[i]-48;
	}

	return sum;
}

char w2c(Word w)
{
	return w.TabWord[0];
}

boolean isOp(Word w)
{
	char op[5] = "+-*/^";
	
	int i;
	for (i = 0; i < 5; i++)
		if (op[i] == w.TabWord[0])
			return true;
	return false;
}

int main()
{
	STARTWORD();
	Stack s; CreateEmpty(&s);

	if (endWord)
	{
		printf("Ekspresi kosong\n");
	}
	else
	{
		int x, y;
		while (!endWord)
		{
			if (!isOp(currentWord))
			{
				Push(&s, w2i(currentWord));
				printf("%d\n", w2i(currentWord));
			}
			else
			{
				Pop(&s, &y);
				Pop(&s, &x);
				Push(&s, op(x,y,w2c(currentWord)));

				printf("%d %c %d\n", x, w2c(currentWord), y);
				printf("%d\n", op(x,y,w2c(currentWord)));
			}

			ADVWORD();
		}

		Pop(&s, &x);
		printf("Hasil=%d\n", x);
	}
}