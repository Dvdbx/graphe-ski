#include "Station.h"
#include "borne.h"
#include <windows.h>

#define millieu 70
///class Station
Station::Station()
{
    m_ordre = 0;
    m_taille = 0;
}

Station::Station(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    ifs >> m_ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre de Station");

    ///on cree les differents Points
    for (int i=0; i<m_ordre; ++i)
    {
        m_points.push_back( new Point{} );
    };

    ///on cree les differents Points
    for (int i=0; i<m_ordre; ++i)
    {
        int _num;
        std::string _nom;
        int _altitude;
        ifs >> _num >> _nom >> _altitude;
        m_points[_num - 1] = new Point{_num, _nom, _altitude};
    };

    /*
    ///on cree les differents Points
    for (int i=0; i<m_ordre; ++i)
    {
        int _num;
        std::string _nom;
        int _altitude;
        ifs >> _num >> _nom >> _altitude;
        m_points.push_back( new Point{_num, _nom, _altitude} );
    };*/


    ifs >> m_taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille de Station");

    ///on cree les trajets
    for (int i=0; i<m_taille; ++i)
    {
        int _num;
        int num_sommet_depart;
        int num_sommet_arrivee;
        std::string _nom;
        std::string _type;

        ifs >> _num >> _nom >> _type >> num_sommet_depart >> num_sommet_arrivee;

        Trajet *a = new Trajet{m_points[num_sommet_depart-1],m_points[num_sommet_arrivee-1],_num,_nom,_type};
        ajoutTrajet(a);
        m_points[num_sommet_depart-1]->ajouterAdj(a);
        m_points[num_sommet_arrivee-1]->ajouterEntrant(a);
    }

    m_flot_max = 0;

}

/// Destructeur de Station. Les Points ont été allouées dynamiquement
Station::~Station()
{
    /*
    for (auto s : m_points)
        delete s;
        */
}

/// Retourne l'ordre de Station (ordre = nombre de Points)
int Station::getOrdre() const
{
    return m_ordre;
}

/// Retourne la taille de Station
int Station::getTaille() const
{
    return m_taille;
}

///Retourne le vecteur de tous les Points
std::vector <Point*> Station::getPoints()
{
    return m_points;
}

///Retourne le vecteur de toutes les Trajets
std::vector <Trajet*> Station::getTrajet()
{
    return m_trajets;
}

///Ajoute une Trajet
void Station::ajoutTrajet(Trajet*a)
{
    m_trajets.push_back(a);
}

/// c'est la "méthode d'affichage" des objets de type Station
void Station::afficher()
{
    std::cout << "  Ordre = " << getOrdre() << std::endl;
    std::cout << "  Taille = " << getTaille() << std::endl;
    std::cout << "  Points : " << std::endl;
    for(auto s : m_points)
        s->afficher();

}

/// initialise les distances : calcule le temps necessaire pour effectuer les differents trajets
/// initialise les capacités
void Station::initialiserDistances()
{
    for(auto t : m_trajets)
    {
        t->calculerDistance();
        std::string type = t->getType();
        float temps;
        float tp; // Temps de parcours : 5 min pour 100m pour piste verte
        int dp = 100; // Distance de parcours
        int c; // Constante : 4 pour TPH

        if(type == "V")
        {
            tp = 5;
            c = 0;
            temps = ((tp*t->getDistance())/dp) + c;
            t->setCap(700);
        }
        else if(type == "B")
        {
            tp = 4;
            c = 0;
            temps = ((tp*t->getDistance())/dp) + c;
            t->setCap(600);
        }
        else if(type == "R")
        {
            tp = 3;
            c = 0;
            temps = ((tp*t->getDistance())/dp) + c;
            t->setCap(900);
        }
        else if(type == "N")
        {
            tp = 2;
            c = 0;
            temps = ((tp*t->getDistance())/dp) + c;
            t->setCap(400);
        }
        else if(type == "KL")
        {
            tp = 0.1;
            c = 0;
            temps = ((tp*t->getDistance())/dp) + c;
            t->setCap(750);
        }
        else if(type == "SURF")
        {
            tp = 10;
            c = 0;
            temps = ((tp*t->getDistance())/dp) + c;
            t->setCap(850);
        }
        ///capacités données
        else if(type == "TPH")
        {
            tp = 2;
            c = 4;
            temps = ((tp*t->getDistance())/dp) + c;
            t->setCap(1200);
        }
        else if(type == "TC")
        {
            tp = 3;
            c = 2;
            temps = ((tp*t->getDistance())/dp) + c;
            t->setCap(2200);
        }
        else if(type == "TSD")
        {
            tp = 3;
            c = 1;
            temps = ((tp*t->getDistance())/dp) + c;
            t->setCap(2500);
        }
        else if(type == "TS")
        {
            tp = 4;
            c = 1;
            temps = ((tp*t->getDistance())/dp) + c;
            t->setCap(1800);
        }
        else if(type == "TK")
        {
            tp = 4;
            c = 1;
            temps = ((tp*t->getDistance())/dp) + c;
            t->setCap(800);
        }
        else if(type == "BUS")
        {
            t->setCap(300);
            std::string nom = t->getNom();
            if(nom == "navette1600-1800" || nom == "navette1800-1600")
            {
                temps = 30; // 30 min
            }
            else if(nom == "navette1600-2000" || nom == "navette2000-1600")
            {
                temps = 40;
            }
        }
        t->setTemps(temps);
    }
}

