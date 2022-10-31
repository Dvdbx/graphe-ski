#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

#include "borne.h"
#include "Trajet.h"
#include "Point.h"
#include "Station.h"
#include <vector>

#define UP 72
#define DOWN 80
#define GAUCHE 75
#define DROITE 77
#define ENTREE 13
#define ESPACE 32
#define ESC 27
#define millieu 70
#define couleur 12
#define FICHIER "data_arcs_update.txt"
///BORNE INTERACTIVE

//On sauvegarde les pistes a eviter
//le temps
void logoLesArcs(int x,int y)
{

    gotoligcol(x,y);
    std::cout<<"     / /    / ____// ___/     /   |   / __ \ / ____// ___/";
    gotoligcol(x+1,y);
    std::cout<<"    / /    / __/   \__ \       / /| |  / /_/ // /     \__ \ ";
    gotoligcol(x+2,y);
    std::cout<<"   / /___ / /___  ___/ /    / ___ | / _, _// /___  ___/ / ";

    gotoligcol(x+3,y);
    std::cout<<"  /_____//_____/ /____/    /_/  |_|/_/ |_| \____/ /____/  ";


}




bool verifPseudo(std::string pseudo)///Verifie si le compte existe ou pas
{
    std::string nomFichier = "skieurs.txt";
    std::ifstream ifs{nomFichier}; ///fichier contenant le pseudo de tous les inscrits
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );


    std::string ligne;
    while(getline(ifs, ligne)) ///Tant qu'on n'est pas à la fin, on lit
    {
        //std::cout << ligne << std::endl;
        if (pseudo == ligne)
        {
            return true;
        }
    }
    return false;
}



bool inscription(std::string &pseudo)
{

    int touche=0,i=1,fin=0;

    while(!fin)
    {
        system("cls");
        afficheBande();
        color(couleur,0);
        gotoligcol(4,millieu);
        std::cout<<"INSCRIPTION";
        color(15,0);
        gotoligcol(6,millieu);
        std::cout<<"Saisissez un pseudo :";
        std::string nomUtilisateur;
        std::cin>>nomUtilisateur;
        ///Verifier qu'il existe pas sinon demander un nv pseudo ou retour au menu
        bool test = verifPseudo(nomUtilisateur);

        if(test == true) ///Le compte exxiste deja
        {
            gotoligcol(7,millieu);
            std::cout<<"Ce compte existe deja, saisissez un nouveau pseudo ou connecter vous a votre compte!";
            touche = 0;
            //sleep(100);
            ///Choix : nv pseudo ou connexion
            while(touche!=ENTREE)
            {


                if(touche == GAUCHE)
                {
                    i++;
                }
                else if (touche == DROITE)
                {
                    i--;
                }
                if(i<1)
                {
                    i=2;
                }
                if(i>2)
                {
                    i=1;
                }

                if(i==1)
                {
                    gotoligcol(10,millieu-10);
                    color(couleur,0);
                    std::cout<<" -Nouveau pseudo  ";
                    color(15,0);
                    gotoligcol(10,millieu+10);
                    std::cout<<"                                                                                                    ";
                    gotoligcol(10,millieu+10);
                    std::cout<<"  Connexion ";

                }
                else if(i==2)
                {
                    gotoligcol(10,millieu-10);
                    std::cout<<"                                                                                                          ";
                    gotoligcol(10,millieu-10);
                    color(15,0);
                    std::cout<<"  Nouveau pseudo ";
                    color(couleur,0);
                    gotoligcol(10,millieu+10);
                    std::cout<<" -Connexion-  " ;
                }

                touche = getch();


            }

            if(i==2)
            {
                return false; /// PAS INSCRIT NI CONNECTE
            }


        }
        else
        {
            system("cls");
            color(couleur,0);
            gotoligcol(4,millieu);
            std::cout<<"Bonjour "<<nomUtilisateur;
            pseudo = nomUtilisateur;

            ///ECRITURE DU NOM DU SKIEUR DANS LE FICHIER
            std::ofstream flux("skieurs.txt", std::ios::app);
            // std::ofstream flux{"skieurs.txt"};
            if (!flux)
                throw std::runtime_error( "Impossible d'ouvrir en lecture skieurs.txt");
            flux<<nomUtilisateur<<std::endl;


            ///ECRITURE DE SON MDP
            nomUtilisateur =  nomUtilisateur+".txt";
            std::ofstream ifs{nomUtilisateur};///fichier du skieur
            if (!ifs)
                throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomUtilisateur);
            color(15,0);
            gotoligcol(7,millieu);
            std::cout<<"Saisissez votre mot de passe : ";
            std::string mdp;
            std::cin>>mdp;
            ifs<<mdp<<std::endl;
            ifs<<"-1"<<std::endl<<"-2";
            gotoligcol(8,millieu);
            std::cout<<"Votre compte a bien ete enregistre";
            touche = getch();
            return true;

        }

    }
    return true;

}


bool connexion(std::string &pseudo)
{
    int fin =0,touche=0,i=1;


    while(!fin)
    {
        system("cls");

        afficheBande();
        color(couleur,0);
        gotoligcol(4,millieu);
        std::cout<<"CONNEXION";
        color(15,0);
        gotoligcol(6,millieu);
        std::cout<<"Saisissez votre pseudo :";
        std::string nomUtilisateur;
        std::cin>>nomUtilisateur;
        ///Verifier qu'il existe pas sinon demander un nv pseudo ou retour au menu
        bool test = verifPseudo(nomUtilisateur);

        if(test == false)
        {
            gotoligcol(7,millieu);
            std::cout<<"Ce compte n'existe pas, saisissez un pseudo existant ou creez un compte!";
            touche = 0;
            //sleep(100);
            ///Choix : pseudo ou inscription
            while(touche!=ENTREE)
            {

                if(touche == GAUCHE)
                {
                    i++;
                }
                else if (touche == DROITE)
                {
                    i--;
                }
                if(i<1)
                {
                    i=2;
                }
                if(i>2)
                {
                    i=1;
                }

                if(i==1)
                {
                    gotoligcol(10,millieu-13);
                    color(couleur,0);
                    std::cout<<" -Ressaisir le pseudo  ";
                    color(15,0);
                    gotoligcol(10,millieu+10);
                    std::cout<<"                                                                                                    ";
                    gotoligcol(10,millieu+10);
                    std::cout<<"  Inscription ";

                }
                else if(i==2)
                {
                    gotoligcol(10,millieu-13);
                    std::cout<<"                                                                                                          ";
                    gotoligcol(10,millieu-13);
                    color(15,0);
                    std::cout<<"  Ressaisir le pseudo ";
                    color(couleur,0);
                    gotoligcol(10,millieu+10);
                    std::cout<<" -Inscription-  " ;
                }

                touche = getch();


            }

            if(i==2)
            {
                return false; /// PAS CONNECTE
            }


        }
        else ///Il se connecte a son compye
        {
            pseudo = nomUtilisateur;
            nomUtilisateur = nomUtilisateur+".txt";
            std::ifstream ifs(nomUtilisateur);
            if (!ifs)
                throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomUtilisateur);
            int tentative = 0;
            std::string mdp; //std::fstream fic(nomUtilisateur);
            std::string mdpLu;
            getline(ifs,mdpLu);
            // std::cout << "ddddhehehe :" << mdpLu << std::endl; //gotoligcol(7,millieu);
            gotoligcol(8,millieu);
            std::cout<<"Saisissez votre mot de passe : ";
            std::cin >> mdp;
            while(mdpLu != mdp && tentative < 3) // Quand false
            {
                tentative++;
                gotoligcol(8,millieu);
                std::cout<<"                                           ";
                gotoligcol(8,millieu);
                std::cout << "Mot de passe incorrect ! Tentative :" << tentative << "/3";
                gotoligcol(9,millieu);
                std::cout << "Erreur de saisie, ressasir : ";
                std::cin >> mdp;
            }
            //std::cout <<"correct" << std::endl;
            //touche = getch();
            if(tentative == 3)
            {
                return false;
            }

            return true;

        }

    }
    return true;


    ///si oui mdp
    ///charger la station
    ///sinon retour au menu


}


