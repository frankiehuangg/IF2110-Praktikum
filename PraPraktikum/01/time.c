/*
NIM : 13521092
Nama : Frankie Huang
Tanggal : 7 September 2022
Topik : ADT Sederhana
Deskripsi : ADT Time yang menyimpan tipe data time
*/

#include "time.h"
#include "boolean.h"
#include <stdio.h>

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsTIMEValid (int H, int M, int S)
/* Mengirim true jika H,M,S dapat membentuk T yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
{
	if (H > 23 ||  H < 0)
		return 0;
	if (M > 59 || M < 0)
		return 0;
	if (S > 59 || S < 0)
		return 0;
	return 1;
}

/* *** Konstruktor: Membentuk sebuah TIME dari komponen-komponennya *** */
void CreateTime (TIME * T, int HH, int MM, int SS)
/* Membentuk sebuah TIME dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk TIME */
{
	Hour(*T) = HH;
	Minute(*T) = MM;
	Second(*T) = SS;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaTIME (TIME * T)
/* I.S. : T tidak terdefinisi */
/* F.S. : T terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk T */
/* yang valid. Tidak mungkin menghasilkan T yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika TIME tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh: 
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk TIME <1,3,4> */
{
	int HH, MM, SS;
	scanf("%d %d %d", &HH, &MM, &SS);

	if (IsTIMEValid(HH, MM, SS)) {
		CreateTime(T, HH, MM, SS);
	}
	else {
		printf("Jam tidak valid\n");
		BacaTIME(T);
	}
}
   
void TulisTIME (TIME T)
/* I.S. : T sembarang */
/* F.S. : Nilai T ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen T ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 
{
	printf("%d:%d:%d", Hour(T), Minute(T), Second(T));
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long TIMEToDetik (TIME T)
/* Diberikan sebuah TIME, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */
{
	return 3600*Hour(T) + 60*Minute(T) + Second(T);
}

TIME DetikToTIME (long N)
/* Mengirim  konversi detik ke TIME */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang 
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus: 
   N1 = N mod 86400, baru N1 dikonversi menjadi TIME */
{
	N = N%86400;
	TIME t;
	Hour(t) = N/3600;
	Minute(t) = (N%3600)/60;
	Second(t) = N%60;
	return t;
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean TEQ (TIME T1, TIME T2)
/* Mengirimkan true jika T1=T2, false jika tidak */
{
	if ((Hour(T1) == Hour(T2)) && (Minute(T1) == Minute(T2)) && (Second(T1) == Second(T2)))
		return 1;
	return 0;
}
boolean TNEQ (TIME T1, TIME T2)
/* Mengirimkan true jika T1 tidak sama dengan T2 */
{
	return !TEQ(T1, T2);
}
boolean TLT (TIME T1, TIME T2)
/* Mengirimkan true jika T1<T2, false jika tidak */
{
	if (TIMEToDetik(T1) < TIMEToDetik(T2))
		return 1;
	return 0;
}
boolean TGT (TIME T1, TIME T2)
/* Mengirimkan true jika T1>T2, false jika tidak */
{
	if (TIMEToDetik(T1) > TIMEToDetik(T2))
		return 1;
	return 0;
}

/* *** Operator aritmatika TIME *** */
TIME NextDetik (TIME T)
/* Mengirim 1 detik setelah T dalam bentuk TIME */
{
	return DetikToTIME(TIMEToDetik(T) + 1);
}
TIME NextNDetik (TIME T, int N)
/* Mengirim N detik setelah T dalam bentuk TIME */
{
	return DetikToTIME(TIMEToDetik(T) + N);
}
TIME PrevDetik (TIME T)
/* Mengirim 1 detik sebelum T dalam bentuk TIME */
{
	return DetikToTIME(TIMEToDetik(T) - 1);
}
TIME PrevNDetik (TIME T, int N)
/* Mengirim N detik sebelum T dalam bentuk TIME */
{
	return DetikToTIME(TIMEToDetik(T) - N);
}
/* *** Kelompok Operator Aritmetika *** */
long Durasi (TIME TAw, TIME TAkh)
/* Mengirim TAkh-TAw dlm Detik, dengan kalkulasi */
/* Jika TAw > TAkh, maka TAkh adalah 1 hari setelah TAw */
{
	long sec1 = TIMEToDetik(TAw);
	long sec2 = TIMEToDetik(TAkh);
	if (sec1 > sec2)
		sec2 += 86400;
	return sec2-sec1;
}

// int main()
// {
// 	TIME t1, t2;
// 	BacaTIME(&t1);
// 	BacaTIME(&t2);
// 	TulisTIME(t1);
// 	TulisTIME(t2);

// 	printf("%ld\n", TIMEToDetik(t1));
// 	printf("%ld\n", TIMEToDetik(t2));

// 	long d1 = 86399*2;
// 	long d2 = 86400*2;
// 	TulisTIME(DetikToTIME(d1));
// 	TulisTIME(DetikToTIME(d2));
// 	TulisTIME(DetikToTIME(0));

// 	if (TEQ(t1, t2))
// 		printf("TEQ\n");
// 	if (TNEQ(t1, t2))
// 		printf("TNEQ\n");
// 	if (TLT(t1, t2))
// 		printf("TLT\n");
// 	if (TGT(t1, t2))
// 		printf("TGT\n");

// 	TIME t3 = {12, 34, 56};
// 	TulisTIME(NextDetik(t3));
// 	TulisTIME(NextNDetik(t3, 4));
// 	TulisTIME(PrevDetik(t3));
// 	TulisTIME(PrevNDetik(t3, 57));

// 	printf("%ld\n", Durasi(t1, t2));
// 	TIME t4 = {0, 0, 1}, t5 = {0, 0, 0}; 
// 	printf("%ld\n", Durasi(t4, t5));

// 	return 0;
// }