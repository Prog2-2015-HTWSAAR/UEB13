/*
 * Auswertung.h
 *
 *  Created on: 21.07.2015
 *      Author: sbastian
 */

#ifndef AUSWERTUNG_H_
#define AUSWERTUNG_H_

#include "Ergebnis.h"

#include <fstream>

class Auswertung {
public:
	Auswertung();
	void laden(string filename);
	void ausgebenFaecher();
	void ausgebenMatrikelNr();
	static const int maxAnzahlErgebnisse = 500;
private:
	Ergebnis** ergebnisTab;
	int anzahlErgebnisse;
};

#endif /* AUSWERTUNG_H_ */
