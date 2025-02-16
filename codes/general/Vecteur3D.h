#include <iostream>
#include <cmath>
#include <array>
#pragma once

enum coord{Ox,Oy,Oz};

struct Erreur { //On définit ici le type d'exception que l'on utilisera
	int code;	// dans le programme
	std::string message;
	
};

typedef std::array<unsigned int,3> Coordonnees;

class Vecteur3D{
	
	private : 

		double x;
		double y;
		double z;
	
    public:

		//Constructeurs
		Vecteur3D(const double x_ = 0,
				  const double y_ = 0,
				  const double z_ = 0)
		: x(x_), y(y_), z(z_)
		{}
		
		constexpr Vecteur3D(const double x_, //utile pour définir des 
							const double y_, //vecteurs unitaires
							const double z_,
							const bool b)
		: x(x_), y(y_), z(z_)
		{} 
	
		//Setters
		void set_coord(coord c,double valeur);
		void set_all_coord(double nv_x,double nv_y,double nv_z);
		
		//Méthode d'affichage
		std::ostream& afficher(std::ostream& sortie) const {
			sortie << x << ' ' << y << ' ' << z;
			return sortie;
		}
		
		//Opérateurs de logique (internes)
		bool operator==(Vecteur3D const& V) const{
			return ((V.x==x)and(V.y==y)and(V.z==z));
		}
		bool operator!=(Vecteur3D const& V) const{return not(*this==V);}
		
		//Opérateurs arithmétiques ou propres aux vecteurs (internes)
		Vecteur3D& operator+=(Vecteur3D const& autre);
		Vecteur3D& operator-=(Vecteur3D const& autre);
		Vecteur3D& operator-(); //prend l'opposé du vecteur
		Vecteur3D& operator*=(double scal);
		Vecteur3D operator^(Vecteur3D const& autre);
        double operator&(Vecteur3D const& autre) const;
		
		//Anciennes méthodes pour définir les opérations 
		//(inutilisées depuis la définition des opérateurs internes)
		Vecteur3D addition(Vecteur3D autre) const;
		Vecteur3D soustraction(Vecteur3D autre) const;
		Vecteur3D oppose() const;
		Vecteur3D mult(double scal) const;
		Vecteur3D prod_vect(Vecteur3D autre) const;
		double prod_scal(Vecteur3D autre) const;
		
		//Méthode pour trouver le vecteur unitaire associé à un vecteur
		Vecteur3D unitaire()const;
		
		Vecteur3D floor()const;	/* Méthode qui créé un vecteur dont 
								   les coordonnées sont les parties 
								   entières des instances courantes
								   pour faciliter les calculs de choc */
		
		//Méthode pour calculer la norme et la norme au carré du vecteur
		double norme() const{return sqrt(x*x + y*y + z*z);}
		double norme2() const{return norme()*norme();}
		
        Coordonnees to_array() const;
};

//Vecteurs unitaires de base
constexpr Vecteur3D vectx(1,0,0,true);
constexpr Vecteur3D vecty(0,1,0,true);
constexpr Vecteur3D vectz(0,0,1,true);

//opérateurs externes
const Vecteur3D operator+(Vecteur3D, const Vecteur3D&);
const Vecteur3D operator-(Vecteur3D, const Vecteur3D&);
const Vecteur3D operator*(Vecteur3D, const double);
const Vecteur3D operator*(const double,Vecteur3D);

//Opérateur d'affichage
std::ostream& operator<<(std::ostream& sortie,Vecteur3D const& v);


