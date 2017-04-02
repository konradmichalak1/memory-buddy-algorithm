#include "memory.h"
/*------------------------------------------------------------KLASA RAM ----------------------------------------------------------------*/
/* KONSTRUKTOR */
RAM::RAM(){
	for (int i = 0; i < SIZE * 16; i++)
		RAM_SPACE[i] = '-';

	n = 0;
	wynik = 0;
}

/* POBRANIE WIELKOŒCI PROGRAMU */
int RAM::Get_program_size(string sciezka_do_pliku) {

	int program_size = 0;
	string text;
	fstream plik;
	
	plik.open(sciezka_do_pliku, ios::in);
	if (plik.good()) {
		getline(plik, text);
		//cout << text << endl;
		program_size = text.length();
	}
	
	else cout << "Blad pliku - Plik nie istnieje lub jest uszkodzony\n";
	PROGRAM = new char[program_size];
	for (int i = 0; i < program_size; i++) {
		PROGRAM[i] = text[i];
	}
	plik.clear();
	plik.close();
	
	return program_size;
}
/*
//funkcja niezapisujaca spacji
int RAM::Get_program_size2(string nazwa_pliku, string sciezka_do_pliku) {
	int program_size = 0;
	string text;
	string text_bez_spacji;
	fstream plik;

	plik.open(sciezka_do_pliku, ios::in);
	if (plik.good()) {
		getline(plik, text);
		program_size = text.length();
	}
	else cout << "Blad pliku - Plik nie istnieje lub jest uszkodzony\n";

	
	for (int i = 0; i < text.length(); i++) {
		if (text[i] != ' ' && text[i] != '	')
		text_bez_spacji += text[i];
	}
	program_size = text_bez_spacji.length();
	//cout << text_bez_spacji;
	PROGRAM = new char[program_size];
	for (int i = 0; i < program_size; i++) {
		PROGRAM[i] = text_bez_spacji[i];
	}
	//cout << program_size;

	return program_size;
}
*/

/* LICZENIE POTÊGI LICZBY 2 */
int RAM::Power_of_two(int n) {
	if (n == 0) return 1;
	else { return 2*Power_of_two(n - 1); }
	
}

/* ODSZUKANIE ODPOWIEDNIEGO OBSZARU DLA PROGRAMU */
/* Zwraca wartoœæ n lub -1, je¿eli -1 oznacza to, ¿e plik jest albo zbyt du¿y, albo wyst¹pi³ jakiœ problem podczas pobierania rozmiaru pliku */
int RAM::Find_program_recommended_size(string sciezka_do_pliku) {
	int x = Get_program_size(sciezka_do_pliku);
	for (int i = 0; i <= 4; i++) { // przedzia³ od 0 - 4, bo 2^4 = 16, a 16 * 16 = 256 czyli ca³a wolna przestrzeñ pamiêci
		if (x <= 0) return -1;
		if (x <= SIZE*Power_of_two(i)) return i;
	}

	return -1;
}
/* ZWRACA DLUGOSC PETLI FOR DLA FUNKCJI Find_free_space() */
int RAM::Get_length(string sciezka_do_pliku) {
	int n = Find_program_recommended_size(sciezka_do_pliku);
	if (n ==-1) { return 0;  }
	if (n == 0) { return 16; }
	if (n == 1) { return 8;  }
	if (n == 2) { return 4;  }
	if (n == 3) { return 2;  }
	if (n == 4) { return 1;  }
	else return 0;
}

