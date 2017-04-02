#include "memory.h"
int main() {
	FSA fsa;
	RAM ram;
	string nazwa, sciezka;
	ram.Find_free_space("pr1", "a.txt");
	cout << "tera ja" << endl << endl;
	ram.Zarezerwuj_pamiec("pr1", "pr1", "b.txt");


	/*
	int c;
	cout << "[1]Dodaj proces do pamieci \n[2]Usun proces z pamieci \n[3]Wyswietl zawartosc pamieci\n";
	for (;;) {
		cin >> c;
		switch (c) {
			case 1: {
				cout << "Podaj nazwe procesu: ";
				cin >> nazwa;
				cout << "Podaj sciezke: ";
				cin >> sciezka;
				ram.Zarezerwuj_pamiec("", nazwa, sciezka);
				break;
			}
			case 2: {
				cout << "Podaj nazwe procesu: ";
				cin >> nazwa;
				ram.Free_RAM(nazwa);
				break;
			}
			case 3: {
				ram.Show_RAM_state();
			}
		}

	}
	*/
	system("pause");
	return 0;
}