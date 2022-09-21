#include <stdio.h>
#include "listdin.h"

int main()
{
	ListDin l1; CreateListDin(&l1, 200); readList(&l1);
	ListDin l2; CreateListDin(&l2, 200); readList(&l2);
	ListDin l3; CreateListDin(&l3, 400);

	int i = 0;
	while (i < NEFF(l1))
	{
		if (indexOf(l3,ELMT(l1,i)) == IDX_UNDEF)
			insertLast(&l3,ELMT(l1,i));
		i++;
	}
	int j = 0;
	while (j < NEFF(l2))
	{
		if (indexOf(l3,ELMT(l2,j)) == IDX_UNDEF)
			insertLast(&l3,ELMT(l2,j));
		j++;
	}

	sort(&l3,true);
	printf("%d\n",NEFF(l3));
	printList(l3); printf("\n");

	return 0;
}