void Station::parametrageDistance(std::string pisteChanger, float _tp)
{
    for(auto t : m_trajets)
    {
        t->calculerDistance();
        std::string type = t->getType();
        float temps;
        float tp; // Temps de parcours : 5 min pour 100m pour piste verte
        int dp = 100; // Distance de parcours
        int c; // Constante : 4 pour TPH

        if(type == "V")
        {
            tp = 5;
            c = 0;
            temps = ((tp*t->getDistance())/dp) + c;
        }
        else if(type == "B")
        {
            tp = 4;
            c = 0;
            temps = ((tp*t->getDistance())/dp) + c;
        }
        else if(type == "R")
        {
            tp = 3;
            c = 0;
            temps = ((tp*t->getDistance())/dp) + c;
        }
        else if(type == "N")
        {
            tp = 2;
            c = 0;
            temps = ((tp*t->getDistance())/dp) + c;
        }
        else if(type == "KL")
        {
            tp = 0.1;
            c = 0;
            temps = ((tp*t->getDistance())/dp) + c;
        }
        else if(type == "SURF")
        {
            tp = 10;
            c = 0;
            temps = ((tp*t->getDistance())/dp) + c;
        }
        else if(type == "TPH")
        {
            tp = 2;
            c = 4;
            temps = ((tp*t->getDistance())/dp) + c;
        }
        else if(type == "TC")
        {
            tp = 3;
            c = 2;
            temps = ((tp*t->getDistance())/dp) + c;
        }
        else if(type == "TSD")
        {
            tp = 3;
            c = 1;
            temps = ((tp*t->getDistance())/dp) + c;
        }
        else if(type == "TS")
        {
            tp = 4;
            c = 1;
            temps = ((tp*t->getDistance())/dp) + c;
        }
        else if(type == "TK")
        {
            tp = 4;
            c = 1;
            temps = ((tp*t->getDistance())/dp) + c;
        }
        else if(type == "BUS")
        {
            std::string nom = t->getNom();
            if(nom == "navette1600-1800" || nom == "navette1800-1600")
            {
                temps = 30; // 30 min
            }
            else if(nom == "navette1600-2000" || nom == "navette2000-1600")
            {
                temps = 40;
            }
        }

        if(type == pisteChanger)
        {
            temps = ((_tp*t->getDistance())/dp) + c;
        }
        t->setTemps(temps);
    }
}


