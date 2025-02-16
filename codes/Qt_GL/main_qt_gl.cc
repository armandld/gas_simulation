#include <QApplication>
#include "glwidget.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  // Création du widget OpenGL
  GLWidget w(20.0, 20.0, 20.0, 0.5, 0, 273.15);
  int i(0);
  while (i<100){
    w.ajouteParticule(Particule_spe<Argon>());
    w.ajouteParticule(Particule_spe<Helium>());
    w.ajouteParticule(Particule_spe<Neon>());
    ++i;
  }
  w.ajouteParticule_tracable(Particule_spe<Neon>());
  w.show();
  return a.exec();
}
