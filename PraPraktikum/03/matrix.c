/* ********** Definisi TYPE Matrix dengan Index dan elemen integer ********** */

// NIM         : 13521092
// Nama        : Frankie Huang
// Tanggal     : 21 September 2022
// Topik       : ADT Matrix
// Deskripsi   : Implementasi ADT Matrix

#include <stdio.h>
#include "matrix.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void createMatrix(int nRows, int nCols, Matrix *m)
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
{
   ROW_EFF(*m) = nRows;
   COL_EFF(*m) = nCols;
}

/* *** Selektor "Dunia Matrix" *** */
boolean isMatrixIdxValid(int i, int j)
/* Mengirimkan true jika i, j adalah index yang valid untuk matriks apa pun */
{
   if (i >= 0 && i < ROW_CAP && j >= 0 && j < COL_CAP)
      return true;
   return false;
}

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
IdxType getLastIdxRow(Matrix m)
/* Mengirimkan Index baris terbesar m */
{
   return ROW_EFF(m)-1;
}
IdxType getLastIdxCol(Matrix m)
/* Mengirimkan Index kolom terbesar m */
{
   return COL_EFF(m)-1;
}
boolean isIdxEff(Matrix m, IdxType i, IdxType j)
/* Mengirimkan true jika i, j adalah Index efektif bagi m */
{
   if (i >= 0 && i < ROW_EFF(m) && j >= 0 && j < COL_EFF(m))
      return true;
   return false;
}
ElType getElmtDiagonal(Matrix m, IdxType i)
/* Mengirimkan elemen m(i,i) */
{
   return ELMT(m,i,i);
}

