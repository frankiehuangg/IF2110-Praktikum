/* MODUL INTEGER DYNAMIC LIST */
/* Berisi definisi dan semua primitif pemrosesan list integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori list dinamik */

#include "listdin.h"
#include <stdlib.h>
#include <stdio.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDin(ListDin *l, int capacity)
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
{
   BUFFER(*l) = (ElType*) malloc(capacity*sizeof(ElType));
   NEFF(*l) = 0;
   CAPACITY(*l) = capacity;
}

void dealocateList(ListDin *l)
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
{
   free(BUFFER(*l));
   CAPACITY(*l) = 0;
   NEFF(*l) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLength(ListDin l)
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
{
   return NEFF(l);
}
/* *** Daya tampung container *** */

/* *** Selektor INDEKS *** */
IdxType getFirstIdx(ListDin l)
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
{
   return 0;
}
IdxType getLastIdx(ListDin l)
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
{
   return NEFF(l)-1;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListDin l, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/
{
   if (i >= 0 && i < CAPACITY(l))
      return true;
   return false;
}
boolean isIdxEff(ListDin l, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..NEFF(l) */
{
   if (i >= 0 && i < NEFF(l))
      return true;
   return false;
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(ListDin l)
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
{
   if (NEFF(l) == 0)
      return true;
   return false;
}
/* *** Test list penuh *** */
boolean isFull(ListDin l)
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
{
   if (NEFF(l) == CAPACITY(l))
      return true;
   return false;
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readList(ListDin *l)
/* I.S. l sembarang dan sudah dialokasikan sebelumnya */
/* F.S. List l terdefinisi */
/* Proses : membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= CAPACITY(l) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
      0 satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk l kosong */
{
   int n; scanf("%d", &n);

   while (n < 0 || n > CAPACITY(*l))
      scanf("%d", &n);

   NEFF(*l) = n;

   int i;
   for (i = 0; i < n; i++)
      scanf("%d", &ELMT(*l,i));
}
void printList(ListDin l)
/* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
{
   printf("[");
   
   int i, n = NEFF(l)-1;
   for (i = IDX_MIN; i < n; i++)
      printf("%d,",ELMT(l,i));

   printf("%d]", ELMT(l,n));
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika list : Penjumlahan, pengurangan, perkalian, ... *** */
ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus)
/* Prekondisi : l1 dan l2 memiliki Neff sama dan tidak kosong */
/* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi elemen l2 pada indeks yang sama */
{
   int i, n = NEFF(l1);
   
   if (plus)
      for (i = IDX_MIN; i < n; i++)
         ELMT(l1,i) += ELMT(l2,i);
   else
      for (i = IDX_MIN; i < n; i++)
         ELMT(l1,i) -= ELMT(l2,i);

   return l1;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
boolean isListEqual(ListDin l1, ListDin l2)
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika nEff l1 = l2 dan semua elemennya sama */
{
   if (NEFF(l1) != NEFF(l2))
      return false;

   int i, n = NEFF(l1);
   for (i = IDX_MIN; i < n; i++)
      if (ELMT(l1,i) != ELMT(l2,i))
         return false;

   return true;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOf(ListDin l, ElType val)
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
/* Jika tidak ada, mengirimkan IDX_UNDEF */
/* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
/* Skema Searching yang digunakan bebas */
{
   if (NEFF(l) == 0)
      return IDX_UNDEF;

   int i = IDX_MIN, n = NEFF(l);
   while ( i < n)
   {
      if (ELMT(l,i) == val)
         return i;
      i++;
   }

   return IDX_UNDEF;
}

/* ********** NILAI EKSTREM ********** */
void extremeValues(ListDin l, ElType *max, ElType *min)
/* I.S. List l tidak kosong */
/* F.S. max berisi nilai maksimum l;
        min berisi nilai minimum l */
{
   int i, n = NEFF(l);
   for (i = IDX_MIN; i < n; i++)
   {
      if (ELMT(l,i) > *max)
      {
         *max = ELMT(l,i);
      }
      if (ELMT(l,i) < *min)
      {
         *min = ELMT(l,i);
      }
   }
}

/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut)
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */
{
   NEFF(*lOut) = NEFF(lIn);
   CAPACITY(*lOut) = NEFF(lIn);

   int i, n = NEFF(*lOut);
   for (i = IDX_MIN; i < n; i++)
      ELMT(*lOut,i) = ELMT(lIn,i);
}
ElType sumList(ListDin l)
/* Menghasilkan hasil penjumlahan semua elemen l */
/* Jika l kosong menghasilkan 0 */
{
   ElType sum = 0;

   int i, n = NEFF(l);
   for (i = IDX_MIN; i < n; i++)
      sum += ELMT(l,i);

   return sum;
}
int countVal(ListDin l, ElType val)
/* Menghasilkan berapa banyak kemunculan val di l */
/* Jika l kosong menghasilkan 0 */
{
   int amt = 0;

   int i, n = NEFF(l);
   for (i = IDX_MIN; i < n; i++)
      if (ELMT(l,i) == val)
         amt++;

   return amt;
}

/* ********** SORTING ********** */
void sort(ListDin *l, boolean asc)
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */
{
    int i, key, j;
    int n = NEFF(*l);
    if (asc)
    {
        for (i=1; i < n; i++)
        {
            key = ELMT(*l,i);
            j = i-1;

            while (j >= 0 && ELMT(*l,j) > key)
            {
                ELMT(*l,j+1) = ELMT(*l,j);
                j--;
            }
            ELMT(*l,j+1) = key;
        }
    }
    else
    {
        for (i=1; i < n; i++)
        {
            key = ELMT(*l,i);
            j = i-1;

            while (j >= 0 && ELMT(*l,j) < key)
            {
                ELMT(*l,j+1) = ELMT(*l,j);
                j--;
            }
            ELMT(*l,j+1) = key;
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListDin *l, ElType val)
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
{
   ELMT(*l,NEFF(*l)) = val;
   NEFF(*l)++;
}
/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListDin *l, ElType *val)
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
{
   NEFF(*l)--;
}

/* ********* MENGUBAH UKURAN ARRAY ********* */
void expandList(ListDin *l, int num)
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */
{
   // tambahkan ukuran capacity
   CAPACITY(*l) += num;
   // copy isi l ke temp
   ListDin temp; copyList(*l, &temp);
   // kosongkan l, perbanyak kapasitas
   CreateListDin(l, CAPACITY(*l));
   // copy isi temp ke l
   copyList(temp, l);
}

void shrinkList(ListDin *l, int num)
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */
{
   // kurangi ukuran capacity
   CAPACITY(*l) -= num;
   // copy isi l ke temp
   ListDin temp; copyList(*l, &temp);
   // kosongkan l, perbanyak kapasitas
   CreateListDin(l, CAPACITY(*l));
   // copy isi temp ke l
   copyList(temp, l);
}

void compressList(ListDin *l)
/* Proses : Mengubah capacity sehingga nEff = capacity */
/* I.S. List tidak kosong */
/* F.S. Ukuran nEff = capacity */
{
   // kurangi ukuran capacity
   CAPACITY(*l) = NEFF(*l);
   // copy isi l ke temp
   ListDin temp; copyList(*l, &temp);
   // kosongkan l, perbanyak kapasitas
   CreateListDin(l, CAPACITY(*l));
   // copy isi temp ke l
   copyList(temp, l);
}
