#include "time.h"
#include <stdio.h>

typedef struct {
	TIME Time1;
	TIME Time2;
} DURASI;

#define Waktu1(T) (T).Time1
#define Waktu2(T) (T).Time2

int main()
{
	int rec; scanf("%d", &rec);
	int i;

	TIME PAwal = {23,59,59}, PAkhir={0,0,0};

	for (i = 0; i < rec; i++)
	{
		printf("[%d]\n", i+1);

		DURASI d;
		BacaTIME(&Waktu1(d));
		BacaTIME(&Waktu2(d));

		if (TLT(Waktu1(d), Waktu2(d))) {
			printf("%ld\n", Durasi(Waktu1(d), Waktu2(d)));

			if (TLT(Waktu1(d), PAwal))
				PAwal = Waktu1(d);
			if (TGT(Waktu2(d), PAkhir))
				PAkhir = Waktu2(d);
		}
		else {
			printf("%ld\n", Durasi(Waktu2(d), Waktu1(d)));

			if (TLT(Waktu2(d), PAwal))
				PAwal = Waktu2(d);
			if (TGT(Waktu1(d), PAkhir))
				PAkhir = Waktu1(d);
		}
	}

	TulisTIME(PAwal); printf("\n");
	TulisTIME(PAkhir); printf("\n");

	return 0;
}