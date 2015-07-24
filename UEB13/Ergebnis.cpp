/*
 * Ergenis.cpp
 *
 *  Created on: 21.07.2015
 *      Author: sbastian
 */

#include "Ergebnis.h"
#include <sstream>

Ergebnis::Ergebnis() {
	this->matrikelnummer = 0;
	this->fachbezeichnung = "";
	this->note = 0.0;
}

ostream& operator<<(ostream& o, const Ergebnis& ergebnis){
	return o << ergebnis.toString();
}
string Ergebnis::toString() const {
	ostringstream o;
	o << matrikelnummer << " | " << fachbezeichnung << " | " << note << endl;
	return o.str();
}