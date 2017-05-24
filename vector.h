#pragma once

#include <cmath>

//en esta seccion se declaran as fuerzas usadas que afextan a la falda.
//se hcacen los calculos necesarios para poder simular el movimiento
//haciendo operacion de vectores.


//se crea la clase con los datos que afectaran la falda
class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3() = default;

    Vector3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    ~Vector3() = default;

    const float distancia() const {
        return sqrtf(x*x + y*y + z*z);
    }

    //se normaliza el vector
    void normalizar() {
        float dist = this->distancia();
        x = x / dist;
        y = y / dist;
        z = z / dist;
    }

    //suma de vectores
    const Vector3 operator+(const Vector3 v1) const {
        Vector3 vr;
        vr.x = this->x + v1.x;
        vr.y = this->y + v1.y;
        vr.z = this->z + v1.z;
        return vr;
    }

    //resta de vectores
    const Vector3 operator-() const {
        Vector3 vr;
        vr.x = - this->x;
        vr.y = - this->y;
        vr.z = - this->z;
        return vr;
    }

    //resta de vectores
    const Vector3 operator-(const Vector3 v1) const {
        Vector3 vr;
        Vector3 v2 = *this;
        vr.x = v2.x - v1.x;
        vr.y = v2.y - v1.y;
        vr.z = v2.z - v1.z;
        return vr;
    }

    //multiplicacion de vectores
    const Vector3 operator*(float scalar) const {
        Vector3 vr;
        vr.x = this->x * scalar;
        vr.y = this->y * scalar;
        vr.z = this->z * scalar;
        return vr;
    }

    //multiplicacion de vectores
    const Vector3 operator*(const Vector3 v1) const {
        Vector3 vr;
        Vector3 v2 = *this;
        vr.x = v2.x * v1.x;
        vr.y = v2.y * v1.y;
        vr.z = v2.z * v1.z;
        return vr;
    }

    //conseguir el producto punto
    const float producto_punto(const Vector3 v2) const {
        const Vector3& v1 = *this;
        return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
    }

    //producto cruz
    const Vector3 producto_cruz(const Vector3& v2) const {
        Vector3 vr;
        const Vector3& v1 = *this;
        vr.x = v1.y*v2.z - v1.z*v2.z;
        vr.y = v1.z*v2.x - v1.x*v2.z;
        vr.z = v1.x*v2.y - v1.y*v2.x;
        return vr;
    }

    //se rota el angulo
	const Vector3 rotar(const Vector3& eje, float angulo) const {
		Vector3 vr;
		const Vector3 v1 = *this;
		const float c = cosf(angulo);
		// Forumla de Rodriguez.
		vr = v1*c + eje.producto_cruz(v1)*sinf(angulo) + (eje*v1.producto_punto(eje)*(1 - c));
		return vr;
	}


};
