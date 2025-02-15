#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include "Systeme.h"
#include "Dessinable.h"
#include "Particule.h"
#include "GenerateurAleatoire.h"
#include "SupportADessin.h"

using namespace std;

//****************************   SYSTEME   ****************************


//Constructeurs---------------------------------------------------------

Systeme::Systeme(double a,double b,double c,
				 double epsilon,unsigned int graine,double temperature):
enceinte(a,b,c),epsilon(epsilon),tirage(graine),temperature(temperature),premier_tirage(false)
{}

Systeme::Systeme(double a, double b, double c):
Systeme(a,b,c,1,0,273.15){}

Systeme::Systeme():
Systeme(20.0,20.0,20.0){}


//Méthodes d'ajout/suppression de particules du système-----------------

//Méthodes intermédiaires évitant le copier-coller
void Systeme::ajoute(bool aleatoire){

    if(aleatoire){
        composants[composants.size()-1]->init(tirage,enceinte,temperature);//on tire aléatoirement les positions et vitesse de la particule 	//après l'avoir copiée en un unique_ptr
    }
}

void Systeme_intelligent::ajoute(bool aleatoire){

    Systeme::ajoute(aleatoire);
    composants[composants.size()-1]->set_kase(actualise(((composants[composants.size()-1])->getPos())*(1/epsilon),composants.size()-1));
}

void Systeme::ajouteParticule(Particule const& p, bool aleatoire) {

	composants.push_back(p.copie());

    ajoute(aleatoire);
}

void Systeme::ajouteParticule_tracable(Particule const& p, bool aleatoire) { //L'argument est const

    composants.push_back(p.copie_tracable());
    ajoute(aleatoire);
}

void Systeme_intelligent::ajouteParticule(Particule const& p, bool aleatoire) { //L'argument est const

	composants.push_back(p.copie_intelligente());
	
    ajoute(aleatoire);
}



void Systeme_intelligent::ajouteParticule_tracable(Particule const& p, bool aleatoire) { //L'argument est const

    composants.push_back(p.copie_TI());

    ajoute(aleatoire);
}

//Méthodes d'évolution ------------------------------------------------

void Systeme::evolue_bis(vector<Tableau> all_candida,					//On récupère un tableau de collisons
                        SupportADessin& ecran		 ){					//où une collision est un ensemble de particules candidates à un choc


    for(auto const& candida : all_candida){

            size_t choisie(0); 									//on initialise une variable qui correspond à l'index de la particule choisie dans candida.
            do{															//
                choisie = tirage.uniforme(0,candida.size()-1); 			//On tire un index au hasard dans le vector candida
            }while(choisie == (candida.size()-1));  					//L'index choisi correspondra à la particule choisie pour le choc
                                                                        //Il est important de remarquer qu'on tire ici un double qui sera ensuite tronqué lors de l'affectation
                                                                        //pour donner un size_t, c'est la raison pour laquelle on augmente de 1 l'intervalle dans lequel on va piocher.
                                                                        //Sinon, le tirage ne sera pas uniforme (il est très peu probable de tirer le dernier index),
                                                                        //et on exclut la très faible probabilité pour que la valeur non voulue (la taille du tableau soit choisie.

            ostringstream oss;
            oss<<"La particule "<< candida[candida.size() - 1]	+ 1		//on ajoute 1 car i représente l'index
                <<" entre en collision avec une autre particule."<<endl
                <<endl
                <<" avant le choc :"<<endl
                <<"  "<<*composants[candida[candida.size()-1]]<<endl									//on affiche les particules qui vont s'entrechoquer
                <<"  "<<*composants[candida[choisie]]<<endl;

                composants[candida[candida.size()-1]]->
                rencontre_particule(*composants[candida[choisie]],		//on fait appel à la méthode rencontre_particule des particules
                                    epsilon,tirage, !premier_tirage);
                if(!premier_tirage){
                 premier_tirage = true;
                }


            oss<<" après le choc :"<<endl
               <<"  "<<*composants[candida[candida.size()-1]]<<endl
               <<"  "<<*composants[candida[choisie]]<<endl<<endl;


            ecran.dessine(oss.str());
        }

}

