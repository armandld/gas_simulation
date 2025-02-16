#pragma once
#include <iostream>
#include <string>

//On pré déclare les classes essentielles au code ici, pour éviter
//les dépendances cycliques
class Particule;

template<typename type>
class Particule_spe;

class Enceinte;

class Systeme;

template<typename type>
class Particule_spe_Tracable;

//Ces types "vides" servent à créer les modèles de classe attendus
enum class Neon{};
enum class Argon{};
enum class Helium{};

class SupportADessin {

	public:

        //Constructeur, Destructeur et Constructeur de copie
        SupportADessin() = default;

        //On empêche toute copie...
        SupportADessin(SupportADessin const&) = delete;
        SupportADessin& operator=(SupportADessin const&) = delete;
        SupportADessin(SupportADessin&&) = delete;
        SupportADessin& operator=(SupportADessin&&) = delete;

        // on suppose ici que les supports ne seront ni copiés ni déplacés
	
        virtual void dessine(Particule const&) = 0;

        virtual void dessine(Particule_spe<Neon> const&) = 0;
        virtual void dessine(Particule_spe<Argon> const&) = 0;
        virtual void dessine(Particule_spe<Helium> const&) = 0;

        virtual void dessine(Particule_spe_Tracable<Neon> const&) = 0;
        virtual void dessine(Particule_spe_Tracable<Argon> const&) = 0;
        virtual void dessine(Particule_spe_Tracable<Helium> const&) = 0;

        virtual void dessine(Enceinte const&) = 0;
        virtual void dessine(std::string) = 0;
	
};