std::string menuConnexion() ///Connexion d'un skieur a la borne
{
    curseurOFF();

    int touche,i,choix;
    bool quitter = false;
    std::string pseudo;

    while(!quitter)
    {
        system("cls");
        //logoLesArcs(36,0);
        afficheBande();
        // etoile(10,10);
        gotoligcol(4,70);
        color(couleur,0);
        std::cout<<"  CONNEXION A VOTRE COMPTE  ";
        gotoligcol(8,millieu);
        color(couleur,0);
        std::cout<<" -Connexion-  ";
        gotoligcol(10,millieu);
        color(15,0);
        std::cout<<"  Inscription  ";

        touche =0;

        while(touche!=ENTREE)
        {

            touche = getch();

            if(touche == DOWN)
            {
                i++;
            }
            else if (touche == UP)
            {
                i--;
            }
            if(i<1)
            {
                i=2;
            }
            if(i>2)
            {
                i=1;
            }
            if(i==1)
            {
                gotoligcol(8,millieu);
                color(couleur,0);
                std::cout<<" -Connexion-  ";

                color(15,0);
                gotoligcol(10,millieu);
                std::cout<<"                                                                                                    ";
                gotoligcol(10,millieu);
                std::cout<<"  Inscription ";

            }
            else if(i==2)
            {
                gotoligcol(8,millieu);
                std::cout<<"                                                                                                          ";
                gotoligcol(8,millieu);
                color(15,0);
                std::cout<<"  Connexion ";
                color(couleur,0);
                gotoligcol(10,millieu);
                std::cout<<" -Inscription-  " ;
            }
        }

        choix = i;

        switch(choix)
        {
        case 1:
            system("CLS");
            afficheBande();
            quitter = connexion(pseudo);
            break;

        case 2:
            system("CLS");
            afficheLigne();
            quitter = inscription(pseudo);
            break;


        }

    }


    touche = getch();
    return pseudo;

}

void menu() ///Menu de la borne
{

    gotoligcol(4,0);
    color(12,0);
    std::cout << "Mettre en plein ecran" << std::endl;
    std::cout << "Saisir une touche pour commencer..." << std::endl;
    color(15,0);



    int touche = getch();
    system("CLS");
    std::string pseudo =  menuConnexion(); ///pseudo du skieur sur la borne
    system("cls");


    int choix=1;
    Station g {"data_arcs.txt"};
    g.initialiserDistances();
    g.MAJfichier("data_arcs_update.txt");

    /*
    Station g2 {"data_arcs2.txt"};
    g2.initialiserDistances();
    g2.MAJfichier("data_arcs_update2.txt");
    */

    while(choix!=8)
    {
        system("CLS");
        logoLesArcs(36,0);

        affichage_menu();
        gotoligcol(20,80);

        Sleep(100);
        ChargementPreference(pseudo,g);

        do
        {

            menu2(choix);
            touche = getch();

            switch(touche)
            {
            case 80:
                choix++;
                break;
            case 72:
                choix --;
                break;
            }


            if(choix<1)
            {
                choix = 8;
            }
            else if(choix>8)
            {
                choix = 1;
            }



        }
        while(touche!=13);


        switch(choix)
        {
        case 1:
            system("cls");
            afficherTrajet(g);
            break;

        case 2:
            system("cls");
            affichePoints(g);
            break;

        case 3:

            system("cls");
            optimisation(g);
            g.resetTrajet();

            break;

        case 4:
            system("CLS");
            curseurON();
            menu_PCC(g);
            break;

        case 5:
            curseurON();
            reglage(g,pseudo);

            break;

        case 6:
            //affluenceMax(g);
            system("cls");
            affluence(g);
            //touche = 0;
            break;

        case 7:
            system("cls");
            bonus(g);
            touche = 0;
            break;

        case 8:
            system("CLS");
            choix = 8;
            break;
        case 9:

            break;

        }

    }


}

void affluence(Station g)
{

    system("cls");
    afficheBande();
    int initial,_final,touche = 0, nbChemin;

    gotoligcol(4,millieu);
    color(couleur,0);
    std::cout<<"Calcul du flot max entre deux points";

    gotoligcol(8,65);
    color(15,0);
    std::cout<<"Saisir le numero du point de depart ( 1 - 37 )" << std::endl;
    gotoligcol(10,65);
    while ( ! ( std::cin >> initial ) || initial < 1 || initial > 37)
    {
        std::cerr << "Erreur de saisie, ressasir" << std::endl;
        std::cin.clear();
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    }
    gotoligcol(12,65);
    std::cout<<"Saisir le numero du point d'arrivee ( 1 - 37 )" << std::endl;
    gotoligcol(14,65);
    while ( ! ( std::cin >> _final ) || _final< 1 || _final > 95)
    {
        std::cerr << "Erreur de saisie, ressasir" << std::endl;
        std::cin.clear();
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    }

    while(touche!=0)
    {

    }
    g.FF(initial,_final,nbChemin);
    g.PCCFlot(initial);
    g.affichePredFlot(initial,_final,nbChemin);
    touche = getch();

}



void bonus(Station g)
{
    int touche = 0;
    int i=1;
    int choix;

    gotoligcol(4,70);
    color(couleur,0);
    std::cout<<"  BONUS  ";

    gotoligcol(8,65);
    color(couleur,0);
    std::cout<<" -Arbre de couvrance minimale- ";
    color(15,0);
    gotoligcol(10,65);
    std::cout<<"  Arbre de couvrance maximale  ";


    while(touche!=ENTREE)
    {
        touche = getch();

        if(touche == DOWN)
        {
            i++;
        }
        else if (touche == UP)
        {
            i--;
        }
        if(i<1)
        {
            //i=3;
            i=2;
        }
        if(i>2)
        {
            i=1;
        }

        if(i==1)
        {



            gotoligcol(8,65);
            std::cout<<"                                                                                                    ";
            color(couleur,0);
            gotoligcol(8,65);
            std::cout<<" -Arbre de couvrance minimale- ";
            color(15,0);
            gotoligcol(10,65);
            std::cout<<"  Arbre de couvrance maximale  ";

        }
        else if(i==2)
        {

            color(15,0);
            gotoligcol(8,65);
            std::cout<<" Arbre de couvrance minimale  " ;

            color(couleur,0);
            gotoligcol(10,65);
            std::cout<<" -Arbre de couvrance maximale-           ";
            color(15,0);

        }


    }

    choix = i;



    switch(choix)
    {
    case 1:
        system("CLS");
        afficheLigne();
        g.kruskal(0);
        g.afficheArbre(0);
        touche = getch();

        break;

    case 2:
        system("CLS");
        afficheLigne();
        g.kruskal(1);
        g.afficheArbre(1);


        touche = getch();


        break;


    }

    //touche = getch();

}

bool verifNiveau(std::string niveau)
{
    if(niveau == "N" || niveau == "R" ||niveau == "B" ||niveau == "V")
    {
        return true;
    }
    else
        return false;
}

bool verifRemontees(std::string remontees)
{
    if(remontees == "TPH" || remontees == "TC" || remontees == "TSD" || remontees == "TS" || remontees == "TK" || remontees == "Rien")
    {
        return true;
    }
    else
        return false;
}

