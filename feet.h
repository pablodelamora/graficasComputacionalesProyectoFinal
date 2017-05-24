#pragma once
#include <GL/glut.h>
#include <stdlib.h>

//Todas las funcionalidades estan explicadas en arm.h ya que seccion
//iguales las clases y su funcionalidad cambia solo valores

class Feet{
    private:
        int rotacion;
        int revolucion;
        int torcion;
        double x,y,z;
        double t1,t2,tz;
    public:
        Feet();
        Feet(double t1, double t2, double tz);
        void draw();//Dibuja la extremidad
        void rotar(int r);//Rota la extremidad
        void revolucionar(int r);//Revoluciona la extremidad
        void torcionar(int r);//Torciona la extremidad

};

Feet::Feet(){}

Feet::Feet(double t1, double t2, double tz){
    rotacion = 0;
    revolucion = 0;
    torcion = 0;
    x=1.2;
    y=.5;
    z=1;
    this->t1 = t1;
    this->t2 = t2;
    this->tz = tz;
}

void Feet::draw(){

    GLfloat mat[] = { 238/255.0, 92/255.0, 191/255.0, 1.0f };
    GLfloat mat_shininess[] = { 0.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//color

    glTranslatef (t1, 0.0, tz);
    glRotatef ((GLfloat) rotacion, 0.0, 0.0, 1.0);
    glRotatef ((GLfloat) revolucion, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) torcion, 1.0, 0.0, 0.0);
    glTranslatef (t2, 0.0, 0.0);

    glPushMatrix();
        glScalef (x, y, z);//Escala la extremidad
        glutSolidSphere (1.0,10,10);//Dibuja
    glPopMatrix();
}

void Feet::rotar(int r){
  if (r>0){
    if (rotacion+r < 90){
      rotacion = (rotacion + r) %360;
    }
  }
  else{
    if (rotacion+r > -1){
      rotacion = (rotacion + r) %360;
    }
  }
}

void Feet::revolucionar(int r){
  if (r>0){
    if (revolucion+r < 60){
      revolucion = (revolucion + r) %360;
    }
  }
  else{
    if (revolucion+r > -60){
      revolucion = (revolucion + r) %360;
    }
  }
}

void Feet::torcionar(int r){
    torcion = (torcion + r) %360;
}
