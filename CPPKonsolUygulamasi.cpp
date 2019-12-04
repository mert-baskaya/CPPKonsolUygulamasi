/****************************************************************************
**
**				ÖÐRENCÝ ADI.............: Mert Baþkaya
**				ÖÐRENCÝ NUMARASI........: B181210395
**				DERS GRUBU..............: 1C
****************************************************************************/


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>

using namespace std;

/* Sahne yapýsý */
struct Sahne {
	Sahne(int gen, int yuk, char krk) {
		genislik = gen;
		yukseklik = yuk;
		karakter = krk;
	}

	int genislik, yukseklik;
	char karakter;
};

/* Sekil yapýsý */
struct Sekil {
	int x, y, boyut;
	char karakter;

	/* Sekil yapýsýnýn kurucu fonksiyonu */
	Sekil(int x, int y, int boyut, char krk) {
		this->x = x;
		this->y = y;
		this->boyut = boyut;
		karakter = krk;
	}
};

/* Fonksyiyon prototip tanýmlarý */
void koordinatAta(int, int);
void sahneCiz(Sahne*);
Sekil* lSekliOlustur();
void lSekliCiz(Sekil*);
Sekil* lSekliAsagiGotur(Sekil*, int);

int main() {
	/* Rastgele zaman tohumu */
	srand(time(NULL));
	
	/* Gerekli deðiþken tanýmlamalarý */
	char chars[] = { '*', '#', '$', '+', '@' };
	int genislik[] = { 30, 40, 50 };
	int sahneGenisligi = genislik[rand() % 3];
	int sahneYuksekligi = rand() % 11 + 20;
	char sahneKarakteri = chars[rand() % 5];
	
	/* Sahne ve Sekil nesnelerinin oluþturulmasý */
	Sahne* sahne = new Sahne(sahneGenisligi, sahneYuksekligi, sahneKarakteri);
	Sekil* sekil = lSekliOlustur();
	
	/* Uygulamanýn istenilen biçimde çalýþmasýný saðlayan sonsuz while döngüsü */
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

/* Sahne çizen fonksiyon */
void sahneCiz(Sahne* sahne) {
	
	/*Sað->Aþaðý->Sol->Yukarý þeklinde çalýþan sahne çizimi döngüleri*/
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

/* L þeklini oluþturan fonksiyon */
Sekil* lSekliOlustur() {
	char chars[] = { '*', '#', '$', '+', '@' };
	char lSekliKarakteri = chars[rand() % 5];
	int boyut = rand() % 6 + 2;
	int y = 3;
	int x = rand() % 21 + 5;
	
	/* Sekil nesnesinin oluþturulmasý*/
	Sekil* sekil = new Sekil(x, y, boyut, lSekliKarakteri);

	return sekil;
}

/* L þeklinin çizimini yapan fonksiyon */
void lSekliCiz(Sekil* sekil) {
	int x = sekil->x;
	int y = sekil->y;
	int boyut = sekil->boyut;
	char krk = sekil->karakter;

	/* Önce soldan aþaðý inerek, sað, yukarý, sol, yukarý, sol þeklinde ilerleyerek þekli çizer */
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

	/* Þeklin boyutu tek ve çift olursa þeklin tamamýn çizilemeyeceði durum oluþuyor, bundan ötürü aþaðýdaki þekilde kontrol saðladým */
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

/* L þeklini sahnenin aþaðýsýna taþýyýp tabana dokunup dokunmadýðýný kontrol eden fonksiyon */
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