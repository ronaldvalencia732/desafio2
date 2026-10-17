#include "Usuario.h"
#include <cstring>
#include <iostream>

using namespace std;

Usuario::Usuario()
    : fechaNacimiento(), fechaRegistro(),
    numAmigos(0), maxAmigos(2),
    numEnviados(0), maxEnviados(2),
    numRecibidos(0), maxRecibidos(2),
    numSolicitudes(0), maxSolicitudes(2),
    numAlbumes(0), maxAlbumes(2) {

    nombreUsuario = new char[1]; nombreUsuario[0] = '\0';
    correoElectronico = new char[1]; correoElectronico[0] = '\0';
    fotoPerfil = new char[1]; fotoPerfil[0] = '\0';
    clave = new char[1]; clave[0] = '\0';
    ciudadOrigen = new char[1]; ciudadOrigen[0] = '\0';
    paisOrigen = new char[1]; paisOrigen[0] = '\0';

    listaAmigos = new Usuario*[maxAmigos];
    for (int i = 0; i < maxAmigos; i++) listaAmigos[i] = nullptr;

    mensajesEnviados = new Mensaje[maxEnviados];
    mensajesRecibidos = new Mensaje[maxRecibidos];

    solicitudesPendientes = new char*[maxSolicitudes];
    for (int i = 0; i < maxSolicitudes; i++) solicitudesPendientes[i] = nullptr;

    misAlbumes = new Album[maxAlbumes];
}

Usuario::Usuario(const char* nom, const Fecha& fn, const char* cor, const char* fp, const char* clv, const char* ciu, const char* pai, const Fecha& fr)
    : fechaNacimiento(fn), fechaRegistro(fr),
    numAmigos(0), maxAmigos(2),
    numEnviados(0), maxEnviados(2),
    numRecibidos(0), maxRecibidos(2),
    numSolicitudes(0), maxSolicitudes(2),
    numAlbumes(0), maxAlbumes(2) {

    nombreUsuario = new char[strlen(nom ? nom : "") + 1]; strcpy(nombreUsuario, nom ? nom : "");
    correoElectronico = new char[strlen(cor ? cor : "") + 1]; strcpy(correoElectronico, cor ? cor : "");
    fotoPerfil = new char[strlen(fp ? fp : "") + 1]; strcpy(fotoPerfil, fp ? fp : "");
    clave = new char[strlen(clv ? clv : "") + 1]; strcpy(clave, clv ? clv : "");
    ciudadOrigen = new char[strlen(ciu ? ciu : "") + 1]; strcpy(ciudadOrigen, ciu ? ciu : "");
    paisOrigen = new char[strlen(pai ? pai : "") + 1]; strcpy(paisOrigen, pai ? pai : "");

    listaAmigos = new Usuario*[maxAmigos];
    for (int i = 0; i < maxAmigos; i++) listaAmigos[i] = nullptr;

    mensajesEnviados = new Mensaje[maxEnviados];
    mensajesRecibidos = new Mensaje[maxRecibidos];

    solicitudesPendientes = new char*[maxSolicitudes];
    for (int i = 0; i < maxSolicitudes; i++) solicitudesPendientes[i] = nullptr;

    misAlbumes = new Album[maxAlbumes];
}

