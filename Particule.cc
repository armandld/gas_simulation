#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <memory>
#include <list>
#include "Vecteur3D.h"
#include "Particule.h"
#include "GenerateurAleatoire.h"
#include "SupportADessin.h"

using namespace std;

//***************************   PARTICULE   ***************************

//Initialisation des attributs de classe

unsigned int Particule::nb_particules = 0;

bool Particule::affichageCouleur = true;

bool Particule::affichageTrace=false;


//Constructeurs --------------------------------------------------------

Particule::Particule(Vecteur3D pos, Vecteur3D v, double m):
    pos(pos),
    v(v),
    m(m),
    nom(std::to_string(nb_particules)) //A noter que la première
    {++nb_particules;}				   //particule est la "particule 0"


Particule::Particule():
    Particule(Vecteur3D(0,0,0),
              Vecteur3D(1,1,1),
              1				  )
{}

//Constructeur de copie ------------------------------------------------

Particule::Particule(Particule const& autre):
    pos(autre.pos),
    v(autre.v),
    m(autre.m),
    nom(std::to_string(nb_particules))
    {++nb_particules;}

//Méthode init (tirage des position et vitesses) -----------------------
void Particule::init(GenerateurAleatoire& tirage,
                     Enceinte const& e			,
                     double const temp			){

    pos = Vecteur3D(tirage.uniforme(0,e.getHauteur()),
                    tirage.uniforme(0,e.getLargeur()),
                    tirage.uniforme(0,e.getProfondeur()));

    v = Vecteur3D(tirage_gauss(tirage,temp),
                  tirage_gauss(tirage,temp),
                  tirage_gauss(tirage,temp));
}

//Méthode intermédiaire de init ----------------------------------------

double Particule::tirage_gauss(GenerateurAleatoire& tirage,
                               double const temp		  ) const {
   return tirage.gaussienne(0.0,sqrt(m*pow(10,-3)*(1/8.314472) * temp));
}

/*Méthodes nécessaires au polymorphisme,        ------------------------
  mais non utilisable pour une simple particule ------------------------*/

Coordonnees Particule::getKase() const
{
    throw Erreur{001,
        "Utilisation de getKase() pour une particule non intelligente"};
}

void Particule::set_kase(Coordonnees const& v)
{
    throw Erreur{002,
        "Utilisation de getKase() pour une particule non intelligente"};
}

list<Vecteur3D> Particule::getMemoire() const
{
    throw Erreur{003,
        "Utilisation de getMemoire() pour une particule non traçable"};
}
//Test de proximité entre deux particules ------------------------------

bool Particule::proximite(Particule const& autre,
                          double pas_espace)const{
 return(pos*(1/pas_espace)).floor()==(autre.pos*(1/pas_espace)).floor();
}

//Méthode d'affichage --------------------------------------------------

string Particule::affiche_nom() const{ return nom;}

void Particule::afficher(std::ostream& sortie)const
{
    sortie<<"Particule "<<affiche_nom()
          <<" : pos : "<<pos
          <<" ; v : "<<v
          <<" ; m : "<<m;
}

//Méthodes de l'évolution de la particule ------------------------------
void Particule::evolue(double dt){
    pos += dt * v;
}

void Particule::rencontre_particule(Particule& autre,double epsilon,
                                    GenerateurAleatoire& tirage	   ,
                                    bool premier_tirage		   ){
    Vecteur3D vg((m/(m+autre.m))*v+(autre.m/(m+autre.m))*(autre.v));
    double L((v-vg).norme());
    double z(tirage.uniforme(-L,L));
    double phi(0);
    do{
        phi = tirage.uniforme(0,2*M_PI);
    }while(phi == 2*M_PI);
    double r(sqrt(L*L-z*z));
    if(premier_tirage){

        z = 0;
        phi = M_PI/3;
        r = L;

    }

    Vecteur3D v0(r*cos(phi),r*sin(phi),z);
    v = vg + v0;
    autre.v = vg - (m/autre.m)*v0;
}

void Particule::surface(coord O,double dimension_enceinte,
                        SupportADessin& ecran){

    Vecteur3D axe;
    unsigned int face_1(0);
    unsigned int face_2(0);

    //Au dépend de la coordonnée, on fixe le vecteur unitaire choisi
    // et les faces correspondantes
    switch (O){
        case Ox :
            axe = vectx;
            face_1 = 1;
            face_2 = 2;
            break;
        case Oy :
            axe  = vecty;
            face_1 = 3;
            face_2 = 4;
            break;
        case Oz :
            axe = vectz;
            face_1 = 5;
            face_2 = 6;
            break;
    }

    if((pos&axe)>dimension_enceinte or (pos&axe)<0 ){

        v -= 2 * (v&axe)*axe;
        ostringstream oss;
        oss<<"La particule "<<nom<<" rebondit sur la face ";

        if((pos&axe)>dimension_enceinte){	//Pour la première face

            pos -= (2 *((pos&axe)-dimension_enceinte))*axe;
            oss<<face_1<<endl;

        }else{								//Pour la face opposée

            pos -= 2 * (pos&axe) *axe;
            oss<<face_2<<endl;
        }

        ecran.dessine(oss.str());
    }
}

