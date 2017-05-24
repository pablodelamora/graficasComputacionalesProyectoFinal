#pragma once
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>


class Neck{
    private:
        int rotacion;
        int revolucion;
        int torcion;
        double x,y,z;
        double t1,t2,tz;
    public:
        Neck();
        Neck(double t1, double t2, double tz);
        void draw();
        void rotar(int r);//Rota la extremidad
        void revolucionar(int r);//Revoluciona la extremidad
        void torcionar(int r);//Torciona la extremidad

};

Neck::Neck(){}

Neck::Neck(double t1, double t2, double tz){
    rotacion = 0;
    revolucion = 0;
    torcion = 0;
    x=.6;
    y=.6;
    z=.8;
    this->t1 = t1;
    this->t2 = t2;
    this->tz = tz;
}

void Neck::draw(){

    GLfloat mat[] = {238/255.0, 92/255.0, 191/255.0, 1.0f };
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

void Neck::rotar(int r){
  if (r>0){
    if (rotacion+r < 50){
      rotacion = (rotacion + r) %360;
    }
  }
  else{
    if (rotacion+r > -50){
      rotacion = (rotacion + r) %360;
    }
  }

}

void Neck::revolucionar(int r){
  if (r>0){
    if (revolucion+r < 50){
      revolucion = (revolucion + r) %360;
    }
  }
  else{
    if (revolucion+r > -50){
      revolucion = (revolucion + r) %360;
    }
  }
}

void Neck::torcionar(int r){
  if (r>0){
    if (torcion+r < 70){
      torcion = (torcion + r) %360;
    }
  }
  else{
    if (torcion+r > -70){
      torcion = (torcion + r) %360;
    }
  }
}
