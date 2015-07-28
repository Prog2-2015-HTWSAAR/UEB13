#include "Notenschnitt.h"
#include <sstream>
#include <iostream>
Notenschnitt::Notenschnitt() {
	this->matrikelnummer = 0;
	this->notenschnitt = 0.0;
	this->sort = 0;
}

Notenschnitt::Notenschnitt(int MatrNummer, double notenSchnitt) {
	matrikelnummer = MatrNummer;
	notenschnitt = notenSchnitt;
	sort = 0;
}

string Notenschnitt::toString() const {
	ostringstream o;
	int stdLeanght = 15;

	o << matrikelnummer << "\t" << "\t" << notenschnitt << endl;

	return o.str();
}
