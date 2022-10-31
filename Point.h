#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#define INFINI 99999999

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Trajet.h"
#include "utilitaire.h"

class Trajet;

/// La classe Point représente un Point du graphe
class Point
{
private:

    /// Données spécifiques du Point
    int m_num;
    std::string m_nom;
    int m_altitude;

    /// Données pour le PCC
    int m_etat;
    //Point*m_pred;
    float m_poids;
    Trajet*m_pred;
    int m_numCC;

    ///vecteur des trajets sortants
    std::vector <Trajet*> m_adjacents;

     ///vecteur des trajets entrants
    std::vector <Trajet*> m_entrants;

public:

/// La construction se fait directement depuis le fichier ouvert en cours de lecture...
    Point();
    Point(int _num,std::string _nom, int _altitude);
    ~Point();

/// Retourne le num du Point
    int getNum() const;

/// Retourne le num CC du Point
    int getNumCC() const;

/// modifie le numCC du Point
    void setNumCC(int _numCC);

/// Retourne le nom du Point
    std::string getNom() const;

/// Retourne l'altitude du Point
    int getAltitude() const;
/*
///retourne le Point predecesseur
    Point* getPred();

/// Méthode d'ajout de Point predecesseur
    void setPred(Point*_pred);
*/
///retourne le trajet inverse
    Trajet* getPred();

/// Méthode d'ajout du trajet predecesseur
    void setPred(Trajet*_pred);

/// modifie l'etat du Point
    void setEtat(int nb);

/// Retourne l'etat du Point
    int getEtat() const;

/// modifie le temps du Point
    void setPoids(float nb);

/// Retourne le temps du Point
    float getPoids() const;

///retourne les Trajets sortants
    std::vector<Trajet*> getAdjacents();

///retourne les Trajets entrants
    std::vector<Trajet*> getEntrants();

///on trie la liste des Trajets par numéro de départ
    void triAdjacents();

///on trie la liste des arretes adjacentes par flux
    void triAdjacentsFlux();

/// c'est la "méthode d'affichage" des objets de type Points
    void afficher()const;

/// ajouter les adjacences
    void ajouterAdj(Trajet *a);

/// ajouter les adj entrants
    void ajouterEntrant(Trajet *a);

///remise à zéro du point
    void resetPoint();

/// Efface les adjacents
    void clearAdjacents();

/// remplacer les adjacents
    void setAdjacents(std::vector <Trajet*> newAdj);
/*
/// supprimer Trajet
void supprimAdj(Trajet *t)
    {
        for(auto s : m_adjacents)
            if(t == s)
            {
                s = NULL;
            }
         m_adjacents.shrink_to_fit();
    }
*/
};

///class template pour comparer des pointeurs (pour la priority queue)
class MyCompare
{
public:
    template<typename T>
    bool operator()(T *a, T *b)
    {
        return (*a) > (*b);
    }
};

///Surchage < operateur priority_queue
bool operator < (const Point& s1, const Point &s2);

///Surchage > operateur priority_queue
bool operator > (const Point& s1, const Point &s2);

#endif // POINT_H_INCLUDED
