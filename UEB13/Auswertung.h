/*
 * Auswertung.h
 *
 *  Created on: 21.07.2015
 *      Author: sbastian
 */

#ifndef AUSWERTUNG_H_
#define AUSWERTUNG_H_

#include "Ergebnis.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>    
#include <stdexcept>
class AuswertungsException : public logic_error {
public:
	AuswertungsException(const string& msg = "") : logic_error(msg) {}
};
class Auswertung {
public:
	Auswertung();
	void runReadIn(string fileName);
	friend ostream& operator<< (ostream& o, const Auswertung& ausw);

private:
	static const char* error_std;
	static const int ZERO_VALUE;
	static const int HIGH_VALUE;
	static const int maxAnzahlErgebnisse = 500;
	static const int UPPER_BORDER_MATRIKEL_NR;
	static const int LOWER_BORDER_MATRIKEL_NR;
	void checkExistence(int matrikel, string bezeichnung, double note);
	string toString() const;
	void sortArrayFaecher();
	void sortArrayNote(Ergebnis** &ergebnisse, int size);
	void sortArrayNote(Ergebnis** &ergebnisse, int size, int lowerBorder);
	void resetSorted();
	void sortArrayMatrikelNr(Ergebnis** &ergebnisse, int size);
	void sortArrayMatrikelNr(Ergebnis **& ergebnisse, int size, int lowerBorder);
	int berechneNotenschnitt(Ergebnis** &durchschnitt);
	void startReadProgress(fstream& file);
	void trim(string& str);
	void ausgabeNotendurchschnitt(Ergebnis** &durchschnitt, int anzahlSaetze);
	void splitStringToThreeStrings(string& toBeSplitted, string& firstNewString, string& secondNewString, string& thirdNewString);
	int strToMatrikelnummer(stringstream& linestream);
	double strToNote(stringstream& linestream);
	string readStringInput();
	void clearInput();
	bool fileExists(string fileName);
	Ergebnis** ergebnisTab;
	int anzahlErgebnisse;

	int lines;
};

#endif /* AUSWERTUNG_H_ */
