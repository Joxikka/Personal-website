//#pragma once

#ifndef Slika_H
#define Slika_H

#include <iostream>
#include <string>

#include "Piksel.h"

#define MIN_SIRINA 0
#define MIN_VISINA 0
#define MAX_SIRINA 7680
#define MAX_VISINA 4320

class Slika
{
private:
	//Attributes
	int _sirina; //Broj piksela koji predstavlja sirinu slike je ustvari broj kolona "matrice" slike
	int _visina; //Broj piksela koji predstavlja visinu slike je ustvari broj vrsta "matrice" slike

	//Sliku posmatramo kao matricu piksela cije dimenzije (broj vrsta i kolona) dinamicki odredjujemo citanjem fajla slike.
	//Medjutim kako je piksel objekat klase Piksel (tj. nije "prost" tip podatka, npr. int, char, ...),
	// to matricu piksela slike ne mozemo posmatrati kao ** pokazivac, tj. kao pokazivac na pokazivac,
	// vec kao *** pokazivac tipa Piksel, tj. pokazivac na pokazivac na pokazivac na objekat tipa Piksel.
	//Pokazivac na pokazivac bi mogli da koristimo u slucaju da je element matrice neki "prost" tip podatka a ne kao ovde objekat klase.
	//Da je na primer piksel slike predstavljen prostije (tj. jednim simbolom/string-om), na primer u heksa zapisu (#FFFFFF),
	// onda bi mogli da prodjemo sa ** pokazivacem. 
	Piksel*** _matricaPiksela;

	//Private Setters
	//Hocu da koristim metode za postavljanje sirine i visine slike, kao i matrice slike (bez vrednosti),
	// jer tako mogu da vrsim validaciju vrednosti koje se dodeljuju i tako kontrolisem nemoguce/nedozvoljene vrednosti.
	//Obzirom da se sirina i visina slike ne postavljaju direktnim zadavanjem vrednosti, vec se iscitavaju iz fajla,
	// to nema potrebe da ove metode budu "dostupne spolja" tj. da budu public.
	//Sustinski, obzirom da ce se metode pozivati samo iz drugih metoda klase, ima vise smisla da budu private.
	bool postaviSirinu(int sirina);
	bool postaviVisinu(int visina);

	bool kreirajMatricuSlike();

	//Private Helpers - Pomocne f-je koje cemo koristiti u okviru metode za ucitavanje slike ucitajSliku()

	//Metoda/f-ja ce da vrsi citanje vrednosti pozicija dok ne procita simbol \n i vrsiti njegovo konvertovanje u broj
	int procitajBroj(std::string podaciSlike, int& pozicija);

	//Metoda/f-ja ce da vrsi citanje RGB vrednosti vrednosti jednog piksela,
	// tj. tri broja u nizu iz ulaznog string-a i da kreira/inicijalizuje pokazivac na objekat klase Piksel
	// inicijalizovan sa vrednostima procitanih brojeva.
	//Primer dela ulaznog string-a koji reprezentuje jednu RGB sekvencu: ...\n128\n50\n9\n...
	Piksel* postaviPiksel(std::string podaciSlike, int& pozicija);

public:
	//Constructors
	Slika();

	//Copy Constructor
	//Kopija konstruktora - Ovaj konstruktor se izvrsava u slucaju kada se instanciranje objekta klase vrsi:
	// - inicijalizacijom preko drugog objekta (npr. Slika novaSlika = staraSlika;)
	// - kada je objekat ulazni argument neke f-je (npr. void inputJeObjekat(Slika ulaznaSlika);)
	// - kada je objekat izlazni argument neke f-je (npr. Slika outputJeObjekat(){ ... return slikaIzFje};)
	//Ulazni argument u kopiju konstruktora mora biti referenca objekta klase propustena kao konstanta.
	Slika(const Slika& img);

	//Destructors
	//Destruktor klase je metoda koja se automatski izvrsava kada brisemo objekat klase (komanda/poziv operatora delete).
	//Destruktor uvek postoji (kao i konstruktor!) bez obzira da li ga mi definisali ili ne (u ovom slucaju ga definise kompajler ali kao f-ju koja je "prazna").
	//Ime destruktora klase je sacinjeno od prefiksa ~ i imena klase (za razliku od konstruktora gde je samo ime klase). Npr. ~ImeKlase()
	//Klasa moze imati samo jedan definisan destruktor (za razliku od konstruktora kojih moze biti vise - overload).
	//Mora biti public void metoda, bez ulaznih parametara.
	//Destruktor ne pozivamo direktno, vec se on izvrsava sa brisanjem objekta, tj. sa komandom: delete imeObjektaKlase;
	//
	//Destruktor klase je obavezan ukoliko klasa sadrzi atribute tipa pokazivac da bi mogli da izbrisemo podatke na koje oni pokazuju.
	//U suprotnom izbrisacemo samo vrednosti adresa na koje oni pokazuju, tj. adrese gde su podaci stvarno smesteni, 
	// ali ne i same podatke - oni ostaju "zarobljeni/zaglavljeni" u memoriji (tzv. "memory leaking").
	//Nas destruktor mora izbrisati iz dinamicke memorije sve sto je neki objekat klase kreirao tokom rada programa,
	// tj. sve sto je proisteklo iz inicijalizacije njegovih pokazivaca (u nasem zadatku to je ***_matricaPiksela).
	~Slika();

	//Setters
	bool ucitajSliku(std::string podaciSlike);

	bool efekatCrnoBelaSlika();
	bool efekatInverznaSlika();

	//Getters
	int sirina();
	int visina();

	std::string format();

	std::string snimiSliku();
};

#endif // !Slika_H