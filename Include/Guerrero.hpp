#ifndef GUERRERO_HPP
#define GUERRERO_HPP

#include "Unidad.hpp"

class Guerrero : public Unidad {
private:
    int fuerza;   // 0 a 100: potencia el ataque, sirve de armadura y permite revivir

public:
    Guerrero();
    Guerrero(std::string nombre, int nivel, int salud, int ataqueBase, int fuerza);
    ~Guerrero();

    int  getFuerza() const;
    void setFuerza(int fuerza);

    void imprime(std::ostream &os = std::cout) const override;
    int  calculaAtaque() override;
    void recibeAtaque(int danio) override;
    int  poder() const override;
    void revive() override;
};

#endif
