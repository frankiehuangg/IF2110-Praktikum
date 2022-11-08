/* File: queuelinked.c */

// Nama     : Frankie Huang
// NIM      : 13521092
// Tanggal  : 8 November 2022
// Topik    : Queue dengan rep list berkait
// Deskripsi: Implementasi queue dengan rep. list berkait

#include <stdio.h>
#include "queuelinked.h"

/* Prototype manajemen memori */
Address newNode(ElType x)
/* Mengembalikan alamat sebuah Node hasil alokasi dengan info = x, 
   atau NIL jika alokasi gagal */
{
    Address a = (Node*) malloc(sizeof(Node));

    if (a != NIL)
    {
        NEXT(a) = NIL;
        INFO(a) = x;
    }

    return a;
}
boolean isEmpty(Queue q)
/* Mengirim true jika q kosong: ADDR_HEAD(q)=NULL and ADDR_TAIL(q)=NULL */
{
    if (ADDR_HEAD(q) == NIL && ADDR_TAIL(q) == NIL)
        return true;
    return false;
}
int length(Queue q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika q kosong */
{
    int len = 0;

    while (ADDR_HEAD(q) != NIL)
    {
        len++;
        ADDR_HEAD(q) = NEXT(ADDR_HEAD(q));
    }

    return len;
}

/*** Kreator ***/
void CreateQueue(Queue *q)
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk */
{
    ADDR_HEAD(*q) = NIL;
    ADDR_TAIL(*q) = NIL;
}
void DisplayQueue(Queue q)
/* Proses : Menuliskan isi Queue, ditulis di antara kurung siku; antara dua elemen 
    dipisahkan dengan separator "koma", tanpa tambahan karakter di depan, di tengah, 
    atau di belakang, termasuk spasi dan enter */
/* I.S. q boleh kosong */
/* F.S. Jika q tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Queue kosong : menulis [] */
{
    if (isEmpty(q))
    {
        printf("[]");
    }
    else
    {
        printf("[%d", HEAD(q));
        ADDR_HEAD(q) = NEXT(ADDR_HEAD(q));

        while (ADDR_HEAD(q) != NIL)
        {
            printf(",%d", HEAD(q));
            ADDR_HEAD(q) = NEXT(ADDR_HEAD(q));
        }

        printf("]");
    }
}

/*** Primitif Enqueue/Dequeue ***/
void enqueue(Queue *q, ElType x)
/* Proses: Mengalokasi x dan menambahkan x pada bagian Tail dari q
           jika alokasi berhasil; jika alokasi gagal q tetap */
/* Pada dasarnya adalah proses insertLast */
/* I.S. q mungkin kosong */
/* F.S. x menjadi Tail, Tail "maju" */
{
    Address a = newNode(x);

    if (isEmpty(*q))
    {
        ADDR_HEAD(*q) = a;
        ADDR_TAIL(*q) = a;
        NEXT(ADDR_HEAD(*q)) = NIL;
    }
    else
    {
        NEXT(ADDR_TAIL(*q)) = a;
        ADDR_TAIL(*q) = a;
        NEXT(ADDR_TAIL(*q)) = NIL;
    }
}
void dequeue(Queue *q, ElType *x)
/* Proses: Menghapus x pada bagian HEAD dari q dan mendealokasi elemen HEAD */
/* Pada dasarnya operasi deleteFirst */
/* I.S. q tidak mungkin kosong */
/* F.S. x = nilai elemen HEAD pd I.S., HEAD "mundur" */
{
    *x = HEAD(*q);

    Address t = ADDR_HEAD(*q);
    if (NEXT(ADDR_HEAD(*q)) != NIL)
    {
        ADDR_HEAD(*q) = NEXT(ADDR_HEAD(*q));
    }
    else
    {
        ADDR_HEAD(*q) = NIL;
        ADDR_TAIL(*q) = NIL;
    }
    
    free(t);
}