Usuario::Usuario(const Usuario& otro)
    : fechaNacimiento(otro.fechaNacimiento), fechaRegistro(otro.fechaRegistro),
    numAmigos(otro.numAmigos), maxAmigos(otro.maxAmigos),
    numEnviados(otro.numEnviados), maxEnviados(otro.maxEnviados),
    numRecibidos(otro.numRecibidos), maxRecibidos(otro.maxRecibidos),
    numSolicitudes(otro.numSolicitudes), maxSolicitudes(otro.maxSolicitudes),
    numAlbumes(otro.numAlbumes), maxAlbumes(otro.maxAlbumes) {

    nombreUsuario = new char[strlen(otro.nombreUsuario) + 1]; strcpy(nombreUsuario, otro.nombreUsuario);
    correoElectronico = new char[strlen(otro.correoElectronico) + 1]; strcpy(correoElectronico, otro.correoElectronico);
    fotoPerfil = new char[strlen(otro.fotoPerfil) + 1]; strcpy(fotoPerfil, otro.fotoPerfil);
    clave = new char[strlen(otro.clave) + 1]; strcpy(clave, otro.clave);
    ciudadOrigen = new char[strlen(otro.ciudadOrigen) + 1]; strcpy(ciudadOrigen, otro.ciudadOrigen);
    paisOrigen = new char[strlen(otro.paisOrigen) + 1]; strcpy(paisOrigen, otro.paisOrigen);

    listaAmigos = new Usuario*[maxAmigos];
    for (int i = 0; i < maxAmigos; i++) {
        listaAmigos[i] = (i < numAmigos) ? otro.listaAmigos[i] : nullptr;
    }

    mensajesEnviados = new Mensaje[maxEnviados];
    for (int i = 0; i < numEnviados; i++) mensajesEnviados[i] = otro.mensajesEnviados[i];

    mensajesRecibidos = new Mensaje[maxRecibidos];
    for (int i = 0; i < numRecibidos; i++) mensajesRecibidos[i] = otro.mensajesRecibidos[i];

    solicitudesPendientes = new char*[maxSolicitudes];
    for (int i = 0; i < maxSolicitudes; i++) {
        if (i < numSolicitudes && otro.solicitudesPendientes[i]) {
            solicitudesPendientes[i] = new char[strlen(otro.solicitudesPendientes[i]) + 1];
            strcpy(solicitudesPendientes[i], otro.solicitudesPendientes[i]);
        } else {
            solicitudesPendientes[i] = nullptr;
        }
    }

    misAlbumes = new Album[maxAlbumes];
    for (int i = 0; i < numAlbumes; i++) misAlbumes[i] = otro.misAlbumes[i];
}

Usuario::~Usuario() {
    delete[] nombreUsuario;
    delete[] correoElectronico;
    delete[] fotoPerfil;
    delete[] clave;
    delete[] ciudadOrigen;
    delete[] paisOrigen;

    delete[] listaAmigos;
    delete[] mensajesEnviados;
    delete[] mensajesRecibidos;

    for (int i = 0; i < numSolicitudes; i++) {
        delete[] solicitudesPendientes[i];
    }
    delete[] solicitudesPendientes;

    delete[] misAlbumes;
}

Usuario& Usuario::operator=(const Usuario& otro) {
    if (this != &otro) {
        delete[] nombreUsuario; delete[] correoElectronico; delete[] fotoPerfil;
        delete[] clave; delete[] ciudadOrigen; delete[] paisOrigen;
        delete[] listaAmigos; delete[] mensajesEnviados; delete[] mensajesRecibidos;
        for (int i = 0; i < numSolicitudes; i++) delete[] solicitudesPendientes[i];
        delete[] solicitudesPendientes;
        delete[] misAlbumes;

        fechaNacimiento = otro.fechaNacimiento;
        fechaRegistro = otro.fechaRegistro;
        numAmigos = otro.numAmigos; maxAmigos = otro.maxAmigos;
        numEnviados = otro.numEnviados; maxEnviados = otro.maxEnviados;
        numRecibidos = otro.numRecibidos; maxRecibidos = otro.maxRecibidos;
        numSolicitudes = otro.numSolicitudes; maxSolicitudes = otro.maxSolicitudes;
        numAlbumes = otro.numAlbumes; maxAlbumes = otro.maxAlbumes;

        nombreUsuario = new char[strlen(otro.nombreUsuario) + 1]; strcpy(nombreUsuario, otro.nombreUsuario);
        correoElectronico = new char[strlen(otro.correoElectronico) + 1]; strcpy(correoElectronico, otro.correoElectronico);
        fotoPerfil = new char[strlen(otro.fotoPerfil) + 1]; strcpy(fotoPerfil, otro.fotoPerfil);
        clave = new char[strlen(otro.clave) + 1]; strcpy(clave, otro.clave);
        ciudadOrigen = new char[strlen(otro.ciudadOrigen) + 1]; strcpy(ciudadOrigen, otro.ciudadOrigen);
        paisOrigen = new char[strlen(otro.paisOrigen) + 1]; strcpy(paisOrigen, otro.paisOrigen);

        listaAmigos = new Usuario*[maxAmigos];
        for (int i = 0; i < maxAmigos; i++) {
            listaAmigos[i] = (i < numAmigos) ? otro.listaAmigos[i] : nullptr;
        }

        mensajesEnviados = new Mensaje[maxEnviados];
        for (int i = 0; i < numEnviados; i++) mensajesEnviados[i] = otro.mensajesEnviados[i];

        mensajesRecibidos = new Mensaje[maxRecibidos];
        for (int i = 0; i < numRecibidos; i++) mensajesRecibidos[i] = otro.mensajesRecibidos[i];

        solicitudesPendientes = new char*[maxSolicitudes];
        for (int i = 0; i < maxSolicitudes; i++) {
            if (i < numSolicitudes && otro.solicitudesPendientes[i]) {
                solicitudesPendientes[i] = new char[strlen(otro.solicitudesPendientes[i]) + 1];
                strcpy(solicitudesPendientes[i], otro.solicitudesPendientes[i]);
            } else {
                solicitudesPendientes[i] = nullptr;
            }
        }

        misAlbumes = new Album[maxAlbumes];
        for (int i = 0; i < numAlbumes; i++) misAlbumes[i] = otro.misAlbumes[i];
    }
    return *this;
}

