#ifndef MAGO_HPP
#define MAGO_HPP

#include "Unidad.hpp"

class Mago : public Unidad {
private:
    int mana;   // 0 a 100: energia magica

public:
    Mago();
    Mago(std::string nombre, int nivel, int salud, int ataqueBase, int mana);
    ~Mago();

    int  getMana() const;
    void setMana(int mana);
    void ganaMana(int puntos);   // se usa cuando el mago derrota a un enemigo

    void imprime(std::ostream &os = std::cout) const override;
    int  calculaAtaque() override;
    void recibeAtaque(int danio) override;
    int  poder() const override;
    void revive() override;
};

#endif
