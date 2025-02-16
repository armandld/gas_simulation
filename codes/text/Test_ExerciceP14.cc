#include <iostream>
#include <memory>
#include <sstream>
#include "Systeme.h"
#include "Particule.h"
#include "Textviewer.h"


using namespace std;

int main() {

    TextViewer ecran(cout);

    Systeme_intelligent s(20,20,20,1,0,273.15);

    Systeme& systeme(s);

    systeme.ajouteParticule(Particule_spe<Helium>({1,1,1},{0,0,0}));
    systeme.ajouteParticule(Particule_spe<Neon>({1,18.5,1},{0,0.2,0}));
    systeme.ajouteParticule(Particule_spe<Argon>({1,1,3.1},{0,0,-0.5}));

    ostringstream oss;
    oss << "Le système est à l'état suivant : "<<endl;
    ecran.dessine(oss.str());
    oss.str("");
    systeme.dessine_sur(ecran);
    oss<<endl;
    ecran.dessine(oss.str());

    for(int i(0);i<15;++i){
        systeme.evolue(1,ecran);
        systeme.dessine_sur(ecran);
        oss.str("");
        oss<<endl<<"--------------------------------------------"<<endl;
        ecran.dessine(oss.str());
    }
    systeme.supprimeParticules();
    oss.str("");
    oss << "Après vidage, le système contient "
         << "les particules suivantes :" << endl;
    ecran.dessine(oss.str());
    systeme.dessine_sur(ecran);

    return 0;
}
