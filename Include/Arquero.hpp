#ifndef ARQUERO_HPP
#define ARQUERO_HPP

#include "Unidad.hpp"

class Arquero : public Unidad {
private:
    float precision;   // 0.0 a 100.0: probabilidad de tiro critico y de esquivar

public:
    Arquero();
    Arquero(std::string nombre, int nivel, int salud, int ataqueBase, float precision);
    ~Arquero();

    float getPrecision() const;
    void  setPrecision(float precision);

    void imprime(std::ostream &os = std::cout) const override;
    int  calculaAtaque() override;
    void recibeAtaque(int danio) override;
    int  poder() const override;
    void revive() override;
};

#endif
