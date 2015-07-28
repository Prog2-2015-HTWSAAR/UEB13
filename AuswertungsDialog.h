#pragma once
#ifndef AuswertungsDialog_H_
#define AuswertungsDialog_H_

#include <iostream>
#include <string>
#include <sstream>    
#include <fstream>
#include "Auswertung.h"

using namespace std;

class AuswertungsDialog
{
public:
	void startDialog();
	AuswertungsDialog();
	~AuswertungsDialog();


private:
	bool readFileName();
	static const char* error_std;
	static const int ZERO_VALUE;
	static const int HIGH_VALUE;
	bool fileExists(string fileName);
	string readStringInput();
	void clearInput();
	string eingabe;
	bool fileExist;
	Auswertung auswert;
};
#endif
