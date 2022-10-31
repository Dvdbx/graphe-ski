#include "utilitaire.h"

void curseurOFF()
{
    CONSOLE_CURSOR_INFO cci;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsole, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cci);
}

void curseurON()
{
    CONSOLE_CURSOR_INFO cci;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsole, &cci);
    cci.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cci);
}
std::string convertTemps(float _temps)
{
    int heures = 0;
    int minutes = 0;
    int secondes = 0;

    ///conversion du temps en secondes
    secondes = _temps*60;

    /// on determine le nombre de seconde et le nombre de minute
    minutes = secondes / 60;
    secondes = secondes % 60;

    /// on calcule le nombre d'heure par rapport au minute
    heures = minutes / 60;
    minutes = minutes % 60;

    ///on retourne le calcul en chaine de caractere
    return (std::to_string(heures) + "h " + std::to_string(minutes) + "min " + std::to_string(secondes) + "s");
};

/// FONCTIONS DU MENU :

void gotoligcol( int lig, int col ) /// SOURCE : ECE
{
// ressources
    COORD mycoord;

    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}


void color(int couleurDuTexte,int couleurDeFond) /// Fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