///Ajout des capacités
void Station::MAJfichier(std::string nomFic)
{
    std::string const nomFichier(nomFic);
    std::ofstream monFlux(nomFichier.c_str());

    if(monFlux)
    {
        int ordre = getOrdre();
        int taille = getTaille();

        monFlux << ordre << std::endl;
        for(auto s : m_points)
        {
            monFlux << s->getNum() << "\t" << s->getNom() << "\t" << s->getAltitude() << std::endl;
        }

        monFlux << taille << std::endl;
        for(auto t : m_trajets)
        {
            monFlux << t->getNum() << "\t" << t->getNom() << "\t" << t->getType() << "\t" << t->getS1()->getNum()
                    << "\t" << t->getS2()->getNum() << "\t" << t->getTemps() << "\t" << t->getCap() << std::endl;
        }
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
    monFlux.close();
}

///on trie la liste des Points par ordre croissant
void Station::triPoints()
{
    std::sort(m_points.begin(), m_points.end(), [](Point* s1, Point* s2)
    {
        return s1->getNum() < s2->getNum();
    });
}

///on trie la liste des Points découverts par ordre croissant
void Station::triDecouverts()
{
    std::sort(m_decouverts.begin(), m_decouverts.end(), [](Point* s1, Point* s2)
    {
        return s1->getNum() < s2->getNum();
    });
}
/*
///on trie la liste des Points decouverts par flux decroissants
void Station::triDecouvertsFlux()
{
    std::sort(m_decouverts.begin(), m_decouverts.end(), [](Point* a1, Point* a2)
    {
        return a1->getPred()->getCap() - a1->getPred()->getFlot()  < a2->getPred()->getCap() - a2->getPred()->getFlot() ;
    });
}*/

///on trie la liste des Points decouverts par flux decroissants
void Station::triDecouvertsFlux()
{
    std::sort(m_decouverts.begin(), m_decouverts.end(), [](Point* a1, Point* a2)
    {
        return a1->getPred()->getFlux()  < a2->getPred()->getFlux() ;
    });
}

/// nettoyer tous les predecesseurs
void Station::resetPoints()
{
    for(auto s : m_points)
        s->resetPoint();
}

///nettoyer le vecteur des sommets découverts
void Station::cleanDecouverts()
{
    m_decouverts.clear();
}

///Plus courts chemins en temps
void Station::PCC(int Id)
{
    Id--;
    std::priority_queue<Point*, std::vector<Point*>,MyCompare > parcours;

    ///pour enlever les doublons et trier a la fin du programme du aux maj
    std::set <Point*> enOrdre;

    ///on insere le premier Point dans la queue
    m_points[Id]->setPoids(0);
    parcours.push(m_points[Id]);

    while ( !parcours.empty())
    {
        Point*s1 = parcours.top();

        ///marquage du Point
        s1->setEtat(1);
        m_decouverts.push_back(s1);
        parcours.pop();

        ///on parcourt les Points adjacents du Point de la queue
        for(auto s : s1->getAdjacents())
        {
            //std::cout << "test" << std::endl;
            //s->afficher();
            ///Si le Point adjacent n'est pas marqué
            //std::cout << " dd " << s->getMarque() << std::endl;
            if((s->getS2()->getEtat() == 0) && (s->getMarque() == 0))
            {
                ///on actualise ses infos si le chemin actuel est plus courts
                if(s->getS2()->getPoids() > s->getTemps() + s1->getPoids() )
                {
                    //s->getS2()->setPred(s1);
                    s->getS2()->setPred(s);
                    s->getS2()->setPoids(s->getTemps() + s1->getPoids());
                    parcours.push(s->getS2());
                }
            }

        }
    }
    for(auto s : m_decouverts)
        enOrdre.insert(s);

    cleanDecouverts();

    for(auto t : enOrdre)
        m_decouverts.push_back(t);

}

///Plus courts chemins en flot
void Station::PCCFlot(int Id)
{
    Id--;
    std::vector<Point*>parcours;

    ///pour enlever les doublons et trier a la fin du programme du aux maj
    std::set <Point*> enOrdre;

    ///nettoyer le vecteur des sommets decouverts
    cleanDecouverts();

    ///on insere le premier Point dans la queue
    m_points[Id]->setPoids(0);
    parcours.push_back(m_points[Id]);

    while ( !parcours.empty())
    {
        Point*s1 = parcours.back();

        ///marquage du Point
        s1->setEtat(1);
        m_decouverts.push_back(s1);
        parcours.pop_back();

        ///on parcourt les Points adjacents du Point de la queue
        for(auto s : s1->getAdjacents())
        {

            ///Si le Point adjacent n'est pas marqué
            if((s->getS2()->getEtat() == 0) && (s->getMarque() == 0))
            {
                ///on actualise ses infos si le chemin actuel est plus courts
                if(s->getS2()->getPoids() > s->getFlot() + s1->getPoids() )
                {
                    s->getS2()->setPred(s);
                    s->getS2()->setPoids(s->getFlot() + s1->getPoids());
                    parcours.push_back(s->getS2());
                }
            }

        }
        ///trier le vecteur de sommet par poids pour le prochain tour
        std::sort(parcours.begin(), parcours.end(), [](Point* s1, Point* s2)
        {
            return s1->getPoids() > s2->getPoids();
        });
    }
    for(auto s : m_decouverts)
        enOrdre.insert(s);

    cleanDecouverts();

    for(auto t : enOrdre)
        m_decouverts.push_back(t);

}


///Plus courts chemin en nombre de points
void Station::BFS(int Id)
{
    Id--;
    std::queue <Point*> parcours;

    ///nettoyer le vecteur des sommets decouverts
    cleanDecouverts();

    ///on insere le premier sommet dans la file
    parcours.push(m_points[Id]);
    parcours.front()->setEtat(1);

    ///tant que la file n'est pas vide
    while(!parcours.empty())
    {
        ///on trie les sommets adjacents du premier sommet par ordre croissant
        parcours.front()->triAdjacents();

        ///on ajoute les sommets adjacents non visites du sommet decouvert dans la file
        for(auto s : parcours.front()->getAdjacents())
        {
            if((s->getMarque() == 0)&&(s->getS2()->getEtat() == 0))
            {
                s->getS2()->setEtat(1);
                s->getS2()->setPred(s);
                parcours.push(s->getS2());
                m_points.push_back(s->getS2());
            }

        }
        ///on enleve le sommet decouvert
        m_decouverts.push_back(parcours.front());
        parcours.pop();

    }
    ///on trie la liste de sommets decouverts par numéro de sommets
    triDecouverts();

}

///on affiche la liste des predecesseurs
void Station::affichePCC(int Id, int affichetemps)
{
    //system("cls");
    char a;

    a = 0xCD;
    color(15,0);
    for(int i=0; i<172; i++)
    {
        gotoligcol(0,i);
        std::cout<<a;
    }
    gotoligcol(2,55);
    color(12,0);
    std::cout << " Affichage des plus courts chemins pour acceder au point " << Id << " : " << std::endl;
    color(15,0);

    if(m_decouverts.size() != 1)
    {
        triDecouverts();
        for(auto s : m_decouverts)
        {
            if(s->getNum() != Id)
            {
                color(15,0);
                Point*temp = s;
                while(temp->getNum() != Id)
                {
                    std::cout << temp->getNom() <<" ("<<temp->getPred()->getType() << ") <-- ";
                    temp = temp->getPred()->getS1();
                }

                if(affichetemps == 0)
                {

                    std::cout <<temp->getNom()<<" | Temps : ";
                    color(12,0);
                    std::cout<< convertTemps(s->getPoids());
                    std::cout << std::endl;
                    color(15,0);

                }
                else
                {
                    std::cout <<temp->getNom();
                    std::cout << std::endl;
                }
            }

        }
    }
    else
    {
        std::cout << " Le point " << m_decouverts[0]->getNom() << " est un puit, il n'a pas de trajets sortants";
        std::cout << std::endl;
    }

    m_decouverts.clear();
    resetPoints();
}

/// affichage de la liste d'un predecesseur
void Station::affichePred(int Id, int _final, int affichetemps)
{
    //system("cls");
    char a;

    a = 0xCD;
    color(15,0);
    for(int i=0; i<172; i++)
    {
        gotoligcol(0,i);
        std::cout<<a;
    }
    gotoligcol(2,55);
    color(12,0);

    bool exist = false;

    for(auto s : m_decouverts)
    {
        if(s->getNum() == _final)
            exist = true;
    }

    if(/*m_decouverts.size() != 1 && */exist == true)
    {
        ///trouver le Point final par numéro
        /*
        for(auto d : m_decouverts)
            if(d->getNum() == _final)
            {
                s = d;
                f = d;
            }
        */
        Point *f = m_points[_final - 1];


        ///affichage du chemin en deroulant les predecesseurs
        gotoligcol(3,10);
        std::cout << "Itineraire le plus cours de " <<m_points[Id-1]->getNom()<<" a "<< m_points[_final-1]->getNom() << " : ";
        color(15,0);
        gotoligcol(5,10);
        if(f->getNum() != Id)
        {
            Point*temp = f;
            while(temp->getNum() != Id)
            {
                std::cout << "|"<< temp->getNom() <<" ("<<temp->getPred()->getType() << ") |<--";
                temp = temp->getPred()->getS1();
            }
            std::cout << "|" << temp->getNom() << "|" ;
        }
        else std::cout << " |" << f->getNom() << "|";
        std::cout << std::endl;

        f = m_points[_final - 1];

        if(affichetemps == 0)
        {
            ///affichage du calcul de la distance
            gotoligcol(7,10);
            color(15,0);
            std::cout << "Calcul du temps : ";
            color(15,0);
            if(f->getNum() != Id)
            {
                Point*temp = f;
                while(temp->getNum() != Id)
                {
                    std::cout << convertTemps(temp->getPred()->getTemps());

                    if(temp->getPred()->getS1()->getNum() != Id)
                        std::cout << " + ";

                    temp = temp->getPred()->getS1();
                }

                std::cout << " = " << convertTemps(m_points[_final-1]->getPoids()) << std::endl;
            }
            else std::cout << convertTemps(m_points[_final-1]->getPoids());
        }

    }
    else std::cout << "Il n'existe pas de chemin possible entre ces deux points " << std::endl;

    m_decouverts.clear();
    resetPoints();
}

/// affichage de la liste d'un predecesseur par flot
void Station::affichePredFlot(int Id, int _final,int nbChemin)
{
    //system("cls");
    char a;
    nbChemin += 10;

    a = 0xCD;
    color(15,0);
    for(int i=0; i<172; i++)
    {
        gotoligcol(0,i);
        std::cout<<a;
    }
    gotoligcol(2+nbChemin,4);
    color(12,0);

    bool exist = false;

    for(auto s : m_decouverts)
    {
        if(s->getNum() == _final)
            exist = true;
    }

    if(/*m_decouverts.size() != 1 && */exist == true)
    {
        ///trouver le Point final par numéro
        /*
        for(auto d : m_decouverts)
            if(d->getNum() == _final)
            {
                s = d;
                f = d;
            }
        */
        Point *f = m_points[_final - 1];


        ///affichage du chemin en deroulant les predecesseurs
        gotoligcol(3+nbChemin,4);
        std::cout << "Itineraire avec le moins d'affluence de " <<m_points[Id-1]->getNom()<<" a "<< m_points[_final-1]->getNom() << " : ";
        color(15,0);
        gotoligcol(5+nbChemin,4);
        if(f->getNum() != Id)
        {
            Point*temp = f;
            while(temp->getNum() != Id)
            {
                std::cout << "|"<< temp->getNom() <<" ("<<temp->getPred()->getType() << ") |<--";
                temp = temp->getPred()->getS1();
            }
            std::cout << "|" << temp->getNom() << "|" ;
        }
        else std::cout << " |" << f->getNom() << "|";
        std::cout << std::endl;

        f = m_points[_final - 1];

        ///affichage du calcul de la distance
        gotoligcol(7+nbChemin,4);
        color(15,0);
        std::cout << "Calcul du total des flots du chemin : ";
        color(15,0);
        if(f->getNum() != Id)
        {
            Point*temp = f;
            while(temp->getNum() != Id)
            {
                std::cout << temp->getPred()->getFlot();

                if(temp->getPred()->getS1()->getNum() != Id)
                    std::cout << " + ";

                temp = temp->getPred()->getS1();
            }

            std::cout << " = " << m_points[_final-1]->getPoids();
        }
        else std::cout << m_points[_final-1]->getPoids();

    }
    else std::cout << "Il n'existe pas de chemin possible entre ces deux points " ;

    ///tout nettoyer
    m_decouverts.clear();
    resetPoints();
    resetTrajet();
}



/// Supprime une piste par type
void Station::supprimerPiste(std::string delPiste)
{
    if(delPiste == "V" || delPiste == "B" || delPiste == "R" ||delPiste == "N" || delPiste == "KL" || delPiste == "SURF" ||
            delPiste == "TPH" || delPiste == "TC" ||
            delPiste == "TSD" || delPiste == "TS" || delPiste == "TK")
    {
        for(auto pt : m_points)
        {
            //std::vector <Trajet*> tmpAdj;
            for(auto trajetAdj : pt->getAdjacents())
            {
                if(trajetAdj->getType() == delPiste)
                {
                    trajetAdj->setMarque(1);
                    //std::cout << " trajetAdj->getMarque " << trajetAdj->getMarque() << std::endl;
                }
            }
            //pt->clearAdjacents();
            //pt->setAdjacents(tmpAdj);
        }
    }
    else
        std::cout << "Vous avez saisie une piste qui n'existe pas !" << std::endl;

    /*
    for(auto pt : m_points)
    {
        //std::vector <Trajet*> tmpAdj;
        for(auto trajetAdj : pt->getAdjacents())
        {
            if(trajetAdj->getType() == delPiste)
            {
                trajetAdj->setMarque(1);

                //std::cout << " trajetAdj->getMarque " << trajetAdj->getMarque() << std::endl;
            }
            else if(trajetAdj->getType() != delPiste)
            {   //trajetAdj->setMarque(0);
                //std::cout << " trajetAdj->getMarque " << trajetAdj->getMarque() << std::endl;
                //tmpAdj.push_back(trajetAdj);
            }
        }

        //pt->clearAdjacents();
        //pt->setAdjacents(tmpAdj);

    }
    */

}

/// Supprime les trajets par remontee
void Station::supprimerRemontee(std::string delRemontee)
{
    if(delRemontee == "TPH" || delRemontee == "TC" || delRemontee == "TSD" ||
            delRemontee == "TS" || delRemontee == "TK")
    {
        for(auto pt : m_points)
        {
            for(auto trajetAdj : pt->getAdjacents())
            {
                if(trajetAdj->getType() == delRemontee)
                {
                    trajetAdj->setMarque(1);
                }
            }
        }
    }
    else if(delRemontee == "Rien")
    {

    }
    else
        std::cout << "Vous avez saisie une remontee qui n'existe pas !" << std::endl;
}


/// Supprime toutes les remontées
void Station::supprimerToutesRemontee()
{
    std::string type;
    for(auto pt : m_points)
    {
        for(auto trajetAdj : pt->getAdjacents())
        {
            type = trajetAdj->getType();
            if(type == "TPH" || type == "TC" || type == "TSD" ||
                    type == "TS" || type == "TK")
            {
                trajetAdj->setMarque(1);
            }
        }
    }
}

/// Supprime toutes les pistes sauf celle envoyé en parametre
void Station::supprimerAutrePiste(std::string garderPiste)
{
    if(garderPiste == "V" || garderPiste == "B" || garderPiste == "R" ||
            garderPiste == "N" || garderPiste == "KL" || garderPiste == "SURF")
    {
        for(auto pt : m_points)
        {
            for(auto trajetAdj : pt->getAdjacents())
            {
                if(trajetAdj->getType() != garderPiste)
                {
                    trajetAdj->setMarque(1);
                }
            }
        }
    }
    else
        std::cout << "Probleme de piste ! " << std::endl;
}


/// Trouve le parcours en fonction du niveau, des remontees et du temps que le skieur possède
void Station::parcoursPersonnalise(int depart, std::string niveau, float duree, std::string remontees, int affichetemps)
{
    system("cls");
    char a;

    a = 0xCD;
    color(15,0);
    for(int i=0; i<172; i++)
    {
        gotoligcol(0,i);
        std::cout<<a;
    }
    gotoligcol(2,55);
    color(11,0);
    std::cout << " Affichage des plus courts chemins du point " << depart << " : " << std::endl;
    std::cout << "Pour des pistes " << niveau << std::endl;
    std::cout << "Pour une duree de " << duree << " minutes " << std::endl;
    if(remontees == "Rien")
    {
        std::cout << "Avec toutes les remontees " << std::endl;
    }
    else
    {
        std::cout << "Sans la remontees : " << remontees << std::endl;
    }

    color(15,0);
    // On supprime les remontees :
    supprimerRemontee(remontees); // Si il n'y a pas de remontee a supprimer envoyer "Rien"

    // N R B V //
    // On supprime des types de piste en fonction du niveau de la personne
    if(niveau == "V")
    {
        supprimerPiste("R");
        supprimerPiste("B");
        supprimerPiste("N");
    }
    else if(niveau == "B")
    {
        supprimerPiste("R");
        supprimerPiste("N");
    }
    else if(niveau == "R")
    {
        supprimerPiste("N");
    }

    // On lance Djikstra
    PCC(depart);

    // On affiche les PCC
    if(m_decouverts.size() != 1)
    {
        triDecouverts();
        for(auto s : m_decouverts)
        {
            if(s->getPoids() < duree)
            {
                if(s->getNum() != depart)
                {
                    color(15,0);
                    Point*temp = s;
                    while(temp->getNum() != depart)
                    {
                        std::cout << temp->getNom() << " <-- ";
                        temp = temp->getPred()->getS1();
                    }

                    if(affichetemps == 0)
                    {

                        std::cout <<temp->getNom()<<" | Temps : ";
                        color(12,0);
                        std::cout<< convertTemps(s->getPoids());
                        std::cout << std::endl;
                        color(15,0);
                    }
                    else
                    {
                        std::cout <<temp->getNom();
                        std::cout << std::endl;
                    }
                }
            }
        }
    }
    else
    {
        std::cout << " Le point " << m_decouverts[0]->getNom() << " est un puit, il n'a pas de trajets sortants";
        std::cout << std::endl;
    }

    /// On réinitialise tous
    m_decouverts.clear();
    resetPoints();
}

///DFS iteratif recherche d'un chemin entre la source et le puit
bool Station::DFS(int Id,int _final)
{
    /// on décale les valeurs pour avoir les bons numéros de tableau
    Id--;
    _final--;

    std::stack <Point*> parcours;

    ///s'il existe un chemin augmentant
    bool chemin = false;

    ///nettoyer le vecteur des arretes decouverts
    cleanDecouverts();

    ///on insere le premier Point dans la pile
    parcours.push(m_points[Id]);
    parcours.top()->setEtat(1);
    m_decouverts.push_back(parcours.top());

    ///tant que la pile n'est pas égale à la sortie ou nul
    while((!parcours.empty())&&(parcours.top() != m_points[_final]))
    {

        ///Point temporaire, ancien Point de la pile
        Point*tmp_s = parcours.top();
        Trajet*tmp_a = nullptr;

        ///on trie les Points adjacents de l'ancien Point par ordre croissant de flux
        tmp_s->triAdjacentsFlux();

        ///on enleve le Point decouvert
        parcours.pop();

        ///on ajoute les sommets adjacents non visités du sommet decouvert dans la pile
        ///si l'arrete est directe
        for(auto s : tmp_s->getAdjacents())
        {
            if((s->getS2()->getEtat() == 0)&&(s->getMarque() == 0))
            {
                s->getS2()->setPred(s);
                s->getS2()->setEtat(1);
                parcours.push(s->getS2());
                s->setFlux(s->getCap() - s->getFlot());
                tmp_a = s;
            }

        }

        ///ajouter le point si possible
        if(tmp_a != nullptr)
        {
            m_decouverts.push_back(tmp_a->getS2());
        }

        else if (tmp_a == nullptr)
        {
            /// si on trouve une arrete inverse de flot positive
            for(auto s : tmp_s->getEntrants())
            {
                if((s->getS1()->getEtat() == 0)&&(s->getFlot() > 0))
                {
                    s->getS1()->setPred(s);
                    s->getS1()->setEtat(1);
                    parcours.push(s->getS1());
                    s->setFlux(s->getFlot());
                    tmp_a = s;
                }

            }
            if(tmp_a != nullptr)
            {
                tmp_a->setSens(-1);
                m_decouverts.push_back(tmp_a->getS1());
            }
        }
    }

    ///si un chemin menant au puit existe
    if(m_points[_final]->getPred() != nullptr)
    {
        chemin = true;
    };

    return chemin;
}

void Station::FF(int Id,int _final,int &nbChemin)
{
    color(12,0);
    system("cls");
    afficheBande();
    nbChemin =0;

    color(12,0);
    gotoligcol(4,4);
    std::cout << "Calcul du flot max du point " << Id << " au point " << m_points[_final-1]->getNom() << " :";

    color(15,0);
    int tmp_flot = 0;
    std::vector <Trajet*> grapheEcart;
    bool chemin = true;

    //int nbChemin = 0; ///pour bien afficher les chemins a la suite

    while(chemin == true)
    {
        ///recherche d'un chemin entre la source et le puit
        chemin = DFS(Id,_final);

        ///si chemin trouvé, calculer le flot
        if(chemin == true)
        {
            ///ne garder que le chemin propre
            m_decouverts.clear();
            Point*temp = m_points[_final - 1];

            while(temp != m_points[Id - 1])
            {
                m_decouverts.push_back(temp);

                if(temp->getPred()->getSens() == 1)
                    temp = temp->getPred()->getS1();

                else if(temp->getPred()->getSens() == -1)
                    temp = temp->getPred()->getS2();
            }

            ///calcul du flot augmentant
            triDecouvertsFlux();
            tmp_flot = m_decouverts[0]->getPred()->getFlux();
            m_flot_max+= tmp_flot;

            ///
            for(auto a : m_decouverts)
            {
                if(a->getPred()->getSens() == 1)
                {
                    a->getPred()->setFlot(a->getPred()->getFlot() + tmp_flot);
                    grapheEcart.push_back(a->getPred());
                }

                if(a->getPred()->getSens() == -1)
                {
                    a->getPred()->setFlot(a->getPred()->getFlot() - tmp_flot);
                    a->getPred()->setSens(1);
                    grapheEcart.push_back(a->getPred());
                }
            }

            ///on démarque les sommets
            for(auto s : m_points)
            {
                s->setEtat(0);
            }

            ///on marque les arretes capés
            for(auto a : m_trajets)
            {
                if((a->getSens() == 1)&&(a->getFlot() == a->getCap()))
                {
                    a->setMarque(1);
                }
                if((a->getSens() == -1)&&(a->getFlot() < a->getCap()))
                {
                    a->setMarque(0);
                }
            }

            ///affichage du chemin de flot augmantant
            Point *f = m_points[_final - 1];
            nbChemin++;

            gotoligcol(6 + nbChemin,4);

            if(f->getNum() != Id)
            {
                Point*temp = f;
                while(temp->getNum() != Id)
                {

                    std::cout << "|"<< temp->getNom() << "|<--";
                    temp = temp->getPred()->getS1();
                }
                std::cout << "|" << temp->getNom() << "|";
            }
            else std::cout << " |" << f->getNom() << "|";

            //gotoligcol(8 + nbChemin,4);
            std::cout << "-Flot augmentant : " << tmp_flot ;

        }
        ///on remet les sommets à 0
        resetPoints();

    }
    gotoligcol(10+nbChemin,4);
    std::cout << "Flot max : " << m_flot_max;

    for(auto a : grapheEcart)
        a->setMarque(0);

    /*
    ///tout nettoyer à la fin
    m_decouverts.clear();
    resetPoints();
    resetTrajet();*/
}

///sous graphe partiel pour le flot
void Station::SGP(int ini, int _final)
{
    bool ok = false;

    ///on enlève les puits et les sources naturels autre que ceux que l'on veut garder
    for(auto a : m_trajets)
    {
        ///si le trajet est relié à un puit à enlever
        if((a->getS2()->getAdjacents().empty())&&(a->getS2() != m_points[_final - 1]))
        {
            a->setMarque(1);
            a->getS2()->setEtat(1);

        }
        ///si le trjaet est relié à une source à enlever
        else if((a->getS1()->getEntrants().empty())&&(a->getS2() != m_points[ini - 1]))
        {
            a->setMarque(1);
            a->getS2()->setEtat(1);
        }

    }

    ///on enleve les puits-sources à double sens (comme le sommet 13)
    for(auto s : m_points)
    {
        if((s != m_points[ini - 1])&& (s != m_points[_final - 1]))
        {
            if(s->getEtat() == 0)
            {
                unsigned int compteur = 0;
                int tmp = s->getAdjacents()[0]->getS2()->getNum();

                ///on regarde si tous ses trajets vont aux meme sommet
                for(auto a : s->getAdjacents())
                    if(a->getS2()->getNum() == tmp)
                        compteur++;
                ///si oui, on supprime les trajets retours s'ils existent
                if(compteur == s->getAdjacents().size())
                {
                    for(auto e : s->getEntrants())
                        if(e->getS1()->getNum() == tmp)
                        {
                            e->setMarque(1);
                        }
                }
            }
        }
    }

    ///on enleve les puits et les sources atificiels créés jusqu'a ce qu'il n'en reste plus
    while(!ok)
    {
        ok = true;
        for(auto s : m_points)
        {
            if(( s->getEtat() == 0)&&(s != m_points[ini - 1])&& (s != m_points[_final - 1]))
            {
                unsigned int compteur = 0;

                ///on marque les trajets des puits
                for(auto a : s->getAdjacents())
                    if(a->getMarque() == 1)
                        compteur++;

                if(compteur == s->getAdjacents().size())
                {
                    s->setEtat(1);
                    ok = false;

                    for(auto a : s->getEntrants())
                    {
                        a->setMarque(1);
                    }
                }
                compteur = 0;

                ///on marque les trajets des sources
                for(auto a : s->getEntrants())
                    if(a->getMarque() == 1)
                        compteur++;

                if(compteur == s->getEntrants().size())
                {
                    s->setEtat(1);
                    ok = false;

                    for(auto a : s->getAdjacents())
                    {
                        a->setMarque(1);
                    }
                }
            }
        }
    }

    ///on definit le point initial comme une source et le point final comme un puit en marquant les arretes entrantes et sortantes
    for(auto a : m_points[ini - 1]->getEntrants())
    {
        a->setMarque(1);
    }

    for(auto a : m_points[_final - 1]->getAdjacents())
    {
        a->setMarque(1);
    }

    ///on appelle le programme de calcul des flots
    int chemin;
    FF(ini,_final,chemin);
}

/// Verifie s'il existe un trajet sans remontees
bool Station::trajetSansRemontees(int _final)
{

    bool exist = false;
    for(auto s : m_decouverts)
    {
        if(s->getNum() == _final)
        {
            exist = true;
        }
    }

    return exist;
}


/// Cherche le PCC sans remontees entre le point de depart et le point d'arrivé
void Station::PCCOptimiseRemontees(int Id, int _final)
{
    supprimerToutesRemontee();
    resetPoints();
    cleanDecouverts();
    PCC(Id);
    //0 false - 1 true
    bool trajet = trajetSansRemontees(_final);
    if(trajet == false)
    {
        resetTrajet();
        resetPoints();
        cleanDecouverts();
        PCC(Id);
        affichePred(Id,_final,0);
        color(12,0);
        std::cout << std::endl;
        gotoligcol(9,10);
        std::cout << "Il n'y a pas de trajet avec 0 remontee entre " << Id << " et " << _final << std::endl;
        color(15,0);
    }
    else
    {
        affichePred(Id,_final,0);
    }
}

/// Cherche les PCC qui n'emprunte que les descentes
void Station::PCCOptimiseDescentes(int depart)
{
    supprimerToutesRemontee();
    resetPoints();
    cleanDecouverts();
    PCC(depart);
    affichePCC(depart,0);
}

/// On réinitialise
void Station:: resetTrajet()
{
    for(auto elem : m_trajets)
    {
        elem->setMarque(0);
        elem->setFlot(0);
    }
}

///trouver l'arbre de poids minimal de la station
void Station::kruskal(int max_min)
{
    ///compteurs a nuls
    int nbArretes = 0;
    int i = 0;

    ///trier les arretes par poids croissants
    if(max_min == 0)
    {
        std::sort(m_trajets.begin(), m_trajets.end(), [](Trajet* a1, Trajet* a2)
        {
            return a1->getDistance() < a2->getDistance();
        });
    }
    else if (max_min == 1)
    {
        std::sort(m_trajets.begin(), m_trajets.end(), [](Trajet* a1, Trajet* a2)
        {
            return a1->getDistance() > a2->getDistance();
        });
    }

    //std::cout << "(Numero d'etapes | sommet : numCC )" << std::endl;

    ///tant que le nombre d'arretes parcourues est inferieur a l'ordre - 1
    while(nbArretes < m_ordre - 1)
    {
        Trajet* a = m_trajets[i];

        ///si l'arrete ajoutée ne crée pas de cycle
        if(a->getS1()->getNumCC() != a->getS2()->getNumCC() )
        {
            ///numero de connexité temporaire
            int numCC = a->getS2()->getNumCC();

            ///l'inserer dans l'arbre
            m_arbre.push_back(a);

            ///et changer le numCC de tous les sommets de meme numCC à changer
            for(unsigned int i=0; i< m_points.size(); i++)
            {
                if(m_points[i]->getNumCC() == numCC)
                    m_points[i]->setNumCC(a->getS1()->getNumCC());
            }

            /*
            ///affichage des différentes étapes

            std::cout << " Etape " << nbArretes + 1 << " | ";
            for(auto s : m_points)
            {
                std::cout << s->getId() << " : " << s->getNumCC() << " | ";
            }
            std::cout << std::endl;
            */

            ///augmenter le compteur d'arretes
            nbArretes++;

        }

        ///incrementer i pour passer a l'arrete suivante
        i++;
    }
    std::cout << std::endl;

}

///on affiche le nouvel arbre obtenu
void Station::afficheArbre(int max_min)
{
    int comptPoids = 0 ;
    gotoligcol(2,70);
    if(max_min == 0)
        std::cout << " Arbre de distance minimal : " << std::endl;
    else if(max_min == 1)
        std::cout << " Arbre de distance maximal : " << std::endl;
    gotoligcol(4,1);
    for(auto a : m_arbre)
        a->afficher();
    std::cout << std::endl;

    std::cout << " Distance total : ";
    for(unsigned int i = 0; i < m_arbre.size(); i++)
        if(i == m_arbre.size() - 1 )
        {
            comptPoids += m_arbre[i]->getDistance();
            //std::cout << m_arbre[i]->getDistance() << " = " << comptPoids << " km";
            std::cout << comptPoids << " km";
        }
        else
        {
            comptPoids += m_arbre[i]->getDistance();
            //std::cout << m_arbre[i]->getDistance() << " + ";
        }
    std::cout << std::endl;
    m_arbre.clear();
    resetPoints();



}

///Changer le temps des pistes a partir des valeurs du fichier
void Station::changerTemps(std::vector<std::pair<std::string,int>> pistesdel)
{
    // Parcours du vecteur de pair (type et temps)
    for(auto piste : pistesdel)
    {
        // Vérifie si c'est une piste
        std::string type = piste.first;
        if(type == "V" || type == "B" || type == "R" ||type == "N" || type == "KL" || type == "SURF" ||
                type == "TPH" || type == "TC" || type == "TSD" || type == "TS" || type == "TK")
        {
            // Pour tous les trajets
            for(auto trajet : m_trajets)
            {
                // Si le type du trajet est le meme que celui dont on veut modifier le temps
                if(trajet->getType() == type)
                {
                    // On change le temps avec un produit en croix
                    trajet->setTemps((trajet->getDistance()*piste.second)/100);
                }

            }
        }
        else
        {
            // Si ce n'est pas une piste ou remontees
            std::cout << "Type de piste incorrect ! " << std::endl;
        }


    }
}


///Supprimer les pistes que le skieur ne souhaite pas emprunter
void Station :: chargementGraphePersonnaliseType(std::vector<std::string> delPiste)
{

    for(auto piste : delPiste)
    {
        supprimerPiste(piste);
    }
}

void Station::changerCapacite(float capacite, std::string type)
{
    if(type == "V" || type == "B" || type == "R" ||type == "N" || type == "KL" || type == "SURF")
    {
        for(auto trajet : m_trajets)
        {
            if(trajet->getType() == type)
                trajet->setCap(capacite);
        }
        std::cout << "la capacite a ete modifie " << std::endl;
    }
    else
        std::cout << "Le type de piste saisie n'existe pas !" << std::endl;
}







