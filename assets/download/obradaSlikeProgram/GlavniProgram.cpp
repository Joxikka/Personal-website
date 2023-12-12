
#include <iostream>
#include <fstream>
#include <sstream>

#include "Slika.h"

#include <string>
#include <windows.h>

using namespace std;

string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
}

int main() {

	cout << "\n" << getexepath() << "\n" << endl;

	Slika* testSlika = new Slika();

	ifstream input;
	input.open("C:\\Users\\mrtig\\source\\repos\\Vezbe-Obrada_Slika\\Debug\\Test_Input.txt"); //Azurirati putanju do fajla u slucaju promene okruzenja!

	stringstream inputString;
	inputString << input.rdbuf();

	string podaciSlike = inputString.str();
	input.close();

	testSlika->ucitajSliku(podaciSlike);
	cout << "\nFORMAT SLIKE: " << testSlika->format() << "\n" << endl;

	testSlika->efekatCrnoBelaSlika();
	podaciSlike = testSlika->snimiSliku();

	ofstream output;
	output.open("C:\\Users\\mrtig\\source\\repos\\Vezbe-Obrada_Slika\\Debug\\Test_Output.txt"); //Azurirati putanju snimanja fajla u slucaju promene okruzenja!
	output << podaciSlike;
	output.close();

	Slika inicijalizacijaPrazanKonstruktor = Slika();

	Slika dodelaPrazanKonstruktor;
	dodelaPrazanKonstruktor = inicijalizacijaPrazanKonstruktor;


	Slika inicijalizacijaKopijaKonstruktora = *testSlika;

	delete testSlika;

	return 0;
}