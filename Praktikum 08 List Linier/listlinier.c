/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* ElType adalah integer */

// Nama 	: Frankie Huang
// NIM 		: 13521092
// Tanggal 	: 24 Oktober 2022
// Topik	: List berkait
// Deskripsi: Implementasi list berkait

#include <stdio.h>
#include <stdlib.h>
#include "listlinier.h"
#include "boolean.h"

Address newNode(ElType val)
/* Definisi List : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */
{
	Address a = (Node*) malloc(sizeof(Node));

	if (a != NULL)
	{
		INFO(a) = val;
		NEXT(a) = NULL;
	}
	return a;
}

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
	FIRST(*l) = NULL;
}

/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l)
/* Mengirim true jika list kosong */
{
	if (FIRST(l) == NULL)
		return true;
	return false;
}

/****************** GETTER SETTER ******************/
ElType getElmt(List l, int idx)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
{
	Address temp = FIRST(l);

	int i = 0;
	while (i < idx)
	{
		FIRST(temp) = NEXT(temp);
		i++;
	}

	return INFO(temp);
}

void setElmt(List *l, int idx, ElType val)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
{
	Address temp = FIRST(*l);

	int i = 0;
	while (i < idx)
	{
		FIRST(temp) = NEXT(temp);
		i++;
	}

	INFO(temp) = val;
}

int indexOf(List l, ElType val)
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */
{
	Address temp = FIRST(l);

	int i = 0;
	while (FIRST(temp) != NULL)
	{
		if (INFO(temp) == val)
			return i; 

		FIRST(temp) = NEXT(temp);
		i++;
	}

	return IDX_UNDEF;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
{
	Address t = newNode(val);

	if (FIRST(t) != NULL)
	{
		NEXT(t) = FIRST(*l);
		FIRST(*l) = FIRST(t);
	}
}

void insertLast(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
	Address t = newNode(val);

	if (FIRST(t) != NULL)
	{
		if (isEmpty(*l))
		{
			insertFirst(l, val);
		}
		else
		{
			Address temp = *l;

			while (NEXT(temp) != NULL)
				FIRST(temp) = NEXT(temp);
			
			NEXT(temp) = FIRST(t);
		}
	}
}

void insertAt(List *l, ElType val, int idx)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
	Address t = newNode(val);

	if (FIRST(t) != NULL)
	{
		if (idx == 0)
		{
			insertFirst(l, val);
		}
		else
		{
			Address temp = *l;

			int i = 0;
			while (i < idx-1)
			{
				FIRST(temp) = NEXT(temp);
				i++;
			}

			NEXT(t) = NEXT(temp);
			NEXT(temp) = FIRST(t);
		}
	}
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
{
	Address temp = FIRST(*l);

	*val = INFO(temp);
	FIRST(*l) = NEXT(temp);

	free(temp);
}
void deleteLast(List *l, ElType *val)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */
{
	Address temp = FIRST(*l);
	Address last = NULL;

	while (NEXT(temp) != NULL)
	{
		last = FIRST(temp);
		FIRST(temp) = NEXT(temp);
	}

	if (last == NULL)
	{
		*l = NULL;
	}
	else
	{
		NEXT(last) = NULL;
	}

	*val = INFO(temp);
	free(temp);
}

void deleteAt(List *l, int idx, ElType *val)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
{
	if (idx == 0)
	{
		deleteFirst(l, val);
	}
	else
	{
		Address temp = FIRST(*l);
		int i = 0;
		while (i < idx-1)
		{
			FIRST(temp) = NEXT(temp);
			i++;
		}

		Address last = NEXT(temp);
		*val = INFO(last);
		NEXT(temp) = NEXT(last);
		free(last);
	}
	
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l)
// void printInfo(List l);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
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
		printf("[%d", INFO(l));
		FIRST(l) = NEXT(l);

		while (FIRST(l) != NULL)
		{
			printf(",%d", INFO(l));
			FIRST(l) = NEXT(l);
		}

		printf("]");
	}
}

