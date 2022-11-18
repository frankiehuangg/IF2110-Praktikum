#include <stdio.h>
#include "listrec.h"

List reverse(List l)
{
	if (isOneElmt(l))
		return l;

	return konsb(reverse(tail(l)), head(l));
}

void print(List l)
{
	if (isOneElmt(l))
	{
		printf("%d", head(l));
	}
	else
	{
		printf("%d ", head(l));
		print(tail(l));
	}
}

int main()
{
	int n; scanf("%d", &n);
	int k; scanf("%d", &k);

	int i;
	if (n % k == 0)
		i = n/k;
	else
		i = n/k+1;
	
	int num;
	while (i > 0)
	{
		List l = NULL;
		int j = 0;
		while (j < k && n > 0)
		{
			scanf("%d", &num);
			l = konsb(l, num);
			
			j++;
			n--;
		}

		l = reverse(l);
		print(l);
		if (i != 1)
			printf(" ");
		i--;
	}
	printf("\n");
}