void parcoursPerso(Station &g)
{
    int point;
    std::string niveau, remontees;
    float duree;

    system("cls");
    afficheBande();
    gotoligcol(1,2);
    std::cout<<"ESC pour revenir au menu de la borne ";

    gotoligcol(10,65);
    std::cout<<"Choisir le point de depart (1-37)";
    gotoligcol(11,65);
    while ( ! ( std::cin >> point ) || point < 1 || point > 37)
    {
        std::cerr << "Erreur de saisie, ressasir" << std::endl;
        std::cin.clear();
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    }



    system("cls");
    afficheBande();
    gotoligcol(1,2);
    gotoligcol(10,65);
    std::cout<<"Choisir votre niveau (Tres bon : N - Bon : R - Correct : B - Mauvais : V)";
    gotoligcol(11,65);
    std::cin >> niveau;
    while(verifNiveau(niveau) == false)
    {
        std::cerr << "Erreur de saisie, ressasir" << std::endl;
        std::cin >> niveau;
    }


    system("cls");
    afficheBande();
    gotoligcol(1,2);
    gotoligcol(10,65);
    std::cout<<"Choisir le temps pendant lequel vous souhaitez skier (en minutes | 1 -> 600)";
    gotoligcol(11,65);
    while ( ! ( std::cin >> duree ) || duree < 1 || duree > 600)
    {
        std::cerr << "Erreur de saisie, ressasir" << std::endl;
        std::cin.clear();
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    }


    system("cls");
    afficheBande();
    gotoligcol(1,2);
    gotoligcol(10,65);
    std::cout<<"Choisir la remontee a eviter (TPH TC TSD TS TK Rien)";
    gotoligcol(11,65);
    std::cin >> remontees;
    while(verifRemontees(remontees) == false)
    {
        std::cerr << "Erreur de saisie, ressasir" << std::endl;
        std::cin >> remontees;
    }

    g.parcoursPersonnalise(point, niveau, duree, remontees, 0);
}



bool verifPiste(std::string type)
{
    if (type != "V" && type != "B" && type != "R" && type != "N" && type!= "KL" && type != "SURF" && type != "TPH" && type != "TC" && type != "TSD" &&
            type != "TS" && type != "TK")
    {
        return false;
    }
    return true;
}


///Reglage des parametres
void reglage(Station &g,std::string pseudo)
{
    std::string pseudo2 = pseudo;
    std::string mdp;
    std::string temp;
    //int stop=0;
    std::vector<std::string> pistes;
    int temp2;
    std::vector<std::pair<std::string,int>> pistesdel;
    std::pair<std::string,int> pistesdelTemp;

    ///Ouverture du fichier du skieur en lecture
    pseudo = pseudo+".txt";

    std::ifstream ifs(pseudo);
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + pseudo);

    ///LIRE ET STOCKER CE QU'IL Y A DANS LE FICHIER

    ifs>>mdp;
    //std::cout<<mdp;
    while(temp != "-1")
    {
        ifs>>temp;
        if(temp!="-1")
        {
            pistes.push_back(temp);
            // std::cout<<temp<<" ";
        }

    }
    while(temp!="-2")
    {
        ifs>>temp;
        ifs>>temp2;
        if(temp != "-2")
        {
            pistesdelTemp.first = temp;
            pistesdelTemp.second = temp2;
            pistesdel.push_back(pistesdelTemp);
            // std::cout<<temp<<" "<<temp2;
        }
    }


    int touche =0,choix;



    system("cls");
    gotoligcol(1,2);
    std::cout<<"ESC pour revenir au menu de la borne ";
    curseurOFF();
    afficheBande();
    gotoligcol(4,70);
    color(couleur,0);
    std::cout<<"  REGLAGES  ";
    gotoligcol(8,millieu);
    color(couleur,0);
    std::cout<<" -Modifier le temps des trajets-  ";
    gotoligcol(10,millieu);
    color(15,0);
    std::cout<<"  Pistes a eviter  ";
    color(15,0);
    gotoligcol(12,millieu);
    std::cout<<"  Modifier les capacites  ";



    float temps;
    std::string type;
    int i=1;

    while (touche!=ENTREE)///menu
    {

        touche = getch();
        if(touche == DOWN)
        {
            i++;
        }
        else if (touche == UP)
        {
            i--;
        }
        else if(touche == ESC)
        {
            return;

        }
        if(i<1)
        {
            i=3;
        }
        if(i>3)
        {
            i=1;
        }
        if(i==1)
        {
            gotoligcol(8,millieu);
            color(couleur,0);
            std::cout<<" -Modifier le temps des trajets-  ";

            color(15,0);
            gotoligcol(10,millieu);
            std::cout<<"                                                                                                    ";
            gotoligcol(10,millieu);
            std::cout<<"  Pistes a eviter ";
            color(15,0);
            gotoligcol(12,millieu);
            std::cout<<"  Modifier les capacites  ";

        }
        else if(i==2)
        {
            gotoligcol(8,millieu);
            std::cout<<"                                                                                                          ";
            gotoligcol(8,millieu);
            color(15,0);
            std::cout<<"  Modifier le temps des trajets ";
            color(couleur,0);
            gotoligcol(10,millieu);
            std::cout<<" -Pistes a eviter-  " ;
            color(15,0);
            gotoligcol(12,millieu);
            std::cout<<"  Modifier les capacites  ";
        }
        else if(i==3)
        {
            gotoligcol(8,millieu);
            std::cout<<"                                                                                                          ";
            gotoligcol(8,millieu);
            color(15,0);
            std::cout<<"  Modifier le temps des trajets ";

            gotoligcol(10,millieu);
            std::cout<<"  Pistes a eviter  " ;
            color(couleur,0);
            gotoligcol(12,millieu);
            std::cout<<" -Modifier les capacites-  " ;
            color(15,0);
        }
    }


    choix = i;

    std::ofstream flux(pseudo);
    if (!flux)
        throw std::runtime_error( "Impossible d'ouvrir en ecriture " + pseudo);

    switch(choix)
    {
    case 1:
        ///Modification du temps de chaque type de pistes
        system("cls");
        gotoligcol(4,70);
        color(couleur,0);
        std::cout<<"  REGLAGES  ";

        if(pseudo2 == "touchousse")
        {


            gotoligcol(6,millieu-5);
            color(15,0);
            std::cout<<"Modification des temps de trajets";
            color(15,0);
            gotoligcol(7,millieu-5);
            std::cout<<"Saisir le type de piste a modifier :";
            std::cin>>type;

            while (!verifPiste(type))
            {
                gotoligcol(7,millieu-5);
                std::cout<<"                                   ";
                gotoligcol(7,millieu-5);
                std::cout<<"Ce type de piste n'existe pas, resaissir :";
                curseurON();
                gotoligcol(8,millieu-5);
                std::cin>>type;
            }

            gotoligcol(9,millieu-5);
            std::cout<<"Saisir le nouveau temps de parcours pour 100m :";
            std::cin>>temps;


            ///ECRIRE DANS LE FICHIER DU NOM DU JOUEUR
            flux<<mdp<<std::endl;
            for (auto elem : pistes)
            {
                flux<<elem<<std::endl;
            }
            flux<<"-1"<<std::endl;

            for (auto elem : pistesdel)
            {
                flux<<elem.first<<" "<<elem.second<<std::endl;
            }
            ///ECRIRE A LA SUITE
            flux<<type<<" "<<temps<<std::endl;
            flux<<"-2";

            g.parametrageDistance(type,temps); ///calcul des distances
            g.MAJfichier(FICHIER); /// enregistrement des nouvelles valeurs dans le fichier
            gotoligcol(11,millieu-5);
            std::cout<<"Vos changements ont bien ete enregistres";

        }
        else
        {
            flux<<mdp<<std::endl;
            for (auto elem : pistes)
            {
                flux<<elem<<std::endl;
            }
            flux<<"-1"<<std::endl;

            for (auto elem : pistesdel)
            {
                flux<<elem.first<<" "<<elem.second<<std::endl;
            }
            ///ECRIRE A LA SUITE
            //flux<<type<<" "<<temps<<std::endl;
            flux<<"-2";


            gotoligcol(6,millieu);
            color(15,0);
            std::cout<<"Vous n'etes pas M.Touchousse vous ne pouvez pas modifier ses valeurs! ";
        }

        touche = getch();




        break;

    case 2:
        ///Supprimer des types de pistes demandé
        system("CLS");
        gotoligcol(4,70);
        color(couleur,0);
        std::cout<<"  REGLAGES  ";
        gotoligcol(6,millieu-5);
        color(15,0);
        std::cout<<"Saisir le type de piste que vous souhaitez eviter : ";
        color(15,0);
        std::cin>>type;

        while (!verifPiste(type))
        {
            gotoligcol(7,millieu-5);
            std::cout<<"                                   ";
            gotoligcol(7,millieu-5);
            std::cout<<"Ce type de piste n'existe pas, ressaisir :";
            curseurON();
            gotoligcol(8,millieu-5);
            std::cin>>type;
        }



        ///ECRIRE DANS LE FICHIER DU NOM DU JOUEUR
        flux<<mdp<<std::endl;
        for (auto elem : pistes)
        {
            flux<<elem<<std::endl;
        }
        flux<<type<<std::endl;
        flux<<"-1"<<std::endl;

        for (auto elem : pistesdel)
        {
            flux<<elem.first<<" "<<elem.second<<std::endl;
        }
        flux<<"-2";




        gotoligcol(8,millieu-5);
        std::cout<<"Vos changements ont bien ete enregistres";
        touche = getch();


        break;

    case 3 :


        flux<<mdp<<std::endl;
        for (auto elem : pistes)
        {
            flux<<elem<<std::endl;
        }
        flux<<"-1"<<std::endl;

        for (auto elem : pistesdel)
        {
            flux<<elem.first<<" "<<elem.second<<std::endl;
        }
        ///ECRIRE A LA SUITE
        //flux<<type<<" "<<temps<<std::endl;
        flux<<"-2";

        if(pseudo2 == "touchousse")
        {

            modifieCap(g);
        }
        else
        {
            system("cls");
            gotoligcol(4,70);
            color(couleur,0);
            std::cout<<"  REGLAGES  ";
            gotoligcol(6,millieu);
            color(15,0);
            std::cout<<"Vous n'etes pas M.Touchousse vous ne pouvez pas modifier ces valeurs! ";
        }

        touche = getch();




    }


}

