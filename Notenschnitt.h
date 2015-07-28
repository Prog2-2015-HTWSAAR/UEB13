#ifndef NOTENSCHNITT_H_
#define NOTENSCHNITT_H_
#include <string>
using namespace std;

class Notenschnitt {
public:
	Notenschnitt();
	Notenschnitt(int matrNummer, double notenSchnitt);

	int getMatrikelnummer() const {
		return matrikelnummer;
	}

	double getNotenschnitt() const {
		return notenschnitt;
	}
	void setNotenschnitt(double n) {
		notenschnitt = n;
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
	bool getSort() {
		return sort;
	}
	string toString() const;
private:
	int matrikelnummer;
	double notenschnitt;
	int sort;
};
#endif