void Systeme::evolue(double dt, SupportADessin& ecran){
	
	vector<Tableau> all_candida;
	
	for(size_t i(0);i<composants.size();++i){
		
		composants[i]->evolue(dt);	//les particules se déplacent...

        composants[i]->rencontre_paroi(enceinte,ecran);
	}
	
	for(size_t i(0);i<composants.size();++i){
		
            Tableau tab = candida_constructor(i);
			tab.push_back(i);
			if(tab.size()>1){
				all_candida.push_back(tab);
			}
	}
	
	evolue_bis(all_candida,ecran);
}

void Systeme_intelligent::evolue(double dt, SupportADessin& ecran){
	
	vector<Tableau> all_candida;
	
	for(size_t i(0);i<composants.size();++i){
		
		Vecteur3D previous_pos(composants[i]->getPos());
		
        Coordonnees ex_kase(composants[i]->getKase());
		
		composants[i]->evolue(dt);
		
        composants[i]->rencontre_paroi(enceinte,ecran);


		Vecteur3D new_pos(composants[i]->getPos());
		
		if( ( (previous_pos*(1/epsilon)).floor() ) != ((new_pos*(1/epsilon))).floor() ){
			
			 Tableau& ex_case = kases[ex_kase[0]][ex_kase[1]][ex_kase[2]];

           // Retire la particule de son ancienne case
           bool done(false);
           for (Tableau::iterator it = ex_case.begin(); it != ex_case.end() and !done;++it) {
                if (*it == i) {
                    ex_case.erase(it);
                    done = true;
                }
            }
        composants[i]->set_kase(actualise((new_pos)*(1/epsilon),i));
        }
    }
		

	for(size_t i(0);i<kases.size();i+=1){
		for(size_t j(0);j<kases[i].size();j+=1){
			for(size_t k(0);k<kases[i][j].size();k+=1){
				if((kases[i][j][k]).size()>1){
					all_candida.push_back(kases[i][j][k]);
				}
			}
		}
	}

	evolue_bis(all_candida,ecran);
}

Tableau Systeme::candida_constructor(size_t i){
	Tableau res ;
	for(size_t j(0);j<i;++j){
		if(composants[i]->proximite(*composants[j],epsilon)){ //On vérifie que les deux particules se trouvent au même endroit (même pas d'espace)
			res.push_back(j);
		}
	}
	return res;
}


//Méthodes d'affichage--------------------------------------------------

void Systeme::dessine_sur(SupportADessin& support) const {
    enceinte.dessine_sur(support);
    if (composants.size()>0) {
    for (auto const& comp:composants) {
        comp->dessine_sur(support);
        }
    }else{
        ostringstream oss;
        oss<<"Le système est vide."<<endl;
        support.dessine(oss.str());
    }
}

ostream& Systeme::afficher(ostream& sortie) const {
	
    if (composants.size()>=1) {	//on vérifie que le système n'est pas vide

		for (auto const& part:composants) {
			part->afficher(sortie);
			sortie<<endl;
		}
	}
	else {

		sortie << "Le système est vide." << endl;
		
	}
	return sortie;
	
}

//Méthode publique uniquement dédiée au changement de caméra
const std::unique_ptr<Particule>&  Systeme::getComposant() const{
    if(composants.empty()) throw(Erreur{006,"Accès à la première particule d'un système vide"});
    return composants[0];
}


ostream& operator<<(ostream& sortie, Systeme const& s) {
	
	s.afficher(sortie);
	return sortie;
	
}
//************************************************************************************************


Systeme_intelligent::Systeme_intelligent(double a,double b,double c,
				 double epsilon,unsigned int graine,double temperature):
	Systeme(a,b,c,epsilon,graine,temperature)
{
	kases.clear();
	
    for(int i(0);i<=(enceinte.getHauteur()/epsilon);++i){
        kases.push_back({});
        for(size_t j(0);j<=(enceinte.getLargeur()/epsilon);++j){
            kases[i].push_back({});
            for(size_t k(0);k<=(enceinte.getProfondeur()/epsilon);++k){
				kases[i][j].push_back({});
			}
		}
	}
}


Coordonnees Systeme_intelligent::actualise(Vecteur3D const& v,size_t num_part){
	v.floor();
	size_t a(v&vectx);
	size_t b(v&vecty);
	size_t c(v&vectz);
	kases[a][b][c].push_back(num_part);
    return v.to_array();
}
