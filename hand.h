#pragma once
#include <GL/glut.h>
#include <stdlib.h>


class Hand{
    private:
        int rotacion;
        int revolucion;
        int torcion;
        double x,y,z;
        double t1,t2,tz;
    public:
        Hand();
        Hand(double t1, double t2, double tz);
        void draw();//Dibuja la extremidad
        void rotar(int r);//Rota la extremidad
        void revolucionar(int r);//Revoluciona la extremidad
        void torcionar(int r);//Torciona la extremidad

};

Hand::Hand(){}

Hand::Hand(double t1, double t2, double tz){
    rotacion = 0;
    revolucion = 0;
    torcion = 0;
    x=1.2;
    y=.7;
    z=1;
    this->t1 = t1;
    this->t2 = t2;
    this->tz = tz;
}

void Hand::draw(){

    GLfloat mat[] = { 238/255.0, 92/255.0, 191/255.0, 1.0f };
    GLfloat mat_shininess[] = { 0.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTranslatef (t1, 0.0, tz);
    glRotatef ((GLfloat) rotacion, 0.0, 0.0, 1.0);
    glRotatef ((GLfloat) revolucion, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) torcion, 1.0, 0.0, 0.0);
    glTranslatef (t2, 0.0, 0.0);

    glPushMatrix();
        glScalef (x, y, z);
        glutSolidSphere (1.0,10,10);
    glPopMatrix();
}

void Hand::rotar(int r){
  if (r>0){
    if (rotacion+r < 90){
      rotacion = (rotacion + r) %360;
    }
  }
  else{
    if (rotacion+r > -90){
      rotacion = (rotacion + r) %360;
    }
  }
}

void Hand::revolucionar(int r){
  if (r>0){
    if (revolucion+r < 45){
      revolucion = (revolucion + r) %360;
    }
  }
  else{
    if (revolucion+r > -45){
      revolucion = (revolucion + r) %360;
    }
  }
}

void Hand::torcionar(int r){
    torcion = (torcion + r) %360;
}
