#pragma once

#include "vector.h"

class Esfera
{
public:
	Vector3 pivote;
	float radio;
	Esfera(Vector3 pivote, float radio) {
		this->pivote = pivote;
		this->radio = radio;
	}
	~Esfera() = default;

	void renderizar() {
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glColor3f(0.2, 1.0, 0.2);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glPushMatrix();
		glTranslatef(pivote.x, pivote.z, pivote.y);
		glutSolidSphere(radio, 50, 50);
		glPopMatrix();
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	}
};

class Capsula {
public:
	Vector3 pivote;
	Vector3 longitud;
	float radio;
	float longitudScalar;

	Capsula(Vector3 pivote, Vector3 longitud, float radio) {
		this->pivote = pivote;
		this->longitud = longitud;
		longitudScalar = longitud.distancia();
		this->longitud.normalizar();
		this->radio = radio;
	}
	~Capsula() = default;

	void renderizar() {
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glColor3f(0.2, 1.0, 0.2);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glPushMatrix();
		glTranslatef(pivote.x, pivote.z, pivote.y);
		glutSolidSphere(radio, 25, 25);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(pivote.x + longitud.x*longitudScalar, pivote.z + longitud.z*longitudScalar, pivote.y + longitud.y*longitudScalar);
		glutSolidSphere(radio, 25, 25);
		glPopMatrix();
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	};
};
