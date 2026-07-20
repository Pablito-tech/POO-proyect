#include "Unidad.hpp"
#include <cstdlib>

Unidad::Unidad() {
    nombre = "Sin nombre";
    nivel = 1;
    salud = 100;
    ataqueBase = 10;
}

Unidad::Unidad(std::string nombre, int nivel, int salud, int ataqueBase) {
    this->nombre = nombre;
    this->nivel = nivel;
    this->salud = salud;
    this->ataqueBase = ataqueBase;
}

Unidad::~Unidad() {}

std::string Unidad::getNombre() const { return nombre; }
int Unidad::getNivel() const { return nivel; }
int Unidad::getSalud() const { return salud; }
int Unidad::getAtaqueBase() const { return ataqueBase; }

void Unidad::setNombre(std::string nombre) { this->nombre = nombre; }
void Unidad::setNivel(int nivel) { this->nivel = nivel; }
void Unidad::setAtaqueBase(int ataqueBase) { this->ataqueBase = ataqueBase; }

void Unidad::setSalud(int salud) {
    if (salud < 0) salud = 0;
    if (salud > 100) salud = 100;
    this->salud = salud;
}

bool Unidad::estaViva() const { return salud > 0; }

void Unidad::imprime(std::ostream &os) const {
    os << "Unidad: " << nombre
       << " | Nivel: " << nivel
       << " | Salud: " << salud
       << " | Ataque base: " << ataqueBase;
}

// Ataque generico: base + bono por nivel + un poco de azar
int Unidad::calculaAtaque() {
    return ataqueBase + (nivel * 2) + (rand() % 6); // +0 a +5
}

void Unidad::recibeAtaque(int danio) {
    if (danio < 0) danio = 0;
    salud -= danio;
    if (salud < 0) salud = 0;
}

int Unidad::poder() const {
    return (salud / 2) + ataqueBase + (nivel * 2);
}

// ---------- Sobrecarga de operadores ----------

// Llama a imprime(), que es virtual: si el objeto es un Mago se ejecuta
// Mago::imprime, si es Guerrero se ejecuta Guerrero::imprime, etc.
std::ostream& operator<<(std::ostream &os, const Unidad &u) {
    u.imprime(os);
    return os;
}

// poder() tambien es virtual, asi que cada clase aporta su atributo especial
bool Unidad::operator>(const Unidad &otra) const {
    return this->poder() > otra.poder();
}
