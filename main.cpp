//Pablo de la Mora
//Abraham Esses



#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include "body.h"
#include "leg.h"
#include "leg2.h"
#include "arm.h"
#include "hand.h"
#include "neck.h"
#include "head.h"
#include "feet.h"
#include "forearm.h"
#include "vector.h"
#include "falda.h"
#include "figuras.h"

GLuint LoadTexture(const char * filename)
{

	GLuint texture;

	int width, height;

	unsigned char * data;

	FILE * file;

	file = fopen(filename, "rb");

	if (file == NULL) {
		printf("Texture Loading failed!\n");
		return 0;
	}
	width = 256;
	height = 256;
	data = (unsigned char *)malloc(width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}

//en esta seccion se crean las variables con las dimensiones del cuerpo
//que acabo de crear


//las teclas para mover al personaje empieza en la q y va hasta la B
//recorriendo las letras del teclado de derecha a Izquierda
//las mayusculas hacen el movimiento contrario a la minuscula

//torso
Body body(-3.5,0,0);

//brazos
Arm armL(0.0, 1.75,-2.5,0);
Arm armR(0.0, 1.75, 2.5, 1);

//antebrazos
Forearm forearmL (1.75, 2.6, 0.0, 1);
Forearm forearmR (1.75, 2.6, 0.0, 0);

//manos
Hand handR(2.6, .7, 0.0);
Hand handL(2.6, .7, 0.0);

//piernas
Leg upperLegR(0.0, 1.75,-1.5);
Leg upperLegL(0.0, 1.75, 1.5);

//piernas bajas
Leg2 lowerLegR(1.75, 2.6, 0.0);
Leg2 lowerLegL(1.75, 2.6, 0.0);

//pies
Feet feetR(2.6, .7, 0.0);
Feet feetL(2.6, .7, 0.0);


Neck neck( 0.0, .6, 0.0);
Head head(1.1, .7, 0.0);

//se crea la falda
Vector3 faldaPos(-3.5, 0.0, 0.0);
Falda falda(faldaPos, 3.0, 2.25, 4.0, 32, 12);


//se crean las esferas
Vector3 esferaPos(-3.5, 0.0, -2.0);
Esfera esferaColCuerpo(esferaPos, 2.25);

//capsulas
Vector3 capsulaDerPos(-3.5, 1.5, -2.0);
Vector3 capsulaIzqPos(-3.5, -1.5, -2.0);
Vector3 capsulaLargo(0.0, 0.0, -4.0);
Capsula capsulaIzqCol(capsulaIzqPos, capsulaLargo, 1.5);
Capsula capsulaDerCol(capsulaDerPos, capsulaLargo, 1.5);

GLuint marbolTex = 0;

//aqui se declara la iluminacion y materiales
void init(void)
{
   GLfloat mat_specular[] = { 0.6, 0.6, 0.6, 1.0 };
   GLfloat mat_ambient[] = {1.0,1.0,1.0,1.0};
   GLfloat mat_shininess[] = { 0.0 };
   GLfloat light_position[] = { 0.0, 5.0, 5.0, 1.0 };

   glClearColor (0.0, 0.0, 0.0, 1.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);


   falda.inicializar();

   marbolTex = LoadTexture("marble.bmp");

}

int down = 0, lastx;
int direccion = 0;
int zoom = 0;





/* ARGSUSED1 */
void
motion(int x, int y)
{
    if (down & direccion==0) {
        glRotatef(lastx - x, 1, 0, 0);
        lastx = x;
        glutPostRedisplay();
    }
    else  if (down & direccion==1) {
          glRotatef(lastx - x, 0, 1, 0);
          lastx = x;
          glutPostRedisplay();
      }

    else  if (down & direccion==2) {
          glRotatef(lastx - x, 0, 0, 1);
          lastx = x;
          glutPostRedisplay();
      }


      if(down & zoom == 0){


      }

}








//funiones que dibujan las partes completas
//se pintan todos los brazos en una misma funcion
//asi como piernas y cabeza

//torso
void drawBody(){
  body.draw();
}

//brazos
void drawArms(){
  glPushMatrix();
      armL.draw();
      forearmL.draw();
      handL.draw();
  glPopMatrix();
  glPushMatrix();
      armR.draw();
      forearmR.draw();
      handR.draw();
  glPopMatrix();
}

//piernas
void drawLegs(){
  glPushMatrix();
      upperLegL.draw();
      lowerLegL.draw();
      feetL.draw();
  glPopMatrix();
  glPushMatrix();
      upperLegR.draw();
      lowerLegR.draw();
      feetR.draw();
  glPopMatrix();
}

//cabeza
void drawHead(){
  glPushMatrix();
      neck.draw();
      head.draw();
  glPopMatrix();
}

void drawFalda() {
    glPushMatrix();
        falda.renderizar(true, false);
    glPopMatrix();
}



//Se usan las funciones y se colocan donde se desean para que tenga
//sentido
void display(void)
{
  GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
  GLfloat mat_ambient_color[] = { 0.5, 0.8, 0.2, 1.0 };
  GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
  GLfloat mat_specular[] = { .5, .5, .5, .5 };
  GLfloat no_shininess[] = { 0.0 };
  GLfloat low_shininess[] = { 5.0 };
  GLfloat high_shininess[] = { 100.0 };
  GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

  GLfloat mat_diffuse_body[] = { 0.8, 0.7, 0.5, 1.0 };
  GLfloat mat_diffuse_falda[] = { 0.8, 0.5, 0.1, 1.0 };
  glShadeModel(GL_SMOOTH);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_body);
        glPushMatrix();
          glTranslatef(0.0,3,0);
          drawBody();
        glPopMatrix();

        glPushMatrix();
          glRotatef(-90,0,0,1);
          glTranslatef(-5,-3.0,0.0);
          drawArms();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-3.5,-3.5,0);
            glRotatef(-90,0,0,1);
            drawLegs();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-3.5, 9.5,0);
            glRotatef( 90,0,0,1);
            drawHead();
        glPopMatrix();

    glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_diffuse_falda);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_falda);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse_falda);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	falda.actualizar();
	falda.ajustar(esferaColCuerpo);
	falda.ajustar(capsulaIzqCol);
	falda.ajustar(capsulaDerCol);
	drawFalda();

	esferaColCuerpo.renderizar();
	capsulaIzqCol.renderizar();
	capsulaDerCol.renderizar();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_FLAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glDisable(GL_LIGHTING);
	glBegin(GL_TRIANGLES);
		glBindTexture(GL_TEXTURE_2D, marbolTex);
		glVertex3f(100.0, -20.0, -100.0);
		glTexCoord2f(1.0, 0);
		glNormal3f(0, 1, 0);
		glVertex3f(100.0, -20.0, 100.0);
		glTexCoord2f(1.0, 1.0);
		glNormal3f(0, 1, 0);
		glVertex3f(-100.0, -20.0, -100.0);
		glTexCoord2f(0, 0);
		glNormal3f(0, 1, 0);

		glVertex3f(100.0, -20.0, 100.0);
		glTexCoord2f(1.0, 1.0);
		glNormal3f(0, 1, 0);
		glVertex3f(-100.0, -20.0, 100.0);
		glTexCoord2f(0, 1.0);
		glNormal3f(0, 1, 0);
		glVertex3f(-100.0, -20.0, -100.0);
		glTexCoord2f(0, 0);
		glNormal3f(0, 1, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}


