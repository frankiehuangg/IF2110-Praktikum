#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

void check(BinTree t)
{
	printf("empty: %d\n", isTreeEmpty(t));
	printf("one: %d\n", isOneElmt(t));
	printf("left: %d\n", isUnerLeft(t));
	printf("right: %d\n", isUnerRight(t));
	printf("biner: %d\n\n", isBinary(t));
}

int main()
{
	// BinTree t11 = NewTree(1, NULL, NULL);
	// check(t11);

	// BinTree t21 = NewTree(1, NULL, NULL);
	// BinTree t22 = NewTree(2, t21, NULL);
	// check(t22);

	// BinTree t31 = NewTree(1, NULL, NULL);
	// BinTree t32 = NewTree(2, NULL, t31);
	// check(t32);

	// BinTree t41 = NewTree(1, NULL, NULL);
	// BinTree t42 = NewTree(2, NULL, NULL);
	// BinTree t43 = NewTree(3, t41, t42);
	// check(t43);


	BinTree t5 = NewTree(5, NULL, NULL);
	BinTree t4 = NewTree(4, NULL, NULL);
	BinTree t3 = NewTree(3, NULL, NULL);
	BinTree t2 = NewTree(2, t4, t5);
	BinTree t1 = NULL;


	// printPreorder(t1); printf("\n");
	// printPreorder(t4); printf("\n");
	// printPreorder(t2); printf("\n");
	// printPreorder(t3); printf("\n");

	CreateTree(1, t2, t3, &t1);
	printTree(t1, 3);
}