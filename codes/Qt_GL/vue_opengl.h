#pragma once
#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "glsphere.h"
#include "SupportADessin.h"
#include "Enceinte.h"
#include "Particule.h"


class VueOpenGL : public SupportADessin {
 public:
  // méthode(s) de dessin (héritée(s) de SupportADessin)
    void dessine(Particule const& p) override;

    void dessine(Enceinte const& e) override;
    void dessine(std::string s) override;

    void dessine(Particule_spe<Neon> const& n) override;
    void dessine(Particule_spe<Argon> const& a) override;
    void dessine(Particule_spe<Helium> const& h) override;

    void dessine(Particule_spe_Tracable<Neon> const& nt) override;
    void dessine(Particule_spe_Tracable<Argon> const& at) override;
    void dessine(Particule_spe_Tracable<Helium> const& ht) override;

  // méthodes de (ré-)initialisation
  void init();
  void initializePosition();
  void changeCamera(Particule const&);

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);
  
  // méthode utilitaire offerte pour simplifier
  void dessineEnceinte(QMatrix4x4 const& point_de_vue = QMatrix4x4(),Enceinte const& e = Enceinte() );
  void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void dessineSphere(QMatrix4x4 const& point_de_vue,
                     double rouge = 1.0, double vert = 1.0, double bleu = 1.0);

  void dessineTracable(QMatrix4x4 const& point_de_vue = QMatrix4x4(), Tracable const& t=Tracable() );
  void dessineVitesse(QMatrix4x4);

 private:

  void dessine(Particule const&, double, double, double);
  void dessine_tracable(Tracable const&, double, double, double);

  QMatrix4x4 dessine_partie1();
  void dessine_partie2(QMatrix4x4&, Particule const&, double, double, double);

  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;
  GLSphere sphere;

  // Caméra
  QMatrix4x4 matrice_vue;
};
