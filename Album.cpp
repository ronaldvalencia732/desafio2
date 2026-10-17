#include "Album.h"
#include <cstring>
#include <iostream>

using namespace std;

Album::Album() : numFotos(0), maxFotos(2) {
    titulo = new char[1]; titulo[0] = '\0';
    rutaUbicacion = new char[1]; rutaUbicacion[0] = '\0';
    privacidad = new char[8]; strcpy(privacidad, "privado");
    coleccionFotos = new Foto[maxFotos];
}

Album::Album(const char* t, const char* r, const char* p) : numFotos(0), maxFotos(2) {
    titulo = new char[strlen(t ? t : "") + 1]; strcpy(titulo, t ? t : "");
    rutaUbicacion = new char[strlen(r ? r : "") + 1]; strcpy(rutaUbicacion, r ? r : "");
    privacidad = new char[strlen(p ? p : "") + 1]; strcpy(privacidad, p ? p : "");
    coleccionFotos = new Foto[maxFotos];
}

Album::Album(const Album& otro) : numFotos(otro.numFotos), maxFotos(otro.maxFotos) {
    titulo = new char[strlen(otro.titulo) + 1]; strcpy(titulo, otro.titulo);
    rutaUbicacion = new char[strlen(otro.rutaUbicacion) + 1]; strcpy(rutaUbicacion, otro.rutaUbicacion);
    privacidad = new char[strlen(otro.privacidad) + 1]; strcpy(privacidad, otro.privacidad);
    coleccionFotos = new Foto[maxFotos];
    for (int i = 0; i < numFotos; i++) {
        coleccionFotos[i] = otro.coleccionFotos[i];
    }
}

Album::~Album() {
    delete[] titulo;
    delete[] rutaUbicacion;
    delete[] privacidad;
    delete[] coleccionFotos;
}

Album& Album::operator=(const Album& otro) {
    if (this != &otro) {
        delete[] titulo;
        delete[] rutaUbicacion;
        delete[] privacidad;
        delete[] coleccionFotos;

        numFotos = otro.numFotos;
        maxFotos = otro.maxFotos;

        titulo = new char[strlen(otro.titulo) + 1]; strcpy(titulo, otro.titulo);
        rutaUbicacion = new char[strlen(otro.rutaUbicacion) + 1]; strcpy(rutaUbicacion, otro.rutaUbicacion);
        privacidad = new char[strlen(otro.privacidad) + 1]; strcpy(privacidad, otro.privacidad);

        coleccionFotos = new Foto[maxFotos];
        for (int i = 0; i < numFotos; i++) {
            coleccionFotos[i] = otro.coleccionFotos[i];
        }
    }
    return *this;
}

void Album::ampliarCapacidad() {
    maxFotos *= 2;
    Foto* nuevaLista = new Foto[maxFotos];
    for (int i = 0; i < numFotos; i++) {
        nuevaLista[i] = coleccionFotos[i];
    }
    delete[] coleccionFotos;
    coleccionFotos = nuevaLista;
}

char* Album::getTitulo() const { return titulo; }
char* Album::getRutaUbicacion() const { return rutaUbicacion; }
char* Album::getPrivacidad() const { return privacidad; }
int Album::getNumFotos() const { return numFotos; }

void Album::agregarFotografia(const Foto& f) {
    if (numFotos == maxFotos) {
        ampliarCapacidad();
    }
    coleccionFotos[numFotos] = f;
    numFotos++;
}

Foto* Album::consultarFoto(int indice) const {
    if (indice < 0 || indice >= numFotos) return nullptr;
    return &coleccionFotos[indice];
}

void Album::listarFotos() const {
    for (int i = 0; i < numFotos; i++) {
        coleccionFotos[i].imprimirDetalle();
    }
}

bool Album::esVisiblePara(const char* rol) const {
    if (!rol) return false;
    if (strcmp(privacidad, "publico") == 0) return true;
    if (strcmp(rol, "dueño") == 0) return true;
    if (strcmp(privacidad, "amigos") == 0 && strcmp(rol, "amigo") == 0) return true;
    return false;
}

size_t Album::obtenerBytes() const {
    size_t bytes = sizeof(*this);
    if (titulo) bytes += (strlen(titulo) + 1) * sizeof(char);
    if (rutaUbicacion) bytes += (strlen(rutaUbicacion) + 1) * sizeof(char);
    if (privacidad) bytes += (strlen(privacidad) + 1) * sizeof(char);
    for (int i = 0; i < numFotos; i++) {
        bytes += coleccionFotos[i].obtenerBytes();
    }
    return bytes;
}