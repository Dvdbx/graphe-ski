#ifndef BORNE_H_INCLUDED
#define BORNE_H_INCLUDED
#include "utilitaire.h"
#include "Station.h"



void afficheSkieurDessin();
void affichage_menu();
void menu2(int position);
void menu();
void afficherTrajet(Station g);
void menu_PCC(Station g);
void afficheBande ();
void affichePoints(Station g);
void convertTemps();
void contour_carte(int x,int y,int col);
void optimisation(Station graphe);
bool verifNiveau(std::string niveau);
void parcoursPerso(Station &g);
void reglage(Station &g,std::string pseudo);
void bonus(Station g);
void afficheLigne();
bool connexion(std::string &pseudo);
bool inscription(std::string &pseudo);
std::string menuConnexion();
bool verifPseudo(std::string pseudo);
void ChargementPreference(std::string pseudo,Station g);
bool verifPiste(std::string type);
void affluenceMax(Station g);
void logoLesArcs(int x,int y);
void modifieCap(); ///modifier les capacités
void affluence(Station g);
void modifieCap(Station g);


#endif // BORNE_H_INCLUDED
