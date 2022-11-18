#include <stdio.h>
#include <stdlib.h>
#include "listrec.h"

/* Manajemen Memori */
Address newNode(ElType x)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak NIL, dan misalnya
   menghasilkan p, maka INFO(p)=x, NEXT(p)=NIL */
/* Jika alokasi gagal, mengirimkan NIL */
{
   Address a = (Node*) malloc(sizeof(Node));

   if (a != NIL)
   {
      NEXT(a) = NIL;
      INFO(a) = x;
   }

   return a;
}

/* Pemeriksaan Kondisi List */
boolean isEmpty(List l)
/* Mengirimkan true jika l kosong dan false jika l tidak kosong */
{
   if (l == NULL)
      return true;
   return false;
}
boolean isOneElmt(List l)
/* Mengirimkan true jika l berisi 1 elemen dan false jika > 1 elemen atau kosong */
{
   if (length(l) == 1)
      return true;
   return false;
}

/* Primitif-Primitif Pemrosesan List */
ElType head(List l)
/* Mengirimkan elemen pertama sebuah list l yang tidak kosong */
{
   return INFO(l);
}
List tail(List l)
/* Mengirimkan list l tanpa elemen pertamanya, mungkin mengirimkan list kosong */
{
   return NEXT(l);
}
List konso(List l, ElType e)
/* Mengirimkan list l dengan tambahan e sebagai elemen pertamanya. e dialokasi terlebih dahulu. 
   Jika alokasi gagal, mengirimkan l */
{
   Address a = newNode(e);
   NEXT(a) = l;
   return a;
}
List konsb(List l, ElType e)
/* Mengirimkan list l dengan tambahan e sebagai elemen terakhirnya */
/* e harus dialokasi terlebih dahulu */
/* Jika alokasi e gagal, mengirimkan l */ 
{
   if (isEmpty(l))
   {
      return newNode(e);
   }

   NEXT(l) = konsb(tail(l), e);
   return l;
   
}
List copy(List l)
/* Mengirimkan salinan list Ll (menjadi list baru) */
/* Jika ada alokasi gagal, mengirimkan l */ 
{
   if (isEmpty(l))
      return NIL;
   return konso(copy(tail(l)), head(l));
}
List concat(List l1, List l2)
/* Mengirimkan salinan hasil konkatenasi list l1 dan l2 (menjadi list baru) */
/* Jika ada alokasi gagal, menghasilkan NIL */
{
   if (isEmpty(l1))
      return copy(l2);

   return konso(concat(tail(l1), l2), head(l1));
}

/* Fungsi dan Prosedur Lain */
int length(List l)
/* Mengirimkan banyaknya elemen list l, mengembalikan 0 jika l kosong */
{
   if (isEmpty(l))
      return 0;
   return 1 + length(NEXT(l));
}
boolean isMember(List l, ElType x)
/* Mengirimkan true jika x adalah anggota list l dan false jika tidak */
{
   if (isEmpty(l))
      return false;
   if (INFO(l) == x)
      return true;
   return isMember(NEXT(l), x);
}
void displayList(List l)
/* I.S. List l mungkin kosong */
/* F.S. Jika list tidak kosong, nilai list dicetak ke bawah */
/*      Dipisahkan dengan newline (\n) dan diakhiri dengan newline */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak:
  1
  20
  30
 */
/* Jika list kosong, tidak menuliskan apa-apa  */
{
   if (!isEmpty(l))
   {
      printf("%d\n", head(l));
      displayList(tail(l));
   }
}

/*** Pencarian nilai ekstrim ***/
/* Prekondisi untuk Max/Min/Sum/Average : List tidak kosong */
ElType maxList (List l)
/* Mengirimkan nilai INFO(p) yang maksimum */
{
   if (isOneElmt(l))
      return INFO(l);

   if (head(l) > head(tail(l)))
      return maxList(konso(tail(tail(l)), head(l)));

   return maxList(konso(tail(tail(l)), head(tail(l))));
}

ElType minList (List l)
/* Mengirimkan nilai INFO(p) yang minimum */
{
   if (isOneElmt(l))
      return INFO(l);

   if (head(l) < head(tail(l)))
      return minList(konso(tail(tail(l)), head(l)));

   return minList(konso(tail(tail(l)), head(tail(l))));
}