/* ZNALEZIENIE OBSZARU I ZAPISANIE W PAMIÊCI PROGRAMU */
int RAM::Find_free_space(string nazwa_w_pamieci, string sciezka_do_pliku) {

	for (int i = 0; i < 255; i++) {
		RAM_SPACE[i];
	}
	int status;
	int DLUGOSC = Get_length(sciezka_do_pliku);
	int n = Find_program_recommended_size(sciezka_do_pliku);
	if (DLUGOSC == 0) {
		cout << "Nie mozna zapisac programu w pamieci.\n";
		return 0;
	}

	for (int i = 0; i < DLUGOSC; i++) {
		status = fsa.Is_free(Power_of_two(n) * SIZE * i, (Power_of_two(n) * SIZE * (i + 1)) - 1);
		if (status == 0) {
			cout << "obszar " << (Power_of_two(n) * 16 * i) << "-" << (Power_of_two(n) * 16 * (i + 1)) - 1 << " ZAJETY.\n";
		} //jezeli funkcja is_free mowi, ze obszar jest zajety, petla sprawdza kolejny obszar
		/*np. n = 1, wtedy DLUGOSC = 8, argumentami funkcji is_free dla pierwszego wykonania petli jest A = 2^1*16*0 = 0 oraz B=2*16*1 - 1=32-1=31. Sprawdza obszar 0-31 */
		/*drugie wykonanie petli: A=2*16*1=32, B=2*16*2-1 = 63, sprawdza zakres 32-63  */
		else if (status == 1) {
			cout << "obszar " << (Power_of_two(n) * 16 * i) << "-" << (Power_of_two(n) * 16 * (i + 1)) - 1 << " WOLNY.\n";
			fsa.Save_FSA(Power_of_two(n) * SIZE * i, (Power_of_two(n) * SIZE * (i + 1)) - 1, nazwa_w_pamieci);
			Save_program_on_RAM(Power_of_two(n) * 16 * i, (Power_of_two(n) * 16 * (i + 1)) - 1, sciezka_do_pliku);
			return 0;
		}
	}
	return 0;
}
/* JE¯ELI ZNALEZIONA ZOSTALA WOLNA PRZESTRZEN, ZAWARTOSC PROGRAMU MOZNA ZAPISAC W RAMie */
int RAM::Save_program_on_RAM(int A, int B, string sciezka_do_pliku) {
	int n = Get_program_size(sciezka_do_pliku);
	for (int i = A; i < B; i++) {
		RAM_SPACE[i] = '-';
	}
	int k = 0;
	for (int j = A; j < A+n; j++) {
		RAM_SPACE[j] = PROGRAM[k];
		k++;
	}
	return A;
}
void RAM::Free_RAM(string nazwa_w_pamieci){
int A, B;
	A = fsa.Zwolnij_pamiec_A(nazwa_w_pamieci);
	B = fsa.Zwolnij_pamiec_B(nazwa_w_pamieci);
	cout << "Proces " << nazwa_w_pamieci << " [" << A << "-" << B << "] zwolniony.\n\n";
	for (int i = A; i < B; i++) {
		RAM_SPACE[i] = '-';
	}
}

void RAM::Show_RAM_state() {
	int pocz=0;
	int kon = 0;
	short a=0;
	for (int i = 0; i < SIZE; i++) {
		if (fsa.free_space_array[i][1] != fsa.free_space_array[i + 1][1]) {
			kon = i;
			cout << pocz * 16 << "-" << ((i+1) * 16) - 1 << " Program: " << fsa.nazwy_programow[i] << endl;
			pocz = i + 1;
		}
	}
	cout << "Czy wyswietlic zawartosc pamieci? TAK[1] NIE[2]";
	cin >> a;
	if (a == 1) {
		for (int i = 0; i < SIZE*16; i++) {
			cout << RAM_SPACE[i];
			if ((i + 1) % 16 == 0) cout << endl;
		}
	}
	
}

int RAM::Zarezerwuj_pamiec(string nazwa_ojca, string nazwa_nowego, string sciezka_do_pliku) {
	int adres_w_pamieci;

	if (nazwa_ojca == nazwa_nowego) {
		//EXEC - nadpisuje plik o nazwa_ojca plikiem z argumentu sciezka_do_pliku
		Free_RAM(nazwa_ojca);
		adres_w_pamieci = Find_free_space(nazwa_nowego, sciezka_do_pliku);
	}
	else if (nazwa_ojca != nazwa_nowego && sciezka_do_pliku == "") {
		//FORK - nazwa_nowego zostaje zapisany i dostaje to samo co posiada nazwa_ojca

	}

	cout << endl << adres_w_pamieci << endl;
	return adres_w_pamieci;
}

