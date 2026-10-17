#include "Mensaje.h"
#include <cstring>
#include <iostream>

using namespace std;

Mensaje::Mensaje() : fechaEnvio(), leido(false) {
    emisor = new char[1]; emisor[0] = '\0';
    receptor = new char[1]; receptor[0] = '\0';
    contenidoTexto = new char[1]; contenidoTexto[0] = '\0';
}

Mensaje::Mensaje(const char* em, const char* re, const char* txt, const Fecha& f)
    : fechaEnvio(f), leido(false) {
    emisor = new char[strlen(em ? em : "") + 1]; strcpy(emisor, em ? em : "");
    receptor = new char[strlen(re ? re : "") + 1]; strcpy(receptor, re ? re : "");
    contenidoTexto = new char[strlen(txt ? txt : "") + 1]; strcpy(contenidoTexto, txt ? txt : "");
}

Mensaje::Mensaje(const Mensaje& otro)
    : fechaEnvio(otro.fechaEnvio), leido(otro.leido) {
    emisor = new char[strlen(otro.emisor) + 1]; strcpy(emisor, otro.emisor);
    receptor = new char[strlen(otro.receptor) + 1]; strcpy(receptor, otro.receptor);
    contenidoTexto = new char[strlen(otro.contenidoTexto) + 1]; strcpy(contenidoTexto, otro.contenidoTexto);
}

Mensaje::~Mensaje() {
    delete[] emisor;
    delete[] receptor;
    delete[] contenidoTexto;
}

Mensaje& Mensaje::operator=(const Mensaje& otro) {
    if (this != &otro) {
        delete[] emisor;
        delete[] receptor;
        delete[] contenidoTexto;

        fechaEnvio = otro.fechaEnvio;
        leido = otro.leido;

        emisor = new char[strlen(otro.emisor) + 1]; strcpy(emisor, otro.emisor);
        receptor = new char[strlen(otro.receptor) + 1]; strcpy(receptor, otro.receptor);
        contenidoTexto = new char[strlen(otro.contenidoTexto) + 1]; strcpy(contenidoTexto, otro.contenidoTexto);
    }
    return *this;
}

char* Mensaje::getEmisor() const { return emisor; }
char* Mensaje::getReceptor() const { return receptor; }
char* Mensaje::getContenidoTexto() const { return contenidoTexto; }
Fecha Mensaje::getFechaEnvio() const { return fechaEnvio; }

bool Mensaje::estaLeido() const { return leido; }
void Mensaje::marcarLeido() { leido = true; }

void Mensaje::mostrarContenido() const {
    cout << "De: " << (emisor ? emisor : "")
    << " | Fecha: " << fechaEnvio.getDia() << "/" << fechaEnvio.getMes() << "/" << fechaEnvio.getAnio()
    << " | Texto: " << (contenidoTexto ? contenidoTexto : "") << endl;
}

bool Mensaje::estaEnRango(const Fecha& inicio, const Fecha& fin) const {
    return !fechaEnvio.esMenor(inicio) && !fechaEnvio.esMayor(fin);
}

size_t Mensaje::obtenerBytes() const {
    size_t bytes = sizeof(*this);
    if (emisor) bytes += (strlen(emisor) + 1) * sizeof(char);
    if (receptor) bytes += (strlen(receptor) + 1) * sizeof(char);
    if (contenidoTexto) bytes += (strlen(contenidoTexto) + 1) * sizeof(char);
    return bytes;
}