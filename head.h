#pragma once
#include <GL/glut.h>
#include <stdlib.h>


class Head{
    private:
        int rotacion;
        int revolucion;
        int torcion;
        double x,y,z;
        double t1,t2,tz;
    public:
        Head();
        Head(double t1, double t2, double tz);
        void draw();//Dibuja la extremidad
        void rotar(int r);//Rota la extremidad
        void revolucionar(int r);//Revoluciona la extremidad
        void torcionar(int r);//Torciona la extremidad

};

Head::Head(){}

Head::Head(double t1, double t2, double tz){
    rotacion = 0;
    revolucion = 0;
    torcion = 0;
    x=1.7;
    y=1;
    z=1.5;
    this->t1 = t1;
    this->t2 = t2;
    this->tz = tz;
}

void Head::draw(){

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

void Head::rotar(int r){
    rotacion = (rotacion + r) %360;
}

void Head::revolucionar(int r){
    revolucion = (revolucion + r) %360;
}

void Head::torcionar(int r){
    torcion = (torcion + r) %360;
}