void Usuario::redimensionarAmigos() {
    maxAmigos *= 2;
    Usuario** nuevo = new Usuario*[maxAmigos];
    for (int i = 0; i < maxAmigos; i++) {
        nuevo[i] = (i < numAmigos) ? listaAmigos[i] : nullptr;
    }
    delete[] listaAmigos;
    listaAmigos = nuevo;
}

void Usuario::redimensionarEnviados() {
    maxEnviados *= 2;
    Mensaje* nuevo = new Mensaje[maxEnviados];
    for (int i = 0; i < numEnviados; i++) {
        nuevo[i] = mensajesEnviados[i];
    }
    delete[] mensajesEnviados;
    mensajesEnviados = nuevo;
}

void Usuario::redimensionarRecibidos() {
    maxRecibidos *= 2;
    Mensaje* nuevo = new Mensaje[maxRecibidos];
    for (int i = 0; i < numRecibidos; i++) {
        nuevo[i] = mensajesRecibidos[i];
    }
    delete[] mensajesRecibidos;
    mensajesRecibidos = nuevo;
}

void Usuario::redimensionarSolicitudes() {
    maxSolicitudes *= 2;
    char** nuevo = new char*[maxSolicitudes];
    for (int i = 0; i < maxSolicitudes; i++) {
        nuevo[i] = (i < numSolicitudes) ? solicitudesPendientes[i] : nullptr;
    }
    delete[] solicitudesPendientes;
    solicitudesPendientes = nuevo;
}

void Usuario::redimensionarAlbumes() {
    maxAlbumes *= 2;
    Album* nuevo = new Album[maxAlbumes];
    for (int i = 0; i < numAlbumes; i++) {
        nuevo[i] = misAlbumes[i];
    }
    delete[] misAlbumes;
    misAlbumes = nuevo;
}

char* Usuario::getNombreUsuario() const { return nombreUsuario; }
Fecha Usuario::getFechaNacimiento() const { return fechaNacimiento; }
char* Usuario::getCorreoElectronico() const { return correoElectronico; }
char* Usuario::getFotoPerfil() const { return fotoPerfil; }
char* Usuario::getClave() const { return clave; }
char* Usuario::getCiudadOrigen() const { return ciudadOrigen; }
char* Usuario::getPaisOrigen() const { return paisOrigen; }
Fecha Usuario::getFechaRegistro() const { return fechaRegistro; }

int Usuario::getNumAmigos() const { return numAmigos; }
int Usuario::getNumEnviados() const { return numEnviados; }
int Usuario::getNumRecibidos() const { return numRecibidos; }
int Usuario::getNumSolicitudes() const { return numSolicitudes; }
int Usuario::getNumAlbumes() const { return numAlbumes; }

void Usuario::vincularAmigo(Usuario* u) {
    if (u && !esAmigoDe(u)) {
        if (numAmigos == maxAmigos) redimensionarAmigos();
        listaAmigos[numAmigos] = u;
        numAmigos++;
    }
}

bool Usuario::esAmigoDe(Usuario* u) const {
    if (!u) return false;
    for (int i = 0; i < numAmigos; i++) {
        if (listaAmigos[i] == u) return true;
    }
    return false;
}

Usuario* Usuario::getAmigoPorIndice(int indice) const {
    if (indice < 0 || indice >= numAmigos) return nullptr;
    return listaAmigos[indice];
}

void Usuario::registrarMensajeEnviado(const Mensaje& m) {
    if (numEnviados == maxEnviados) redimensionarEnviados();
    mensajesEnviados[numEnviados] = m;
    numEnviados++;
}

