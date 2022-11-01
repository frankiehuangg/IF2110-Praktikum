#include <stdio.h>
#include "listlinier.h"

int main()
{
	int len; scanf("%d", &len);
	int ope; scanf("%d", &ope);

	List l; CreateList(&l);

	int val;
	float hit = 0;

	int i = 0;

	if (len == 0)
	{
		while (i < ope)
		{
			scanf("%d", &val);
			printf("miss []\n");
			i++;
		}

		printf("hit ratio: 0.00\n");
	}
	else
	{
		while (i < ope)
		{
			scanf("%d", &val);

			int idx = indexOf(l, val);

			if (i == 0)
			{
				insertFirst(&l, val);

				printf("miss ");
				displayList(l);
				printf("\n");
			}

			// x ada di cache
			else if (idx != IDX_UNDEF)
			{
				deleteAt(&l, idx, &val);
				insertFirst(&l, val);

				hit++;
				printf("hit ");
				displayList(l);
				printf("\n");
			}

			// x tidak ada cache belum penuh
			else if (length(l) < len)
			{
				insertFirst(&l, val);

				printf("miss ");
				displayList(l);
				printf("\n");
			}

			// x tidak ada cache sudah penuh
			else
			{
				insertFirst(&l, val);
				deleteLast(&l, &val);

				printf("miss ");
				displayList(l);
				printf("\n");
			}

			i++;
		}

		if (ope != 0)
			printf("hit ratio: %.2f\n", hit/ope);
		else
			printf("hit ratio: 0.00\n");
	}
}