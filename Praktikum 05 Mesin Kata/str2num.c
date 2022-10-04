// NIM         : 13521092
// Nama        : Frankie Huang
// Tanggal     : 29 September 2022
// Topik       : Mesin kata
// Deskripsi   : Program mengganti string menjadi integer

#include <stdio.h>
#include "wordmachine.h"

boolean EndWord;
boolean isInt = false;
int sum = 0;

void printWord()
{	
	isInt = false;
	
	if (!isInt && sum != 0)
	{
		printf("%d ", sum);
		sum = 0;
	}

	for (int i = 0; i < currentWord.Length; i++)
		printf("%c", currentWord.TabWord[i]);
}

boolean check(int s, char string[])
{
	Word testWord;
	testWord.Length = currentWord.Length;

	int i;

	for (i = 0; i < testWord.Length; i++)
		testWord.TabWord[i] = currentWord.TabWord[i];

	for (i = 0; i < testWord.Length; i++)
		if (testWord.TabWord[i] > 64 && currentWord.TabWord[i] < 91)
		    testWord.TabWord[i] += 32;

	for (i = 0; i < s; i++)
		if (string[i] != testWord.TabWord[i])
			return false;

	return true;
}

int main()
{
	START();
	IgnoreBlanks();

	while (currentChar != MARK)
	{
		if (currentChar == BLANK)
		{
			if (!isInt)
				printf(" ");
			ADV();
		}

		CopyWord();

		if (currentWord.Length == 3 && check(3, "dua")){
			isInt = true; sum += 2;
		}
		else if (currentWord.Length == 3 && check(3, "nol")){
			printf("0");
		}
		else if (currentWord.Length == 4)
		{
			if (check(4, "satu")){
				isInt = true; sum += 1;
			}
			else if (check(4, "tiga")){
				isInt = true; sum += 3;
			}
			else if (check(4, "lima")){
				isInt = true; sum += 5;
			}
			else if (check(4, "enam")){
				isInt = true; sum += 6;
			}
			else{
				printWord();
			}
		}
		else if (currentWord.Length == 5)
		{
			if (check(5, "empat")){
				isInt = true; sum += 4;
			}
			else if (check(5, "tujuh")){
				isInt = true; sum += 7;
			}
			else if (check(5, "belas")){
				isInt = true; sum += 10;
			}
			else if (check(5, "puluh"))
			{
				isInt = true;
				if (sum > 100)
				{
					int temp = sum % 100;
					sum /= 10;
					sum += temp;
					sum *= 10;
				}
				else
					sum *= 10;
			}
			else if (check(5, "ratus")){
				isInt = true; sum *= 100;
			}
			else{
				printWord();
			}
		}
		else if (currentWord.Length == 7)
		{
			if (check(7, "delapan")){
				isInt = true; sum += 7;
			}
			else if (check(7, "sepuluh")){
				isInt = true; sum += 10;
			}
			else if (check(7, "sebelas")){
				isInt = true; sum += 11;
			}
			else if (check(7, "seratus")){
				isInt = true; sum += 100;
			}
			else{
				printWord();
			}
		}
		else if (currentWord.Length == 8)
		{
			if (check(8, "sembilan")){
				isInt = true; sum += 9;
			}
			else{
				printWord();
			}
		}
		else
		{
			printWord();
		}
	}

	if (isInt)
		printf("%d", sum);

	printf("\n");
}

// 03 dua
// 04 satu tiga lima enam belas puluh ratus
// 05 empat tujuh
// 07 delapan sepuluh sebelas
// 08 sembilan
