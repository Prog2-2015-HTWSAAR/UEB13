/*
 * Ergenis.h
 *
 *  Created on: 21.07.2015
 *      Author: sbastian
 */

#ifndef ERGEBNIS_H_
#define ERGEBNIS_H_
#include <string>
using namespace std;

class Ergebnis {
public:
	Ergebnis();
	Ergebnis(int eMatrNummer, string eFachbezeich, double eNote);
	Ergebnis(int eMatrNummer, double eNote);


	string getFachbezeichnung() const {
		return fachbezeichnung;
	}

	int getMatrikelnummer() const {
		return matrikelnummer;
	}

	double getNote() const {
		return note;
	}
	void setNote(double n){
		note = n;
	}
	void setFachbezeichnung(string s){
		fachbezeichnung = s;
	}
	void setMatrikelnummer(int m){
		matrikelnummer = m;
	}
	void resetSorted() {
		sorted = 0;
	}
	void setSorted() {
		sorted = 1;
	}
	int getSorted() {
		return sorted;
	}
	friend ostream& operator<< (ostream& o, const Ergebnis& ergebnis);
	string toString() const;
	int compareFaecher(const Ergebnis& ergebnis);
	int compareMatrikelNr(const Ergebnis& ergebnis);
private:
	int compareDoubles(double a, double b);
	int matrikelnummer;
	string fachbezeichnung;
	double note;
	int sorted;
};

#endif /* ERGEBNIS_H_ */