void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, -8.0, -40.0);
   glRotatef (-45.0, 0.0, 1.0, 0.0);
}



void
mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            lastx = x;
            down = 1;
        } else {
            down = 0;
        }
    }

    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            lastx = x;
            down = 1;
        } else {
            down = 0;
        }
    }


}







//en esta parte se definen las teclas para poder mover al personaje

//teclas que mueven la cabeza
void rotarCabeza(unsigned char key){
    switch(key){
        //Cabeza y cuello
        case 'q':
            neck.rotar(5);
            glutPostRedisplay();
        break;
        case 'Q':
            neck.rotar(-5);
            glutPostRedisplay();
        break;
        case 'w':
            neck.torcionar(5);
            glutPostRedisplay();
        break;
        case 'W':
            neck.torcionar(-5);
            glutPostRedisplay();
        break;
    }
}

//teclas que mueven los brazos
void rotarBrazos(unsigned char key){
    switch(key){
        //brazo Izquierdo
        case 'e':
            armL.rotar(5);
            glutPostRedisplay();
        break;
        case 'E':
            armL.rotar(-5);
            glutPostRedisplay();
        break;
        case 'r':
            armL.revolucionar(5);
            glutPostRedisplay();
        break;
        case 'R':
            armL.revolucionar(-5);
            glutPostRedisplay();
        break;
        //Brazo Derecho
        case 't':
            armR.rotar(5);
            glutPostRedisplay();
        break;
        case 'T':
            armR.rotar(-5);
            glutPostRedisplay();
        break;
        case 'y':
            armR.revolucionar(5);
            glutPostRedisplay();
        break;
        case 'Y':
            armR.revolucionar(-5);
            glutPostRedisplay();
        break;
    }
}

