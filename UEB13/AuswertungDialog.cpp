#include "AuswertungDialog.h"
const int AuswertungDialog::ZERO_VALUE = 0;
const int AuswertungDialog::HIGH_VALUE = 1000;
const char* AuswertungDialog::error_std = "Datei existiert nicht!!";

AuswertungDialog::AuswertungDialog(){}
AuswertungDialog::~AuswertungDialog(){}

void AuswertungDialog::startDialog(){
	while (!readFileName()) {}
}

bool AuswertungDialog::readFileName(){
	cout << "fileName: ";
	eingabe = readStringInput();
	if (fileExists(eingabe)){
		fileExist = true;
		auswert.runReadIn(eingabe);
	}
	else {
		fileExist = false;
		cout << error_std;
	}
	return fileExist;
}
string AuswertungDialog::readStringInput() {
	string input;
	cin >> input;
	clearInput();
	return input;
}
void AuswertungDialog::clearInput() {
	cin.clear();
	cin.ignore(HIGH_VALUE, '\n');
}
bool AuswertungDialog::fileExists(string fileName) {
	const char* constName = fileName.c_str();
	ifstream infile(constName);
	return infile.good();
}