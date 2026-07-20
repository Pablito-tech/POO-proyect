#include "Arquero.hpp"
#include <cstdlib>

Arquero::Arquero() : Unidad() {
    precision = 50.0;
}

Arquero::Arquero(std::string nombre, int nivel, int salud, int ataqueBase, float precision)
    : Unidad(nombre, nivel, salud, ataqueBase) {
    setPrecision(precision);
}

Arquero::~Arquero() {}

float Arquero::getPrecision() const { return precision; }

void Arquero::setPrecision(float precision) {
    if (precision < 0.0)   precision = 0.0;
    if (precision > 100.0) precision = 100.0;
    this->precision = precision;
}

void Arquero::imprime(std::ostream &os) const {
    os << "[ARQUERO ] ";
    Unidad::imprime(os);
    os << " | Precision: " << precision << "%";
}

// Con probabilidad = precision/2 hace TIRO CRITICO (dano x1.75).
// Si no sale el critico, tiene 20% de FALLAR el tiro (dano a la mitad).
int Arquero::calculaAtaque() {
    int danio = Unidad::calculaAtaque();
    int tirada = rand() % 100;

    if (tirada < (int)(precision / 2)) {
        danio = (danio * 7) / 4;
        std::cout << "   >> " << nombre << " acierta un TIRO CRITICO!" << std::endl;
    } else if ((rand() % 100) < 20) {
        danio = danio / 2;
        std::cout << "   >> " << nombre << " falla parcialmente el tiro." << std::endl;
    }
    return danio;
}

// El arquero es agil: con probabilidad precision/4 esquiva y recibe la mitad.
// Pero es de constitucion debil: si es nivel 1 o 2 recibe 20% mas de dano.
void Arquero::recibeAtaque(int danio) {
    int danioReal = danio;

    if ((rand() % 100) < (int)(precision / 4)) {
        danioReal = danioReal / 2;
        std::cout << "   >> " << nombre << " ESQUIVA parcialmente el ataque!" << std::endl;
    }
    if (nivel <= 2) {
        danioReal = (danioReal * 6) / 5;
        std::cout << "   >> " << nombre << " es de complexion debil (+20% de dano)." << std::endl;
    }
    if (danioReal < 1) danioReal = 1;

    std::cout << "   >> " << nombre << " recibe " << danioReal
              << " de dano (original: " << danio << ")." << std::endl;
    Unidad::recibeAtaque(danioReal);

    revive();                                 // ultima oportunidad de vida
}

int Arquero::poder() const {
    return Unidad::poder() + (int)(precision / 2);
}

// SALTO EVASIVO: si cae a 0 pero su precision es de 50% o mas, alcanza a
// esquivar el golpe mortal. Cuesta 35 puntos de precision.
void Arquero::revive() {
    if (salud > 0) return;

    if (precision >= 50.0) {
        setPrecision(precision - 35.0);
        setSalud(15);
        std::cout << "   ** " << nombre << " REVIVIO gracias a su PRECISION (salto evasivo)! "
                  << "Salud: " << salud << " | Precision restante: " << precision << "%"
                  << std::endl;
    } else {
        std::cout << "   ** " << nombre << " ya no tiene punteria para esquivar... HA MUERTO."
                  << std::endl;
    }
}
