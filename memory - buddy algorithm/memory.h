#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <fstream>
using namespace std;
const int  SIZE = 16; //rozmiar strony
static int licznik = 0;
class FSA { //FSA - Free Space Array - informuje o stanie RAMU
public:
	int free_space_array[SIZE][2]; //tablica pocz�tkowo wyzerowana, wartosc 1 oznacza zaj�cie danego indeksu przez jaki� proces, [LICZBA_RAMEK][LICZBA_PROGRAMOW]
	int program_nr; //numer programu zapisanego w pami�ci
	string nazwy_programow[16];
	bool Is_free(int, int); //sprawdza czy dany obszar pamieci jest wolny
	int Save_FSA(int, int, string);  //zmienia status w pamieci na zajety
	int Zwolnij_pamiec_A(string nazwa_w_pamieci);
	int Zwolnij_pamiec_B(string nazwa_w_pamieci);
	FSA();
};

class RAM {
public:
	FSA fsa;
	int n; //pot�ga dw�jki
	char RAM_SPACE[16 * SIZE]; // 256 znak�w
	char *PROGRAM; //Przechowuje zawartosc programu
	RAM();
	int Get_program_size(string); //Pobierze dlugosc programu ktory nastepnie zapisze do RAMu
	int Get_program_size2(string);
	int Find_program_recommended_size(string); //wyszukuje n, by m�c zarezerwowa� przestrzen do odpowiedniej pot�gi 2
	int Power_of_two(int); //argument - n, funkcja zwraca 2^n;
	int Find_free_space(string, string); //Poszuka w przestrzeni RAM, wolnego obszaru w kt�rym b�dzie mo�na zapisa� program, zwraca przedzia� w pami�ci
	int Get_length(string); //zwraca n, dla funkcji find_free_space
	int Save_program_on_RAM(int,int,string); //zapisuje program w pamieci RAM
	int FORK_Save_on_RAM(int, int, string);
	void Show_RAM_state(); //pokaze wszystkie informacje o pamieci
	
	void Free_RAM(string);
	int Zarezerwuj_pamiec(string nazwa_pliku, string nazwa_w_pamieci, string sciezka_do_pliku);
	/*
	void Zarezerwuj_pamiec(string nazwa_pliku, string nazwa_pod_jaka_ma_zostac_zaladowany_w_pamieci, string sciezka_do_pliku)
	//1 - NAZWA PLIKU KT�REGO KOD MA ZOSTA� ZA�ADOWANY
	Z DYSKU DO PAMI�CI, 2 - NAZWA POD JAK� KOD MA ZOSTA�
	W PAMI�CI ZA�ADOWANY, 3 - �CIE�KA DO PLIKU TXT KT�REGO
	KOD MA ZOSTA� ZAPISANY W PLIKU Z PARAMETRU NR 1
	*/
	int wynik;
};



