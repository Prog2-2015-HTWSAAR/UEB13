#include "Auswertung.h"
#include <math.h>

const int Auswertung::ZERO_VALUE = 0;
const int Auswertung::HIGH_VALUE = 1000;
const int Auswertung::UPPER_BORDER_MATRIKEL_NR = 9999999;
const int Auswertung::LOWER_BORDER_MATRIKEL_NR = 99999;

const char* Auswertung::error_std = "_ERROR_";


Auswertung::Auswertung() {
	anzahlErgebnisse = 0;
	anzahlDurchschnitte = 0;
	lines = 0;
	ergebnisTab = new Ergebnis*[maxAnzahlErgebnisse];
	notenschnittTab = new Notenschnitt*[maxAnzahlErgebnisse];
}

Auswertung::~Auswertung() {}

void Auswertung::checkExistence(Ergebnis** e, int matrikel, string bezeichnung, double note, int anzahl) {
	for (int i = 0; i < anzahl; i++) {
		if (matrikel == e[i]->getMatrikelnummer()) {
			if (bezeichnung.compare(e[i]->getFachbezeichnung()) == 0) {
				throw AuswertungsException("Objekt existiert schon Line: ");
			}
		}
	}
}

void Auswertung::clearInput() {
	cin.clear();
	cin.ignore(HIGH_VALUE, '\n');
}
void Auswertung::runReadIn(string fileName) {
	fstream file;
	const char* fName = fileName.c_str();
	file.open(fName);
	startReadProgress(file);
	file.close();
	sortByAlphabeticalFach(ergebnisTab, anzahlErgebnisse);
	sortByAlphabeticalNote(ergebnisTab, anzahlErgebnisse);
	cout << toString(ergebnisTab, anzahlErgebnisse);
	calcNotendurchschnitt(ergebnisTab, notenschnittTab, anzahlErgebnisse, anzahlDurchschnitte);
	sortByMatrikel(notenschnittTab, anzahlDurchschnitte);
	cout << toStringDurchschnitt(notenschnittTab, anzahlDurchschnitte);

}
void Auswertung::calcNotendurchschnitt(Ergebnis** &e, Notenschnitt** &n, int anz, int &anzDurchschnitte) {
	resetSortFlag(e, anz);
	int found;
	double notenDurch = 0.0;
	for (int i = 0; i < anz; i++) {
		if (!e[i]->getSort()) {
			found = 1;
			notenDurch = e[i]->getNote();
			e[i]->setSort();
			for (int j = 0; j < anz; j++) {
				if (e[i]->getMatrikelnummer() == e[j]->getMatrikelnummer() && !e[j]->getSort()) {
					notenDurch += e[j]->getNote();
					e[j]->setSort();
					found++;
				}

			}
			notenDurch /= found;
			Notenschnitt* nTmp = new Notenschnitt(e[i]->getMatrikelnummer(), notenDurch);
			n[anzDurchschnitte] = nTmp;
			anzDurchschnitte++;
		}
	}
}
void Auswertung::startReadProgress(fstream& file) {
	string completeLine, matrikelNrString, fachbezeichnung, notenString;
	int matrikelNr;
	double note;
	stringstream linestream;
	while (getline(file, completeLine)) {
		try {
			lines++;
			linestream.clear();
			linestream.str(completeLine);
			matrikelNr = strToMatrikelnummer(linestream);
			linestream >> fachbezeichnung;
			note = strToNote(linestream);
			checkExistence(ergebnisTab, matrikelNr, fachbezeichnung, note, anzahlErgebnisse);
			Ergebnis* erg = new Ergebnis(matrikelNr, fachbezeichnung, note);
			ergebnisTab[anzahlErgebnisse] = erg;
			anzahlErgebnisse++;
		}
		catch (AuswertungsException& e) {
			cout << error_std << e.what() << lines << endl;
		}
	}
}
int Auswertung::strToMatrikelnummer(stringstream& linestream) {
	int matrikelNr = -1;
	linestream >> matrikelNr;
	//mtNummer = stoi(s);
	if (matrikelNr <= LOWER_BORDER_MATRIKEL_NR || matrikelNr >= UPPER_BORDER_MATRIKEL_NR) {
		throw AuswertungsException("Matrikelnummer konnte nicht ermittelt werden Line: ");
	}
	return matrikelNr;
}
void Auswertung::sortByNote(Ergebnis** &e, int anzahl) {
	resetSortFlag(e, anzahl);

	Ergebnis** eTmp;
	eTmp = new Ergebnis*[anzahl];
	double minimum;
	int minimumPosition;
	int found = 0;
	for (int i = 0; i < anzahl; i++) {
		for (int a = 0; a < anzahl;) {
			if (!e[a]->getSort() && found < anzahl) {
				minimum = e[a]->getNote();
				minimumPosition = a;
				for (int j = 0; j < anzahl; j++) {
					if (minimum > e[j]->getNote() && !e[j]->getSort()) {
						minimum = e[j]->getNote();
						minimumPosition = j;
					}
				}
				e[minimumPosition]->setSort();
				eTmp[found] = e[minimumPosition];
				found++;
			}
			else {
				a++;
			}
		
		}
	}
	e = eTmp;
}