//teclas que mueven los antebrazos
void rotarAnteBrazos(unsigned char key){
    switch(key){
        //Antebrazo Izquierdo
        case 'u':
            forearmL.rotar(5);
            glutPostRedisplay();
        break;
        case 'U':
            forearmL.rotar(-5);
            glutPostRedisplay();
        break;
        case 'i':
            forearmL.torcionar(5);
            glutPostRedisplay();
        break;
        case 'I':
            forearmL.torcionar(-5);
            glutPostRedisplay();
        break;
        //Antebrazo Derecho
        case 'o':
            forearmR.rotar(5);
            glutPostRedisplay();
        break;
        case 'O':
            forearmR.rotar(-5);
            glutPostRedisplay();
        break;
        case 'p':
            forearmR.torcionar(5);
            glutPostRedisplay();
        break;
        case 'P':
            forearmR.torcionar(-5);
            glutPostRedisplay();
        break;

    }
}

//teclas que rotan las manos
void rotarManos(unsigned char key){
    switch(key){
        //Mano Izquierda
        case 'a':
            handL.rotar(5);
            glutPostRedisplay();
        break;
        case 'A':
            handL.rotar(-5);
        glutPostRedisplay();
        break;
        case 's':
            handL.revolucionar(5);
            glutPostRedisplay();
        break;
        case 'S':
            handL.revolucionar(-5);
        glutPostRedisplay();
        break;
        //Mano Derecha
        case 'd':
            handR.rotar(5);
            glutPostRedisplay();
        break;
        case 'D':
            handR.rotar(-5);
        glutPostRedisplay();
        break;
        case 'f':
            handR.revolucionar(5);
            glutPostRedisplay();
        break;
        case 'F':
            handR.revolucionar(-5);
        glutPostRedisplay();
        break;

    }
}


//teclas que rotan las piernas
void rotarPiernas(unsigned char key){
	const Vector3 ejeX(1.0, 0.0, 0.0);
	const Vector3 ejeY(0.0, 0.0, 1.0);
	const Vector3 ejeZ(0.0, 1.0, 0.0);
	static int countDerZM = 12;
	static int countDerXM = 12;
	static int countIzqZM = 12;
	static int countIzqXM = 12;
    switch(key){
        //Pierna Izquierda
        case 'g':

			if (countDerZM <= 24) {
				upperLegL.rotar(5);
				capsulaDerCol.longitud = capsulaDerCol.longitud.rotar(ejeZ, -PI*4.0 / 180.0);
				countDerZM++;
			}
            glutPostRedisplay();
        break;
        case 'G':
			if (countDerZM >= 0) {
				capsulaDerCol.longitud = capsulaDerCol.longitud.rotar(ejeZ, PI*4.0 / 180.0);
				countDerZM--;
				upperLegL.rotar(-5);
			}
        glutPostRedisplay();
        break;
        case 'h':
			if (countDerXM <= 24) {
				upperLegL.revolucionar(5);
				capsulaDerCol.longitud = capsulaDerCol.longitud.rotar(ejeX, -PI*4.0 / 180.0);
				countDerXM++;
			}
            glutPostRedisplay();
        break;
        case 'H':
			if (countDerXM >= 0) {
				upperLegL.revolucionar(-5);
				capsulaDerCol.longitud = capsulaDerCol.longitud.rotar(ejeX, PI*4.0 / 180.0);
				countDerXM--;
			}
        glutPostRedisplay();
        break;

        //Pierna Derecha
        case 'j':
            upperLegR.rotar(5);
			capsulaIzqCol.longitud = capsulaIzqCol.longitud.rotar(ejeZ, -PI*4.0 / 180.0);
            glutPostRedisplay();
        break;
        case 'J':
            upperLegR.rotar(-5);
			capsulaIzqCol.longitud = capsulaIzqCol.longitud.rotar(ejeZ, PI*4.0 / 180.0);
			glutPostRedisplay();
        break;
        case 'k':
            upperLegR.revolucionar(5);
			capsulaIzqCol.longitud = capsulaIzqCol.longitud.rotar(ejeX, -PI*3.5 / 180.0);
            glutPostRedisplay();
        break;
        case 'K':
            upperLegR.revolucionar(-5);
			capsulaIzqCol.longitud = capsulaIzqCol.longitud.rotar(ejeX, PI*3.5 / 180.0);
        glutPostRedisplay();
        break;
    }
}