void Particule::rencontre_paroi(Enceinte const& enceinte,
                                SupportADessin& ecran	){

    surface(Ox,enceinte.getHauteur(),ecran);
    surface(Oy,enceinte.getLargeur(),ecran);
    surface(Oz,enceinte.getProfondeur(),ecran);

}

//Méthodes nécessaires à la conception de collections hétérogènes et homogènes
unique_ptr<Particule> Particule::copie() const{
    return unique_ptr<Particule>(new Particule (*this));
}

unique_ptr<Particule> Particule::copie_intelligente() const{
    return unique_ptr<Particule>(new Intelligente (*this));
}

unique_ptr<Particule> Particule::copie_tracable() const{
    return unique_ptr<Particule>(new Tracable (*this));
}

unique_ptr<Particule> Particule::copie_TI() const{
    return unique_ptr<Particule>(new TI (*this));
}


//************** Fin des définition des méthodes de PARTICULE **********

std::ostream& operator<<(std::ostream& sortie, Particule const& p)
{
    p.afficher(sortie);
    return sortie;
}

//*******************  SOUS-CLASSES DE PARTICULES   *******************

//Constructeurs des sous classes INTELLIGENTE et TRACABLE

Intelligente::Intelligente(Particule const& p):
    Particule(p),kase({}){}

Intelligente::Intelligente():
    Particule(),kase({}){}

Tracable::Tracable():
    Particule(){}

Tracable::Tracable(Particule const& p):
    Particule(p){}

//Méthode évolue propre à Tracable
void Tracable::evolue(double dt){
    pos+= dt*v;
    size_t i(0);
    if(memoire.size()==taille_trace){ //la taille de cette trace est limitée
        memoire.pop_front();
    }
    memoire.push_back(pos);
}

//Constructeurs des sous-classes de Particule
template <typename type>
Particule_spe<type>::Particule_spe(Vecteur3D pos,Vecteur3D v):
    Particule(pos,v,getMass()){}

template <typename type>
Particule_spe<type>::Particule_spe():
    Particule_spe<type>(Vecteur3D(0,0,0), Vecteur3D(1,1,1)){}

//Définition du static getMass() qui empêche la création de sous classe
// autres que Neon, Argon et Helium

template <typename type>
double Particule_spe<type>::getMass(){
    throw (Erreur{004,
    "Une particule_spe ni Argon,ni Helium, ni Neon cherche à être instanciée"});
}

//Méthodes d'affichage des sous-classes de Particule--------------------

template <typename type>
string Particule_spe<type>::affiche_nom() const{
    throw(Erreur{005,"Une particule ni Argon,ni Helium, ni Neon cherche à etre affichée"});
    return "";
}

template<> string Particule_spe<Neon>::affiche_nom() const{
    return "Neon";
}

template<> string Particule_spe<Argon>::affiche_nom() const{
    return "Argon";
}

template<> string Particule_spe<Helium>::affiche_nom() const{
    return "Helium";
}

//Spécialisation des méthodes nécessaires-------------------------------

template<> double Particule_spe<Neon>::getMass(){
    return 20.1797;
}

template<> double Particule_spe<Argon>::getMass(){
    return 39.948;
}

template<> double Particule_spe<Helium>::getMass(){
    return 4.002602;
}

//Méthode pour les collections hétérogènes des sous-classes de Particule
template<typename type>
unique_ptr<Particule> Particule_spe<type>::copie() const {
    return unique_ptr<Particule>(new Particule_spe<type>(*this));
}

template <typename type>
unique_ptr<Particule> Particule_spe<type>::copie_intelligente() const {
    return unique_ptr<Particule> (new Particule_spe_Intelligente<type>(*this));
}

template<typename type>
unique_ptr<Particule> Particule_spe<type>::copie_tracable() const{
    return unique_ptr<Particule>(new Particule_spe_Tracable<type>(*this));
}

template<typename type>
unique_ptr<Particule> Particule_spe<type>::copie_TI() const{
    return unique_ptr<Particule>(new Particule_spe_TI<type>(*this));
}

//Déclaration des modèles de classe nécessaires
template class Particule_spe<Neon>;
template class Particule_spe<Argon>;
template class Particule_spe<Helium>;

template class Particule_spe_Intelligente<Neon>;
template class Particule_spe_Intelligente<Argon>;
template class Particule_spe_Intelligente<Helium>;

template class Particule_spe_Tracable<Neon>;
template class Particule_spe_Tracable<Argon>;
template class Particule_spe_Tracable<Helium>;

template class Particule_spe_TI<Neon>;
template class Particule_spe_TI<Argon>;
template class Particule_spe_TI<Helium>;
