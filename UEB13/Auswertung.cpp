/*
 * Auswertung.cpp
 *
 *  Created on: 21.07.2015
 *      Author: sbastian
 */
#include "Auswertung.h"
#include <math.h>
const int Auswertung::ZERO_VALUE = 0;
const int Auswertung::HIGH_VALUE = 1000;
const int Auswertung::UPPER_BORDER_MATRIKEL_NR = 9999999;
const int Auswertung::LOWER_BORDER_MATRIKEL_NR = 99999;

const char* Auswertung::error_std = "_ERROR_";

Auswertung::Auswertung() {
	anzahlErgebnisse = 0;
	lines = 0;
	ergebnisTab = new Ergebnis*[maxAnzahlErgebnisse];
}
void Auswertung::runReadIn(string fileName) {
	fstream file;
	Ergebnis** duchschnittNote;
	int anzahlVerschiedenerSaetze;
	const char* fName = fileName.c_str();
	file.open(fName);
	startReadProgress(file);
	file.close();
	duchschnittNote = new Ergebnis*[anzahlErgebnisse];
	sortArrayNote(ergebnisTab, anzahlErgebnisse);
	cout << toString();

	sortArrayFaecher();
	//anzahlVerschiedenerSaetze = berechneNotenschnitt(duchschnittNote);
	cout << toString();
//	ausgabeNotendurchschnitt(duchschnittNote, anzahlVerschiedenerSaetze);
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
			checkExistence(matrikelNr, fachbezeichnung, note);
			Ergebnis* erg = new Ergebnis(matrikelNr, fachbezeichnung, note);
			ergebnisTab[anzahlErgebnisse] = erg;
			anzahlErgebnisse++;
		}
		catch (AuswertungsException& e) {
			cout << error_std << e.what() << lines << endl;
		}
	}
}

