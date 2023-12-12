#include "Slika.h"

using namespace std;

//Private Setters

bool Slika::postaviSirinu(int sirina) {
	if (sirina < MIN_SIRINA) {
		this->_sirina = MIN_SIRINA;
		return false;
	}
	else if (sirina > MAX_SIRINA) {
		this->_sirina = MAX_SIRINA;
		return false;
	}
	else {
		this->_sirina = sirina;
		return true;
	}
};

bool Slika::postaviVisinu(int visina) {
	if (visina < MIN_VISINA) {
		this->_visina = MIN_VISINA;
		return false;
	}
	else if (visina > MAX_VISINA) {
		this->_visina = MAX_VISINA;
		return false;
	}
	else {
		this->_visina = visina;
		return true;
	}
};

bool Slika::kreirajMatricuSlike() {
	//Prvo definisemo matricu piksela kao dinamicki niz pokazivaca na nizove vrsta matrice.
	this->_matricaPiksela = new Piksel** [this->visina()]; //Napomena: Svako new (alokacija/zauzece dinamicke memorije) podrazumeva i jedno delete (delokaciju/oslobadjanje dinamicke memorije)

	//Zatim prolazimo kroz definisani niz pokazivaca na vrste i definisemo dinamicki niz piksela za svaku vrstu
	//Vrednost piksela je u sustini pokazivac na objekat klase Piksel (stoga jos jedan pokazivac)
	for (int vrsta = 0; vrsta < this->visina(); vrsta++) {
		this->_matricaPiksela[vrsta] = new Piksel* [this->sirina()];
	}

	return true;
}

//Private Helpers - Pomocne f-je koje cemo koristiti u okviru metode za ucitavanje slike

// Ulazna pozicija je referenca obzirom da hocemo da zadrzimo vrednost promena pozicije izvrsenih unutar f-je.
int Slika::procitajBroj(string podaciSlike, int& pozicija) {
	int broj = 0;

	while (podaciSlike[pozicija] != '\n') {
		//cout << "podaciSlike[" << pozicija << "] = " << podaciSlike[pozicija] << "	tekuci broj: " << broj << endl;
		broj = 10 * broj + (podaciSlike[pozicija] - '0'); //razlika dve char promenljive je ustvari vrednost razlike njihovih ascii kodova (npr. '5' - '0' = 53 - 48 = 5) cime dobijamo i brojcanu vrednost procitanog karaktera broja
		pozicija++;
	}
	//cout << "Procitani broj: " << broj << endl;
	//cout << "--------------------------------------" << endl;

	//Obzirom da je poslednja vrednost pozicije ustvari \n, onda cemo pre nego sto izadjemo iz f-je
	// pomeriti vrednost pozicije na sledeci clan/znak
	pozicija++;

	return broj;
}

// Ulazna pozicija je referenca obzirom da hocemo da zadrzimo vrednost promena pozicije izvrsenih unutar f-je.
Piksel* Slika::postaviPiksel(string podaciSlike, int& pozicija) {
	Piksel* procitaniPiksel = new Piksel();

	procitaniPiksel->postaviRed(this->procitajBroj(podaciSlike, pozicija));
	procitaniPiksel->postaviGreen(this->procitajBroj(podaciSlike, pozicija));
	procitaniPiksel->postaviBlue(this->procitajBroj(podaciSlike, pozicija));

	cout << "\nRGB = (" << static_cast<unsigned>(procitaniPiksel->red()) << ", " << static_cast<unsigned>(procitaniPiksel->green()) << ", " << static_cast<unsigned>(procitaniPiksel->blue()) << ")" << endl;

	return procitaniPiksel;
}


//Constructors

Slika::Slika() {
	cout << "IZVRSAVA SE PRAZAN/DEFAULT KONSTRUKTOR" << endl;
	this->postaviSirinu(MIN_SIRINA);
	this->postaviVisinu(MIN_VISINA);

	this->_matricaPiksela = nullptr;
}

//Copy Constructor
Slika::Slika(const Slika& img) {
	cout << "IZVRSAVA SE KOPIJA KONSTRUKTORA" << endl;
	this->postaviSirinu(img._sirina);
	this->postaviVisinu(img._visina);
	this->kreirajMatricuSlike();
	cout << this->_matricaPiksela << endl;
	for (int vrsta = 0; vrsta < this->visina(); vrsta++) {
		for (int kolona = 0; kolona < this->sirina(); kolona++) {
			this->_matricaPiksela[vrsta][kolona] = new Piksel;
			*this->_matricaPiksela[vrsta][kolona] = *img._matricaPiksela[vrsta][kolona];
		}
	}
	cout << this->_matricaPiksela << endl;
	cout << img._matricaPiksela << endl;

	cout << this->_matricaPiksela[20][20] << endl;
	cout << img._matricaPiksela[20][20] << endl;

	cout << static_cast<unsigned>(this->_matricaPiksela[20][20]->green()) << endl;
	cout << static_cast<unsigned>(img._matricaPiksela[20][20]->green()) << endl;
}

//Destructors

