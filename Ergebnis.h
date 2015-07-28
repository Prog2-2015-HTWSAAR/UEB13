#ifndef ERGEBNIS_H_
#define ERGEBNIS_H_
#include <string>
using namespace std;

class Ergebnis {
public:
	Ergebnis();
	Ergebnis(int eMatrNummer, string eFachbezeich, double eNote);


	string getFachbezeichnung() const {
		return fachbezeichnung;
	}

	int getMatrikelnummer() const {
		return matrikelnummer;
	}

	double getNote() const {
		return note;
	}
	void setNote(double n) {
		note = n;
	}
	void setFachbezeichnung(string s) {
		fachbezeichnung = s;
	}
	void setMatrikelnummer(int m) {
		matrikelnummer = m;
	}
	void setSort() {
		sort = true;
	}
	void resetSort() {
		sort = false;
	}
	bool getSort(){
		return sort;
	}
	friend ostream& operator<< (ostream& o, const Ergebnis& ergebnis);
	string toString() const;
private:
	int matrikelnummer;
	string fachbezeichnung;
	double note;
	bool sort;
};
#endif