#ifndef USUARIO_H
#define USUARIO_H

#include "Fecha.h"
#include "Mensaje.h"
#include "Album.h"
#include <cstddef>

class Usuario {
private:
    char* nombreUsuario;
    Fecha fechaNacimiento;
    char* correoElectronico;
    char* fotoPerfil;
    char* clave;
    char* ciudadOrigen;
    char* paisOrigen;
    Fecha fechaRegistro;

    Usuario** listaAmigos;
    int numAmigos;
    int maxAmigos;

    Mensaje* mensajesEnviados;
    int numEnviados;
    int maxEnviados;

    Mensaje* mensajesRecibidos;
    int numRecibidos;
    int maxRecibidos;

    char** solicitudesPendientes;
    int numSolicitudes;
    int maxSolicitudes;

    Album* misAlbumes;
    int numAlbumes;
    int maxAlbumes;

    void redimensionarAmigos();
    void redimensionarEnviados();
    void redimensionarRecibidos();
    void redimensionarSolicitudes();
    void redimensionarAlbumes();

public:
    Usuario();
    Usuario(const char* nom, const Fecha& fn, const char* cor, const char* fp, const char* clv, const char* ciu, const char* pai, const Fecha& fr);
    Usuario(const Usuario& otro);
    ~Usuario();

    Usuario& operator=(const Usuario& otro);

    char* getNombreUsuario() const;
    Fecha getFechaNacimiento() const;
    char* getCorreoElectronico() const;
    char* getFotoPerfil() const;
    char* getClave() const;
    char* getCiudadOrigen() const;
    char* getPaisOrigen() const;
    Fecha getFechaRegistro() const;

    int getNumAmigos() const;
    int getNumEnviados() const;
    int getNumRecibidos() const;
    int getNumSolicitudes() const;
    int getNumAlbumes() const;

    void vincularAmigo(Usuario* u);
    bool esAmigoDe(Usuario* u) const;
    Usuario* getAmigoPorIndice(int indice) const;

    void registrarMensajeEnviado(const Mensaje& m);
    void registrarMensajeRecibido(const Mensaje& m);
    Mensaje* getMensajeEnviado(int indice) const;
    Mensaje* getMensajeRecibido(int indice) const;

    void recibirSolicitudAmistad(const char* emisor);
    char* getSolicitudPorIndice(int indice) const;
    void borrarSolicitud(int indice);

    void crearAlbum(const Album& a);
    Album* getAlbumPorIndice(int indice) const;
    Album* buscarAlbumPorTitulo(const char* titulo) const;

    void listarAmigos() const;
    void listarAlbumes() const;

    size_t obtenerBytes() const;
};

#endif // USUARIO_H