//#pragma once

#ifndef Piksel_H
#define Piksel_H

#define DEFAULT_RED 0
#define DEFAULT_GREEN 0
#define DEFAULT_BLUE 0

class Piksel
{
private:
	//Attributes
	unsigned char _red;
	unsigned char _green;
	unsigned char _blue;

public:
	//Constructors
	Piksel();

	Piksel(unsigned char red, unsigned char green, unsigned char blue);

	Piksel(unsigned char RGB[3]);

	//Getters
	unsigned char red();
	unsigned char green();
	unsigned char blue();

	unsigned char* RGB();

	//Setters
	void postaviRed(unsigned char red);
	void postaviGreen(unsigned char green);
	void postaviBlue(unsigned char blue);

	//Methods (metode/f-je koje su u svojoj biti Setter-i jer je rezultat njihovog izvrsenja i azuriranje atributa objekta klase
	bool sivaBoja(); //F-ja moze da bude i void tipa, ali ako bih hteo da pisem npr. testove onda bi pozeljnije bilo da f-ja ima izlaz 
	bool suprotnaBoja();

};

#endif // !Piksel_H

