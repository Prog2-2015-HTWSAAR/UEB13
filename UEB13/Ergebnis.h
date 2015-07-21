/*
 * Ergenis.h
 *
 *  Created on: 21.07.2015
 *      Author: sbastian
 */

#ifndef ERGEBNIS_H_
#define ERGEBNIS_H_

using namespace std;

class Ergebnis {
public:
	Ergebnis();

	const string& getFachbezeichnung() const {
		return fachbezeichnung;
	}

	int getMatrikelnummer() const {
		return matrikelnummer;
	}

	double getNote() const {
		return note;
	}

private:
	int matrikelnummer;
	string fachbezeichnung;
	double note;
};

#endif /* ERGEBNIS_H_ */
