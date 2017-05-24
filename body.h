#pragma once
#include <GL/glut.h>
#include <stdlib.h>

//Todas las funcionalidades estan explicadas en arm.h ya que seccion
//iguales las clases y su funcionalidad cambia solo valores


class Body{
    private:
        int rotacion;
        int revolucion;
        int torcion;
        double x,y,z;//escala
        double t1,t2,tz;
    public:
        Body();
        Body(double t1, double t2, double tz);
        void draw();
        void rotar(int r);//Rota la extremidad
        void revolucionar(int r);//Revoluciona la extremidad
        void torcionar(int r);//Torciona la extremidad

};
Body::Body(){

}
Body::Body(double t1, double t2, double tz){
    rotacion = 0;
    revolucion = 0;
    torcion = 0;
    x=2.5;
    y=7;
    z=2.3;
    this->t1 = t1;
    this->t2 = t2;
    this->tz = tz;
}

void Body::draw(){

    GLfloat mat[] = { 255/255.0, 255/255.0, 255/255.0, 1.0f };
    GLfloat mat_shininess[] = { 0.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//color

    glTranslatef (t1, 0.0, tz);//traslada la extremidad
    //Las siguientes 3 lineas rotan la extremidad
    glRotatef ((GLfloat) rotacion, 0.0, 0.0, 1.0);
    glRotatef ((GLfloat) revolucion, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) torcion, 1.0, 0.0, 0.0);
    glTranslatef (t2, 0.0, 0.0);

    glPushMatrix();
        glScalef (x, y, z);
        glutSolidSphere (1.0,10,10);
    glPopMatrix();
}

void Body::rotar(int r){
    rotacion = (rotacion + r) %360;
}

void Body::revolucionar(int r){
  if (r>0){
    if (revolucion+r < 40){
      revolucion = (revolucion + r) %360;
    }
  }
  else{
    if (revolucion+r > -40){
      revolucion = (revolucion + r) %360;
    }
  }
}

void Body::torcionar(int r){
    torcion = (torcion + r) %360;
}
