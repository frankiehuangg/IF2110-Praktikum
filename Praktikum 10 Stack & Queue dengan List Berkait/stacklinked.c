/* File: stacklinked.c */

// Nama     : Frankie Huang
// NIM      : 13521092
// Tanggal  : 8 November 2022
// Topik    : Stack dengan rep list berkait
// Deskripsi: Implementasi stack dengan rep. list berkait

#include <stdio.h>
#include "stacklinked.h"

/* Prototype manajemen memori */
Address newNode(ElType x)
/* Mengembalikan alamat sebuah Node hasil alokasi dengan info = x, 
   atau 
   NULL jika alokasi gagal */   
{
	Address a = (Node*) malloc(sizeof(Node));

	if (a != NIL)
	{
		NEXT(a) = NIL;
		INFO(a) = x;
	}

	return a;
}

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean isEmpty(Stack s)
/* Mengirim true jika Stack kosong: TOP(s) = NIL */
{
	if (ADDR_TOP(s) == NIL)
		return true;
	return false;
}

int length(Stack s)
/* Mengirimkan banyaknya elemen stack. Mengirimkan 0 jika Stack s kosong */
{
	int len = 0;

	while(!isEmpty(s))
	{
		len++;
		ADDR_TOP(s) = NEXT(ADDR_TOP(s));
	}

	return len;
}

void CreateStack(Stack *s)
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stack s yang kosong */
{
	ADDR_TOP(*s) = NIL;
}

void DisplayStack(Stack s)
/* Proses : Menuliskan isi Stack, ditulis di antara kurung siku; antara dua elemen 
	dipisahkan dengan separator "koma", tanpa tambahan karakter di depan, di tengah, 
	atau di belakang, termasuk spasi dan enter */
/* I.S. s boleh kosong */
/* F.S. Jika s tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Stack kosong : menulis [] */
{
	if (isEmpty(s))
	{
		printf("[]");
	}
	else
	{
		printf("[%d", TOP(s));
		ADDR_TOP(s) = NEXT(ADDR_TOP(s));

		while (!isEmpty(s))
		{
			printf(",%d", TOP(s));
			ADDR_TOP(s) = NEXT(ADDR_TOP(s));
		}
		
		printf("]");
	}
}

void push(Stack *s, ElType x)
/* Menambahkan x sebagai elemen Stack s */
/* I.S. s mungkin kosong, x terdefinisi */
/* F.S. x menjadi Top yang baru jika alokasi x berhasil, */
/*      jika tidak, s tetap */
/* Pada dasarnya adalah operasi insertFirst pada list linier */
{
	Address a = newNode(x);

	if (isEmpty(*s))
	{
		ADDR_TOP(*s) = a;
		NEXT(ADDR_TOP(*s)) = NIL;
	}
	else
	{
		NEXT(a) = ADDR_TOP(*s);
		ADDR_TOP(*s) = a;
	}
}

void pop(Stack *s, ElType *x)
/* Menghapus Top dari Stack s */
/* I.S. s tidak kosong */
/* F.S. x adalah nilai elemen Top yang lama, */
/*      elemen Top yang lama didealokasi */
/* Pada dasarnya adalah operasi deleteFirst pada list linier */
{
	*x = TOP(*s);

	Address t = ADDR_TOP(*s);
	ADDR_TOP(*s) = NEXT(ADDR_TOP(*s));
	free(t);
}