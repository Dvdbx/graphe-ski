#ifndef STATION_H_INCLUDED
#define STATION_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
#include "Point.h"
#include "Trajet.h"


/// La classe Station représente un Station dans son ensemble
class Station
{
private:
    /// La Station est constitué d'une collection de Points
    std::vector<Point*> m_points;

    /// Points découverts
    std::vector<Point*> m_decouverts;

    /// La Station est constitué d'une collection de Trajets
    std::vector<Trajet*> m_trajets;

    ///Arbre de poids minimal ou maximal
    std::vector<Trajet*> m_arbre;

    int m_ordre;
    int m_taille;
    int m_flot_max;

public:
    /// La construction de Station se fait à partir d'un fichier ou vide ( arbre vide )
    /// dont le nom est passé en paramètre
    Station(std::string nomFichier);

    Station();

    /// Destructeur de Station. Les Points ont été allouées dynamiquement
    ~Station();

    /// Retourne l'ordre de Station (ordre = nombre de Points)
    int getOrdre() const;

    /// Retourne la taille de Station
    int getTaille() const;

    ///Retourne le vecteur de tous les Points
    std::vector <Point*> getPoints();

    ///Retourne le vecteur de tous les Trajets
    std::vector <Trajet*> getTrajet();

    ///Ajoute un Trajet
    void ajoutTrajet(Trajet*a);

    ///on trie la liste des Points par ordre croissant
    void triPoints();

    ///on trie la liste des Points découverts par ordre croissant
    void triDecouverts();

    ///on trie la liste des Points decouverts par flux decroissants
    void triDecouvertsFlux();

    /// c'est la "méthode d'affichage" des objets de type Station
    void afficher();

    /// initialise les distances : calcule le temps necessaire pour effectuer les differents trajets
    void initialiserDistances();

    /// Changer les parametre pour les distances
    void parametrageDistance(std::string pisteChanger, float _tp);

    /// mise à jour du fichier : on rajoute le temps
    void MAJfichier(std::string nomFic);

    ///Plus courts chemins en temps
    void PCC(int Id);

    ///Plus courts chemins en flot
    void PCCFlot(int Id);

    ///on affiche la liste des PCC dans l'ordre
    void affichePCC(int Id,int affichetemps);

    /// affichage de la liste d'un predecesseur
    void affichePred(int Id, int _final, int affichetemps);

    /// affichage de la liste d'un predecesseur par flot
    void affichePredFlot(int Id, int _final,int nbChemin);

    /// remise à zéro de tous les points
    void resetPoints();

    ///nettoyer le vecteur des sommets découverts
    void cleanDecouverts();

    /// Supprime une piste par type
    void supprimerPiste(std::string delPiste);

    /// Supprime les trajets par remontee : elimination par choix
    void supprimerRemontee(std::string delRemontee);

    /// Supprime toutes les remontées
    void supprimerToutesRemontee();

    /// Supprime toutes les pistes sauf celle envoyé en parametre
    void supprimerAutrePiste(std::string garderPiste);

    /// Trouve le parcours en fonction du niveau, des remontees et du temps que le skieur possède
    void parcoursPersonnalise(int depart, std::string niveau, float duree, std::string remontees, int affichetemps);

    /// Retourne le flot max
    int getFlotMax() const;

    ///modifie la valeur du flot max
    void setFlotMax(int _flot);

    ///Plus courts chemin en nombre de points
    void BFS(int Id);

    ///calcul de flot entre deux points
    void FF(int ini, int _final,int &nbChemin );

    bool DFS(int Id, int _final);

    ///sous graphe partiel pour le flot
    void SGP(int ini, int _final);

    ///calcul le flot min du chemin courant
    int calculFlot(int Id,int _final);

    /// Regarde si il existe un parcours
    bool trajetSansRemontees(int _final);

    /// Trouve le chemin avec le moins de remontees
    void PCCOptimiseRemontees(int depart, int arrive);

    /// Trouve les chemins avec les descentes
    void PCCOptimiseDescentes(int depart);

    ///Réinitialiser le marquage des trajets aprés optimisation
    void resetTrajet();

    ///trouver l'arbre de poids minimal ou maximal de la station
    void kruskal(int max_min);

    ///on affiche le nouvel arbre obtenu
    void afficheArbre(int max_min);

    ///Supprimer les pistes que le skieur ne souhaite pas emprunter
    void chargementGraphePersonnaliseType(std::vector<std::string> delPiste);

    ///Changer le temps des pistes a partir des valeurs du fichier
    void changerTemps(std::vector<std::pair<std::string,int>> pistesdel);

    void changerCapacite(float capacite, std::string type);



};


#endif // STATION_H_INCLUDED
