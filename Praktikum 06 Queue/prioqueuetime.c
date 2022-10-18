/* File : prioqueuetime.h */
/* Definisi ADT Priority Queue Time dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */
/* Elemen queue terurut membesar berdasarkan elemen time */

#include "prioqueuetime.h"
#include <stdio.h>
#include <stdlib.h>

/* ********* Prototype ********* */
boolean IsEmpty (PrioQueueTime Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    if (Head(Q) == Nil && Tail(Q) == Nil)
        return true;
    return false;
}
boolean IsFull (PrioQueueTime Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
    if (((Tail(Q) + MaxEl(Q) - Head(Q)) % MaxEl(Q)) + 1 == MaxEl(Q))
        return true;
    return false;
}
int NBElmt (PrioQueueTime Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
    if (IsEmpty(Q))
        return 0;
    return ((Tail(Q) + MaxEl(Q) - Head(Q)) % MaxEl(Q)) + 1;
}

/* *** Kreator *** */
void MakeEmpty (PrioQueueTime * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
    (*Q).T = (infotype*) malloc((Max+1) * sizeof(infotype));

    if ((*Q).T == NULL)
    {
        MaxEl(*Q) = 0;
    }
    else
    {
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
        MaxEl(*Q) = Max;
    }
}

/* *** Destruktor *** */
void DeAlokasi(PrioQueueTime * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
    free((*Q).T);
    MaxEl(*Q) = 0;
}

/* *** Primitif Add/Delete *** */
void Enqueue (PrioQueueTime * Q, infotype X)
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut membesar berdasarkan time */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
        TAIL "maju" dengan mekanisme circular buffer; */
{
    if (IsEmpty(*Q))
    {
        Head(*Q) = 1;
        Tail(*Q) = 1;
        InfoTail(*Q) = X;
    }
    else
    {
        int amt = NBElmt(*Q);
        int i = Tail(*Q);

        while ((Time(X) < Time(Elmt(*Q,i))) && (amt > 0))
        {
            Elmt(*Q, (i % MaxEl(*Q)) + 1) = Elmt(*Q,i);

            i--;
            amt--;

            if (i == 0)
                i = MaxEl(*Q);
        }

        Elmt(*Q, (i % MaxEl(*Q)) + 1) = X;
        Tail(*Q) = (Tail(*Q) % MaxEl(*Q)) + 1;
    }
}
void Dequeue (PrioQueueTime * Q, infotype * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
{
    *X = InfoHead(*Q);
    if (NBElmt(*Q) == 1)
    {
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    }
    else
        Head(*Q) = (Head(*Q) % MaxEl(*Q)) + 1;
}

/* Operasi Tambahan */
void PrintPrioQueueTime (PrioQueueTime Q)
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<time-1> <elemen-1>
...
<time-n> <elemen-n>
#
*/
{
    infotype val;
    while (!IsEmpty(Q))
    {
        Dequeue(&Q, &val);
        printf("%d %c\n", Time(val), Info(val));
    }

    printf("#\n");
}