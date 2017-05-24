#pragma once

#include <GL/glut.h>
#include <stdio.h>
#include "vector.h"
#include "figuras.h"

// Basado originalmente de: https://github.com/ArturoNereu/ClothSim/blob/master/include/Particle.h

//la falda esta creada de muchas particulas interconectadas entre si por resortes
class Particula
{
    public:
        float masa; //masa de la particula

        float radio; //radio de la particula

        Vector3 posicion; //la posicion de la particula
        Vector3 posicionAnterior; //la ultima posicion de la particula
        Vector3 fuerzaAcumulada;
        Vector3 velocidad;
        bool estaFija; //las de hasta arriba pegadas a la cintura son fijas
        //para que no se vaya volando la falda
        Vector3 normal;

        //constructor
        Particula() {
            masa = 0.05;
            radio = 1.0;
            Vector3 base(0.0,0.0,0.0);
            posicion = base;
            posicionAnterior = base;
            fuerzaAcumulada = base;
            velocidad = base;
            estaFija = false;
            normal = base;
        }
        ~Particula() = default;

        //se le asigna la posicion a la particula
        void ponerPosicion(Vector3& v1) {
            posicion = v1;
            posicionAnterior = v1;
        }
        //se le anulan las fuerzas que se le estaban aplicando
        void anularFuerzas() {
            fuerzaAcumulada = fuerzaAcumulada * 0;
        }

        //se agrega una nueva fuerza que influya en el comportamiento
        void agregarFuerza(const Vector3& v1) {
            fuerzaAcumulada = fuerzaAcumulada + v1;
        }

        //se renderiza
        void renderizar() {
            glPointSize((int)radio*4);

            if(estaFija)
                glColor3f(0, 0.5, 1.0);
            else
                glColor3f(1.0, 0.5, 0.1);

            glBegin(GL_POINTS);
                glVertex3f(posicion.x, posicion.z, posicion.y);
            glEnd();
        }

        //se aplica formula de verlet para conseguir posicion
        Vector3 integracionVerletDePosicion() {
            Vector3 sigPos;
            sigPos.x = (posicion.x * 2) + (fuerzaAcumulada.x * (0.1f * 0.1f)) - posicionAnterior.x;
			sigPos.y = (posicion.y * 2) + (fuerzaAcumulada.y * (0.1f * 0.1f)) - posicionAnterior.y;
			sigPos.z = (posicion.z * 2) + (fuerzaAcumulada.z * (0.1f * 0.1f)) - posicionAnterior.z;
            return sigPos;
        }

        //se actualiza
        void actualizar() {
            velocidad.x = fuerzaAcumulada.x * 0.1f;
			velocidad.y = fuerzaAcumulada.y * 0.1f;
			velocidad.z = fuerzaAcumulada.z * 0.1f;
            if (!estaFija) {
                Vector3 tmp = posicion;
                posicion = integracionVerletDePosicion();
                posicionAnterior = tmp;
            }
        }

    //se ajusta la esfera
		void ajustar(Esfera& e) {
			Vector3 v = posicion - e.pivote;
			float d = v.distancia();
			if (d < e.radio + 0.2) {
				float l = e.radio - d + 0.2;
				v.normalizar();
				posicionAnterior = posicion;
				posicion = posicion + (v*l);
			}
		}

    //se ajusta la capsula
		void ajustar(Capsula& c) {
			const Vector3 v = posicion - c.pivote;
			const Vector3 normal = c.longitud;
			const Vector3 reflect = normal*v.producto_punto(normal);
			Vector3 v2 = v - reflect;
			const float t = v2.distancia();
			if (t < c.radio + 0.1) {
				v2.normalizar();
				posicionAnterior = posicion;
				posicion = posicion + v2*(c.radio - t + 0.1);
			}
		}
};
