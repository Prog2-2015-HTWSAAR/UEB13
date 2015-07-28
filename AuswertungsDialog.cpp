#include "AuswertungsDialog.h"
const int AuswertungsDialog::ZERO_VALUE = 0;
const int AuswertungsDialog::HIGH_VALUE = 1000;
const char* AuswertungsDialog::error_std = "Datei existiert nicht!!";

AuswertungsDialog::AuswertungsDialog() {}
AuswertungsDialog::~AuswertungsDialog() {}

void AuswertungsDialog::startDialog() {
	while (!readFileName()) {}
}

bool AuswertungsDialog::readFileName() {
	cout << "fileName: ";
	eingabe = readStringInput();
	if (fileExists(eingabe)) {
		fileExist = true;
		auswert.runReadIn(eingabe);
	}
	else {
		fileExist = false;
		cout << error_std;
	}
	return fileExist;
}
string AuswertungsDialog::readStringInput() {
	string input;
	cin >> input;
	clearInput();
	return input;
}
void AuswertungsDialog::clearInput() {
	cin.clear();
	cin.ignore(HIGH_VALUE, '\n');
}
bool AuswertungsDialog::fileExists(string fileName) {
	const char* constName = fileName.c_str();
	ifstream infile(constName);
	return infile.good();
}