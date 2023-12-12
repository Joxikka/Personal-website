#include "Piksel.h"

//Constructors
Piksel::Piksel() {
	this->postaviRed(DEFAULT_RED);
	this->postaviGreen(DEFAULT_GREEN);
	this->postaviBlue(DEFAULT_BLUE);
};

Piksel::Piksel(unsigned char red, unsigned char green, unsigned char blue) {
	this->postaviRed(red);
	this->postaviGreen(green);
	this->postaviBlue(blue);
};


Piksel::Piksel(unsigned char RGB[3]) {
	this->postaviRed(RGB[0]);
	this->postaviGreen(RGB[1]);
	this->postaviBlue(RGB[2]);
};


//Getters
unsigned char Piksel::red() {
	return this->_red;
};

unsigned char Piksel::green() {
	return this->_green;
};

unsigned char Piksel::blue() {
	return this->_blue;
};


unsigned char* Piksel::RGB() {
	unsigned char rgb[3] = { this->red(), this->green(), this->blue() };
	return rgb;
};


//Setters
void Piksel::postaviRed(unsigned char red) {
	this->_red = red;
};

void Piksel::postaviGreen(unsigned char green) {
	this->_green = green;
};

void Piksel::postaviBlue(unsigned char blue) {
	this->_blue = blue;
};


//Methods
// Result {true, false} - True ukoliko je f-ja uspesno izvrsena. U suprotnom false
bool Piksel::sivaBoja() {
	//Postoji vise algoritama po kojima se boja konvertuje u nijansu sive (https://www.tutorialspoint.com/dip/grayscale_to_rgb_conversion.htm).
	//Koristicemo "Weighted" metod, po kojem svim RGB parametrima dodeljujemo vrednost po formuli: (0.3 * R) + (0.59 * G) + (0.11 * B)

	unsigned char gray = (0.3*this->red() + 0.59*this->green() + 0.11*this->blue());

	this->postaviRed(gray);
	this->postaviGreen(gray);
	this->postaviBlue(gray);

	return true;
};

// Result {true, false} - True ukoliko je f-ja uspesno izvrsena. U suprotnom false
bool Piksel::suprotnaBoja() {

	this->postaviRed(~this->red());
	this->postaviGreen(~this->green());
	this->postaviBlue(~this->blue());

	return true;
};

