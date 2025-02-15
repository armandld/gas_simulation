#pragma once
#include <random>

class GenerateurAleatoire {
	
	public:
	
        GenerateurAleatoire(unsigned int graine = std::random_device()());
		
		double uniforme(double min, double max);
		
		double gaussienne(double moyenne, double ecart_type);

	private:

		std::default_random_engine              generateur            ;
		std::uniform_real_distribution<double>  distribution_uniforme ;
		std::normal_distribution<double> distribution_gaussienne	  ;
};
