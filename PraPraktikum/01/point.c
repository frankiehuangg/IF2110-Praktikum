/*
NIM : 13521092
Nama : Frankie Huang
Tanggal : 7 September 2022
Topik : ADT Sederhana
Deskripsi : ADT Time yang menyimpan tipe data point
*/

#include "point.h"
#include <math.h>
#include <stdio.h>
        
/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
void CreatePoint (POINT * P, float X, float Y) 
/* Membentuk sebuah POINT dari komponen-komponennya */
{
	Absis(*P) = X;
	Ordinat(*P) = Y;
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */                                                 
void BacaPOINT (POINT * P)
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk 
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2 
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
{
	float X, Y;
	scanf("%f %f", &X, &Y);
	CreatePoint(P, X, Y);
}
void TulisPOINT (POINT P)
/* Nilai P ditulis ke layar dengan format "(X,Y)" 
   tanpa spasi, enter, atau karakter lain di depan, belakang, 
   atau di antaranya 
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */                
{
	printf("(%.2f,%.2f)", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQ (POINT P1, POINT P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
	if ((Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2)))
		return 1;
	return 0;
}
boolean NEQ (POINT P1, POINT P2)
/* Mengirimkan true jika P1 tidak sama dengan P2 */
{
	if ((Absis(P1) != Absis(P2)) || (Ordinat(P1) != Ordinat(P2)))
		return 1;
	return 0;
}

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (POINT P)
/* Menghasilkan true jika P adalah titik origin */
{
	if (Absis(P) == 0 && Ordinat(P) == 0)
		return 1;
	return 0;
}
boolean IsOnSbX (POINT P)
/* Menghasilkan true jika P terletak Pada sumbu X */
{
	if (Ordinat(P) == 0)
		return 1;
	return 0;
}
boolean IsOnSbY (POINT P)
/* Menghasilkan true jika P terletak pada sumbu Y */
{
	if (Absis(P) == 0)
		return 1;
	return 0;
}
int Kuadran (POINT P)
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */
{
	if (Absis(P) > 0 && Ordinat(P) > 0)
		return 1;
	else if (Absis(P) < 0 && Ordinat(P) > 0)
		return 2;
	else if (Absis(P) < 0 && Ordinat(P) < 0)
		return 3;
	else
		return 4;
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */                           
POINT NextX (POINT P)
/* Mengirim salinan P dengan absis ditambah satu */
{
	Absis(P) += 1;
	return P;
}              
POINT NextY (POINT P)
/* Mengirim salinan P dengan ordinat ditambah satu */
{
	Ordinat(P) += 1;
	return P;
}              
POINT PlusDelta (POINT P, float deltaX, float deltaY)
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
{
	Absis(P) += deltaX;
	Ordinat(P) += deltaY;
	return P;
}              
POINT MirrorOf (POINT P, boolean SbX)
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
{
	if (SbX)
		Ordinat(P) *= -1;
	else
		Absis(P) *= -1;
	return P;
}         
float Jarak0 (POINT P)
/* Menghitung jarak P ke (0,0) */
{
	return sqrt(Absis(P)*Absis(P) + Ordinat(P)*Ordinat(P));
}
float Panjang (POINT P1, POINT P2)
/* Menghitung panjang garis yang dibentuk P1 dan P2 */
/* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. */
/* Tuliskan spec fungsi yang lebih tepat. */
{
	float l = Absis(P1)-Absis(P2);
	float w = Ordinat(P1)-Ordinat(P2);
	return sqrt(l*l + w*w);
}
void Geser (POINT *P, float deltaX, float deltaY)
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
{
	Absis(*P) += deltaX;
	Ordinat(*P) += deltaY;
}
void GeserKeSbX (POINT *P)
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
{
	Ordinat(*P) = 0;
}
void GeserKeSbY (POINT *P)
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
{
	Absis(*P) = 0;
}
void Mirror (POINT *P, boolean SbX)
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
{
	if (SbX)
		Ordinat(*P) *= -1;
	else
		Absis(*P) *= -1;
}
void Putar (POINT *P, float Sudut)
/* I.S. P terdefinisi */
/* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) */
{
	Sudut *= M_PI / 180;
	float absis = Absis(*P)*cos(Sudut) - Ordinat(*P)*sin(Sudut);
	float ordinat = Absis(*P)*sin(Sudut) + Ordinat(*P)*cos(Sudut);

	Absis(*P) = absis;
	Ordinat(*P) = ordinat;
}

// int main() 
// {
// 	// POINT p1, p2, p3;
// 	// BacaPOINT(&p1);
// 	// BacaPOINT(&p2);
// 	// TulisPOINT(p1);
// 	// TulisPOINT(p2);

// 	// if (EQ(p1, p2))
// 	// 	printf("EQ\n");
// 	// if (NEQ(p1, p2))
// 	// 	printf("NEQ\n");
// 	// if (IsOrigin(p1))
// 	// 	printf("IsOrigin\n");
// 	// if (IsOnSbX(p1))
// 	// 	printf("IsOnSbX\n");
// 	// if (IsOnSbY(p2))
// 	// 	printf("IsOnSbY\n");
// 	// printf("%d\n", Kuadran(p1));

// 	// p3 = NextX(p1);
// 	// TulisPOINT(p3);

// 	// p3 = NextY(p1);
// 	// TulisPOINT(p3);

// 	// p3 = PlusDelta(p1, 4, 3);
// 	// TulisPOINT(p3);

// 	// p3 = MirrorOf(p3, 0);
// 	// TulisPOINT(p3);

// 	// p3 = MirrorOf(p3, 1);
// 	// TulisPOINT(p3);

// 	// printf("%f\n", Jarak0(p3));

// 	// POINT p4 = {2, 3}, p5 = {5, 7};
// 	// printf("%f\n", Panjang(p4, p5));

// 	// GeserKeSbX(&p3);
// 	// GeserKeSbY(&p3);
// 	// TulisPOINT(p3);
// 	// Geser(&p3, 3, 3);
// 	// TulisPOINT(p3);

// 	// Mirror(&p3, 0);
// 	// TulisPOINT(p3);

	
// 	// Mirror(&p3, 1);
// 	// TulisPOINT(p3);

// 	POINT p3 = {3, 3};

// 	Putar(&p3, 90);
// 	TulisPOINT(p3);

// 	printf("%f", Jarak0(p3));

// 	Putar(&p3, 180);
// 	TulisPOINT(p3);

// 	Putar(&p3, -90);
// 	TulisPOINT(p3);

// 	return 0;
// }