#ifndef TRAJET_H_INCLUDED
#define TRAJET_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "utilitaire.h"
#include "Point.h"

class Point;

/// La classe Trajet représente un trajet du graphe
class Trajet
{
private:

    /// Point de depart
    Point*m_s1;

    ///Point d'arrivée
    Point*m_s2;

    /// Données spécifiques de du trajet
    int m_num;
    float m_temps;
    std::string m_nom;
    std::string m_type;
    int m_distance;
    int m_marque;

     /// Données spécifiques du trajet pour le flux
    int m_cap;
    int m_flot;
    int m_flux;

    ///sens inverse (-1)
    ///sens direct (1)
    int m_sens;


public:

/// La construction se fait directement depuis le fichier ouvert en cours de lecture...
    Trajet();
    Trajet(Point*s1,Point*s2,int _num, std::string _nom, std::string _type );
    ~Trajet();

/// Retourne le numero du trajet
    int getNum() const;

    int getMarque() const{return m_marque;}
    void setMarque(int _marque){m_marque = _marque;}


/// Retourne le nom du trajet
    std::string getNom() const;

/// Retourne le type du trajet
    std::string getType() const;

/// Retourne le temps du trajet
    float getTemps() const;

///modifie la valeur du temps de trajet
    void setTemps(float _temps);

///retourne le Point de depart
    Point* getS1();

///retourne le Point d'arrivée
    Point* getS2();

/// c'est la "méthode d'affichage" des objets de type Trajet
    void afficher()const;

///retourne la distance
    int getDistance() const;

/// change la distance
    void setDistance(int _distance);

/// Calcule la distance entre deux points puis la retourne
    int calculerDistance();

/// Retourne la capacite du trajet
    int getCap() const;

///modifie la valeur de la capcité
    void setCap(int _cap);

/// Retourne le flot du trajet
    int getFlot() const;

///modifie la valeur du flot
    void setFlot(int _flot);

/// Retourne le sens du trajet
    int getSens() const;

/// modifie le sens du trajet
    void setSens(int _sens);

/// Retourne le flux du trajet
    int getFlux() const;

///modifie la valeur du flux
    void setFlux(int _flux);


};


#endif // TRAJET_H_INCLUDED