///CHOISIR UN POINT ET AFFICHER TOUT LES TRAJETS QUI LUI CORRESPOND
void affichePoints(Station g)
{

    std::vector<Trajet*> trajets = g.getTrajet();
    int touche,point,curseur,curseur2;

    while (touche!=ESC)
    {
        system("cls");
        afficheBande();
        gotoligcol(1,2);
        std::cout<<"ESC pour revenir au menu de la borne ";
        gotoligcol(10,65);
        std::cout<<"Choisir un point (1-37)";
        gotoligcol(11,65);


        while ( ! ( std::cin >> point ) || point < 1 || point > 37)
        {
            std::cerr << "Erreur de saisie, ressaisir" << std::endl;
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }

        touche =0;
        int fin =0;

        while( (touche!=ENTREE)&&(!fin))
        {
            gotoligcol(11,65);
            std::cout<<"       ";
            gotoligcol(10,65);
            std::cout<<"                                 ";
            gotoligcol(10,55);
            std::cout<<"Trajets partant du point "<<g.getPoints()[point-1]->getNom();
            gotoligcol(12,55);
            curseur=0; ///

            for(int i=0; i<95; i++)
            {
                if(trajets[i]->getS1()->getNum() == point)
                {
                    gotoligcol(12+curseur,55);
                    std::cout << trajets[i]->getNum() << ". " << trajets[i]->getNom();
                    curseur++;
                }
            }

            if(curseur==0)
            {
                gotoligcol(12,55);
                std::cout<<"Aucun trajet ne part de ce point";
            }

            gotoligcol(10,105);
            std::cout<<"Trajets arrivant au point "<<g.getPoints()[point-1]->getNom();
            gotoligcol(12,105);
            curseur2=0;
            for(int i=0; i<95; i++)
            {
                if(trajets[i]->getS2()->getNum() == point)
                {
                    gotoligcol(12+curseur2,105);
                    std::cout << trajets[i]->getNum() << ". " << trajets[i]->getNom();
                    curseur2++;
                }
            }
            if(curseur2==0)
            {
                gotoligcol(12,105);
                std::cout<<"Aucun trajet n'arrive a ce point";
            }

            if(curseur<curseur2)
            {
                curseur = curseur2;
            }

            gotoligcol(12 + curseur2 +2,65);
            std::cout << "Pressez entree pour recommencer" << std::endl;
            touche = getch();
            if(touche == ESC)
            {
                return;
            }
        }

        touche=getch();
        if(touche==ESC)
        {
            return;
        }

    }

}


///Choisir un trajet et afficher d'ou il vient et ou il arrive
void afficherTrajet(Station g)
{
    afficheBande();
    int touche;



    gotoligcol(1,2);
    std::cout<<"ESC pour revenir au menu de la borne ";

    std::vector<Trajet*> trajets = g.getTrajet();
    int i=0;

    while (touche!=ESC)
    {
        gotoligcol(10,55);
        std::cout<<"                                                                                               ";
        gotoligcol(10,55);
        color(15,0);
        std::cout<<"Choisir un trajet a l'aide des fleches puis presser entree pour afficher ses informations ";

        gotoligcol(15,80);
        std::cout<<"                                                                                                                                                   ";
        gotoligcol(15,80);
        color(15,0);
        std::cout<< trajets[i]->getNum() << ". " << trajets[i]->getNom();


        touche= getch();
        gotoligcol(15,80);
        std::cout<<"                                                                                      ";
        if(touche == DROITE)
        {
            i++;
        }
        else if (touche == GAUCHE)
        {
            i--;
        }
        else if(touche == ENTREE)
        {
            touche =0;
            while ( (touche!=ENTREE)&&(touche!=ESC) )
            {


                gotoligcol(10,55);
                std::cout<<"                                                                                                                  ";
                gotoligcol(10,65);
                std::cout<<"Information sur le trajet "<<trajets[i]->getNom()<<" :";

                gotoligcol(15,80);
                std::cout<<"                                                                                                                                          ";
                gotoligcol(15,65);
                std::cout<<"Le trajet "<<trajets[i]->getNum() << ". " << trajets[i]->getNom()<<" ("<<trajets[i]->getType()<<") va de "<<trajets[i]->getS1()->getNom()<<" vers "<<trajets[i]->getS2()->getNom()<<" en "<< convertTemps(trajets[i]->getTemps());
                color(15,0);
                gotoligcol(17,65);
                color(8,0);
                std::cout<<"Presser entree pour chosir un autre trajet";
                touche = getch();
                gotoligcol(15,65);
                std::cout<<"                                                                       ";
                gotoligcol(17,65);
                std::cout<<"                                                                       ";

                color(15,0);
            }

        }


        if(i<0)
        {
            i=94;
        }
        else if(i>94)
        {
            i=0;
        }
        gotoligcol(10,80);
        std::cout<<"                                                                           ";
    }


}

void afficheLigne()
{
    char a;

    a = 0xCD;
    color(15,0);
    for(int i=0; i<172; i++)
    {
        gotoligcol(0,i);
        std::cout<<a;
    }
}
///Affichage bande du menu
void afficheBande ()
{
    char a;

    a = 0xCD;
    color(15,0);
    for(int i=0; i<172; i++)
    {
        gotoligcol(0,i);
        std::cout<<a;
    }

    for(int i=0; i<172; i++)
    {
        gotoligcol(40,i);
        std::cout<<a;
    }
}

