#ifndef ALBUM_H
#define ALBUM_H

#include "Foto.h"
#include <cstddef>

class Album {
private:
    char* titulo;
    char* rutaUbicacion;
    char* privacidad;
    Foto* coleccionFotos;
    int numFotos;
    int maxFotos;

    void ampliarCapacidad();

public:
    Album();
    Album(const char* t, const char* r, const char* p);
    Album(const Album& otro);
    ~Album();

    Album& operator=(const Album& otro);

    char* getTitulo() const;
    char* getRutaUbicacion() const;
    char* getPrivacidad() const;
    int getNumFotos() const;

    void agregarFotografia(const Foto& f);
    Foto* consultarFoto(int indice) const;
    void listarFotos() const;
    bool esVisiblePara(const char* rol) const;

    size_t obtenerBytes() const;
};

#endif // ALBUM_H