//Brisemo sve pokazivace ali u suprotnom redosledu od njihovog kreiranja, sto bi znacilo:
// - prvo objekte piksela u jednoj vrsti;
// - potom vrstu kao niz pokazivaca (adresa) na objekte piksela (prethodno izbrisane);
// - nakon sto prethodna dva koraka izvrsimo za svaku vrstu, brisemo niz pokazivaca na vrste matrice;
// - na kraju brisemo sam pokazivac _matricaPiksela tj pokazivac na prethodno izbrisani niz vrsta.
Slika::~Slika() {
	for (int vrsta = 0; vrsta < this->visina(); vrsta++) {
		for (int kolona = 0; kolona < this->sirina(); kolona++) {
			delete[] this->_matricaPiksela[vrsta][kolona];
		}
		delete[] this->_matricaPiksela[vrsta];
	}
	delete[] this->_matricaPiksela;
	this->_matricaPiksela = nullptr;
}

//Setters

//Podaci o slici se ucitavaju kao string u sledecem formatu:
// 1280\n720\n-\n125\n12\n123\n0\n255\n50\n...
//
//Ideja je da citamo znak po znak, tj poziciju po poziciju, dok ne procitamo znak '\n'
// (napomena: iako \n je vizuelno prestavljen sa dva karaktera on se cita kao jedan, tj odgovara jednoj poziciji.
//Kada procitamo \n to ce znaciti da je prethodno procitano ili znak '-' ili neki broj.
bool Slika::ucitajSliku(string podaciSlike) {
	//definisemo poziciju koja cuva vrednost pozicije u ulaznom string-u koja treba da se procita
	int pozicija = 0;

	//Obzirom da su sirina i visina slike data na pocetku ulaznog string-a, tj. pre znaka '-',
	// to cemo ova dva podatka procitati pre ciklusa u kojem cemo citati podatke o pikselima.
	this->postaviSirinu(this->procitajBroj(podaciSlike, pozicija));
	if (podaciSlike[pozicija] == '-') //Uslucaju da je ulazni string na primer: 128\n-\n.....
		this->postaviVisinu(this->sirina());
	else //Uslucaju da je ulazni string na primer: 1280\n720\n-\n...
		this->postaviVisinu(this->procitajBroj(podaciSlike, pozicija));

	cout << "\n\n" << "FORMAT SLIKE: " << this->format() << "\n\n" << endl;

	//Nakon izvrsenja pretohdnog if bloka pozicija pokazuje na znak '-', bez obzira da li se izvrsio if ili else uslov.
	//Stoga mozemo slobodno pomeriti poziciju za dva mesta unapred da preskocimo '\n' nakon znaka '-',
	// i tako postavimo poziciju na prvi znak/broj nakon simbola 'n'
	pozicija += 2;

	//Kada znamo dimenzije slike, sledece je definisanje matrice piksela slike
	this->kreirajMatricuSlike();

	//Sada mozemo da u ciklusu iscitavamo ostatak stringa tj. brojeve koje odgovaraju vrednostima boja piksela u RGB sistemu.
	int vrsta = 0;
	int kolona = 0;
	while (pozicija < podaciSlike.length()) {
		this->_matricaPiksela[vrsta][kolona] = this->postaviPiksel(podaciSlike, pozicija);
		kolona++;
		if (kolona == this->sirina()) {
			kolona = 0;
			vrsta++;
		}
		if (vrsta == this->visina()) break;
	}

	return true;
}

bool Slika::efekatCrnoBelaSlika() {
	bool result = true;
	for (int vrsta = 0; vrsta < this->visina(); vrsta++) {
		for (int kolona = 0; kolona < this->sirina(); kolona++) {
			result = result && this->_matricaPiksela[vrsta][kolona]->sivaBoja();
		}
	}
	return result;
}

bool Slika::efekatInverznaSlika() {
	bool result = true;
	for (int vrsta = 0; vrsta < this->visina(); vrsta++) {
		for (int kolona = 0; kolona < this->sirina(); kolona++) {
			result = result && this->_matricaPiksela[vrsta][kolona]->suprotnaBoja();
		}
	}
	return result;
}

//Getters
int Slika::sirina() {
	return this->_sirina;
}

int Slika::visina() {
	return this->_visina;
}

string Slika::format() {
	return to_string(this->sirina()) + "x" + to_string(this->visina());
}

string Slika::snimiSliku() {
	string podaciSlike;

	podaciSlike.append(to_string(this->sirina()));
	podaciSlike.append("\n");

	if (this->sirina() != this->visina()) {
		podaciSlike.append(to_string(this->visina()));
		podaciSlike.append("\n");
	}
	podaciSlike.append("-\n");

	for (int vrsta = 0; vrsta < this->visina(); vrsta++) {
		for (int kolona = 0; kolona < this->sirina(); kolona++) {
			podaciSlike.append(to_string(this->_matricaPiksela[vrsta][kolona]->red()));
			podaciSlike.append("\n");

			podaciSlike.append(to_string(this->_matricaPiksela[vrsta][kolona]->green()));
			podaciSlike.append("\n");

			podaciSlike.append(to_string(this->_matricaPiksela[vrsta][kolona]->blue()));
			podaciSlike.append("\n");
		}
	}
	return podaciSlike;
}