void affichage_menu() /// AFFICHAGE INTERACTIF DU MENU
{
    char a;
    gotoligcol(38,1);
    color(12,0);
    //std::cout<<"STATION DE SKI LES ARCS";
    color(15,0);

    a = 0xCD;
    color(15,0);
    for(int i=0; i<172; i++)
    {
        gotoligcol(0,i);
        std::cout<<a;
    }

    for(int i=0; i<172; i++)
    {
        gotoligcol(40,i);
        std::cout<<a;
    }

    contour_carte(3,70,15);

    gotoligcol(4,75);
    color(12,0);
    std::cout<<"BORNE INTERACTIVE";

    gotoligcol(8,millieu);
    color(couleur,0);
    std::cout<<" -SELECTIONNER UN TRAJET-  ";
    color(15,0);
    gotoligcol(10,millieu);
    std::cout<<"  ACCEDER A UN POINT  ";
    gotoligcol(12,millieu);
    std::cout<<"  PARCOURS PERSONALISE  ";
    gotoligcol(14,millieu);
    std::cout<<"  AFFICHER UN OU LES PLUS COURTS CHEMINS   ";
    gotoligcol(16,millieu);
    std::cout<<"  REGLAGES  ";
    gotoligcol(18,millieu);
    std::cout<<"  AFFLUENCE MAXIMALE  ";
    gotoligcol(20,millieu);
    std::cout<<"  BONUS  ";
    gotoligcol(22,millieu);
    std::cout<<"  QUITTER  ";
}

void menu2(int position)
{
    switch(position)
    {
    case 1:
        gotoligcol(8,millieu);
        color(couleur,0);
        std::cout<<" -SELECTIONNER UN TRAJET-  ";
        color(15,0);
        gotoligcol(10,millieu);
        std::cout<<"  ACCEDER A UN POINT  ";
        gotoligcol(12,millieu);
        std::cout<<"  PARCOURS PERSONALISE  ";
        gotoligcol(14,millieu);
        std::cout<<"  AFFICHER UN OU LES PLUS COURTS CHEMINS   ";
        gotoligcol(16,millieu);
        std::cout<<"  REGLAGES  ";
        gotoligcol(18,millieu);
        std::cout<<"  AFFLUENCE MAXIMALE ";
        gotoligcol(20,millieu);
        std::cout<<"  BONUS  ";
        gotoligcol(22,millieu);
        std::cout<<"  QUITTER  ";
        break;


    case 2:
        gotoligcol(8,millieu);
        std::cout<<"  SELECTIONNER UN TRAJET  ";
        gotoligcol(10,millieu);
        color(couleur,0);
        std::cout<<" -ACCEDER A UN POINT-  ";
        gotoligcol(12,millieu);
        color(15,0);
        std::cout<<"  PARCOURS PERSONALISE ";
        gotoligcol(14,millieu);
        std::cout<<"  AFFICHER UN OU LES PLUS COURTS CHEMINS   ";
        gotoligcol(16,millieu);
        std::cout<<"  REGLAGES  ";
        gotoligcol(18,millieu);
        std::cout<<"  AFFLUENCE MAXIMALE ";
        gotoligcol(20,millieu);
        std::cout<<"  BONUS  ";
        gotoligcol(22,millieu);
        std::cout<<"  QUITTER  ";
        break;
    case 3:
        gotoligcol(8,millieu);
        color(15,0);
        std::cout<<"  SELECTIONNER UN TRAJET  ";
        gotoligcol(10,millieu);
        std::cout<<"  ACCEDER A UN POINT  ";
        gotoligcol(12,millieu);
        color(couleur,0);
        std::cout<<" -PARCOURS PERSONALISE-  ";
        color(15,0);
        gotoligcol(14,millieu);
        std::cout<<"  AFFICHER UN OU LES PLUS COURTS CHEMINS   ";
        gotoligcol(16,millieu);
        std::cout<<"  REGLAGES  ";
        gotoligcol(18,millieu);
        gotoligcol(18,millieu);
        std::cout<<"  AFFLUENCE MAXIMALE ";
        gotoligcol(20,millieu);
        std::cout<<"  BONUS  ";
        gotoligcol(22,millieu);
        std::cout<<"  QUITTER  ";
        break;
    case 4:
        gotoligcol(8,millieu);
        color(15,0);
        std::cout<<"  SELECTIONNER UN TRAJET  ";
        gotoligcol(10,millieu);
        std::cout<<"  ACCEDER A UN POINT  ";
        gotoligcol(12,millieu);
        std::cout<<"  PARCOURS PERSONALISE ";
        gotoligcol(14,millieu);
        color(couleur,0);
        std::cout<<" -AFFICHER UN OU LES PLUS COURTS CHEMINS-   ";
        color(15,0);
        gotoligcol(16,millieu);
        std::cout<<"  REGLAGES  ";
        gotoligcol(18,millieu);
        std::cout<<"  AFFLUENCE MAXIMALE  ";
        gotoligcol(20,millieu);
        std::cout<<"  BONUS  ";
        gotoligcol(22,millieu);
        std::cout<<"  QUITTER  ";
        break;
    case 5:
        gotoligcol(8,millieu);
        color(15,0);
        std::cout<<"  SELECTIONNER UN TRAJET  ";
        gotoligcol(10,millieu);
        std::cout<<"  ACCEDER A UN POINT  ";
        gotoligcol(12,millieu);
        std::cout<<"  PARCOURS PERSONALISE  ";
        gotoligcol(14,millieu);
        std::cout<<"  AFFICHER UN OU LES PLUS COURTS CHEMINS   ";
        gotoligcol(16,millieu);
        color(couleur,0);
        std::cout<<" -REGLAGES-  ";
        color(15,0);
        gotoligcol(18,millieu);
        std::cout<<"  AFFLUENCE MAXIMALE ";
        gotoligcol(20,millieu);
        std::cout<<"  BONUS  ";
        gotoligcol(22,millieu);
        std::cout<<"  QUITTER  ";
        break;
    case 6:
        gotoligcol(8,millieu);
        color(15,0);
        std::cout<<"  SELECTIONNER UN TRAJET  ";
        gotoligcol(10,millieu);
        std::cout<<"  ACCEDER A UN POINT  ";
        gotoligcol(12,millieu);
        std::cout<<"  PARCOURS PERSONALISE  ";
        gotoligcol(14,millieu);
        std::cout<<"  AFFICHER UN OU LES PLUS COURTS CHEMINS   ";
        gotoligcol(16,millieu);
        std::cout<<"  REGLAGES  ";
        gotoligcol(18,millieu);
        color(couleur,0);
        std::cout<<" -AFFLUENCE MAXIMALE-  ";
        color(15,0);
        gotoligcol(20,millieu);
        std::cout<<"  BONUS  ";
        gotoligcol(22,millieu);
        std::cout<<"  QUITTER  ";
        break;
    case 7:
        gotoligcol(8,millieu);
        color(15,0);
        std::cout<<"  SELECTIONNER UN TRAJET  ";
        gotoligcol(10,millieu);
        std::cout<<"  ACCEDER A UN POINT  ";
        gotoligcol(12,millieu);
        std::cout<<"  PARCOURS PERSONALISE  ";
        gotoligcol(14,millieu);
        std::cout<<"  AFFICHER UN OU LES PLUS COURTS CHEMINS   ";
        gotoligcol(16,millieu);
        std::cout<<"  REGLAGES  ";
        gotoligcol(18,millieu);

        std::cout<<"  AFFLUENCE MAXIMALE  ";
        color(couleur,0);
        gotoligcol(20,millieu);
        std::cout<<" -BONUS- ";
        color(15,0);
        gotoligcol(22,millieu);
        std::cout<<"  QUITTER  ";
        color(15,0);
        break;
    case 8:
        gotoligcol(8,millieu);
        color(15,0);
        std::cout<<"  SELECTIONNER UN TRAJET  ";
        gotoligcol(10,millieu);
        std::cout<<"  ACCEDER A UN POINT  ";
        gotoligcol(12,millieu);
        std::cout<<"  PARCOURS PERSONALISE  ";
        gotoligcol(14,millieu);
        std::cout<<"  AFFICHER UN OU LES PLUS COURTS CHEMINS   ";
        gotoligcol(16,millieu);
        std::cout<<"  REGLAGES  ";
        gotoligcol(18,millieu);
        std::cout<<"  AFFLUENCE MAXIMALE  ";
        gotoligcol(20,millieu);
        std::cout<<"  BONUS   ";
        color(couleur,0);
        gotoligcol(22,millieu);
        std::cout<<" -QUITTER-  ";
        color(15,0);


    }
}

