#ifndef MENSAJE_H
#define MENSAJE_H

#include "Fecha.h"
#include <cstddef>

class Mensaje {
private:
    char* emisor;
    char* receptor;
    char* contenidoTexto;
    Fecha fechaEnvio;
    bool leido;

public:
    Mensaje();
    Mensaje(const char* em, const char* re, const char* txt, const Fecha& f);
    Mensaje(const Mensaje& otro);
    ~Mensaje();

    Mensaje& operator=(const Mensaje& otro);

    char* getEmisor() const;
    char* getReceptor() const;
    char* getContenidoTexto() const;
    Fecha getFechaEnvio() const;

    bool estaLeido() const;
    void marcarLeido();
    void mostrarContenido() const;
    bool estaEnRango(const Fecha& inicio, const Fecha& fin) const;

    size_t obtenerBytes() const;
};

#endif // MENSAJE_H