#include <random>
#include "GenerateurAleatoire.h"

using namespace std;

GenerateurAleatoire::GenerateurAleatoire(unsigned int graine)
 :generateur(graine)
{}

double GenerateurAleatoire::uniforme(double min, double max){
	return distribution_uniforme(generateur, 
                                 std::uniform_real_distribution<double>::param_type{min, max});
}

double GenerateurAleatoire::gaussienne(double moyenne,
									   double ecart_type){
    return distribution_gaussienne(generateur, 
                                   std::normal_distribution<double>::param_type{moyenne, ecart_type});
}