void Auswertung::ausgabeNotendurchschnitt(Ergebnis** &durchschnitt, int anzahlSaetze) {
	cout << "Ausgabe Durchschnittsnote: " << endl << "Matrikelnummer" << "\t\t" << "Durchschnittsnote" << endl;
	sortArrayMatrikelNr(durchschnitt, anzahlSaetze);
	for (int i = 0; i < anzahlSaetze; i++){
		cout << durchschnitt[i]->getMatrikelnummer() << "\t\t" << durchschnitt[i]->getNote() << endl;
	}
}
void Auswertung::splitStringToThreeStrings(string& toBeSplitted, string& firstNewString, string& secondNewString, string& thirdNewString) {
	stringstream stream;
	stream.str(toBeSplitted);
	stream >> firstNewString;
	stream >> secondNewString;
	stream >> thirdNewString;
}
bool Auswertung::fileExists(string fileName) {
	const char* constName = fileName.c_str();
	ifstream infile(constName);
	return infile.good();
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
double Auswertung::strToNote(stringstream& linestream) {
	double note = -1.0;
	linestream >> note;
	if (note <= 0 || note > 6) {
		throw AuswertungsException("Note konnte nicht ermittelt werden");
	}
	return note;
}

string Auswertung::readStringInput() {
	string input;
	cin >> input;
	clearInput();
	return input;
}
void Auswertung::clearInput() {
	cin.clear();
	cin.ignore(HIGH_VALUE, '\n');
}
void Auswertung::trim(string& str) {
	string trim_chars = " \t";
	string::size_type pos = str.find_last_not_of(trim_chars);
	if (pos != std::string::npos) {
		str.erase(pos + 1);
		pos = str.find_first_not_of(trim_chars);
		if (pos != std::string::npos)
			str.erase(0, pos);
	}
	else
		str.erase(str.begin(), str.end());

}
ostream& operator<<(ostream& o, const Auswertung& ausw) {
	for (int i = 0; i < ausw.anzahlErgebnisse; i++) {
		o << *ausw.ergebnisTab[i] << endl;
	}
	return o << ausw.toString();
}
string Auswertung::toString() const {
	ostringstream o;
	o << "Matrikelnummer" << "\t" << "Fachbezeichnung" << "\t" << "\t" << "Note" << "\n";

	for (int i = 0; i < anzahlErgebnisse; i++) {
		o << ergebnisTab[i]->toString();
	}
	o << endl;
	return o.str();
}

void Auswertung::sortArrayNote(Ergebnis** &ergebnisse, int size) {
	int lowerBorder = 0;
	sortArrayNote(ergebnisse, size, lowerBorder);
}
void Auswertung::sortArrayNote(Ergebnis** &ergebnisse, int size, int lowerBorder) {
	Ergebnis* tempErgebnis;
	for (int i = lowerBorder; i < size; i++) {
		for (int j = lowerBorder; j < size; j++) {
			if (ergebnisse[i]->getNote() < ergebnisse[j]->getNote()) {
				tempErgebnis = ergebnisse[i];
				ergebnisse[i] = ergebnisse[j];
				ergebnisse[j] = tempErgebnis;
			}
		}
	}
}
void Auswertung::resetSorted() {
	for (int i = 0; i < anzahlErgebnisse; i++){
		ergebnisTab[i]->resetSorted();
	}
}
void Auswertung::sortArrayFaecher() {
	Ergebnis** tempErgebnis = new Ergebnis*[anzahlErgebnisse];
	int found = 0;
	for (int i = 0; i < anzahlErgebnisse; i++) {
		for (int j = 0; j < anzahlErgebnisse; j++) {
			if (ergebnisTab[i]->compareFaecher(*ergebnisTab[j]) < 0) {
				tempErgebnis[i] = ergebnisTab[j];
				//ergebnisTab[j]->setSorted();
				found++;
			}
		}
		
	}
	resetSorted();
	ergebnisTab = tempErgebnis;
	/*Ergebnis** tempErgebnis = new Ergebnis*[anzahlErgebnisse+1];
	int found = 0;
	for (int i = 0; i < anzahlErgebnisse; i++) {
		if (ergebnisTab[i]->getMatrikelnummer() > 0) {
			tempErgebnis[found] = ergebnisTab[i];
			found++;
		}
		for (int j = i+1; j < anzahlErgebnisse; j++) {
			if (ergebnisTab[i]->getFachbezeichnung().compare(ergebnisTab[j]->getFachbezeichnung()) == 0)  {
				if (ergebnisTab[j]->getSorted() == 0 && found < anzahlErgebnisse) {
					tempErgebnis[found] = ergebnisTab[j];
					ergebnisTab[j]->setSorted();
					found++;
				}
			}
		}
	}
	resetSorted();
	ergebnisTab = tempErgebnis;	*/
}

void Auswertung::sortArrayMatrikelNr(Ergebnis** &ergebnisse, int size) {
	int lowerB = 0;
	sortArrayMatrikelNr(ergebnisse, size, lowerB);
}
void Auswertung::sortArrayMatrikelNr(Ergebnis** &ergebnisse, int size, int lowerBorder) {
	Ergebnis* tempErgebnis;
	for (int i = lowerBorder; i < size; i++) {
		for (int j = lowerBorder; j < size; j++) {
			if (ergebnisse[i]->getMatrikelnummer() < ergebnisse[j]->getMatrikelnummer()) {
				tempErgebnis = ergebnisse[i];
				ergebnisse[i] = ergebnisse[j];
				ergebnisse[j] = tempErgebnis;
			}
		}
	}
}

int Auswertung::berechneNotenschnitt(Ergebnis** &durchschnitt) {
	double note;
	int anz = 0;
	int haeufMatrikel = 0;
	for (int i = 0; i < anzahlErgebnisse; i++) {
		if (ergebnisTab[i]->getSorted() == 0) {
			haeufMatrikel = 0;
			note = ergebnisTab[i]->getNote();
			ergebnisTab[i]->setSorted();
			for (int j = i + 1; j < anzahlErgebnisse; j++) {
				if (ergebnisTab[i]->getMatrikelnummer() == ergebnisTab[j]->getMatrikelnummer() && ergebnisTab[j]->getSorted() == 0) {
					note += ergebnisTab[j]->getNote();
					ergebnisTab[j]->setSorted();
					haeufMatrikel++;
				}
			}
			note /= haeufMatrikel;
			Ergebnis*matDurchschnitt = new Ergebnis(ergebnisTab[i]->getMatrikelnummer(), note);
			durchschnitt[anz] = matDurchschnitt;
			anz++;
		}
	}
	resetSorted();
	return anz;
}

void Auswertung::checkExistence(int matrikel, string bezeichnung, double note) {
	int runner = 0;
	while (runner < anzahlErgebnisse) {
		if (matrikel == ergebnisTab[runner]->getMatrikelnummer()) {
			if (bezeichnung.compare(ergebnisTab[runner]->getFachbezeichnung()) == 0) {
				throw AuswertungsException("Objekt existiert schon Line: ");

			}
		}
		runner++;
	}
}