/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mOut)
/* Melakukan assignment mOut <- mIn */
{
   createMatrix(ROW_EFF(mIn), COL_EFF(mIn), mOut);

   int i,j;
   for (i = 0; i < ROW_EFF(mIn); i++)
      for (j = 0; j < COL_EFF(mIn); j++)
         ELMT(*mOut,i,j) = ELMT(mIn,i,j);
}

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrix(Matrix *m, int nRow, int nCol)
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
{
   createMatrix(nRow, nCol, m);

   int i,j;
   for (i = 0; i < ROW_EFF(*m); i++)
      for (j = 0; j < COL_EFF(*m); j++)
         scanf("%d", &ELMT(*m,i,j));
}
void displayMatrix(Matrix m)
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
   int i,j;
   for (i = 0; i < getLastIdxRow(m); i++)
   {
      for (j = 0; j < getLastIdxCol(m); j++)
      {
         printf("%d ", ELMT(m,i,j));
      }
      printf("%d\n", ELMT(m,i,getLastIdxCol(m)));
   }
   for (j = 0; j < getLastIdxCol(m); j++)
      printf("%d ", ELMT(m,getLastIdxRow(m),j));
   printf("%d\n", ELMT(m,getLastIdxRow(m), getLastIdxCol(m)));
}

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
Matrix addMatrix(Matrix m1, Matrix m2)
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil penjumlahan matriks: m1 + m2 */
{
   int i,j;
   for (i = 0; i < ROW_EFF(m1); i++)
      for (j = 0; j < COL_EFF(m1); j++)
         ELMT(m1,i,j) += ELMT(m2,i,j);

   return m1;
}
Matrix subtractMatrix(Matrix m1, Matrix m2)
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
{
   int i,j;
   for (i = 0; i < ROW_EFF(m1); i++)
      for (j = 0; j < COL_EFF(m1); j++)
         ELMT(m1,i,j) -= ELMT(m2,i,j);

   return m1;
}
Matrix multiplyMatrix(Matrix m1, Matrix m2)
/* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
/* Mengirim hasil perkalian matriks: salinan m1 * m2 */
{
   Matrix m;
   createMatrix(ROW_EFF(m1), COL_EFF(m2), &m);

   int i,j,k;
   for (i = 0; i < ROW_EFF(m1); i++)
   {
      for (j = 0; j < COL_EFF(m2); j++)
      {
         ELMT(m,i,j) = 0;
         for (k = 0; k < ROW_EFF(m2); k++)
         {
            ELMT(m,i,j) += ELMT(m1,i,k)*ELMT(m2,k,j);
         }
      }
   }

   return m;
}
Matrix multiplyByConst(Matrix m, ElType x)
/* Mengirim hasil perkalian setiap elemen m dengan x */
{
   int i,j;
   for (i = 0; i < ROW_EFF(m); i++)
      for (j = 0; j < COL_EFF(m); j++)
         ELMT(m,i,j) *= x;

   return m;
}
void pMultiplyByConst(Matrix *m, ElType k)
/* I.S. m terdefinisi, k terdefinisi */
/* F.S. Mengalikan setiap elemen m dengan k */
{
   int i,j;
   for (i = 0; i < ROW_EFF(*m); i++)
      for (j = 0; j < COL_EFF(*m); j++)
         ELMT(*m,i,j) *= k;
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
boolean isMatrixEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
/* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
/* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
{
   if (ROW_EFF(m1) != ROW_EFF(m2))
      return false;  
   if (COL_EFF(m1) != COL_EFF(m2))
      return false;

   int i = 0, j;
   while (i < ROW_EFF(m1))
   {
      j = 0;
      while (j < COL_EFF(m1))
      {
         if (ELMT(m1,i,j) != ELMT(m2,i,j))
            return false;
         j++;
      }
      i++;
   }

   return true;
}
boolean isMatrixNotEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika m1 tidak sama dengan m2 */
{
   return !isMatrixEqual(m1,m2);
}
boolean isMatrixSizeEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
/* yaitu RowEff(m1) = RowEff (m2) dan ColEff (m1) = ColEff (m2) */
{
   if (ROW_EFF(m1) == ROW_EFF(m2) && COL_EFF(m1) == COL_EFF(m2))
      return true;
   return false;
}

/* ********** Operasi lain ********** */
int countElmt(Matrix m)
/* Mengirimkan banyaknya elemen m */
{
   return ROW_EFF(m)*COL_EFF(m);
}

/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
boolean isSquare(Matrix m)
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
{
   if (COL_EFF(m) == ROW_EFF(m))
      return true;
   return false;
}
boolean isSymmetric(Matrix m)
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
   dan untuk setiap elemen m, m(i,j)=m(j,i) */
{
   if (!isSquare(m))
      return false;

   int i = 0;
   while (i < ROW_EFF(m))
   {
      int j = i;
      while (j < COL_EFF(m))
      {
         if (ELMT(m,i,j) != ELMT(m,j,i))
            return false;
         j++;
      }
      i++;
   }

   return true;
}
boolean isIdentity(Matrix m)
/* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan 
   setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
{
   if (!isSquare(m))
      return false;

   int i = 0, j;
   while (i < ROW_EFF(m))
   {
      j = 0;
      while (j < COL_EFF(m))
      {
         if (i == j && ELMT(m,i,j) != 1)
            return false;
         if (i != j && ELMT(m,i,j) != 0)
            return false;
         j++;
      }
      i++; 
      j = 0;
   }

   return true;
}
boolean isSparse(Matrix m)
/* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
{
   float size = ROW_EFF(m)*COL_EFF(m);
   float amt = 0;

   int i,j;
   for (i = 0; i < ROW_EFF(m); i++)
      for (j = 0; j < COL_EFF(m); j++)
         if (ELMT(m,i,j) != 0)
            amt++;

   if ((amt*100/size) <= 5)
      return true;
   return false;
}
Matrix negation(Matrix m)
/* Menghasilkan salinan m dengan setiap elemen dinegasikan (dikalikan -1) */
{
   int i,j;
   for (i = 0; i < ROW_EFF(m); i++)
      for (j = 0; j < COL_EFF(m); j++)
         ELMT(m,i,j) *= -1;

   return m;
}
void pNegation(Matrix *m)
/* I.S. m terdefinisi */
/* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
{
   int i,j;
   for (i = 0; i < ROW_EFF(*m); i++)
      for (j = 0; j < COL_EFF(*m); j++)
         ELMT(*m,i,j) *= -1;
}
float determinant(Matrix m)
/* Prekondisi: isSquare(m) */
/* Menghitung nilai determinan m */
{
   int num1, num2, index, det = 1, total = 1;
   int temp[ROW_EFF(m)];

   int i,j,k;
   for (i = 0; i < ROW_EFF(m); i++)
   {
      index = i;

      while (index < ROW_EFF(m) && ELMT(m,index,i) == 0)
         index++;
      if (index == ROW_EFF(m))
         continue;
      if (index != i)
      {
         for (j = 0; j < ROW_EFF(m); j++)
         {
            ELMT(m,index,j) ^= ELMT(m,i,j);
            ELMT(m,i,j) ^= ELMT(m,index,j);
            ELMT(m,index,j) ^= ELMT(m,i,j);
         }
         if ((index-i) % 2 == 1)
            det *= -1;
      }
      for (j = 0; j < ROW_EFF(m); j++)
         temp[j] = ELMT(m,i,j);
      for (j = i + 1; j < ROW_EFF(m); j++)
      {
         num1 = temp[i];
         num2 = ELMT(m,j,i);

         for (k = 0; k < ROW_EFF(m); k++)
            ELMT(m,j,k) = (num1*ELMT(m,j,k)) - (num2*temp[k]);
         total *= num1;
      }
   }

   for (i = 0; i < ROW_EFF(m); i++)
      det *= ELMT(m,i,i);

   return det/total;
}
Matrix transpose(Matrix m)
/* I.S. m terdefinisi dan IsSquare(m) */
/* F.S. menghasilkan salinan transpose dari m, yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
{
   int i,j;
   for (i = 0; i < ROW_EFF(m); i++)
   {
      for (j = i+1; j < COL_EFF(m); j++)
      {
         ELMT(m,i,j) ^= ELMT(m,j,i);
         ELMT(m,j,i) ^= ELMT(m,i,j);
         ELMT(m,i,j) ^= ELMT(m,j,i);
      }
   }

   ROW_EFF(m) ^= COL_EFF(m);
   COL_EFF(m) ^= ROW_EFF(m);
   ROW_EFF(m) ^= COL_EFF(m);

   return m;
}
void pTranspose(Matrix *m)
/* I.S. m terdefinisi dan IsSquare(m) */
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
{
   int i,j;
   for (i = 0; i < ROW_EFF(*m); i++)
   {
      for (j = i+1; j < COL_EFF(*m); j++)
      {
         ELMT(*m,i,j) ^= ELMT(*m,j,i);
         ELMT(*m,j,i) ^= ELMT(*m,i,j);
         ELMT(*m,i,j) ^= ELMT(*m,j,i);
      }
   }

   ROW_EFF(*m) ^= COL_EFF(*m);
   COL_EFF(*m) ^= ROW_EFF(*m);
   ROW_EFF(*m) ^= COL_EFF(*m);
}