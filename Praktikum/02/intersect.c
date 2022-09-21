#include <stdio.h>
#include "liststatik.h"

int main()
{
	ListStatik l1; readList(&l1); sortList(&l1,true);
	ListStatik l2; readList(&l2); sortList(&l1,true);
	ListStatik l3; CreateListStatik(&l3);

	int i = 0;
	while (i < listLength(l1))
	{
		int j = 0;
		while (j < listLength(l2))
		{
			if (ELMT(l1,i) == ELMT(l2,j) && indexOf(l3,ELMT(l1,i)) == IDX_UNDEF)
				insertLast(&l3,ELMT(l1,i));
			j++;
		}
		i++;
	}

	sortList(&l3,true);
	printf("%d\n", listLength(l3));
	printList(l3); printf("\n");

	return 0;
}