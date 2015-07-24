/*
 * Auswertung.cpp
 *
 *  Created on: 21.07.2015
 *      Author: sbastian
 */
#include "Auswertung.h"
const int Auswertung::ZERO_VALUE = 0;
const int Auswertung::HIGH_VALUE = 1000;
const char* Auswertung::error_std = "_ERROR_";

Auswertung::Auswertung() {
	anzahlErgebnisse = 0;
	lines = 0;
	ergebnisTab = new Ergebnis*[maxAnzahlErgebnisse];
}
void Auswertung::initAuswertung(){
	do{} while (!runReadIn());
}
bool Auswertung::runReadIn(){
	bool dateiExist = false;
	cout << "Bitte Dateiname Eingeben: ";
	fileName = readStringInput();
	if (fileExists(fileName)){
		dateiExist = true;
		const char* fName = fileName.c_str();
		file.open(fName);
		startReadProgress();
		file.close();
		cout << toString();
	}
	else{
		cout << "FEHLERHAFTER DATEINAME" << endl;
		dateiExist = false;
	}
	return dateiExist;
}
void Auswertung::startReadProgress(){

	string completeLine, matrikelNrString, fachbezeichnung, notenString;
	int matrikelNr;
	double note;
	while (getline(file, completeLine)){
		try{
			lines++;
//			trim(completeLine);
//			splitStringToThreeStrings(completeLine, matrikelNrString, fachbezeichnung, notenString);
//			matrikelNr = strToMatrikelnummer(matrikelNrString);
//			note = strToNote(notenString);
			stringstream linestream;
			linestream.str(completeLine);
			linestream >> matrikelNr;
			linestream >> fachbezeichnung;
			linestream >> note;
			Ergebnis* erg = new Ergebnis(matrikelNr, fachbezeichnung, note);
			ergebnisTab[anzahlErgebnisse] = erg;
//			cout << completeLine << endl;
//			cout << matrikelNr << endl;
//			cout << fachbezeichnung << endl;
//			cout << note << endl;
			anzahlErgebnisse++;
		}
		catch (FileReadFailtureException& e){
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
int Auswertung::strToMatrikelnummer(string s){
	int mtNummer = 0;
	//mtNummer = stoi(s);
	if (mtNummer <= 0 && mtNummer >= 99999999999999){
		throw FileReadFailtureException("Matrikelnummer konnte nicht ermittelt werden");
	}
	return mtNummer;
}
double Auswertung::strToNote(string s){
	double note = 0.0;
	//note = stod(s);
	if (note <= 0 && note > 6){
		throw FileReadFailtureException("Note konnte nicht ermittelt werden");
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
