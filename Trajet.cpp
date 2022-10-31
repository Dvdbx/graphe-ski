#include "Trajet.h"

///Class Trajet
/// La construction se fait directement depuis le fichier ouvert en cours de lecture...

Trajet::Trajet()
{
    m_s1 = nullptr;
    m_s2 = nullptr;
}

Trajet::Trajet(Point*s1,Point*s2,int _num, std::string _nom, std::string _type )
{
    m_s1 = s1;
    m_s2 = s2;
    m_num = _num;
    m_nom = _nom;
    m_type = _type;
    m_marque = 0;
    m_flot = 0;
    m_sens = 1;
    m_flux = 0;
}

Trajet::~Trajet()
{

}

/// Retourne le numero du trajet
int Trajet::getNum() const
{
    return m_num;
}

/// Retourne le nom du trajet
std::string Trajet::getNom() const
{
    return m_nom;
}

/// Retourne le type du trajet
std::string Trajet::getType() const
{
    return m_type;
}

/// Retourne le temps du trajet
float Trajet::getTemps() const
{
    return m_temps;
}

///modifie la valeur du temps de trajet
void Trajet::setTemps(float _temps)
{
    m_temps = _temps;
}

///retourne le Point de depart
Point* Trajet::getS1()
{
    return m_s1;
}

///retourne le Point d'arrivée
Point* Trajet::getS2()
{
    return m_s2;
}


/// c'est la "méthode d'affichage" des objets de type Trajets
void Trajet::afficher()const
{
    std::cout << "  " << m_num << ". Nom: " << m_nom << " | Type: " << m_type << " | "  << m_s1->getNom()  << " -- " << convertTemps(m_temps) << " --> " << m_s2->getNom() << /*" | cap : " << m_cap << " | marque : " << m_marque <<*/ std::endl;
}


///retourne la distance
int Trajet::getDistance() const
{
    return m_distance;
}

/// change la distance
void Trajet::setDistance(int _distance)
{
    m_distance = _distance;
}

/// Calcule la distance entre deux points puis la retourne
int Trajet::calculerDistance()
{
    int distance = abs(m_s1->getAltitude() - m_s2->getAltitude());
    setDistance(distance);
    return distance;
}

///modifie la valeur de la capcité
void Trajet::setCap(int _cap)
{
    m_cap = _cap;
}

/// Retourne la capacité du trajet
int Trajet::getCap() const
{
    return m_cap;
}

/// Retourne le flot du trajet
int Trajet::getFlot() const
{
    return m_flot;
}

///modifie la valeur du flot
void Trajet::setFlot(int _flot)
{
    m_flot = _flot;
}

/// Retourne le sens du trajet
    int Trajet::getSens() const
    {
        return m_sens;
    }

/// modifie le sens du trajet
    void Trajet::setSens(int _sens)
    {
        m_sens = _sens;
    }

/// Retourne le flux du trajet
    int Trajet::getFlux() const
    {
        return m_flux;
    }

///modifie la valeur du flux
    void Trajet::setFlux(int _flux)
    {
        m_flux = _flux;
    }


