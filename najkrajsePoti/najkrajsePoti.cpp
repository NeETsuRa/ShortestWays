// najkrajsePoti.cpp : Defines the entry point for the console application.
//

/* Karmen Unuk
OA_N0000819_sklop4_naloga2: Najkrajše poti */

/* Napišite program, ki poišèe dolžine najkrajših poti na dinamièen naèin. V programu
   omogoèite, da boste lahko graf prebrali tudi iz datoteke. */

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

class CGraf
{
public:
	CGraf(int N);
	~CGraf(void);
	void DodajPovezavo(int aI, int aJ, int aU);
	int OdstraniPovezavo(int aI, int aJ);
	bool JePovezava(int aI, int aJ);
	int VrniUtez(int aI, int aJ);
	vector<int> VrniSeznamSosedov(int aI);
	void IzpisMatrikeGrafa();
	void IzpisMatrike(int** aM);
	int Min(int aN, int aM);
	int Vsota(int aN, int aM);
	int** PrvotnaMatrika();
	int** MatrikaNajkrajsePoti();

private:
	int stVozlisc;
	int** graf;
};

CGraf::CGraf(int N)
{
	stVozlisc = N;
	graf = new int*[stVozlisc];
	for(int k = 0; k< stVozlisc; k++){
		graf[k]= new int [stVozlisc];
	}

	for (int i = 0; i <stVozlisc; i++){
		for(int j = 0; j< stVozlisc; j++){
			if(i == j){
				graf[i][j] = 0;
			}else{
			graf[i][j]= -1;
			}
		}
	}
}


CGraf::~CGraf(void)
{
}

void CGraf::DodajPovezavo(int aI, int aJ, int aU)
{
	graf[aI][aJ] = aU;
	//graf[aJ][aI] = aU;
}

int CGraf::OdstraniPovezavo(int aI, int aJ)
{
	int aU = graf[aI][aJ];
		graf[aI][aJ] = -1;
	//	graf[aJ][aI] = -1;
		return aU;
}

bool CGraf::JePovezava(int aI, int aJ)
{
	if(graf[aI][aJ] != -1)
		return true;
	else 
		return false;
}

int CGraf::VrniUtez(int aI, int aJ)
{
	if(graf[aI][aJ] != -1)
		return graf[aI][aJ];
	else
		return -1;
}

vector<int> CGraf:: VrniSeznamSosedov(int aI)
{
	vector<int> Sez;
	for(int i = 0; i< stVozlisc; i++){
		if(graf[aI][i] != -1){
			Sez.push_back(graf[aI][i]);
		}
	}
	return Sez;
}

void CGraf:: IzpisMatrikeGrafa()
{
	//cout << "(Utezena) matrika sosednosti: "<< endl;
	for(int i = 0; i< stVozlisc; i++){
		for(int j = 0; j< stVozlisc; j++){
			cout << graf[i][j] << "  ";
		}
		cout << endl;
	}
}

int CGraf:: Min(int aN, int aM)
{
	if(aN == -1){
		return aM;
	}else{
		if(aM == -1){
			return aN;
		}else{
			if(aN < aM){
				return aN;
			}else{
				return aM;
			}
		}
	}
}

int CGraf:: Vsota(int aN, int aM)
{
	if(aN == -1 || aM == -1){
		return -1;
	}else{
		return (aN + aM);
	}
}

/*int** CGraf:: PrvotnaMatrika()
{
	int** PMat;
	PMat = new int*[stVozlisc];
	for(int i = 0; i < stVozlisc; i++){
		PMat[i] = new int[stVozlisc];
	}
	for(int j = 0; j< stVozlisc; j++){
		for(int k = 0; k < stVozlisc; k++){
			PMat[j][k] = graf[j][k];
		}
	}
	return PMat;
}*/

int** CGraf:: MatrikaNajkrajsePoti()
{
	int** NajkrajsaP;
	NajkrajsaP = graf;
	cout << "Postopno preverjanje dodajanja: " <<endl;
	for(int k = 0; k < stVozlisc; k++){
		for(int i = 0; i < stVozlisc; i++){
			for(int j = 0; j < stVozlisc; j++){
				NajkrajsaP[i][j] = Min(NajkrajsaP[i][j], Vsota(NajkrajsaP[i][k], NajkrajsaP[k][j]));
			}
		}
		cout << "D"<< k+1 <<": "<<endl;
		IzpisMatrike(NajkrajsaP);
		cout << endl;
	}
	return NajkrajsaP;
}

void CGraf:: IzpisMatrike(int** aM)
{
	for(int i = 0; i< stVozlisc; i++){
		for(int j = 0; j< stVozlisc; j++){
			cout << aM[i][j] << "  ";
		}
		cout << endl;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "D0: "<<endl;
	CGraf * aG = new CGraf(4);
	aG->DodajPovezavo(0,1,10);
	aG->DodajPovezavo(0,2,31);
	aG->DodajPovezavo(0,3,5);
	aG->DodajPovezavo(1,0,6);
	aG->DodajPovezavo(1,3,11);
	aG->DodajPovezavo(2,1,9);
	aG->DodajPovezavo(2,3,22);
	aG->DodajPovezavo(3,0,20);
	aG->DodajPovezavo(3,1,14);
	aG->DodajPovezavo(3,2,18);
	aG->IzpisMatrikeGrafa();
	cout << endl;
	int** aNP;
	aNP = aG->MatrikaNajkrajsePoti();
	cout << "Matrika najkrajsih poti: "<< endl;
	aG->IzpisMatrike(aNP);
	cout << endl;

	cin.ignore();
	cin.get();
	return 0;
}



