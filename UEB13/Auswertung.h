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
class FileReadFailtureException : public logic_error {
public:
	FileReadFailtureException(const string& msg = "") : logic_error(msg) {}
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
	string toString() const;
	void ausgebenFaecher();
	void ausgebenMatrikelNr();
	void ausgabe();
	void startReadProgress();
	void trim(string& str);
	void splitStringToThreeStrings(string& toBeSplitted, string& firstNewString, string& secondNewString, string& thirdNewString);
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
	stringstream linestream;
};

#endif /* AUSWERTUNG_H_ */
