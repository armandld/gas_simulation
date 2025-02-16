#pragma once
#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QElapsedTimer>        // Classe pour gérer le temps
#include "vue_opengl.h"
#include "Systeme.h"

class GLWidget : public QOpenGLWidget
/* La fenêtre hérite de QOpenGLWidget ;
 * les événements (clavier, souris, temps) sont des méthodes virtuelles à redéfinir.
 */
{
public:
  GLWidget(double a= 20.0, double b= 20.0, double c= 20.0, double epsilon = 1.0, unsigned int graine = 0, double temperature = 273.15, QWidget* parent = nullptr);
  virtual ~GLWidget() = default;

  void ajouteParticule(Particule const& p);
  void ajouteParticule_tracable(Particule const& t);

private:
  // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  // Méthodes de gestion d'évènements
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void timerEvent(QTimerEvent* event)  override;

  // Méthodes de gestion interne
  void pause();

  //Attribut booléen pour savoir si on affiche les informations du système
  bool affichageInfos;

  //Attribut booléen pour savoir si on met la caméra sur une particule
  bool AfficheCamera;

  //Attribut entier décrivant la vitesse de la simulation
  int vitesse_simulation;

  // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
  VueOpenGL vue;

  // Timer
  int timerId;

  // pour faire évoluer les objets avec le bon "dt"
  QElapsedTimer chronometre;

  // objets à dessiner, faire évoluer
  Systeme_intelligent s;
};
