#include <iostream>
#include "Textviewer.h"
#include "Particule.h"
#include "Enceinte.h"
#include "Systeme.h"

void TextViewer::dessine(Particule const& p) {sortie<< p<< std::endl;}
void TextViewer::dessine(Enceinte const& e) {sortie << e;}
void TextViewer::dessine(std::string s) {sortie << s << std::endl;}

void TextViewer::dessine(Particule_spe<Neon> const& n) {sortie << n << std::endl;}
void TextViewer::dessine(Particule_spe<Argon> const& a) {sortie << a << std::endl;}
void TextViewer::dessine(Particule_spe<Helium> const& h) {sortie << h << std::endl;}

void TextViewer::dessine(Particule_spe_Tracable<Neon> const& nt) {sortie << nt << std::endl;}
void TextViewer::dessine(Particule_spe_Tracable<Argon> const& at) {sortie << at << std::endl;}
void TextViewer::dessine(Particule_spe_Tracable<Helium> const& ht) {sortie << ht << std::endl;}
