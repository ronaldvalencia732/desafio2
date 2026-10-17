#ifndef FOTO_H
#define FOTO_H

#include "Fecha.h"
#include <cstddef>

class Foto {
private:
    Fecha fechaCaptura;
    float pesoMB;
    char* rutaArchivo;
    int numLikes;

public:
    Foto();
    Foto(const Fecha& f, float peso, const char* ruta, int likes);
    Foto(const Foto& otra);
    ~Foto();

    Foto& operator=(const Foto& otra);

    Fecha getFechaCaptura() const;
    float getPesoMB() const;
    char* getRutaArchivo() const;
    int getNumLikes() const;

    void incrementarLike();
    void decrementarLike();
    void imprimirDetalle() const;

    size_t obtenerBytes() const;
};

#endif // FOTO_H