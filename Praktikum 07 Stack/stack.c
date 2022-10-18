/* File : stack.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

// Nama     	: Frankie Huang
// NIM			: 13521092
// Tanggal  	: 18 Oktober 2022
// Topik    	: ADT Stack
// Deskripsi 	: Implementasi ADT Stack

#include "stack.h"

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty(Stack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri stack kosong : TOP bernilai Nil */
{
	Top(*S) = Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmpty(Stack S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
	if (Top(S) == Nil)
		return true;
	return false;
}
boolean IsFull(Stack S)
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
{
	if (Top(S) == MaxEl-1)
		return true;
	return false;
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push(Stack * S, infotype X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
	Top(*S)++;
	InfoTop(*S) = X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop(Stack * S, infotype* X)
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
	*X = InfoTop(*S);
	Top(*S)--;
}