void menu_PCC(Station g)
{
    int touche = 0;
    int i=1;
    int choix;
    int initial;
    int _final;

    afficheBande();

    gotoligcol(4,70);
    color(couleur,0);
    std::cout<<"Afficher un ou les plus courts chemins ";
    gotoligcol(8,65);
    color(couleur,0);
    std::cout<<" -Afficher tous les plus courts chemins pour aller a un point ( en temps )- ";
    gotoligcol(10,65);
    color(15,0);
    std::cout<<" Afficher le plus court chemin entre deux points ( en temps )";
    gotoligcol(12,65);
    std::cout<<" Afficher tous les plus courts chemins pour aller a un point ( en nombre d'arcs )";
    gotoligcol(14,65);
    std::cout<<" Afficher le plus court chemin entre deux points ( en nombre d'arcs )";

    while(touche!=ENTREE)
    {
        touche = getch();

        if(touche == DOWN)
        {
            i++;
        }
        else if (touche == UP)
        {
            i--;
        }

        if(i<1)
        {
            i=4;
        }
        if(i>4)
        {
            i=1;
        }

        if(i==1)
        {
            gotoligcol(8,65);
            color(couleur,0);
            std::cout<<" -Afficher tous les plus courts chemins pour aller a un point ( en temps )- ";

            color(15,0);
            gotoligcol(10,65);
            std::cout<<"                                                                                                    ";

            gotoligcol(10,65);
            std::cout<<" Afficher le plus court chemin entre deux points ( en temps )";

            gotoligcol(12,65);
            std::cout<<" Afficher tous les plus courts chemins pour aller a un point ( en nombre d'arcs )";

            gotoligcol(14,65);
            std::cout<<"                                                                                    ";
            gotoligcol(14,65);
            std::cout<<" Afficher le plus court chemin entre deux points ( en nombre d'arcs )";

        }
        else if(i==2)
        {
            gotoligcol(8,65);
            std::cout<<"                                                                                                          ";

            gotoligcol(8,65);
            color(15,0);
            std::cout<<" Afficher tous les plus courts chemins pour aller a un point ( en temps )- ";

            color(couleur,0);
            gotoligcol(10,65);
            std::cout<<" -Afficher le plus court chemin entre deux points ( en temps )-  " ;

            color(15,0);
            gotoligcol(12,65);
            std::cout<<" Afficher tous les plus courts chemins pour aller a un point ( en nombre d'arcs )";

            color(15,0);
            gotoligcol(14,65);
            std::cout<<"                                                                                    ";
            gotoligcol(14,65);
            std::cout<<" Afficher le plus court chemin entre deux points ( en nombre d'arcs )";

        }
        else if(i==3)
        {

            gotoligcol(8,65);
            color(15,0);
            std::cout<<" Afficher tous les plus courts chemins pour aller a un point ( en temps )- ";

            gotoligcol(10,65);
            std::cout<<" Afficher le plus court chemin entre deux points ( en temps )           " ;

            gotoligcol(12,65);
            std::cout<<"                                                                                                          ";

            color(couleur,0);
            gotoligcol(12,65);
            std::cout<<" -Afficher tous les plus courts chemins pour aller a un point ( en nombre d'arcs )- ";

            color(15,0);
            gotoligcol(14,65);
            std::cout<<"                                                                                    ";
            gotoligcol(14,65);
            std::cout<<" Afficher le plus court chemin entre deux points ( en nombre d'arcs )";

        }
        else if(i==4)
        {

            gotoligcol(8,65);
            color(15,0);
            std::cout<<" Afficher tous les plus courts chemins pour aller a un point ( en temps )-      ";

            gotoligcol(10,65);
            std::cout<<" Afficher le plus court chemin entre deux points ( en temps )                           " ;

            gotoligcol(12,65);
            std::cout<<" Afficher tous les plus courts chemins pour aller a un point ( en nombre d'arcs )   ";

            gotoligcol(14,65);
            std::cout<<"                                                                                                            ";

            color(couleur,0);
            gotoligcol(14,65);
            std::cout<<" -Afficher le plus court chemin entre deux points ( en nombre d'arcs )-";

        }

    }

    choix = i;

    /* while ( ! ( std::cin >> choix ) || choix < 1 || choix > 2 )
     {
         std::cerr << "ERREUR DE SAISIE, RESSASIR" << std::endl;;
         std::cin >> choix;
         std::cin.clear(); // effacer les bits d'erreurs
         std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' ); // supprimer la ligne erronée dans le buffer

     }*/

    switch(choix)
    {
    case 1:
        system("CLS");
        gotoligcol(4,60);
        color(couleur,0);
        std::cout<<"Afficher tous les plus courts pour acceder a un point ( en temps ) ";
        gotoligcol(8,65);
        color(15,0);
        std::cout<<"Saisir le numero du point de depart ( 1 - 37 )";

        gotoligcol(10,65);
        while ( ! ( std::cin >> initial ) || initial < 1 || initial > 37)
        {
            gotoligcol(11,65);
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear(); // effacer les bits d'erreurs
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            gotoligcol(10,65);
        }
        system("CLS");
        //afficheBande();

        /// nettoyer tous les predecesseurs de tous les points
        g.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        g.cleanDecouverts();

        g.PCC(initial);
        g.affichePCC(initial,0);

        /// nettoyer tous les predecesseurs de tous les points
        g.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        g.cleanDecouverts();


        break;

    case 2:
        system("CLS");
        afficheBande();
        gotoligcol(4,60);
        color(12,0);
        std::cout<<"Afficher l'itineraire le plus court entre deux points ( en temps ) ";
        gotoligcol(8,65);
        color(15,0);
        std::cout<<"Saisir le numero du point de depart ( 1 - 37 )" << std::endl;
        gotoligcol(10,65);
        while ( ! ( std::cin >> initial ) || initial < 1 || initial > 37)
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
        gotoligcol(12,65);
        std::cout<<"Saisir le numero du point d'arrivee ( 1 - 37 )" << std::endl;
        gotoligcol(14,65);
        while ( ! ( std::cin >> _final ) || _final< 1 || _final > 95)
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
        system("CLS");

        /// nettoyer tous les predecesseurs de tous les points
        g.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        g.cleanDecouverts();

        g.PCC(initial);
        g.affichePred(initial,_final,0);

        /// nettoyer tous les predecesseurs de tous les points
        g.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        g.cleanDecouverts();

        break;

    case 3:
        system("CLS");
        gotoligcol(4,60);
        color(couleur,0);
        std::cout<<"Afficher tous les plus courts pour acceder a un point ( en nombre d'arcs )";
        gotoligcol(8,65);
        color(15,0);
        std::cout<<"Saisir le numero du point de depart ( 1 - 37 )";

        gotoligcol(10,65);
        while ( ! ( std::cin >> initial ) || initial < 1 || initial > 37)
        {
            gotoligcol(11,65);
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear(); // effacer les bits d'erreurs
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            gotoligcol(10,65);
        }
        system("CLS");
        //afficheBande();

        /// nettoyer tous les predecesseurs de tous les points
        g.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        g.cleanDecouverts();

        g.BFS(initial);
        g.affichePCC(initial,1);

        /// nettoyer tous les predecesseurs de tous les points
        g.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        g.cleanDecouverts();

        break;

    case 4:
        system("CLS");
        afficheBande();
        gotoligcol(4,60);
        color(12,0);
        std::cout<<"Afficher l'itineraire le plus court entre deux points ( en nombre d'arcs ) ";
        gotoligcol(8,65);
        color(15,0);
        std::cout<<"Saisir le numero du point de depart ( 1 - 37 )" << std::endl;
        gotoligcol(10,65);
        while ( ! ( std::cin >> initial ) || initial < 1 || initial > 37)
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
        gotoligcol(12,65);
        std::cout<<"Saisir le numero du point d'arrivee ( 1 - 37 )" << std::endl;
        gotoligcol(14,65);
        while ( ! ( std::cin >> _final ) || _final< 1 || _final > 95)
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
        system("CLS");

        /// nettoyer tous les predecesseurs de tous les points
        g.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        g.cleanDecouverts();

        g.BFS(initial);
        g.affichePred(initial,_final,1);

        /// nettoyer tous les predecesseurs de tous les points
        g.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        g.cleanDecouverts();

        break;

    }
    /*
    /// nettoyer tous les predecesseurs de tous les points
    g.resetPoints();

    ///nettoyer le vecteur des sommets découverts
    g.cleanDecouverts();
    */
    touche = getch();

}

