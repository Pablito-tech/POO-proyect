#ifndef UNIDAD_HPP
#define UNIDAD_HPP

#include <string>
#include <iostream>

// Clase ABSTRACTA: no se pueden crear objetos de tipo Unidad porque
// revive() es un metodo virtual puro.
class Unidad {
protected:
    std::string nombre;
    int nivel;        // 1 a 5
    int salud;        // 0 a 100
    int ataqueBase;   // puntos de ataque base

public:
    Unidad();
    Unidad(std::string nombre, int nivel, int salud, int ataqueBase);
    virtual ~Unidad();

    // ---- Getters y setters ----
    std::string getNombre() const;
    int getNivel() const;
    int getSalud() const;
    int getAtaqueBase() const;

    void setNombre(std::string nombre);
    void setNivel(int nivel);
    void setSalud(int salud);
    void setAtaqueBase(int ataqueBase);

    bool estaViva() const;

    // ---- Metodos polimorficos (resolucion en tiempo de ejecucion) ----
    virtual void imprime(std::ostream &os = std::cout) const;
    virtual int  calculaAtaque();
    virtual void recibeAtaque(int danio);
    virtual int  poder() const;      // fuerza de combate, se usa en operator>

    // ---- Metodo VIRTUAL PURO: cada clase derivada decide como revivir ----
    virtual void revive() = 0;

    // ---- Sobrecarga de operadores ----
    // operator<< no puede ser virtual, pero al ser friend delega en imprime(),
    // que si es virtual: asi la impresion tambien es polimorfica.
    friend std::ostream& operator<<(std::ostream &os, const Unidad &u);

    // Compara que combatiente esta en mejores condiciones de pelea.
    bool operator>(const Unidad &otra) const;
};

#endif
