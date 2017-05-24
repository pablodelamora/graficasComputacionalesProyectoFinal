#pragma once
#include <GL/glut.h>
#include <stdlib.h>


class Leg2{
    private:
        int rotacion;
        int revolucion;
        int torcion;
        double x,y,z;
        double t1,t2,tz;
    public:
        Leg2();
        Leg2(double t1, double t2, double tz);
        void draw();
        void rotar(int r);
        void revolucionar(int r);
        void torcionar(int r);

};

Leg2::Leg2(){}

Leg2::Leg2(double t1, double t2, double tz){
    rotacion = 0;
    revolucion = 0;
    torcion = 0;
    x=3.1;
    y=.7;
    z=1;
    this->t1 = t1;
    this->t2 = t2;
    this->tz = tz;
}

void Leg2::draw(){

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

void Leg2::rotar(int r){
  if (r>0){
    if (rotacion+r < 1){
      rotacion = (rotacion + r) %360;
    }
  }
  else{
    if (rotacion+r > -110){
      rotacion = (rotacion + r) %360;
    }
  }
}

void Leg2::revolucionar(int r){
    revolucion = (revolucion + r) %360;
}

void Leg2::torcionar(int r){
    torcion = (torcion + r) %360;
}
