#include <iostream>
#include "RedSocial.h"

using namespace std;

int main() {
    RedSocial red;

    cout << "Inicializando componentes de la plataforma..." << endl;
    red.cargarDatos();

    bool logueado = false;
    int intentos = 0;

    while (!logueado && intentos < 3) {
        logueado = red.iniciarSesion();
        if (logueado) {
            red.mostrarMenu();
        } else {
            intentos++;
            if (intentos < 3) {
                cout << "Intentos disponibles: " << (3 - intentos) << endl;
            }
        }
    }

    cout << "\nGuardando estado de la red..." << endl;
    red.guardarDatos();
    cout << "¡Sesión finalizada con éxito!" << endl;

    return 0;
}