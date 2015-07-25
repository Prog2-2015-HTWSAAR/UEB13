/*
 * Ergenis.cpp
 *
 *  Created on: 21.07.2015
 *      Author: sbastian
 */

#include "Ergebnis.h"
#include <sstream>
#include <iostream>
Ergebnis::Ergebnis() {
	this->matrikelnummer = 0;
	this->fachbezeichnung = "";
	this->note = 0.0;
}

Ergebnis::Ergebnis(int eMatrNummer, string eFachbezeich, double eNote) {
	matrikelnummer = eMatrNummer;
	fachbezeichnung = eFachbezeich;
	note = eNote;
}
ostream& operator<<(ostream& o, const Ergebnis& ergebnis){
	return o << ergebnis.toString();
}
string Ergebnis::toString() const {
	ostringstream o;
	int stdLeanght = 15;
	int leanght = fachbezeichnung.length();
	o << matrikelnummer << "\t" << "\t" << fachbezeichnung;
	while (stdLeanght - leanght > 0 && leanght < 15){
		o << " ";
		stdLeanght--;
	}

	o << "\t" << "\t" << note << endl;
	
	return o.str();
}

int Ergebnis::compareFaecher(const Ergebnis& ergebnis){
	int vergleich = 0;
	vergleich = this->fachbezeichnung.compare(ergebnis.fachbezeichnung);
	if(vergleich != 0){
		return vergleich;
	}else{
		vergleich = compareDoubles(note, ergebnis.note);
		if(vergleich != 0){
			return vergleich;
		}else{
			return compareMatrikelNr(ergebnis);
		}
	}
}

int Ergebnis::compareMatrikelNr(const Ergebnis& ergebnis){
	return compareDoubles((double) matrikelnummer, (double) ergebnis.matrikelnummer);
}

int Ergebnis::compareDoubles(double a, double b){
	if(a > b){
		return 1;
	}
	if(a < b){
		return -1;
	}
	return 0;
}
