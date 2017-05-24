
#pragma once

// basado en: https://github.com/ArturoNereu/ClothSim/blob/master/include/Spring.h por Arturo Neue

#include <GL/glut.h>
#include "particula.h"
#include "vector.h"
#include <cfloat>

class Resorte {
public:
    Particula *inicio; //las particulas interconectadas
    Particula *fin;
    float ks; //coeficiente de agarre
    float kd; //coeficiente elasticidad
    float longitudInicial; //distancia original

    Resorte() = default;

    //se crea el resorte entre dos particulas
    Resorte(Particula *p1, Particula *p2) {
        inicio = p1;
        fin = p2;
        longitudInicial = this->obtenerLongitud();
    }
    ~Resorte() = default;

    //se actualizan los datos cada 25ms
    void actualizar(float ks, float kd) {
        this->ks = ks;
        this->kd = kd;

        applicarFuerza();
    }

    //se manda a la pantalla
    void renderizar() {
        glColor3f(0, 1, 1);
        glBegin(GL_LINES);
            glVertex3f(inicio->posicion.x, inicio->posicion.z, inicio->posicion.y);
            glVertex3f(fin->posicion.x, fin->posicion.z, fin->posicion.y);
        glEnd();
    }

    const float obtenerLongitud() {
		Vector3 tmp;
		tmp.x = (fin->posicion.x - inicio->posicion.x);
		tmp.y = (fin->posicion.y - inicio->posicion.y);
		tmp.z = (fin->posicion.z - inicio->posicion.z);
        return tmp.distancia();
    }
private:

    //se le aplica alguna fuerza que esaba previamente definida
    //en este proyecto se le aplican 3 fuerzas a la falda
    //gravedad, resortes y viento
    void applicarFuerza() {
        Vector3 ve;
		ve.x = fin->posicion.x - inicio->posicion.x;
		ve.y = fin->posicion.y - inicio->posicion.y;
		ve.z = fin->posicion.z - inicio->posicion.z;

        float v1 = ve.producto_punto(inicio->velocidad);
        float v2 = ve.producto_punto(fin->velocidad);

        float fSD = -ks * (longitudInicial - this->obtenerLongitud()) - kd * (v1 - v2);
		if (!std::isfinite(fSD))
			return;
        Vector3 resultado = ve * fSD;
        inicio->agregarFuerza(resultado);
        fin->agregarFuerza(resultado*(-1.0));
    }

};
