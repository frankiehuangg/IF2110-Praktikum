#include <stdio.h>
#include "listrec.h"

int main()
{
	List l = NULL;
	List l2 = NULL;
	// l2 = konso(l2, 1);

	displayList(l);
	l2 = concat(l, l2);

	displayList(l2);
	// printf("%d\n", isEmpty(l));

	// l = konso(l,100); displayList(l);
	// printf("\n");

	// printf("%d\n", isOneElmt(l));

	for (int i = 4; i > -5; i--)
	{
		// l = konso(l,i); 
		l2 = konso(l2, i);
		// displayList(l); printf("\n");
	}
	// l = konso(l, 99);
	l2 = konso(l2, 99);	

	printf("%d\n", compareList(l, l2));

	// printf("%d\n", maxList(l));
	// printf("%d\n", minList(l));
	// printf("%d\n", sumList(l));
	// printf("\n");	

	// List l3 = inverseList(l);
	// displayList(l3); printf("\n");

	// List l5, l6;
	// splitOnX(l, 2, &l5, &l6);
	// displayList(l5); printf("\n");
	// displayList(l6); printf("\n");

	// for (int i = 5; i < 10; i++)
	// {
	// 	l = konsb(l,i); displayList(l);
	// 	printf("\n");
	// }

	// List l2 = copy(l); displayList(l2);
	// printf("\n");
	// l2 = concat(l, l2); displayList(l2);
	// printf("\n");

	// printf("%d\n", length(l2));

	// printf("%d\n", isMember(l, 9));
	// printf("%d\n", isMember(l, 11));
}