/*-------------------------------------------------------KLASA FSA -------------------------------------------------------------*/

/* KONSTRUKTOR */
FSA::FSA() {

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < 2; j++)
			free_space_array[i][j] =  0 ;
	program_nr = 1;
	for (int i = 0; i < 16;i++)
		nazwy_programow[i] = "";
}

/* SPRAWDZA CZY DANY OBSZAR Z ZAKRESU A - B, JEST WOLNY W RAMIE
	A,B - Zakres pamieci w RAMie np: [0-31] lub [64-127] */
bool FSA::Is_free(int A, int B){
	if (B > 255) return 0;
	if (A < 0) return 0;
	A /= 16; //argumentem funkcji jest A i B które s¹ wartosci¹ z przedzia³u 0-255, dzielimy na 16 by wiedzieæ które ramki s¹ zajête
	B /= 16;
	for (int i = A; i <= B; i++) {
		if (free_space_array[i][0]==1) return 0; //jezeli jakikolwiek fragment tego obszaru jest zajety, zwraca 0
	}

	return 1;
}

int FSA::Save_FSA(int A, int B, string nazwa_w_pamieci) {
	if (B > 255) return 0;
	if (A < 0) return 0;
	A /= 16; //argumentem funkcji jest A i B które s¹ wartosci¹ z przedzia³u 0-255, dzielimy na 16 by wiedzieæ które ramki s¹ zajête
	B /= 16;
	cout << "Zapisuje program: " << nazwa_w_pamieci << "\n";
	for (int i = A; i <= B; i++) {
		free_space_array[i][0] = 1;	//ustawienie fragmentu tablicy jako zajêty
		nazwy_programow[i] = nazwa_w_pamieci;
		free_space_array[i][1] = program_nr;	//ustawienie fragmentu tablicy jako zajêty
	}
	program_nr += 1;
	return 1;
}

int FSA :: Zwolnij_pamiec_A(string nazwa_w_pamieci) {
	///SPRAWDZANIE CZY PROCES ISTNIEJE, ZEBY NIE ZWOLNILO PROCESU KTOREGO NIE MA
	int A = 0, B = 0;
	int liczA = -1;
	int liczB = -1;
	///NIE DZIALA ODCZYTYWANIE NAZWY_PROGRAMOW[i];
	for (int i = 0; i < 16; i++) {
		if (nazwy_programow[i] == nazwa_w_pamieci) {
			
			A = i;
			liczA++;
			
			if (i<15 && nazwy_programow[i+1] != nazwa_w_pamieci) {
				B = i+1;
			}
			else if (i == 15) B = i+1;
			
		}
	
	}

	//cout << (B * 16) - 1;
	//cout << "Proces: " << nazwa_w_pamieci << " [" << (A * 16) << ((B * 16)) << "] zwolniony.\n";
	A -= liczA;
	A = A * 16;
	return A;
}

int FSA::Zwolnij_pamiec_B(string nazwa_w_pamieci) {
	///SPRAWDZANIE CZY PROCES ISTNIEJE, ZEBY NIE ZWOLNILO PROCESU KTOREGO NIE MA
	int A = 0, B = -1;
	int liczA = -1;
	int liczB = -1;
	///NIE DZIALA ODCZYTYWANIE NAZWY_PROGRAMOW[i];
	for (int i = 0; i < 16; i++) {
		if (nazwy_programow[i] == nazwa_w_pamieci) {
		B = i+1;
		nazwy_programow[i] = "";
		free_space_array[i][0] = 0;
		free_space_array[i][1] = 0;
		}
	}
	if (B == -1) B = 16;
	
	B = (B * 16) - 1;
	//cout << "Proces: " << nazwa_w_pamieci << " [" << (A * 16) << ((B * 16)) << "] zwolniony.\n";
	return B;
}


