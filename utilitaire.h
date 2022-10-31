#ifndef UTILITAIRE_H_INCLUDED
#define UTILITAIRE_H_INCLUDED

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>

void gotoligcol( int lig, int col );
void color(int couleurDuTexte,int couleurDeFond);
std::string convertTemps(float _temps);
void curseurON();
void curseurOFF();

#endif // UTILITAIRE_H_INCLUDED