int length(List l)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
	if (isEmpty(l))
		return 0;

	int i = 0;
	Address temp = FIRST(l);

	while (FIRST(temp) != NULL)
	{
		FIRST(temp) = NEXT(temp);
		i++;
	}

	return i;
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
boolean fSearch(List L, Address P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
	Address temp = L;

	while (FIRST(temp) != NULL)
	{
		if (temp == P)
			return true;
		FIRST(temp) = NEXT(temp);
	}

	return false;
}
Address searchPrec(List L, ElType X)
/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
{
	Address temp = NEXT(L);
	Address last = FIRST(L);

	while (FIRST(temp) != NULL)
	{
		if (INFO(temp) == X)
			return last;

		FIRST(last) = FIRST(temp);
		FIRST(temp) = NEXT(temp);
	}

	return NULL;
}

/*** Prekondisi untuk Max/Min : List tidak kosong ***/
ElType max(List l)
/* Mengirimkan nilai info(P) yang maksimum */
{
	ElType max = INFO(l);
	Address temp = FIRST(l);

	while (FIRST(temp) != NULL)
	{
		if (INFO(temp) > max)
			max = INFO(temp);

		FIRST(temp) = NEXT(temp);
	}

	return max;
}
Address adrMax(List l)
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
{
	Address temp = FIRST(l);
	Address max = FIRST(l);

	while (FIRST(temp) != NULL)
	{
		if (INFO(temp) > INFO(max))
			FIRST(max) = FIRST(temp);

		FIRST(temp) = NEXT(temp);
	}

	return max;
}
ElType min(List l)
/* Mengirimkan nilai info(P) yang minimum */
{
	ElType min = INFO(l);
	Address temp = FIRST(l);

	while (FIRST(temp) != NULL)
	{
		if (INFO(temp) < min)
			min = INFO(temp);

		FIRST(temp) = NEXT(temp);
	}

	return min;
}
Address adrMin(List l)
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
{
	Address temp = FIRST(l);
	Address min = FIRST(l);

	while (FIRST(temp) != NULL)
	{
		if (INFO(temp) < INFO(min))
			FIRST(min) = FIRST(temp);

		FIRST(temp) = NEXT(temp);
	}

	return min;
}

/****************** PROSES TERHADAP LIST ******************/
List concat(List l1, List l2) 
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
	List l3; CreateList(&l3);

	Address temp = l1;

	while (FIRST(temp) != NULL)
	{
		insertLast(&l3, INFO(temp));

		FIRST(temp) = NEXT(temp);
	}

	temp = l2;

	while (FIRST(temp) != NULL)
	{
		insertLast(&l3, INFO(temp));

		FIRST(temp) = NEXT(temp);
	}

	return l3;
}

/***************** FUNGSI dan PROSEDUR TAMBAHAN **************/
void deleteAll(List *l)
/* Delete semua elemen list dan alamat elemen di-dealokasi */
{
	Address temp = *l;

	int val;
	while (FIRST(temp) != NULL)
	{
		deleteFirst(l, &val);
		FIRST(temp) = NEXT(temp);
	}

	*l = NULL;
}

void copyList(List *l1, List *l2)
/* I.S. L1 sembarang. F.S. L2=L1 */
/* L1 dan L2 "menunjuk" kepada list yang sama.*/
/* Tidak ada alokasi/dealokasi elemen */
{
	*l2 = *l1;
}

void inverseList(List *l)
/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. */
{
	if (!isEmpty(*l))
	{
		Address temp = *l;
		while (NEXT(temp) != NULL)
			FIRST(temp) = NEXT(temp);

		Address last = temp;

		while (FIRST(temp) != *l)
		{
			Address prev = *l;
			while (NEXT(prev) != FIRST(temp))
				FIRST(prev) = NEXT(prev);

			NEXT(temp) = FIRST(prev);
			FIRST(temp) = FIRST(prev);
		}

		NEXT(temp) = NULL;
		*l = last;
	}
}

void splitList(List *l1, List *l2, List l)
/* I.S. l mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah list l1 dan l2 */
/* L tidak berubah: untuk membentuk l1 dan l2 harus alokasi */
/* l1 berisi separuh elemen L dan l2 berisi sisa elemen L */
/* Jika elemen L ganjil, maka separuh adalah length(L) div 2 */
{
	CreateList(l1);
	CreateList(l2);

	int len = length(l)/2;
	int i = 0;

	Address temp = l;
	while (FIRST(temp) != NULL)
	{
		if (i < len)
			insertLast(l1, INFO(temp));
		else
			insertLast(l2, INFO(temp));

		i++;
		FIRST(temp) = NEXT(temp);
	}
}