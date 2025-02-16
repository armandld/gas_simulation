#pragma once
#include <iostream>
#include "SupportADessin.h"

class TextViewer : public SupportADessin {
	
	public:
	
    TextViewer(std::ostream& s = std::cout):
        sortie(s){}
	
	
	void dessine(Particule const& p) override;
    void dessine(Enceinte const& e) override;
    void dessine(std::string s) override;

    void dessine(Particule_spe<Neon> const& n) override;
    void dessine(Particule_spe<Argon> const& a) override;
    void dessine(Particule_spe<Helium> const& h) override;

    void dessine(Particule_spe_Tracable<Neon> const& nt) override;
    void dessine(Particule_spe_Tracable<Argon> const& at) override;
    void dessine(Particule_spe_Tracable<Helium> const& ht) override;

	
	private:
	std::ostream& sortie;
	
};
