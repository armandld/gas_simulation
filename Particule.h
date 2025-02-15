#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <list>
#include "Vecteur3D.h"
#include "Dessinable.h"
#include "Enceinte.h"
#include "GenerateurAleatoire.h"
#include "SupportADessin.h"


class Particule : public Dessinable{

    private:

        // méthode intermédiaire pour rencontre_paroi
        void surface(coord O,double dimension_enceinte,SupportADessin&);

        //méthode intermédiaire pour actualise
        double tirage_gauss(GenerateurAleatoire& tirage,
                                            double temp)const;

    protected:

        //Attributs
        Vecteur3D pos;
        Vecteur3D v;
        const double m;
        const std::string nom;

        //Attributs de classe
        static unsigned int nb_particules;

        static bool affichageTrace;

        static bool affichageCouleur;

        virtual std::string affiche_nom() const;

    public:

        //Constructeurs, constructeur de copie, destructeur et méthode init (tirage des position et vitesses)
        Particule(Vecteur3D pos, Vecteur3D v, const double m);

        Particule();

        Particule(Particule const& autre);

        virtual ~Particule(){--nb_particules;}

     /* Méthode permettant d'attribuer des positions
        et des vitesses aléatoires à la particule */
        virtual void init(GenerateurAleatoire& tirage,
                          Enceinte const& e,double const temp);



        //Getters
        const Vecteur3D& getPos() const {return pos;}

        const Vecteur3D& getV() const {return v;}

        bool getCouleur() const {return affichageCouleur;}

        bool getTrace() const {return affichageTrace;}


        //Méthodes pour modifier l'affichage des particules dans OpenGL
        void changeCouleur(){affichageCouleur = !affichageCouleur;}

        void changeTrace(){affichageTrace = !affichageTrace;}


     /* Méthodes nécessaires au polymorphisme des modèles de collision
        Etant donné qu'elles sont propres aux particules intelligentes
        ou traçables impliquent que leur usage en tant que simple
        particule serait une erreur (utilisation de throw) */

        virtual Coordonnees getKase() const;

        virtual void set_kase(Coordonnees const& v);

        virtual std::list<Vecteur3D> getMemoire() const;


        //Test de proximité entre deux particules
        bool proximite(Particule const& autre, double pas_espace) const;


        //Méthodes d'affichage
        void afficher(std::ostream&)const;

        void dessine_sur(SupportADessin& support) const override
        { support.dessine(*this); }



        //Méthodes de l'évolution de la particule
        virtual void evolue(double);

        void rencontre_particule(Particule&,double epsilon,
                                 GenerateurAleatoire& tirage,
                                 bool premier_tirage = false);

        void rencontre_paroi(const Enceinte&,SupportADessin&);

        //Méthodes nécessaires à la conception de collections hétérogènes et homogènes
        virtual std::unique_ptr<Particule> copie() const;

        virtual std::unique_ptr<Particule> copie_intelligente() const;

        virtual std::unique_ptr<Particule> copie_tracable() const;

        virtual std::unique_ptr<Particule> copie_TI() const;

};

std::ostream& operator<<(std::ostream& sortie,Particule const& p);

//une particule intelligente est propre au système intelligent
class Intelligente: public virtual  Particule{

    protected:

        // Elle connaît notamment sa case:
        Coordonnees kase;

    public:

        //Constructeurs
        Intelligente(Particule const& p);

        Intelligente();

        //Getter
        Coordonnees getKase() const override{return kase;}

        //Setter, nécessaire pour paramétrer la case depuis l'évolution du système
        void set_kase(Coordonnees const& v)override
        {kase = v;}
};

//classe des particules traçables
class Tracable: public virtual Particule{

protected:

        //Elles connaissent leur ancienne position
        std::list<Vecteur3D> memoire;

        //Attribut représnentant le nombre de points maximal qui composent la trace
        static constexpr size_t taille_trace = 1000;

    public:

        //Constructeurs
        Tracable();

        Tracable(Particule const& p);

        //Getter
        std::list<Vecteur3D> getMemoire() const override
        {return memoire;}

        //Méthode qui actualise le vector mémoire
        void evolue(double dt) override;
};

class TI: public Tracable, public Intelligente{ //classe des particules à la fois intelligentes et traçable

    public:

        //Constructeurs
        TI():
        Particule(),Tracable(),Intelligente(){}

        TI(Particule const& p):
        Particule(p),Tracable(p),Intelligente(p){}

        //On fixe les méthodes ambigües
        using Tracable::getMemoire;
        using Tracable::evolue;

        using Intelligente::getKase;
        using Intelligente::set_kase;
};

template <typename type>
class Particule_spe : public virtual Particule {

    private:

        //Chaque type de particule_spe a une masse qui lui est propre
        std::string affiche_nom() const override;

        //Chaque type de particule_spe a une masse qui lui est propre
        static double getMass();


    public:

        //Constructeurs
        Particule_spe(Vecteur3D pos,Vecteur3D v);

        Particule_spe();

        //Méthode d'affichage
        void dessine_sur(SupportADessin& support) const override
        { support.dessine(*this); }

        //Méthodes nécessaires à la conception de collections hétérogènes et homogènes
        std::unique_ptr<Particule> copie() const override;

        std::unique_ptr<Particule> copie_intelligente() const override;

        std::unique_ptr<Particule> copie_tracable() const override;

        std::unique_ptr<Particule> copie_TI() const override;
};


template<typename type>
class Particule_spe_Intelligente:public Particule_spe<type>, public Intelligente{

    public:

        //Constructeurs
        Particule_spe_Intelligente(Particule_spe<type> const& p):
        Particule(p),Particule_spe<type>(p),Intelligente(p){}

        Particule_spe_Intelligente():
        Particule(),Particule_spe<type>(),Intelligente(){}

        //On fixe les méthodes ambigües
        using Intelligente::getKase;
        using Intelligente::set_kase;
};

template<typename type>
class Particule_spe_Tracable:public Particule_spe<type>,public Tracable{

    public:

        //Constructeurs
        Particule_spe_Tracable(Particule_spe<type> const& p):
        Particule(p),Particule_spe<type>(p),Tracable(p){}

        Particule_spe_Tracable():
        Particule(),Particule_spe<type>(), Tracable(){}

        //On fixe les méthodes ambigües
        using Tracable::getMemoire;
        using Tracable::evolue;

        //Méthode d'affichage
        void dessine_sur(SupportADessin& support) const override
        { support.dessine(*this); }

};

template <typename type>
class Particule_spe_TI:public Particule_spe_Tracable<type>, public Intelligente{

    public:

        //Constructeurs
        Particule_spe_TI(Particule_spe<type> const& p):
        Particule(p),Particule_spe_Tracable<type>(p),Intelligente(p){}

        Particule_spe_TI():
        Particule(),Particule_spe_Tracable<type>(),Intelligente(){}

        //On fixe les méthodes ambigües
        using Particule_spe_Tracable<type>::getMemoire;
        using Particule_spe_Tracable<type>::evolue;
        using Particule_spe_Tracable<type>::dessine_sur;

        using Intelligente::getKase;
        using Intelligente::set_kase;
};
