#ifndef REDSOCIAL_H
#define REDSOCIAL_H

#include "Usuario.h"
#include <iostream>

using namespace std;

class RedSocial {
private:
    Usuario** directorioUsuarios;
    int numUsuarios;
    int maxUsuarios;
    Usuario* usuarioSesion;

    bool** matrizRelaciones;
    bool matrizLista;

    long long iteracionesOperacion;
    long long memoriaConsumidaRAM;

    void redimensionarDirectorio();
    void construirMatriz();
    void liberarMatriz();

    // Métodos para persistencia en disco
    void cargarUsuariosDisco();
    void cargarAlbumesDisco();
    void cargarFotosDisco();
    void cargarMensajesDisco();
    void cargarAmistadesDisco();
    void cargarSolicitudesDisco();

    void guardarUsuariosDisco();
    void guardarAmistadesDisco();
    void guardarMensajesDisco();
    void guardarAlbumesDisco();
    void guardarSolicitudesDisco();

public:
    RedSocial();
    ~RedSocial();

    void cargarDatos();
    void guardarDatos();
    bool iniciarSesion();
    void mostrarMenu();
    void mostrarMenuAmistades();
    void mostrarMenuMensajes();

    Usuario* buscarUsuarioPorNombre(const char* nombre) const;
    int contarAmigosEnComun(Usuario* u1, Usuario* u2) const;
    void mostrarMejoresAmigos();
    void actualizarMejoresAmigos();
    void enviarSolicitud();
    void aceptarSolicitud();
    void visitarPerfilAmigo();
    void abrirCarrusel(Album& a);
    void verSugerencias();
    void enviarSolicitudSugerencia(const char* nombre);
    void enviarMensaje();
    void leerNuevosMensajes();
    void buscarMensajePorFecha();

    void iniciarMedicion();
    void detenerMedicion(const char* nombreAccion);
    void registrarIteracion();
    void sumarBytesMemoria(long long bytes);
};

#endif // REDSOCIAL_H