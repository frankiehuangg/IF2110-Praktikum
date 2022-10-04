// NIM         : 13521092
// Nama        : Frankie Huang
// Tanggal     : 29 September 2022
// Topik       : Mesin kata
// Deskripsi   : Program mencari kata terpanjang

#include <stdio.h>
#include "wordmachine.h"

boolean EndWord;
Word currentWord;

int main()
{
	STARTWORD();
	int l = currentWord.Length;

	while (!EndWord)
	{
		ADVWORD();
		if (currentWord.Length > l)
			l = currentWord.Length;
	}

	printf("%d\n", l);
}