#include "Point.h"

///Class Point
/// La construction se fait directement depuis le fichier ouvert en cours de lecture...

Point::Point()
{

}

Point::Point(int _num,std::string _nom, int _altitude)
{
    m_num =_num;
    m_nom = _nom;
    m_altitude = _altitude;
    m_etat = 0;
    m_poids = INFINI;
    m_pred = nullptr;
    m_numCC = _num;

}

Point::~Point() {}


/// Retourne le num du Point
int Point::getNum() const
{
    return m_num;
}

/// Retourne le num CC du Point
int Point::getNumCC() const
{
    return m_numCC;
}

/// modifie le numCC du Point
void Point::setNumCC(int _numCC)
{
    m_numCC = _numCC;
}

/// Retourne le nom du Point
std::string Point::getNom() const
{
    return m_nom;
}

/// Retourne l'altitude du Point
int Point::getAltitude() const
{
    return m_altitude;
}

/// modifie l'etat du Point
void Point::setEtat(int nb)
{
    m_etat=nb;
}

/// Retourne l'etat du Point
int Point::getEtat() const
{
    return m_etat;
}

///retourne les Trajets sortants
std::vector<Trajet*> Point :: getAdjacents()
{
    return m_adjacents;
}

///retourne les Trajets entrants
std::vector<Trajet*> Point :: getEntrants()
{
    return m_entrants;
}

///on trie la liste des Trajets adjacents par Point de depart
void Point::triAdjacents()
{
    std::sort(m_adjacents.begin(), m_adjacents.end(), [](Trajet* a1, Trajet* a2)
    {
        return a1->getS1()->getNum() < a2->getS1()->getNum();
    });
}

///on trie la liste des arretes adjacentes par flux
    void Point::triAdjacentsFlux()
    {
        std::sort(m_adjacents.begin(), m_adjacents.end(), [](Trajet* a1, Trajet* a2)
        {
            return a1->getCap() - a1->getFlot() < a2->getCap() - a2->getFlot() ;
        });
    }
/*
///retourne le Point predecesseur
Point* Point::getPred()
{
    return m_pred;
}

/// Méthode d'ajout de Point predecesseur
void Point::setPred(Point*_pred)
{
    m_pred=_pred;
}*/

///retourne le Point predecesseur
Trajet* Point::getPred()
{
    return m_pred;
}

/// Méthode d'ajout de Point predecesseur
void Point::setPred(Trajet*_pred)
{
    m_pred=_pred;
}

/// ajouter les adjacences
void Point::ajouterAdj(Trajet *a)
{
    m_adjacents.push_back(a);
}

/// ajouter les trajets entrants
void Point::ajouterEntrant(Trajet *a)
{
    m_entrants.push_back(a);
}

/// Efface les adjacents
void Point::clearAdjacents(){
    m_adjacents.clear();
}

/// remplacer les adjacents
void Point::setAdjacents(std::vector <Trajet*> newAdj){
    m_adjacents = newAdj;
}

///retourne le temps
float Point::getPoids() const
{
    return m_poids;
}

/// change le temps
void Point::setPoids(float _tempsP)
{
    m_poids = _tempsP;
}

///remise à zéro du point
void Point::resetPoint()
{
    m_etat = 0;
    m_poids = INFINI;
    m_pred = nullptr;
    m_numCC = m_num;

}

/// c'est la "méthode d'affichage" des objets de type Points
void Point::afficher()const
{
    std::cout << " " << m_num << ". Nom: " << m_nom << " |" << " Altitude: " << m_altitude << std::endl;
    std::cout << " Liste des trajets sortants : " << std::endl;
    for (auto s : m_adjacents)
        s->afficher();

    std::cout << std::endl;
}

///Surchage < operateur priority_queue
bool operator< (const Point& s1, const Point &s2)
{
    return s1.getPoids() < s2.getPoids();
}

///Surchage > operateur priority_queue
bool operator> (const Point& s1, const Point &s2)
{
    return s1.getPoids() > s2.getPoids();
}

