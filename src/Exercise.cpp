#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Unidad.hpp"
#include "Guerrero.hpp"
#include "Arquero.hpp"
#include "Mago.hpp"

using namespace std;

void separador(string titulo) {
    cout << "\n============================================================\n";
    cout << "  " << titulo << "\n";
    cout << "============================================================\n";
}

// Un ataque entre dos combatientes.
// Los parametros son Unidad*, pero calculaAtaque(), recibeAtaque(), revive()
// e imprime() se resuelven en TIEMPO DE EJECUCION segun el tipo real del objeto.
void atacar(Unidad *atacante, Unidad *defensor) {
    if (!atacante->estaViva()) {
        cout << "\n-- " << atacante->getNombre() << " esta fuera de combate, no puede atacar --" << endl;
        return;
    }
    if (!defensor->estaViva()) {
        cout << "\n-- " << defensor->getNombre() << " ya esta derrotado, no recibe mas ataques --" << endl;
        return;
    }

    cout << "\n-- " << atacante->getNombre() << " ataca a " << defensor->getNombre() << " --" << endl;

    int danio = atacante->calculaAtaque();
    cout << "   " << atacante->getNombre() << " genera " << danio << " puntos de ataque." << endl;

    defensor->recibeAtaque(danio);   // dentro de este metodo se llama a revive()

    // Si el defensor quedo derrotado y el atacante es Mago, absorbe su energia
    if (!defensor->estaViva()) {
        Mago *m = dynamic_cast<Mago*>(atacante);
        if (m != NULL) m->ganaMana(30);
    }

    // Se imprime al personaje atacado usando la SOBRECARGA DEL OPERADOR <<
    cout << "   Estado -> " << *defensor << endl;
}

int main() {
    srand(time(NULL));

    // Unidad u("prueba", 1, 100, 10);  // <- ERROR: Unidad es abstracta (revive() es virtual puro)

    // ---------- 1. Vector de apuntadores a Unidad, objetos creados dinamicamente ----------
    separador("1. CREACION DINAMICA DE LOS COMBATIENTES");

    vector<Unidad*> ejercito;
    ejercito.push_back(new Guerrero("Kael el Guerrero", 3, 100, 12, 70));
    ejercito.push_back(new Arquero ("Lyra la Arquera",  3, 100, 14, 80.0));
    ejercito.push_back(new Mago    ("Zarek el Mago",    4, 100, 10, 100));

    cout << "Se crearon " << ejercito.size() << " combatientes de forma dinamica." << endl;

    // ---------- 2. For que imprime los tres personajes (polimorfismo + operator<<) ----------
    separador("2. IMPRESION DE LOS COMBATIENTES (polimorfismo)");

    for (unsigned int i = 0; i < ejercito.size(); i++) {
        cout << i << ") " << *ejercito[i] << endl;   // usa la sobrecarga de <<
    }

    // ---------- 3. For donde pelean todos contra todos ----------
    separador("3. COMBATE: TODOS CONTRA TODOS");

    for (int ronda = 1; ronda <= 4; ronda++) {
        cout << "\n########## RONDA " << ronda << " ##########" << endl;

        for (unsigned int i = 0; i < ejercito.size(); i++) {
            for (unsigned int j = 0; j < ejercito.size(); j++) {
                if (i != j) {
                    atacar(ejercito[i], ejercito[j]);
                }
            }
        }
    }

    // ---------- 4. Estado final ----------
    separador("4. ESTADO FINAL DE LOS COMBATIENTES");

    for (unsigned int i = 0; i < ejercito.size(); i++) {
        cout << *ejercito[i];
        if (ejercito[i]->estaViva()) cout << "  --> SIGUE EN PIE" << endl;
        else                         cout << "  --> DERROTADO" << endl;
    }

    // ---------- 5. Prueba de la sobrecarga de operadores ----------
    separador("5. PRUEBA DE LA SOBRECARGA DE OPERADORES");

    cout << "Operador << con un solo objeto (se desreferencia el apuntador):" << endl;
    cout << *ejercito[0] << endl;

    cout << "\nOperador << encadenado con texto normal:" << endl;
    cout << "El mago es: " << *ejercito[2] << " (poder: " << ejercito[2]->poder() << ")" << endl;

    cout << "\nOperador > para comparar el poder de combate:" << endl;
    for (unsigned int i = 0; i < ejercito.size(); i++) {
        for (unsigned int j = i + 1; j < ejercito.size(); j++) {
            cout << ejercito[i]->getNombre() << " (" << ejercito[i]->poder() << ") vs "
                 << ejercito[j]->getNombre() << " (" << ejercito[j]->poder() << ") -> ";
            if (*ejercito[i] > *ejercito[j])
                cout << "gana en poder " << ejercito[i]->getNombre() << endl;
            else
                cout << "gana en poder " << ejercito[j]->getNombre() << endl;
        }
    }

    // Se busca al mas poderoso usando el operador >
    Unidad *mejor = ejercito[0];
    for (unsigned int i = 1; i < ejercito.size(); i++) {
        if (*ejercito[i] > *mejor) mejor = ejercito[i];
    }
    cout << "\nEl combatiente mas poderoso al final es:" << endl;
    cout << *mejor << endl;

    // ---------- 6. Liberar memoria ----------
    for (unsigned int i = 0; i < ejercito.size(); i++) {
        delete ejercito[i];       // el destructor virtual llama al destructor correcto
    }
    ejercito.clear();

    cout << "\nMemoria liberada. Fin de la simulacion." << endl;
    return 0;
}