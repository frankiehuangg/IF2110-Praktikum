#include "liststatik.h"
#include <stdio.h>

int main()
{
	ListStatik l; readList(&l);
	printList(l); printf("\n");

	int x; scanf("%d", &x);

	// banyak x
	int i, amt = 0;
	for (i = IDX_MIN; i < listLength(l); i++)
		if (ELMT(l,i) == x)
			amt++;
	printf("%d\n", amt);

	// last x
	int idx = IDX_UNDEF;
	i = listLength(l)-1;
	while (i >= 0)
	{
		if (ELMT(l,i) == x)
		{
			idx = i;
			break;
		}
		i--;
	}

	if (idx == IDX_UNDEF)
	{
		printf("%d tidak ada\n", x);
	}
	else
	{
		printf("%d\n", idx);

		// min max median
		sortList(&l, true);

		if (ELMT(l,getLastIdx(l)) == x)
			printf("maksimum\n");
		if (ELMT(l,getFirstIdx(l)) == x)
			printf("minimum\n");

		int n;
		if (listLength(l)%2 == 0)
			n = listLength(l)/2-1;
		else
			n = listLength(l)/2;

		if (ELMT(l,n) == x)
			printf("median\n");
	}

	return 0;
}