void optimisation(Station graphe) ///PARCOURS PERSONNALISE EN FONCTION DES ENVIES ET DU NIVEAU DU SKIEUR
{
    system("cls");
    afficheBande();

    gotoligcol(5,millieu);
    color(couleur,0);
    std::cout<<"Parcours personnalise";
    gotoligcol(8,millieu);
    color(15,0);
    std::cout<<" Eviter un type de piste (temps) ";
    color(15,0);
    gotoligcol(10,millieu);
    std::cout<<"                                                                                                    ";
    gotoligcol(10,millieu);
    std::cout<<"  Personnaliser un trajet (en temps et en type) ";

    gotoligcol(12,millieu);
    std::cout<<"  Eviter un type de piste (nombre d'arcs) ";

    gotoligcol(14,millieu);
    std::cout<<"  Limiter les remontees ";

    gotoligcol(16,millieu);
    std::cout<<"  Accroitre les descentes ";

    int touche,i,choix;
    std::string delRemontee;

    while(touche!=ENTREE) ///menu
    {

        touche = getch();
        if(touche == DOWN)
        {
            i++;
        }
        else if (touche == UP)
        {
            i--;
        }
        if(i<1)
        {
            i=5;
        }
        if(i>5)
        {
            i=1;
        }
        if(i==1)
        {
            gotoligcol(8,millieu);
            color(couleur,0);
            std::cout<<" -Eviter un type de piste (temps)-  ";
            color(15,0);
            gotoligcol(10,millieu);
            std::cout<<"                                                                                                    ";
            gotoligcol(10,millieu);
            std::cout<<"  Personnaliser un trajet (en temps et en type) ";
            gotoligcol(12,millieu);
            std::cout<<"  Eviter un type de piste (nombre d'arcs) ";
            gotoligcol(14,millieu);
            std::cout<<"  Limiter les remontees ";

            gotoligcol(16,millieu);
            std::cout<<"  Accroitre les descentes ";

        }
        else if(i==2)
        {
            gotoligcol(8,millieu);
            std::cout<<"                                                                                                          ";
            gotoligcol(8,millieu);
            color(15,0);
            std::cout<<"  Eviter un type de piste (temps)";
            color(couleur,0);
            gotoligcol(10,millieu);
            std::cout<<" -Personnaliser un trajet (en temps et en type)-  " ;
            gotoligcol(12,millieu);
            color(15,0);
            std::cout<<"  Eviter un type de piste (nombre d'arcs) ";
            gotoligcol(14,millieu);
            std::cout<<"  Limiter les remontees ";

            gotoligcol(16,millieu);
            std::cout<<"  Accroitre les descentes ";
        }
        else if(i==3)
        {
            gotoligcol(8,millieu);
            std::cout<<"                                                                                                          ";
            gotoligcol(8,millieu);
            color(15,0);
            std::cout<<"  Eviter un type de piste (temps)";
            color(15,0);
            gotoligcol(10,millieu);
            std::cout<<"                                                                                                          ";
            gotoligcol(10,millieu);
            std::cout<<"  Personnaliser un trajet (en temps et en type)  " ;
            color(couleur,0);
            gotoligcol(12,millieu);
            std::cout<<" -Eviter un type de piste (nombre d'arcs)- ";


        }
        else if(i==4)
        {
            gotoligcol(8,millieu);
            std::cout<<"                                                                                                          ";
            gotoligcol(8,millieu);
            color(15,0);
            std::cout<<"  Eviter un type de piste (temps)";
            color(15,0);
            gotoligcol(10,millieu);
            std::cout<<"                                                                                                          ";
            gotoligcol(10,millieu);
            std::cout<<"  Personnaliser un trajet (en temps et en type)  " ;
            color(15,0);
            gotoligcol(12,millieu);
            std::cout<<"  Eviter un type de piste (nombre d'arcs) ";
            color(15,0);
            gotoligcol(14,millieu);
            std::cout<<"                                                                                                          ";
            gotoligcol(14,millieu);
            color(couleur,0);
            std::cout<<" -Limiter les remontees- ";
            color(15,0);

            gotoligcol(16,millieu);
            color(15,0);
            std::cout<<"  Accroitre les descentes ";
            color(15,0);

        }
        else if(i==5)
        {
            gotoligcol(8,millieu);
            std::cout<<"                                                                                                          ";
            gotoligcol(8,millieu);
            color(15,0);
            std::cout<<"  Eviter un type de piste (temps)";
            color(15,0);
            gotoligcol(10,millieu);
            std::cout<<"                                                                                                          ";
            gotoligcol(10,millieu);
            std::cout<<"  Personnaliser un trajet (en temps et en type)  " ;
            color(15,0);
            gotoligcol(12,millieu);
            std::cout<<"  Eviter un type de piste (nombre d'arcs) ";
            gotoligcol(14,millieu);
            std::cout<<"  Limiter les remontees ";
            gotoligcol(16,millieu);
            std::cout<<"                                                                                                          ";
            gotoligcol(16,millieu);
            color(couleur,0);
            std::cout<<" -Accroitre les descentes- ";

        }
    }

    choix = i;

    switch(choix)
    {
    case 1 : ///Supprimer un type de piste dans le parcour
        system("cls");
        afficheBande();
        gotoligcol(5,millieu);

        std::cout << "Quelle piste souhaitez vous eviter ? ";
        std::cin >> delRemontee;

        while(!verifPiste(delRemontee))
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin >> delRemontee;
        }

        graphe.supprimerPiste(delRemontee);

        gotoligcol(7,millieu);
        color(15,0);
        int initial,_final;
        std::cout<<"Saisir le numero du point de depart ( 1 - 37 )" << std::endl;
        gotoligcol(10,65);
        while ( ! ( std::cin >> initial ) || initial < 1 || initial > 37)
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
        gotoligcol(12,65);
        std::cout<<"Saisir le numero du point d'arrivee ( 1 - 37 )" << std::endl;
        gotoligcol(14,65);
        while ( ! ( std::cin >> _final ) || _final< 1 || _final > 37)
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }

        system("cls");

        /// nettoyer tous les predecesseurs de tous les points
        graphe.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        graphe.cleanDecouverts();

        graphe.PCC(initial);
        //graphe.affichePred(initial,_final,0);
        graphe.affichePCC(initial,0);


        /// nettoyer tous les predecesseurs de tous les points
        graphe.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        graphe.cleanDecouverts();

        touche = 0;
        touche = getch();

        while(touche ==0)
        {
            touche = getch();
        }

        break;

    case 2:

        system("CLS");
        afficheLigne();
        parcoursPerso(graphe);
        ///g.parcoursPersonnalise();
        touche = getch();
        break;

    case 3:

        system("cls");
        afficheBande();
        gotoligcol(5,millieu);

        std::cout << "Quelle piste souhaitez vous eviter ? ";
        std::cin >> delRemontee;

        while(!verifPiste(delRemontee))
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin >> delRemontee;
        }

        graphe.supprimerPiste(delRemontee);

        gotoligcol(7,millieu);
        color(15,0);
        std::cout<<"Saisir le numero du point de depart ( 1 - 37 )" << std::endl;
        gotoligcol(10,65);
        while ( ! ( std::cin >> initial ) || initial < 1 || initial > 37)
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
        gotoligcol(12,65);
        std::cout<<"Saisir le numero du point d'arrivee ( 1 - 37 )" << std::endl;
        gotoligcol(14,65);
        while ( ! ( std::cin >> _final ) || _final< 1 || _final > 37)
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }

        system("cls");

        /// nettoyer tous les predecesseurs de tous les points
        graphe.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        graphe.cleanDecouverts();

        graphe.BFS(initial);
        graphe.affichePCC(initial,1);

        /// nettoyer tous les predecesseurs de tous les points
        graphe.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        graphe.cleanDecouverts();

        touche = 0;
        touche = getch();
        /*
        while(touche ==0)
        {
            touche = getch();
        }*/

        break;

    case 4:

        system("cls");
        afficheBande();

        gotoligcol(7,millieu);
        color(15,0);
        std::cout<<"Saisir le numero du point de depart ( 1 - 37 )" << std::endl;
        gotoligcol(10,65);
        while ( ! ( std::cin >> initial ) || initial < 1 || initial > 37)
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
        gotoligcol(12,65);
        std::cout<<"Saisir le numero du point d'arrivee ( 1 - 37 )" << std::endl;
        gotoligcol(14,65);
        while ( ! ( std::cin >> _final ) || _final< 1 || _final > 37)
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }

        system("cls");

        /// nettoyer tous les predecesseurs de tous les points
        graphe.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        graphe.cleanDecouverts();

        graphe.PCCOptimiseRemontees(initial, _final);

        /// nettoyer tous les predecesseurs de tous les points
        graphe.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        graphe.cleanDecouverts();

        touche = getch();
        break;

    case 5:
        system("cls");
        afficheBande();


        gotoligcol(7,millieu);
        color(15,0);
        std::cout<<"Saisir le numero du point de depart ( 1 - 37 )" << std::endl;
        gotoligcol(10,65);
        while ( ! ( std::cin >> initial ) || initial < 1 || initial > 37)
        {
            std::cerr << "Erreur de saisie, ressasir" << std::endl;
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }

        system("cls");

        /// nettoyer tous les predecesseurs de tous les points
        graphe.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        graphe.cleanDecouverts();

        graphe.PCCOptimiseDescentes(initial);

        /// nettoyer tous les predecesseurs de tous les points
        graphe.resetPoints();
        ///nettoyer le vecteur des sommets découverts
        graphe.cleanDecouverts();

        touche = getch();
        break;
    }
}

