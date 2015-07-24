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

class FileReadFailtureException : public logic_error {
public:
	FileReadFailtureException(const string& msg = "") : logic_error(msg) {}
};
class Auswertung {
public:
	static const char* error_std;
	static const int ZERO_VALUE;
	static const int HIGH_VALUE;
	Auswertung();
	void laden(string filename);
	void initAuswertung();
	void ausgebenFaecher();
	void ausgebenMatrikelNr();
	static const int maxAnzahlErgebnisse = 500;
	string toString() const;
	friend ostream& operator<< (ostream& o, const Auswertung& ausw);

private:
	void ausgabe();
	void startReadProgress();
	void trim(string& str);
	void splitStringToThreeStrings(string& toBeSplitted, string& firstNewString, string& secondNewString, string& thirdNewString);
	bool runReadIn();
	int strToMatrikelnummer(string s);
	double strToNote(string s);
	string readStringInput();
	void clearInput();
	bool fileExists(string fileName);
	Ergebnis** ergebnisTab;
	int anzahlErgebnisse;
	int lines;
	string fileName;
	fstream file;
};

#endif /* AUSWERTUNG_H_ */
