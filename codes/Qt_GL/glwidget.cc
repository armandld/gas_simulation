#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "glwidget.h"

// ======================================================================
GLWidget::GLWidget(double a, double b, double c, double epsilon, unsigned int graine, double temperature, QWidget* parent)
    : QOpenGLWidget(parent), AfficheCamera(false), vitesse_simulation(10), s(a,b,c,epsilon,graine,temperature)
{ chronometre.restart();}

void GLWidget::ajouteParticule(Particule const& p){
    s.ajouteParticule(p);
}
void GLWidget::ajouteParticule_tracable(Particule const& t){
    s.ajouteParticule_tracable(t);
}

// ======================================================================
void GLWidget::initializeGL()
{
  vue.init();
  timerId = startTimer(20);
}

// ======================================================================
void GLWidget::resizeGL(int width, int height)
{
  /* On commance par dire sur quelle partie de la 
   * fenêtre OpenGL doit dessiner.
   * Ici on lui demande de dessiner sur toute la fenêtre.
   */
  glViewport(0, 0, width, height);

  /* Puis on modifie la matrice de projection du shader.
   * Pour ce faire on crée une matrice identité (constructeur 
   * par défaut), on la multiplie par la droite par une matrice
   * de perspective.
   * Plus de détail sur cette matrice
   *     http://www.songho.ca/opengl/gl_projectionmatrix.html
   * Puis on upload la matrice sur le shader à l'aide de la
   * méthode de la classe VueOpenGL
   */
  QMatrix4x4 matrice;
  matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
  vue.setProjection(matrice);
}

// ======================================================================
void GLWidget::paintGL() {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        try{
            if(AfficheCamera) vue.changeCamera(*(s.getComposant()));
        }
        catch(Erreur const& e){
            if(e.code != 006) throw(Erreur{007,"Invocation de la caméra incorrecte"});
            else AfficheCamera = false;
        }
        s.dessine_sur(vue);
    }

// ======================================================================
void GLWidget::keyPressEvent(QKeyEvent* event)
{
  constexpr double petit_angle(5.0); // en degrés
  constexpr double petit_pas(1.0);

  switch (event->key()) {

  case Qt::Key_Left:
    vue.rotate(petit_angle, 0.0, -1.0, 0.0);
    break;

  case Qt::Key_Right:
    vue.rotate(petit_angle, 0.0, +1.0, 0.0);
    break;

  case Qt::Key_Up:
    vue.rotate(petit_angle, -1.0, 0.0, 0.0);
    break;

  case Qt::Key_Down:
    vue.rotate(petit_angle, +1.0, 0.0, 0.0);
    break;

  case Qt::Key_PageUp:
  case Qt::Key_W:
    vue.translate(0.0, 0.0,  petit_pas);
    break;

  case Qt::Key_PageDown:
  case Qt::Key_S:
    vue.translate(0.0, 0.0, -petit_pas);
    break;

  case Qt::Key_A:
    vue.translate( petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_D:
    vue.translate(-petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_R:
    vue.translate(0.0, -petit_pas, 0.0);
    break;

  case Qt::Key_F:
    vue.translate(0.0,  petit_pas, 0.0);
    break;

  case Qt::Key_Q:
    vue.rotate(petit_angle, 0.0, 0.0, -1.0);
    break;

  case Qt::Key_E:
    vue.rotate(petit_angle, 0.0, 0.0, +1.0);
    break;

  case Qt::Key_Home:
    vue.initializePosition();
    break;

  case Qt::Key_C:
      s.changeCouleur();
      break;

  case Qt::Key_T:
      s.changeTrace();
      break;

  case Qt::Key_I:
      affichageInfos = !affichageInfos;
      break;

  case Qt::Key_X:
      AfficheCamera = !AfficheCamera;
      break;

  case Qt::Key_Space:
	pause();
	break;

  case Qt::Key_1:
      vitesse_simulation = 1;
      break;

  case Qt::Key_2:
      vitesse_simulation = 2;
      break;

  case Qt::Key_3:
      vitesse_simulation = 4;
      break;

  case Qt::Key_4:
      vitesse_simulation = 10;
      break;

  case Qt::Key_5:
      vitesse_simulation = 20;
      break;

  case Qt::Key_6:
      vitesse_simulation = 40;
      break;

  case Qt::Key_7:
      vitesse_simulation = 100;
      break;

  case Qt::Key_8:
      vitesse_simulation = 200;
      break;

  case Qt::Key_9:
      vitesse_simulation = 500;
      break;
  };

  update(); // redessine
}

// ======================================================================
void GLWidget::timerEvent(QTimerEvent* event)
{
  Q_UNUSED(event);

  const double dt = chronometre.elapsed()*vitesse_simulation / 10000.0;
  chronometre.restart();

  s.evolue(dt,vue);
  update();
}

// ======================================================================
void GLWidget::pause()
{
  if (timerId == 0) {
	// dans ce cas le timer ne tourne pas alors on le lance
	timerId = startTimer(20);
	chronometre.restart();
  } else {
	// le timer tourne alors on l'arrête
	killTimer(timerId);
	timerId = 0;
  }
}
