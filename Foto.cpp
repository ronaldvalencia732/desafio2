#include "Foto.h"
#include <cstring>
#include <iostream>

using namespace std;

Foto::Foto() : fechaCaptura(), pesoMB(0.0f), numLikes(0) {
    rutaArchivo = new char[1];
    rutaArchivo[0] = '\0';
}

Foto::Foto(const Fecha& f, float peso, const char* ruta, int likes)
    : fechaCaptura(f), pesoMB(peso), numLikes(likes) {
    if (ruta) {
        rutaArchivo = new char[strlen(ruta) + 1];
        strcpy(rutaArchivo, ruta);
    } else {
        rutaArchivo = new char[1];
        rutaArchivo[0] = '\0';
    }
}

Foto::Foto(const Foto& otra)
    : fechaCaptura(otra.fechaCaptura), pesoMB(otra.pesoMB), numLikes(otra.numLikes) {
    rutaArchivo = new char[strlen(otra.rutaArchivo) + 1];
    strcpy(rutaArchivo, otra.rutaArchivo);
}

Foto::~Foto() {
    delete[] rutaArchivo;
}

Foto& Foto::operator=(const Foto& otra) {
    if (this != &otra) {
        delete[] rutaArchivo;
        fechaCaptura = otra.fechaCaptura;
        pesoMB = otra.pesoMB;
        numLikes = otra.numLikes;
        rutaArchivo = new char[strlen(otra.rutaArchivo) + 1];
        strcpy(rutaArchivo, otra.rutaArchivo);
    }
    return *this;
}

Fecha Foto::getFechaCaptura() const { return fechaCaptura; }
float Foto::getPesoMB() const { return pesoMB; }
char* Foto::getRutaArchivo() const { return rutaArchivo; }
int Foto::getNumLikes() const { return numLikes; }

void Foto::incrementarLike() { numLikes++; }
void Foto::decrementarLike() { if (numLikes > 0) numLikes--; }

void Foto::imprimirDetalle() const {
    cout << "Ruta de la imagen: " << (rutaArchivo ? rutaArchivo : "")
    << " | Me gusta: " << numLikes << endl;
}

size_t Foto::obtenerBytes() const {
    size_t bytes = sizeof(*this);
    if (rutaArchivo) bytes += (strlen(rutaArchivo) + 1) * sizeof(char);
    return bytes;
}