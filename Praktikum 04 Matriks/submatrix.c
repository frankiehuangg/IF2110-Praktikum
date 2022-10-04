#include <stdio.h>
#include "matrix.h"

int main()
{
	int n,m; scanf("%d %d", &n, &m);
	Matrix mat; readMatrix(&mat, n, n);

	int i, j;
	int maxAmt = 0, idx = 0;
	for (i = 0; i < n-m+1; i++)
	{
		for (j = 0; j < n-m+1; j++)
		{
			int rs,cs;
			int amt = 0;

			for (rs = i; rs < i+m; rs++)
				for (cs = j; cs < j+m; cs++)
					if (ELMT(mat,rs,cs) != 0)
						amt++;

			if (amt > maxAmt)
			{
				maxAmt = amt;
				idx = (n-m+1)*i+j+1;
			}
		}
	}

	printf("%d\n", idx);
}