//teclas que rotan las piernas en la parte inferior
void rotarPiernas2(unsigned char key){
    switch(key){
        //Pierna2 Izquierda
        case 'l':
            lowerLegL.rotar(5);
            glutPostRedisplay();
        break;
        case 'L':
            lowerLegL.rotar(-5);
        glutPostRedisplay();
        break;
        //Pierna2 Derecha
        case 'z':
            lowerLegR.rotar(5);
            glutPostRedisplay();
        break;
        case 'Z':
            lowerLegR.rotar(-5);
        glutPostRedisplay();
        break;
    }
}


//teclas que rotan los pies
void rotarTobillos(unsigned char key){
    switch(key){
        //Tobillo Izquierdo
        case 'x':
            feetL.rotar(5);
            glutPostRedisplay();
        break;
        case 'X':
            feetL.rotar(-5);
        glutPostRedisplay();
        break;
        case 'c':
            feetL.revolucionar(5);
            glutPostRedisplay();
        break;
        case 'C':
            feetL.revolucionar(-5);
            glutPostRedisplay();
        break;
        //Tobillo Derecha
        case 'v':
            feetR.rotar(5);
            glutPostRedisplay();
        break;
        case 'V':
            feetR.rotar(-5);
        glutPostRedisplay();
        break;
        case 'b':
            feetR.revolucionar(5);
            glutPostRedisplay();
        break;
        case 'B':
            feetR.revolucionar(-5);
            glutPostRedisplay();
        break;
    }
}

//rotar torso
void rotarTorso(unsigned char key){
	switch (key) {
	case '1':
		body.revolucionar(5);
		glutPostRedisplay();
		break;
	case '2':
		body.revolucionar(-5);
		glutPostRedisplay();
		break;
	}
}

void cambiarViento(unsigned char key){
	  static float fuerza = 0.1;
	  static float angulo = PI;
	  switch (key) {
	  case '3':
		  if (fuerza > 0.005)
			fuerza *= 0.5;
		  falda.ponerFuerzaViento(fuerza);
		  glutPostRedisplay();
		  break;
	  case '4':
		  if (fuerza < 0.5)
			  fuerza *= 2.0;
		  falda.ponerFuerzaViento(fuerza);
		  glutPostRedisplay();
		  break;
	  case '5':
		  angulo += (PI * 0.125);
		  falda.ponerAnguloViento(angulo);
		  glutPostRedisplay();
		  break;
	  case '6':
		  angulo -= (PI * 0.125);
		  falda.ponerAnguloViento(angulo);
		  glutPostRedisplay();
		  break;
	}
}

//se esta analizando el teclado esperando que tecleen algo
void keyboard (unsigned char key, int x, int y)
{
    rotarBrazos(key);
    rotarAnteBrazos(key);
    rotarManos(key);
    rotarPiernas(key);
    rotarPiernas2(key);
    rotarTobillos(key);
    rotarCabeza(key);
    rotarTorso(key);
	cambiarViento(key);
    switch (key) {
        case 27:
            exit(0);
        break;

        /*Movimiento en x*/
           case '8':
           direccion=0;
                glutPostRedisplay();
                break;
           case '9':

           direccion=1;
                glutPostRedisplay();
                break;
       /*Movimiento en Z*/
           case '0':

           direccion=2;
                glutPostRedisplay();
                break;


        default:
        break;
   }
}


//loop para que siempre corra
void simulacion(int value)
{
	glutTimerFunc(25, simulacion, 0);
	glutPostRedisplay();
}


//funcion main que declara tamano de ventana, etc.
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize (900, 800);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   glutTimerFunc(25, simulacion, 0);
   glutMainLoop();
   return 0;
}