void Auswertung::sortByMatrikel(Notenschnitt** &n, int anzahl) {
	resetSortFlag(n, anzahl);

	Notenschnitt** nTmp;
	nTmp = new Notenschnitt*[anzahl];
	int minimum;
	int minimumPosition;
	int found = 0;
	for (int i = 0; i < anzahl; i++) {
		for (int a = 0; a < anzahl;) {
			if (!n[a]->getSort() && found < anzahl) {
				minimum = n[a]->getMatrikelnummer();
				minimumPosition = a;
				for (int j = 0; j < anzahl; j++) {
					if (minimum > n[j]->getMatrikelnummer() && !n[j]->getSort()) {
						minimum = n[j]->getMatrikelnummer();
						minimumPosition = j;
					}
				}
				n[minimumPosition]->setSort();
				nTmp[found] = n[minimumPosition];
				found++;
			}
			else {
				a++;
			}

		}
	}
	n = nTmp;
}
void Auswertung::sortByAlphabeticalFach(Ergebnis** &e, int anzahl) {
	resetSortFlag(e, anzahl);

	Ergebnis** eTmp;
	eTmp = new Ergebnis*[anzahl];
	string minimum;
	int minimumPosition;
	int found = 0;
	double minVal = 0.0;
	for (int i = 0; i < anzahl; i++) {
		for (int a = 0; a < anzahl;) {
			if (!e[a]->getSort() && found < anzahl) {
				minimum = e[i]->getFachbezeichnung();
				minimumPosition = a;
				minVal = e[a]->getNote();
				for (int j = 0; j < anzahl; j++) {
					if (minimum.compare(e[j]->getFachbezeichnung()) >= 0 && !e[j]->getSort()) {
							minimum = e[j]->getFachbezeichnung();
							minimumPosition = j;
					}
				}
				e[minimumPosition]->setSort();
				eTmp[found] = e[minimumPosition];
				found++;
			}
			else {
				a++;
			}

		}
	}
	e = eTmp;
}
void Auswertung::sortByAlphabeticalNote(Ergebnis** &e, int anzahl) {
	resetSortFlag(e, anzahl);

	Ergebnis* eTmp;
	eTmp = new Ergebnis;
	double minimum;
	string s;
	int minimumPosition;
	int found = 0;
	for (int i = 0; i < anzahl; i++) {
		for (int j = 0; j < anzahl; j++){
			if (e[i]->getFachbezeichnung().compare(e[j]->getFachbezeichnung()) == 0) {
				if (e[i]->getNote()< e[j]->getNote()) {
					eTmp = e[j];
					e[j] = e[i];
					e[i] = eTmp;
				}
			}
		}
	}
}
void Auswertung::resetSortFlag(Ergebnis** e, int anzahl) {
	for (int i = 0; i < anzahl; i++) {
		e[i]->resetSort();
	}
}
void Auswertung::resetSortFlag(Notenschnitt** n, int anzahl) {
	for (int i = 0; i < anzahl; i++) {
		n[i]->resetSort();
	}
}
double Auswertung::strToNote(stringstream& linestream) {
	double note = -1.0;
	linestream >> note;
	if (note <= 0 || note > 6) {
		throw AuswertungsException("Note konnte nicht ermittelt werden");
	}
	return note;
}
string Auswertung::toString(Ergebnis** e, int anzahl) {
	ostringstream o;
	o << "Matrikelnummer" << "\t" << "Fachbezeichnung" << "\t" << "\t" << "Note" << "\n";

	for (int i = 0; i < anzahl; i++) {
		o << e[i]->toString();
	}
	o << endl;
	return o.str();
}

string Auswertung::toStringDurchschnitt(Notenschnitt** n, int anzahl) {
	ostringstream o;
	o << "Matrikelnummer" << "\t" << "Note" << "\n";

	for (int i = 0; i < anzahl; i++) {
		o << n[i]->toString();
	}
	o << endl;
	return o.str();
}