ElType sumList (List l)
/* Mengirimkan total jumlah elemen List l */
{
   if (isOneElmt(l))
      return INFO(l);

   return sumList(konso(tail(tail(l)), head(l) + head(tail(l))));
}

float averageList (List l)
/* Mengirimkan nilai rata-rata elemen list l */
{
   float sum = sumList(l);
   return sum/length(l);
}

/*** Operasi-Operasi Lain ***/
List inverseList (List l)
/* Mengirimkan list baru, hasil invers dari l dengan menyalin semua elemen list.
Semua elemen list baru harus dialokasi */
/* Jika alokasi gagal, hasilnya list kosong */
{
   if (isOneElmt(l))
      return l;

   return konsb(inverseList(tail(l)), head(l));
}

void splitPosNeg (List l, List *l1, List *l2)
/* I.S. l mungkin kosong */
/* F.S. Berdasarkan l, dibentuk dua buah list l1 dan l2 */ 
/* l1 berisi semua elemen l yang positif atau 0, sedangkan l2 berisi
semua elemen l yang negatif; semua dengan urutan yang sama seperti di l */
/* l tidak berubah: Semua elemen l1 dan l2 harus dialokasi */
/* Jika l kosong, maka l1 dan l2 kosong */
{
   if (isEmpty(l))
   {
      *l1 = NULL;
      *l2 = NULL;
   }
   else
   {
      splitPosNeg(tail(l), l1, l2);
      if (head(l) >= 0)
         *l1 = konso(*l1, head(l));
      else
         *l2 = konso(*l2, head(l));
   }
}

void splitOnX (List l, ElType x, List *l1, List *l2)
/* I.S. l dan x terdefinisi, l1 dan l2 sembarang. */
/* F.S. l1 berisi semua elemen l yang lebih kecil dari x, dengan urutan
kemunculan yang sama, l2 berisi semua elemen l yang tidak masuk ke
l1, dengan urutan kemunculan yang sama. */
{
   if (isEmpty(l))
   {
      *l1 = NULL;
      *l2 = NULL;
   }
   else
   {
      splitOnX(tail(l), x, l1, l2);
      if (head(l) < x)
         *l1 = konso(*l1, head(l));
      else
         *l2 = konso(*l2, head(l));
   }
}

int compareList (List l1, List l2)
/* Menghasilkan: -1 jika l1 < l2, 0 jika l1 = l2, dan 1 jika l1 > l2 */
/* Jika l[i] adalah elemen l pada urutan ke-i dan |l| adalah panjang l: */
/* l1 = l2: |l1| = |l2| dan untuk semua i, l1[i] = l2[i] */
/* l1 < l2: Jika i adalah urutan elemen yang berbeda yang terkecil
dari l1 dan l2, l1[i]<l2[i] atau: Jika pada semua elemen pada
urutan i yang sama, l1[i]=l2[i], namun |l1|<|l2| */
/* Contoh: [3,5,6,7] < [4,4,5,6]; [1,2,3]<[1,2,3,4] */
/* l1>l2: kebalikan dari l1<l2 */
{
   if (!isEmpty(l1) && isEmpty(l2))
      return 1;

   if (isEmpty(l1) && !isEmpty(l2))
      return -1;

   if (isEmpty(l1) && isEmpty(l2))
      return 0;

   if (head(l1) < head(l2) || length(l1) < length(l2))
      return -1;

   if (head(l1) > head(l2) || length(l1) > length(l2))
      return 1;

   return compareList(tail(l1), tail(l2));
}

boolean isAllExist (List l1, List l2)
/* Menghasilkan true jika semua elemen dalam l1 terdapat dalam l2 (tanpa
memperhatikan urutan ataupun banyaknya elemen).
Kedua list mungkin kosong. Jika l1 kosong, maka hasilnya false. */
{
   if (isEmpty(l1) || !isMember(l2, head(l1)))
      return false;

   if (isOneElmt(l1))
      return isMember(l2, head(l1));

   return isAllExist(tail(l1), l2);
}