void Usuario::registrarMensajeRecibido(const Mensaje& m) {
    if (numRecibidos == maxRecibidos) redimensionarRecibidos();
    mensajesRecibidos[numRecibidos] = m;
    numRecibidos++;
}

Mensaje* Usuario::getMensajeEnviado(int indice) const {
    if (indice < 0 || indice >= numEnviados) return nullptr;
    return &mensajesEnviados[indice];
}

Mensaje* Usuario::getMensajeRecibido(int indice) const {
    if (indice < 0 || indice >= numRecibidos) return nullptr;
    return &mensajesRecibidos[indice];
}

void Usuario::recibirSolicitudAmistad(const char* emisor) {
    if (!emisor) return;
    if (numSolicitudes == maxSolicitudes) redimensionarSolicitudes();
    solicitudesPendientes[numSolicitudes] = new char[strlen(emisor) + 1];
    strcpy(solicitudesPendientes[numSolicitudes], emisor);
    numSolicitudes++;
}

char* Usuario::getSolicitudPorIndice(int indice) const {
    if (indice < 0 || indice >= numSolicitudes) return nullptr;
    return solicitudesPendientes[indice];
}

void Usuario::borrarSolicitud(int indice) {
    if (indice < 0 || indice >= numSolicitudes) return;
    delete[] solicitudesPendientes[indice];
    for (int i = indice; i < numSolicitudes - 1; i++) {
        solicitudesPendientes[i] = solicitudesPendientes[i + 1];
    }
    solicitudesPendientes[numSolicitudes - 1] = nullptr;
    numSolicitudes--;
}

void Usuario::crearAlbum(const Album& a) {
    if (numAlbumes == maxAlbumes) redimensionarAlbumes();
    misAlbumes[numAlbumes] = a;
    numAlbumes++;
}

Album* Usuario::getAlbumPorIndice(int indice) const {
    if (indice < 0 || indice >= numAlbumes) return nullptr;
    return &misAlbumes[indice];
}

Album* Usuario::buscarAlbumPorTitulo(const char* titulo) const {
    if (!titulo) return nullptr;
    for (int i = 0; i < numAlbumes; i++) {
        if (strcmp(misAlbumes[i].getTitulo(), titulo) == 0) {
            return &misAlbumes[i];
        }
    }
    return nullptr;
}

void Usuario::listarAmigos() const {
    if (numAmigos == 0) {
        cout << " (sin amigos)" << endl;
        return;
    }
    for (int i = 0; i < numAmigos; i++) {
        if (listaAmigos[i]) {
            cout << " " << (i + 1) << ". " << listaAmigos[i]->getNombreUsuario() << endl;
        }
    }
}

void Usuario::listarAlbumes() const {
    if (numAlbumes == 0) {
        cout << " (sin álbumes)" << endl;
        return;
    }
    for (int i = 0; i < numAlbumes; i++) {
        cout << " " << (i + 1) << ". " << misAlbumes[i].getTitulo()
        << " [" << misAlbumes[i].getPrivacidad() << "]"
        << " (" << misAlbumes[i].getNumFotos() << " fotos)" << endl;
    }
}

size_t Usuario::obtenerBytes() const {
    size_t bytes = sizeof(*this);
    if (nombreUsuario) bytes += (strlen(nombreUsuario) + 1) * sizeof(char);
    if (correoElectronico) bytes += (strlen(correoElectronico) + 1) * sizeof(char);
    if (fotoPerfil) bytes += (strlen(fotoPerfil) + 1) * sizeof(char);
    if (clave) bytes += (strlen(clave) + 1) * sizeof(char);
    if (ciudadOrigen) bytes += (strlen(ciudadOrigen) + 1) * sizeof(char);
    if (paisOrigen) bytes += (strlen(paisOrigen) + 1) * sizeof(char);

    bytes += maxAmigos * sizeof(Usuario*);
    bytes += maxEnviados * sizeof(Mensaje);
    bytes += maxRecibidos * sizeof(Mensaje);
    bytes += maxSolicitudes * sizeof(char*);

    for (int i = 0; i < numSolicitudes; i++) {
        if (solicitudesPendientes[i]) bytes += (strlen(solicitudesPendientes[i]) + 1) * sizeof(char);
    }
    for (int i = 0; i < numAlbumes; i++) {
        bytes += misAlbumes[i].obtenerBytes();
    }
    return bytes;
}