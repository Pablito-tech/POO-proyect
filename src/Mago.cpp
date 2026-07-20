#include "Mago.hpp"
#include <cstdlib>

Mago::Mago() : Unidad() {
    mana = 100;
}

Mago::Mago(std::string nombre, int nivel, int salud, int ataqueBase, int mana)
    : Unidad(nombre, nivel, salud, ataqueBase) {
    setMana(mana);
}

Mago::~Mago() {}

int Mago::getMana() const { return mana; }

void Mago::setMana(int mana) {
    if (mana < 0)   mana = 0;
    if (mana > 100) mana = 100;
    this->mana = mana;
}

void Mago::ganaMana(int puntos) {
    setMana(mana + puntos);
    std::cout << "   >> " << nombre << " absorbe la energia del enemigo caido. Mana: "
              << mana << std::endl;
}

void Mago::imprime(std::ostream &os) const {
    os << "[MAGO    ] ";
    Unidad::imprime(os);
    os << " | Mana: " << mana;
}

// Si tiene 20 o mas de mana, con probabilidad igual a su mana lanza un HECHIZO
// FUERTE (dano x2) y gasta 20 de mana. Si no, hace un ataque normal y gasta 5.
// Si se queda con menos de 10 de mana, esta agotado y su dano se reduce a la mitad.
int Mago::calculaAtaque() {
    int danio = Unidad::calculaAtaque();

    if (mana >= 20 && (rand() % 100) < mana) {
        danio = danio * 2;
        setMana(mana - 20);
        std::cout << "   >> " << nombre << " lanza un HECHIZO FUERTE! Mana restante: "
                  << mana << std::endl;
    } else {
        setMana(mana - 5);
        if (mana < 10) {
            danio = danio / 2;
            std::cout << "   >> " << nombre << " esta agotado, su ataque es debil. Mana: "
                      << mana << std::endl;
        }
    }
    return danio;
}

// Escudo magico: el mana y el nivel absorben parte del dano.
void Mago::recibeAtaque(int danio) {
    int danioReal = danio;

    if (nivel >= 4 && mana > 80) {
        danioReal = danio / 3;
        setMana(mana - 10);
        std::cout << "   >> ESCUDO MAGICO MAYOR de " << nombre << " (absorbe 2/3)." << std::endl;
    } else if (nivel >= 3 && mana > 60) {
        danioReal = danio / 2;
        setMana(mana - 10);
        std::cout << "   >> ESCUDO MAGICO de " << nombre << " (absorbe 1/2)." << std::endl;
    } else if (mana > 30) {
        danioReal = (danio * 3) / 4;
        setMana(mana - 10);
        std::cout << "   >> Escudo magico menor de " << nombre << " (absorbe 1/4)." << std::endl;
    }
    if (danioReal < 1) danioReal = 1;

    std::cout << "   >> " << nombre << " recibe " << danioReal
              << " de dano (original: " << danio << ")." << std::endl;
    Unidad::recibeAtaque(danioReal);

    revive();                                 // ultima oportunidad de vida
}

int Mago::poder() const {
    return Unidad::poder() + (mana / 2);
}

// REENCARNACION: si cae a 0 pero le quedan 40 o mas de mana, la energia magica
// lo trae de vuelta. Cuesta 40 de mana, asi que solo puede pasar una o dos veces.
void Mago::revive() {
    if (salud > 0) return;

    if (mana >= 40) {
        setMana(mana - 40);
        setSalud(25);
        std::cout << "   ** " << nombre << " REVIVIO gracias a su MANA (reencarnacion)! "
                  << "Salud: " << salud << " | Mana restante: " << mana << std::endl;
    } else {
        std::cout << "   ** " << nombre << " se quedo sin mana suficiente... HA MUERTO."
                  << std::endl;
    }
}
