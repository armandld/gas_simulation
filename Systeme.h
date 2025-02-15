#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include "SupportADessin.h"
#include "Particule.h"
#include "Enceinte.h"
#include "GenerateurAleatoire.h"


typedef std::vector<size_t> Tableau;

class Systeme : public Dessinable{
	
	public:
	
        //Constructeurs, Constructeur de copie, Destructeur,...
		Systeme();

        Systeme(double a, double b, double c);
	
		Systeme(double a, double b,double c,
				double epsilon,unsigned int graine,double temperature);

        //On empêche toute copie...
        Systeme(Systeme const&) = delete;
        Systeme& operator=(Systeme const&) = delete;
        Systeme(Systeme&&) = delete;
        Systeme& operator=(Systeme&&) = delete;
		
		virtual ~Systeme() = default;
	
	
		//Méthodes d'ajout/suppression de particules du système
		virtual void ajouteParticule(Particule const& p,
									 bool aleatoire = true);

        virtual void ajouteParticule_tracable(Particule const& p,
											  bool aleatoire = true);

		void supprimeParticules(){ composants.clear();}
	
	
		//Méthode d'evolution du Système
        virtual void evolue(double,SupportADessin&);
		
		//Méthodes d'affichage
		std::ostream& afficher(std::ostream& sortie) const;
		
		void dessine_sur(SupportADessin& support) const override;

        //Méthode pour modifier l'affichage des particules dans OpenGL
        void changeCouleur(){if(composants.size() != 0) composants[0]->changeCouleur();}

        void changeTrace(){if(composants.size() != 0) composants[0]->changeTrace();}

        //Getter
        const std::unique_ptr<Particule>&  getComposant() const;
		
    protected:

		//Méthode intermédiaire à l'évolution du système
		void evolue_bis(std::vector<Tableau> all_candida,
						SupportADessin& ecran);
		
        //Méthode intermédiaire de ajouteParticule et ajouteParticule_tracable
        virtual void ajoute(bool aleatoire);

		//Attributs
		std::vector<std::unique_ptr<Particule>> composants;
		
		Enceinte enceinte;
		
		double epsilon;
		
		GenerateurAleatoire tirage;
		
		const double temperature;

        bool premier_tirage;
		
	private:
		
		//Méthode construisant les candidats pour UN choc dans le 1er modèle de collision
        Tableau candida_constructor(size_t i);
		
};

std::ostream& operator<<(std::ostream& sortie, Systeme const& s);

//Un systeme_intelligent effectue le deuxième modèle de collision
class Systeme_intelligent: public Systeme{
	
	private:
	
        //Attribut supplémentaire (Enrichissement de la classe Systeme
		std::vector<std::vector<std::vector<Tableau>>> kases; 
		
        //Méthode nécessaire pour actualiser la case qu'occupe une particule
        Coordonnees actualise(Vecteur3D const& v,size_t num_part);

        //Méthode intermédiaire de ajouteParticule et ajouteParticule_tracable
        void ajoute(bool aleatoire) override;
		
	public:
	
		//Constructeurs et Constructeur de copie
		Systeme_intelligent();

        Systeme_intelligent(double a, double b, double c);
	
		Systeme_intelligent(double a, double b,double c,
				double epsilon,unsigned int graine,double temperature);
		
        //On empêche toute copie...
        Systeme_intelligent(Systeme const&) = delete;
        Systeme_intelligent& operator=(Systeme const&) = delete;
        Systeme_intelligent(Systeme&&) = delete;
        Systeme_intelligent& operator=(Systeme&&) = delete;
		
		//Méthodes d'ajout de particules (intelligentes) du système
		void ajouteParticule(Particule const& p,
							bool aleatoire = true) override;
		
		void ajouteParticule_tracable(Particule const& p,
									  bool aleatoire = true) override; 
		
		
		//Méthode d'évolution du Système intelligent (2ème modèle de collision)
		void evolue(double dt,SupportADessin& ecran) override;

};
