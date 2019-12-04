/****************************************************************************
**
**				��RENC� ADI.............: Mert Ba�kaya
**				��RENC� NUMARASI........: B181210395
**				DERS GRUBU..............: 1C
****************************************************************************/


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>

using namespace std;

/* Sahne yap�s� */
struct Sahne {
	Sahne(int gen, int yuk, char krk) {
		genislik = gen;
		yukseklik = yuk;
		karakter = krk;
	}

	int genislik, yukseklik;
	char karakter;
};

/* Sekil yap�s� */
struct Sekil {
	int x, y, boyut;
	char karakter;

	/* Sekil yap�s�n�n kurucu fonksiyonu */
	Sekil(int x, int y, int boyut, char krk) {
		this->x = x;
		this->y = y;
		this->boyut = boyut;
		karakter = krk;
	}
};

/* Fonksyiyon prototip tan�mlar� */
void koordinatAta(int, int);
void sahneCiz(Sahne*);
Sekil* lSekliOlustur();
void lSekliCiz(Sekil*);
Sekil* lSekliAsagiGotur(Sekil*, int);

int main() {
	/* Rastgele zaman tohumu */
	srand(time(NULL));
	
	/* Gerekli de�i�ken tan�mlamalar� */
	char chars[] = { '*', '#', '$', '+', '@' };
	int genislik[] = { 30, 40, 50 };
	int sahneGenisligi = genislik[rand() % 3];
	int sahneYuksekligi = rand() % 11 + 20;
	char sahneKarakteri = chars[rand() % 5];
	
	/* Sahne ve Sekil nesnelerinin olu�turulmas� */
	Sahne* sahne = new Sahne(sahneGenisligi, sahneYuksekligi, sahneKarakteri);
	Sekil* sekil = lSekliOlustur();
	
	/* Uygulaman�n istenilen bi�imde �al��mas�n� sa�layan sonsuz while d�ng�s� */
	while (true) {

		system("cls");
		sahneCiz(sahne);
		lSekliCiz(sekil);
		sekil = lSekliAsagiGotur(sekil, sahneYuksekligi);

		Sleep(100);
	}
}

void koordinatAta(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/* Sahne �izen fonksiyon */
void sahneCiz(Sahne* sahne) {
	
	/*Sa�->A�a��->Sol->Yukar� �eklinde �al��an sahne �izimi d�ng�leri*/
	for (int i = 0; i < sahne->genislik; i++) {
		cout << sahne->karakter;
	}

	for (int i = 0; i < sahne->yukseklik; i++) {
		koordinatAta(sahne->genislik - 1, i);
		cout << sahne->karakter;
	}

	for (int i = 0; i < sahne->genislik; i++) {
		koordinatAta(sahne->genislik - i - 1, sahne->yukseklik - 1);
		cout << sahne->karakter;
	}

	for (int i = 0; i < sahne->yukseklik; i++) {
		koordinatAta(0, sahne->yukseklik - 1 - i);
		cout << sahne->karakter;
	}
}

/* L �eklini olu�turan fonksiyon */
Sekil* lSekliOlustur() {
	char chars[] = { '*', '#', '$', '+', '@' };
	char lSekliKarakteri = chars[rand() % 5];
	int boyut = rand() % 6 + 2;
	int y = 3;
	int x = rand() % 21 + 5;
	
	/* Sekil nesnesinin olu�turulmas�*/
	Sekil* sekil = new Sekil(x, y, boyut, lSekliKarakteri);

	return sekil;
}

/* L �eklinin �izimini yapan fonksiyon */
void lSekliCiz(Sekil* sekil) {
	int x = sekil->x;
	int y = sekil->y;
	int boyut = sekil->boyut;
	char krk = sekil->karakter;

	/* �nce soldan a�a�� inerek, sa�, yukar�, sol, yukar�, sol �eklinde ilerleyerek �ekli �izer */
	for (int i = 0; i < boyut + 1; i++) {
		koordinatAta(x, y);
		cout << krk;
		y++;
	}

	for (int i = 0; i < boyut; i++) {
		koordinatAta(x, y);
		cout << krk;
		x++;
	}

	for (int i = 0; i < (boyut + 1) / 2; i++) {
		koordinatAta(x, y);
		cout << krk;
		y--;
	}

	for (int i = 0; i < boyut / 2; i++) {
		koordinatAta(x, y);
		cout << krk;
		x--;
	}

	for (int i = 0; i < (boyut + 1) / 2 + 1; i++) {
		koordinatAta(x, y);
		cout << krk;
		y--;
	}

	/* �eklin boyutu tek ve �ift olursa �eklin tamam�n �izilemeyece�i durum olu�uyor, bundan �t�r� a�a��daki �ekilde kontrol sa�lad�m */
	if (boyut % 2 == 0) {
		for (int i = 0; i < boyut / 2 + 1; i++) {
			koordinatAta(x, y);
			cout << krk;
			x--;
		}
	}
	else {
		for (int i = 0; i < boyut / 2 + 2; i++) {
			koordinatAta(x, y);
			cout << krk;
			x--;
		}
	}

}

/* L �eklini sahnenin a�a��s�na ta��y�p tabana dokunup dokunmad���n� kontrol eden fonksiyon */
Sekil* lSekliAsagiGotur(Sekil* sekil, int sahneYuksekligi) {
	if (sekil->y + sekil->boyut + 3 < sahneYuksekligi) {
		sekil->y++;
		return sekil;
	}
	else {
		delete sekil;
		return sekil = lSekliOlustur();
	}
}