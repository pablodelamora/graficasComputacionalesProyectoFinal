#pragma once
#include <GL/glut.h>
#include <stdlib.h>


class Arm{
    private:
        int rotacion;
        int revolucion;
        int torcion;
        double x,y,z;//tamanio
        double t1,t2,tz;//traslacion (la da el usuario cuando llama la funcion)
        int derecho; //en el caso de los brazos depende de si es el brazo
        //derecho o izquierdo para poder delimitar los movimientos

    public:
        Arm();
        Arm(double t1, double t2, double tz, int derecho);//funcion que crea la parte
        //del cuerpo
        void draw();//Dibuja la extremidad
        void rotar(int r);//Rota la extremidad
        void revolucionar(int r);//Revoluciona la extremidad
        void torcionar(int r);//Torciona la extremidad

};

Arm::Arm(){}

//la funcion recibe las dimensiones y si es derecho o no
//y asigna los valores
Arm::Arm(double t1, double t2, double tz, int derecho){
    rotacion = 0;
    if (derecho==1)
      revolucion = -20;
    else
      revolucion=20;
    torcion = 0;
    x=3.1;
    y=1;
    z=1;
    this->t1 = t1;
    this->t2 = t2;
    this->tz = tz;
    this->derecho = derecho;
}

//pinta la parte del cuerpo
void Arm::draw(){

    GLfloat mat[] = { 238/255.0, 92/255.0, 191/255.0, 1.0f };//se define el color
    GLfloat mat_shininess[] = { 0.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//color

    glTranslatef (t1, 0.0, tz);//traslada la extremidad
    //aplican las transformaciones
    glRotatef ((GLfloat) rotacion, 0.0, 0.0, 1.0);
    glRotatef ((GLfloat) revolucion, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) torcion, 1.0, 0.0, 0.0);
    glTranslatef (t2, 0.0, 0.0);//Vuelve a trasladar la extremidad

    glPushMatrix();
        glScalef (x, y, z);//Escala la extremidad
        glutSolidSphere (1.0,10,10);//Dibuja esfera
    glPopMatrix();
}

//rota la parte del cuerpo con sus limites
void Arm::rotar(int r){
    if (r>0){
      if (rotacion+r < 200){
        rotacion = (rotacion + r) %360;
      }
    }
    else{
      if (rotacion+r > -50){
        rotacion = (rotacion + r) %360;
      }
    }
}

//revoluciona la parte del cuerpo con sus limites
void Arm::revolucionar(int r){
  if (derecho == 1){
  if (r>0){
    if (revolucion+r < 40){
      revolucion = (revolucion + r) %360;
    }
  }
    else{
      if (revolucion+r > -90){
        revolucion = (revolucion + r) %360;
      }
    }
  }
  else{
    if (r<0){
      if (revolucion+r > -40){
        revolucion = (revolucion + r) %360;
      }
    }
    else{
      if (revolucion+r < 90){
        revolucion = (revolucion + r) %360;
      }
    }
  }
}

//torciona parte del cuerpo
void Arm::torcionar(int r){
    torcion = (torcion + r) %360;
}
