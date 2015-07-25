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
void Auswertung::runReadIn(string fileName){
		fstream file;
		const char* fName = fileName.c_str();
		file.open(fName);
		startReadProgress(file);
		file.close();
		cout << sortierteAusgabe();
}
void Auswertung::startReadProgress(fstream& file){
	string completeLine, matrikelNrString, fachbezeichnung, notenString;
	int matrikelNr;
	double note;
	stringstream linestream;
	while (getline(file, completeLine)){
		try{
			lines++;
			linestream.clear();
			linestream.str(completeLine);
			matrikelNr = strToMatrikelnummer(linestream);
			linestream >> fachbezeichnung;
			note = strToNote(linestream);
			Ergebnis* erg = new Ergebnis(matrikelNr, fachbezeichnung, note);
			ergebnisTab[anzahlErgebnisse] = erg;
			anzahlErgebnisse++;
		}
		catch (AuswertungsException& e){
			cout << error_std << e.what() << lines << endl;
		}
	}
}

void Auswertung::splitStringToThreeStrings(string& toBeSplitted, string& firstNewString, string& secondNewString, string& thirdNewString){
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
int Auswertung::strToMatrikelnummer(stringstream& linestream){
	int matrikelNr;
	linestream >> matrikelNr;
	//mtNummer = stoi(s);
	if (matrikelNr <= LOWER_BORDER_MATRIKEL_NR && matrikelNr >= UPPER_BORDER_MATRIKEL_NR){
		throw AuswertungsException("Matrikelnummer konnte nicht ermittelt werden");
	}
	return matrikelNr;
}
double Auswertung::strToNote(stringstream& linestream) {
	double note = 0.0;
	linestream >> note;
	if (note <= 0 && note > 6){
		throw AuswertungsException("Note konnte nicht ermittelt werden");
	}
	return note;
}
void Auswertung::ausgabe(){
	int runner = 0;
	while (runner < anzahlErgebnisse){
		cout << ergebnisTab[runner]->getMatrikelnummer() << "\t" << /*ergebnisTab[runner]->getFachbezeichnung << "\t" <<*/ ergebnisTab[runner]->getNote() << "\t" << endl;
		runner++;
	}
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
ostream& operator<<(ostream& o, const Auswertung& ausw){
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

void Auswertung::ausgebenFaecher(){
	Ergebnis** faecherErgebnisse = new Ergebnis*[anzahlErgebnisse];
	//TODO implement this method!
}

void Auswertung::ausgebenMatrikelNr(){
	//TODO implement this method!
}

void Auswertung::sortArrayFaecher(Ergebnis** ergebniss, int size){
	//TODO implement this method!
}
void Auswertung::sortArrayMatrikelNr(Ergebnis** ergebnisse, int size){
	//TODO implement this method!
}

double  Auswertung::berechneNotenschnitt(const Ergebnis** ergebnisse, int size, int start, int matrikelNr){
	int i = start;
	int counter = 0;
	double note = 0.0;
	//summiere Noten der Matrikelnummer und zaehle Anzahl
	while((i < size) && (ergebnisse[i]->getMatrikelnummer() == matrikelNr)){
		note += ergebnisse[i]->getNote();
		counter++;
	}
	//berechne Durchschnitt
	note /= counter;
	//Auf zwei stellen runden
	note = round(note * 100) / 100;
	return note;
}
string Auswertung::sortierteAusgabe(){
	ostringstream o;
	int innerRunner = 0;
	int outputRunner = 0;
	int absoluteMinimum = LOWER_BORDER_MATRIKEL_NR;
	int foundMinimum;
	int found = 0;
	o << "Matrikelnummer" << "\t" << "Fachbezeichnung" << "\t" << "\t" << "Note" << "\n";
	while (found != anzahlErgebnisse) {
		foundMinimum = UPPER_BORDER_MATRIKEL_NR;
		while(innerRunner < anzahlErgebnisse) {
			if (ergebnisTab[innerRunner]->getMatrikelnummer() > absoluteMinimum && ergebnisTab[innerRunner]->getMatrikelnummer() < foundMinimum) {
				foundMinimum = ergebnisTab[innerRunner]->getMatrikelnummer();
			}
			innerRunner++;
		}
		while (outputRunner < anzahlErgebnisse) {
			if (ergebnisTab[outputRunner]->getMatrikelnummer() == foundMinimum) {
				o << ergebnisTab[outputRunner]->toString();
				found++;
			}
			outputRunner++;
		}
		absoluteMinimum = foundMinimum;
		innerRunner = 0;
		outputRunner = 0;
	}
	return o.str();
}