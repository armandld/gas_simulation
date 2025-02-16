#include <iostream>
#include <cmath>
#include <array>
#include "Vecteur3D.h"

using namespace std;

void Vecteur3D::set_coord(coord c,double valeur){
	switch(c){
		case Ox :
			x=valeur;
			break;
		case Oy :
			y=valeur;
			break;
		case Oz :
			z=valeur;
			break;
	}
}

void Vecteur3D::set_all_coord(double nv_x,double nv_y,double nv_z){
	set_coord(Ox,nv_x);
	set_coord(Oy,nv_y);
	set_coord(Oz,nv_z);
}

ostream& operator<<(ostream& sortie,Vecteur3D const& v){
	v.afficher(sortie);
	return sortie;
}

Vecteur3D& Vecteur3D::operator+=(Vecteur3D const& autre){
	set_all_coord(x + autre.x, y + autre.y, z + autre.z);
	return *this;
}

const Vecteur3D operator+(Vecteur3D a, Vecteur3D const& b) {
	a+=b;
	return a;
}

const Vecteur3D operator-(Vecteur3D a, Vecteur3D const& b) {
	a-=b;
	return a;
}

const Vecteur3D operator*(Vecteur3D a, double const b) {
	a*=b;
	return a;
}
const Vecteur3D operator*(double const b,Vecteur3D a){
	return a*b;
}

Vecteur3D& Vecteur3D::operator-=(Vecteur3D const& autre){
	set_all_coord(x - autre.x, y - autre.y, z - autre.z);
	return *this;
}

Vecteur3D& Vecteur3D::operator-() {
	set_all_coord(-x,-y,-z);
	return *this;
}

Vecteur3D& Vecteur3D::operator*=(double scal) {
	set_all_coord(scal*x,scal*y,scal*z);
	return *this;
}
	
Vecteur3D Vecteur3D::operator^(Vecteur3D const& autre) {
	Vecteur3D retour;
	retour.set_all_coord(y*autre.z - z*autre.y,
						 z*autre.x - x*autre.z,
						 x*autre.y - y*autre.x);
	return retour;
}

double Vecteur3D::operator&(Vecteur3D const& autre) const {
	return x*autre.x + y*autre.y + z*autre.z;
}
	

Vecteur3D operator~(Vecteur3D v) {
	if(v.norme()!=0){
		
		double scal(1/v.norme());
		v*=scal;
		return v;
		
	}else{
		
        Erreur vect_nul({000,"Vecteur nul (division par la norme du vecteur nul (par 0)"});
		throw vect_nul;
	}
}


Vecteur3D Vecteur3D::addition(Vecteur3D autre) const{
	Vecteur3D res;
	res.set_all_coord(x + autre.x, y + autre.y, z + autre.z);
	return res;
}

Vecteur3D Vecteur3D::soustraction(Vecteur3D autre) const{
	Vecteur3D res;
	res.set_all_coord(x - autre.x, y - autre.y, z - autre.z);
	return res;
}

Vecteur3D Vecteur3D::oppose() const{
	Vecteur3D res;
	res.set_all_coord(-x,-y,-z);
	return res;
}

Vecteur3D Vecteur3D::mult(double scal) const{
	Vecteur3D res;
	res.set_all_coord(scal*x,scal*y,scal*z);
	return res;
}

Vecteur3D Vecteur3D::prod_vect(Vecteur3D autre) const{
	Vecteur3D res;
	res.set_all_coord(y*autre.z - z*autre.y,
					  z*autre.x - x*autre.z,
					  x*autre.y - y*autre.x);
	return res;
}

double Vecteur3D::prod_scal(Vecteur3D autre) const{
	return x*autre.x + y*autre.y + z*autre.z;
}

Vecteur3D Vecteur3D::unitaire()const{
	if(norme()!=0){
		
		Vecteur3D res;
		res.set_all_coord(x,y,z);
		double scal(1/norme());
		res = res.mult(scal);
		return res;
		
	}else{
        Erreur vect_nul({000,"division par la norme du vecteur nul (par 0)"});
		throw vect_nul;
	}
}

Vecteur3D Vecteur3D::floor() const{
	Vecteur3D res(*this);
	res.set_all_coord(::floor(x),::floor(y),::floor(z));
	return res;
}

Coordonnees Vecteur3D::to_array() const{
    return {static_cast<unsigned int>(std::floor(x)),
            static_cast<unsigned int>(std::floor(y)),
            static_cast<unsigned int>(std::floor(z))};
}
