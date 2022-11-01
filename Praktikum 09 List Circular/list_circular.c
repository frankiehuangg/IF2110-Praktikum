/* File : list_circular.h */
/* ADT List Sirkuler dengan elemen terakhir menunjuk pada elemen pertama */
/* Representasi berkait dengan Address adalah pointer */
/* ElType adalah integer */

#include <stdio.h>
#include <stdlib.h>
#include "list_circular.h"

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
	if (FIRST(l) == NULL)
		return true;
	return false;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l)
/* I.S. l sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
	FIRST(*l) = NULL;
}

/****************** Manajemen Memori ******************/
Address allocate(ElType val)
/* Mengirimkan Address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka Address tidak NULL, dan misalnya */
/* menghasilkan P, maka INFO(P)=val, NEXT(P)=NULL */
/* Jika alokasi gagal, mengirimkan NULL */
{
	Address a = (ElmtList*) malloc(sizeof(ElmtList));

	if (a != NULL)
	{
		INFO(a) = val;
		NEXT(a) = NULL;
	}

	return a;
}
void deallocate(Address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian Address P */
{
	free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
Address search(List l, ElType val)
/* Mencari apakah ada elemen list dengan INFO(P)= val */
/* Jika ada, mengirimkan Address elemen tersebut. */
/* Jika tidak ada, mengirimkan NULL */
{
	if (isEmpty(l))
		return NULL;

	if (INFO(FIRST(l)) == val)
		return FIRST(l);

	Address temp = NEXT(FIRST(l));
	while (temp != FIRST(l))
	{
		if (INFO(temp) == val)
			return temp;

		temp = NEXT(temp);
	}

	return NULL;
}

boolean addrSearch(List l, Address p)
/* Mencari apakah ada elemen list l yang beralamat p */
/* Mengirimkan true jika ada, false jika tidak ada */
{
	if (isEmpty(l))
		return false;

	if (FIRST(l) == p)
		return true;

	Address temp = NEXT(FIRST(l));
	while (temp != FIRST(l))
	{
		if (temp == p)
			return true;

		temp = NEXT(temp);
	}

	return false;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val)
/* I.S. List l terdefinisi, mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil */
/* Elemen terakhir list menunjuk ke address dari elemen pertama baru list */
{
	if (isEmpty(*l))
	{
		Address temp = allocate(val);
		NEXT(temp) = temp;
		FIRST(*l) = temp;
	}
	else
	{
		Address temp = allocate(val);
		NEXT(temp) = FIRST(*l);

		Address last = NEXT(FIRST(*l));

		while (NEXT(last) != FIRST(*l))
			last = NEXT(last);

		NEXT(last) = temp;
		FIRST(*l) = temp;
	}
}
void insertLast(List *l, ElType val)
/* I.S. List l terdefinisi, mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
/* Elemen terakhir baru list menunjuk ke address dari elemen pertama list */
{
	if (isEmpty(*l))
	{
		insertFirst(l, val);
	}
	else
	{
		insertFirst(l, val);
		FIRST(*l) = NEXT(FIRST(*l));
	}
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType * val)
/* I.S. List l tidak kosong  */
/* F.S. val adalah elemen pertama List l sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/*      First element yg baru adalah suksesor elemen pertama yang lama */
/*      Jika list baru tidak kosong, Last element menunjuk ke First element baru */
/*      Jika list baru kosong, maka FIRST(*l) = NULL */
/*      Alamat elemen pertama list lama di-dealokasi */
{
	*val = INFO(FIRST(*l));

	if (FIRST(*l) == NEXT(FIRST(*l)))
	{
		FIRST(*l) = NULL;
	}
	else
	{
		Address first = FIRST(*l);
		FIRST(*l) = NEXT(FIRST(*l));

		Address last = NEXT(FIRST(*l));

		while (NEXT(last) != first)
			last = NEXT(last);

		NEXT(last) = FIRST(*l);
		FIRST(*l) = last;
		FIRST(*l) = NEXT(FIRST(*l));

		free(first);
	}
}
void deleteLast(List *l, ElType * val)
/* I.S. List l tidak kosong */
/* F.S. val adalah elemen terakhir list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/*      Last element baru adalah predesesor elemen terakhir yg lama, jika ada */
/*      Jika list baru tidak kosong, Last element baru menunjuk ke First element */
/*      Jika list baru kosong, maka FIRST(*l) = NULL */
/*      Alamat elemen terakhir list lama di-dealokasi */
{
	if (FIRST(*l) == NEXT(FIRST(*l)))
	{
		*val = INFO(FIRST(*l));
		FIRST(*l) = NULL;
	}
	else
	{
		Address temp = NEXT(FIRST(*l));
		Address last = NULL;

		while (NEXT(temp) != FIRST(*l))
		{
			last = temp;
			temp = NEXT(temp);
		}

		*val = INFO(temp);

		if (last == NULL)
		{
			NEXT(FIRST(*l)) = FIRST(*l);
		}
		else
		{

			NEXT(last) = FIRST(*l);
			FIRST(*l) = last;
			FIRST(*l) = NEXT(FIRST(*l));
		}
		free(temp);
	}
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l)
/* I.S. List l mungkin kosong */
/* F.S. Jika list tidak kosong, nilai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
	if (isEmpty(l))
	{
		printf("[]");
	}
	else
	{
		Address temp = FIRST(l);

		printf("[%d", INFO(temp));
		temp = NEXT(temp);

		while (temp != FIRST(l))
		{
			printf(",%d", INFO(temp));
			temp = NEXT(temp);
		}

		printf("]");
	}
}