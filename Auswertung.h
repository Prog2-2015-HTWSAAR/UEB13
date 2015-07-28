#ifndef AUSWERTUNG_H_
#define AUSWERTUNG_H_
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>    
#include <stdexcept>
#include "Ergebnis.h"
#include "Notenschnitt.h"

using namespace std;
class AuswertungsException : public logic_error {
public:
	AuswertungsException(const string& msg = "") : logic_error(msg) {}
};
class Auswertung
{
public:
	void runReadIn(string fileName);

	void calcNotendurchschnitt(Ergebnis **& e, Notenschnitt **& N, int anzahl, int & anzahlDurchschnitte);

	Auswertung();
	~Auswertung();
private: 
	static const char* error_std;
	static const int ZERO_VALUE;
	static const int HIGH_VALUE;
	static const int maxAnzahlErgebnisse = 500;
	static const int UPPER_BORDER_MATRIKEL_NR;
	static const int LOWER_BORDER_MATRIKEL_NR;
	void checkExistence(Ergebnis** e, int matrikel, string bezeichnung, double note, int anzahl);
	string toString(Ergebnis** e, int anzahl);
	string toStringDurchschnitt(Notenschnitt** n, int anzahl);
	void clearInput();
	void startReadProgress(fstream & file);
	int strToMatrikelnummer(stringstream & linestream);
	void sortByNote(Ergebnis ** &e, int anzahl);
	void sortByMatrikel(Notenschnitt ** &e, int anzahl);
	void sortByAlphabeticalFach(Ergebnis ** &e, int anzahl);
	void sortByAlphabeticalNote(Ergebnis ** &e, int anzahl);
	void resetSortFlag(Ergebnis ** e, int anzahl);
	void resetSortFlag(Notenschnitt ** n, int anzahl);
	double strToNote(stringstream & linestream);
	Ergebnis** ergebnisTab;
	Notenschnitt** notenschnittTab;
	int anzahlErgebnisse;
	int anzahlDurchschnitte;
	int lines;

};
#endif
