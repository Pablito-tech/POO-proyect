#include "Guerrero.hpp"
#include <cstdlib>

Guerrero::Guerrero() : Unidad() {
    fuerza = 50;
}

Guerrero::Guerrero(std::string nombre, int nivel, int salud, int ataqueBase, int fuerza)
    : Unidad(nombre, nivel, salud, ataqueBase) {
    setFuerza(fuerza);
}

Guerrero::~Guerrero() {}

int Guerrero::getFuerza() const { return fuerza; }

void Guerrero::setFuerza(int fuerza) {
    if (fuerza < 0) fuerza = 0;
    if (fuerza > 100) fuerza = 100;
    this->fuerza = fuerza;
}

void Guerrero::imprime(std::ostream &os) const {
    os << "[GUERRERO] ";
    Unidad::imprime(os);                     // reutiliza el imprime de la clase base
    os << " | Fuerza: " << fuerza;
}

// Ataque = ataque de Unidad + (fuerza/10). Con fuerza >= 60 hay 25% de golpe
// contundente que aumenta el dano un 50%.
int Guerrero::calculaAtaque() {
    int danio = Unidad::calculaAtaque();     // reutiliza el ataque base
    danio += fuerza / 10;                    // +0 a +10 puntos

    if (fuerza >= 60 && (rand() % 100) < 25) {
        danio = (danio * 3) / 2;
        std::cout << "   >> " << nombre << " lanza un GOLPE CONTUNDENTE!" << std::endl;
    }
    return danio;
}

// La fuerza funciona como armadura: resta fuerza/20 al dano recibido.
// Si el guerrero es de nivel 1 todavia no sabe cubrirse: recibe 25% mas de dano.
// Al final se llama a revive() por si quedo en 0 de salud.
void Guerrero::recibeAtaque(int danio) {
    int danioReal = danio - (fuerza / 20);   // hasta -5 puntos

    if (nivel == 1) {
        danioReal = (danioReal * 5) / 4;
        std::cout << "   >> " << nombre << " es novato y se cubre mal (+25% de dano)." << std::endl;
    }
    if (danioReal < 1) danioReal = 1;         // siempre recibe al menos 1

    std::cout << "   >> " << nombre << " recibe " << danioReal
              << " de dano (original: " << danio << ")." << std::endl;
    Unidad::recibeAtaque(danioReal);          // reutiliza el metodo base

    revive();                                 // ultima oportunidad de vida
}

int Guerrero::poder() const {
    return Unidad::poder() + (fuerza / 2);
}

// SEGUNDO ALIENTO: si cae a 0 pero conserva 40 o mas de fuerza, se levanta.
// Cuesta 40 puntos de fuerza, asi que solo puede pasar una o dos veces.
void Guerrero::revive() {
    if (salud > 0) return;                    // sigue vivo, no hace nada

    if (fuerza >= 40) {
        setFuerza(fuerza - 40);
        setSalud(20 + fuerza / 10);
        std::cout << "   ** " << nombre << " REVIVIO gracias a su FUERZA (segundo aliento)! "
                  << "Salud: " << salud << " | Fuerza restante: " << fuerza << std::endl;
    } else {
        std::cout << "   ** " << nombre << " ya no tiene fuerza suficiente... HA MUERTO."
                  << std::endl;
    }
}