void contour_carte(int x,int y,int col)
{
    char c;
    color(col,0);
    gotoligcol(x, y+1);
    c=0xC9;
    std::cout << c;
    gotoligcol(x, y+25);
    c=0xBB;
    std::cout << c;
    gotoligcol(x+2, y+1);
    c=0xC8;
    std::cout << c;
    gotoligcol(x+2, y+25);
    c=0xBC;
    std::cout << c;
    c=0xCD;

    for (int i=0; i<23; i++)
    {
        gotoligcol(x,y+i+2);
        std::cout <<c;

    }


    for (int i=0; i<23; i++)
    {
        gotoligcol(x+2,y+i+2);
        std::cout <<c;

    }

    c=0xBA;
    for (int i=0; i<1; i++)
    {
        gotoligcol(x+1+i, y+1);
        std::cout <<c;
        gotoligcol(x+1+i, y+25);
        std::cout <<c;
    }
    gotoligcol(x+3,y+23);
}

///Chargement des preference du skieur a partir de son fichier
void ChargementPreference(std::string pseudo,Station g)
{

    std::string mdp;
    std::string temp;
    std::vector<std::string> pistes;
    int temp2;
    std::vector<std::pair<std::string,int>> pistesdel;
    std::pair<std::string,int> pistesdelTemp;

    ///Ouverture du fichier du skieur en lecture
    pseudo = pseudo+".txt";
    std::ifstream ifs(pseudo);
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + pseudo);

    ///LIRE ET STOCKER CE QU'IL Y A DANS LE FICHIER

    ifs>>mdp;
    // std::cout<<mdp;
    while(temp != "-1")
    {
        ifs>>temp;
        if(temp!="-1")
        {
            pistes.push_back(temp);

        }

    }

    while(temp!="-2")
    {
        ifs>>temp;
        ifs>>temp2;
        if(temp != "-2")
        {
            pistesdelTemp.first = temp;
            pistesdelTemp.second = temp2;
            pistesdel.push_back(pistesdelTemp);

        }
    }
    ///Supprimer les pistes que le skieur ne souhaite pas utilise:
    g.chargementGraphePersonnaliseType(pistes);


    ///CHARGER LES NV VALEURS DE TEMPS MODIFIER PAR M.TOUCHOUSSE :


    ///Ouverture du fichier de M.Touchousse en lecture
    pseudo = "touchousse.txt";

    std::ifstream flux(pseudo);
    if (!flux)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + pseudo);

    ///LIRE ET STOCKER CE QU'IL Y A DANS LE FICHIER

    flux>>mdp;
    while(temp != "-1")
    {
        flux>>temp;
        if(temp!="-1")
        {
            pistes.push_back(temp);

        }

    }

    while(temp!="-2")
    {
        flux>>temp;
        flux>>temp2;
        if(temp != "-2")
        {
            pistesdelTemp.first = temp;
            pistesdelTemp.second = temp2;
            pistesdel.push_back(pistesdelTemp);

        }
    }


    g.changerTemps(pistesdel);
}

void modifieCap(Station g) ///modifier les capacités
{
    system("cls");
    afficheBande();
    int cap,touche = 0, nbChemin;
    std::string _type;

    gotoligcol(4,millieu);
    color(couleur,0);

    std::cout<<"Modifications des capacites" << std::endl;

    gotoligcol(8,65);
    color(15,0);
    std::cout<<"Quel type de capacites a modifier ? (N,V,R,BKL,SURF)" << std::endl;
    gotoligcol(10,65);
    std::cin >> _type;

    gotoligcol(12,65);
    std::cout << "Saisir la capacite ( 100 - 1000 )" << std::endl;
    gotoligcol(14,65);
    while ( ! ( std::cin >> cap ) || cap < 100 || cap > 1000)
    {
        std::cerr << "Erreur de saisie, ressasir" << std::endl;
        std::cin.clear();
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    };

    g.changerCapacite(cap, _type);

    while(touche!=0)
    {

    }
    //touche = getch();
}
