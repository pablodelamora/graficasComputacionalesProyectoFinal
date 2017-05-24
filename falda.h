
#include <vector>
#include "vector.h"
#include "particula.h"
#include "resorte.h"

const float PI = 3.14159;

class Falda {
public:
    std::vector<Particula> particulas;
    std::vector<Resorte> resortes;
    std::vector<int> indices;

    Vector3 posicion;
	Vector3 gravedad;
	Vector3 viento;
	float fuerzaViento = 0.1;
	float anguloViento = PI;
    float largo;
    float radio;
	float radioFinal;
    int segmentosX;
    int segmentosY;

    Falda() = default;

    //se inicializa con los valores iniciales
    Falda(Vector3& posicion, float largo, float radio, float radioFinal, int segmentosX, int segmentosY) {
        this->posicion = posicion;
        this->largo = largo;
        this->radio = radio;
		this->radioFinal = radioFinal;
        this->segmentosX = segmentosX;
        this->segmentosY = segmentosY;
		Vector3 g(0.0, 0.0, -0.25);//esta es la gravedad
		gravedad = g;
		actualizarViento();
    }

    //se inicializa la falda
    void inicializar() {
        size_t numParticulas = segmentosX*(segmentosY + 1);
        particulas.reserve(numParticulas);
        resortes.reserve(numParticulas*2);
		indices.reserve(numParticulas*6);
        const float angulo = 2*PI/segmentosX;
        const float distY = largo / segmentosY;
		float inicioRadio = radio;
		float delta = (radioFinal - radio) / segmentosY;
        for (int i = 0; i <= segmentosY; i++) {
            float rotador = 0.0;
            for (int j = 0; j < segmentosX; j++) {
                Vector3 pos = posicion + Vector3(inicioRadio*std::cos(rotador), inicioRadio*std::sin(rotador), -i*distY);
                Particula p;
				if (i == 0)
					p.estaFija = true;
                p.ponerPosicion(pos);
                particulas.push_back(std::move(p));
                rotador += angulo;
            }
			inicioRadio += delta;
        }

		// Resortes Horizontales
		for (int i = 0; i <= segmentosY; i++) {
			for (int k = 0; k < segmentosX; k++) {
				int j = (k + 1) % segmentosX;
				Resorte r(&particulas[k + i*segmentosX], &particulas[j + i*segmentosX]);
				resortes.push_back(std::move(r));
			}
		}

		// Resortes verticales
		for (int i = 0; i < segmentosY; i++) {
			for (int k = 0; k < segmentosX; k++) {
				Resorte r(&particulas[k + i*segmentosX], &particulas[k + (i + 1)*segmentosX]);
				resortes.push_back(std::move(r));
			}
		}

		// Resortes Diagonales
		for (int i = 0; i < segmentosY; i++) {
			for (int k = 0; k < segmentosX; k++) {
				int j = (k + 1) % segmentosX;
				Resorte r(&particulas[k + i*segmentosX], &particulas[j + (i + 1)*segmentosX]);
				resortes.push_back(std::move(r));
				Resorte r2(&particulas[j + i*segmentosX], &particulas[k + (i + 1)*segmentosX]);
				resortes.push_back(std::move(r2));
			}
		}

		// Malla
		for (int i = 0; i < segmentosY; i++) {
			for (int k = 0; k < segmentosX; k++) {
				int j = (k + 1) % segmentosX;
				int a1 = k + i*segmentosX, a2 = k + (i + 1)*segmentosX;
				int a3 = j + i*segmentosX, a4 = j + (i + 1)*segmentosX;
				indices.push_back(a1);
				indices.push_back(a2);
				indices.push_back(a3);

				indices.push_back(a2);
				indices.push_back(a4);
				indices.push_back(a3);
			}
		}

		//Normales (no se usa esta seccion)
		for (int i = 0; i <= segmentosY; i++) {
			for (int k = 0; k < segmentosX; k++) {
				int j = (k + 1) % segmentosX;
				int n = (segmentosX + k - 1) % segmentosX;
				int l = i*segmentosX;
				Vector3 pos = particulas[k + l].posicion;
				Vector3 normal = pos - particulas[j + l].posicion;
				normal = normal + (pos - particulas[n + l].posicion);
				if (i != 0) {
					normal = normal + (pos - particulas[k + ((segmentosY + i - 1) % segmentosY)*segmentosX].posicion);
				}
				if (i != segmentosY) {
					normal = normal + (pos - particulas[k + (i + 1)*segmentosX].posicion);
				}
				normal.normalizar();
				normal = normal + Vector3(0.0, 0.0, 1.0);
				normal.normalizar();
				particulas[k + l].normal = normal;
			}
		}
    }

    //renderiza la falda
    void renderizar(bool malla, bool debug) {
		if (malla) {
            glFrontFace(GL_CW);
			glDisable(GL_AUTO_NORMAL);
			//glDisable(GL_NORMALIZE);
			glBegin(GL_TRIANGLES);
			for (auto it = indices.begin(); it != indices.end(); it++) {
				int p = *it;
				Vector3& pos = particulas[p].posicion;
				Vector3& normal = particulas[p].normal;
				glVertex3f(pos.x, pos.z, pos.y);
				glNormal3f(normal.x, normal.z, normal.y);
			}
			glEnd();
			glEnable(GL_AUTO_NORMAL);
			glEnable(GL_NORMALIZE);
		}
		if (debug) {
			glDisable(GL_LIGHTING);
			for (auto it = resortes.begin(); it != resortes.end(); it++) {
				Resorte& r = *it;
				r.renderizar();
			}
			for (auto it = particulas.begin(); it != particulas.end(); it++) {
				Particula& p = *it;
				p.renderizar();
			}
			glEnable(GL_LIGHTING);
		}
    }

//se actualizan los datos
	void actualizar() {
		for (auto it = particulas.begin(); it != particulas.end(); it++) {
			Particula& p = (*it);
			p.anularFuerzas();
			p.agregarFuerza(gravedad);
			p.agregarFuerza(viento);
		}
		for (auto it = resortes.begin(); it != resortes.end(); it++) {
			Resorte& r = *it;
			r.actualizar(2.0, 0.2);
		}
		for (auto it = particulas.begin(); it != particulas.end(); it++) {
			Particula& p = *it;
			p.actualizar();
		}
	}

  //se ajusta la esfera
	void ajustar(Esfera& e) {
		for (auto it = particulas.begin(); it != particulas.end(); it++) {
			Particula& p = (*it);
			if (!p.estaFija)
				p.ajustar(e);
		}
	}


  //se ajusta la capsula
	void ajustar(Capsula& c) {
		for (auto it = particulas.begin(); it != particulas.end(); it++) {
			Particula& p = (*it);
			if (!p.estaFija)
				p.ajustar(c);
		}
	}

  //se actualiza el viento
	void actualizarViento() {
		Vector3 v(cosf(anguloViento)*fuerzaViento, sinf(anguloViento)*fuerzaViento, 0.0);
		viento = v;
	}

  //se le da fuerza al viento
	void ponerFuerzaViento(float nuevaFuerza) {
		fuerzaViento = nuevaFuerza;
		actualizarViento();
	}

  //se pone el angulo
	void ponerAnguloViento(float nuevoAngulo) {
		anguloViento = nuevoAngulo;
		actualizarViento();
	}
};
