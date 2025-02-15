#pragma once
#include <iostream>
#include "Dessinable.h"
#include "Particule.h"




class Enceinte : public Dessinable{

	private:
	
		double hauteur;
		double largeur;
		double profondeur;
		
		
	public:

		//Constructeurs
        Enceinte(double h, double l, double p):
         hauteur(h), largeur(l), profondeur(p){}
		
        Enceinte():
         Enceinte(20,20,20){};
		
		//Getters
		double getHauteur()const{return hauteur;}
		double getLargeur()const{return largeur;}
		double getProfondeur()const{return profondeur;}
	
        //Méthode d'affichage
		void dessine_sur(SupportADessin& support) const override
		{ support.dessine(*this); }
		
};

std::ostream& operator<<(std::ostream& sortie,Enceinte const& e);

