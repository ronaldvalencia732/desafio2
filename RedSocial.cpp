#include "RedSocial.h"
#include <cstring>
#include <iostream>

using namespace std;

RedSocial::RedSocial()
    : numUsuarios(0), maxUsuarios(4), usuarioSesion(nullptr),
    matrizRelaciones(nullptr), matrizLista(false),
    iteracionesOperacion(0), memoriaConsumidaRAM(0) {

    directorioUsuarios = new Usuario*[maxUsuarios];
    for (int i = 0; i < maxUsuarios; i++) {
        directorioUsuarios[i] = nullptr;
    }
}

RedSocial::~RedSocial() {
    for (int i = 0; i < numUsuarios; i++) {
        delete directorioUsuarios[i];
    }
    delete[] directorioUsuarios;
    liberarMatriz();
}

void RedSocial::redimensionarDirectorio() {
    maxUsuarios *= 2;
    Usuario** nuevo = new Usuario*[maxUsuarios];
    for (int i = 0; i < maxUsuarios; i++) {
        nuevo[i] = (i < numUsuarios) ? directorioUsuarios[i] : nullptr;
    }
    delete[] directorioUsuarios;
    directorioUsuarios = nuevo;
}

void RedSocial::construirMatriz() {
    liberarMatriz();
    if (numUsuarios == 0) return;

    matrizRelaciones = new bool*[numUsuarios];
    for (int i = 0; i < numUsuarios; i++) {
        matrizRelaciones[i] = new bool[numUsuarios];
        for (int j = 0; j < numUsuarios; j++) {
            matrizRelaciones[i][j] = false;
        }
    }

    for (int i = 0; i < numUsuarios; i++) {
        if (!directorioUsuarios[i]) continue;
        int cant = directorioUsuarios[i]->getNumAmigos();
        for (int k = 0; k < cant; k++) {
            Usuario* amigo = directorioUsuarios[i]->getAmigoPorIndice(k);
            if (amigo) {
                int idxAmigo = -1;
                for (int j = 0; j < numUsuarios; j++) {
                    if (directorioUsuarios[j] == amigo) {
                        idxAmigo = j;
                        break;
                    }
                }
                if (idxAmigo != -1) {
                    matrizRelaciones[i][idxAmigo] = true;
                }
            }
        }
    }
    matrizLista = true;
}

void RedSocial::liberarMatriz() {
    if (matrizRelaciones != nullptr) {
        for (int i = 0; i < numUsuarios; i++) {
            delete[] matrizRelaciones[i];
        }
        delete[] matrizRelaciones;
        matrizRelaciones = nullptr;
    }
    matrizLista = false;
}

// Pendiente lectura y escritua en archivos .txt

void RedSocial::cargarUsuariosDisco() {}
void RedSocial::cargarAlbumesDisco() {}
void RedSocial::cargarFotosDisco() {}
void RedSocial::cargarMensajesDisco() {}
void RedSocial::cargarAmistadesDisco() {}
void RedSocial::cargarSolicitudesDisco() {}

void RedSocial::cargarDatos() {
    iniciarMedicion();

    // Inicialización de 3 usuarios de demostración en RAM para probar el programa
    Fecha fnac(15, 8, 2000);
    Fecha finsc(1, 2, 2024);

    Usuario* u1 = new Usuario("juanito", fnac, "juanito@udea.edu.co", "/profile1.png", "123", "Medellin", "Colombia", finsc);
    Usuario* u2 = new Usuario("maria", fnac, "maria@udea.edu.co", "/profile2.png", "456", "Bogota", "Colombia", finsc);
    Usuario* u3 = new Usuario("carlos", fnac, "carlos@udea.edu.co", "/profile3.png", "789", "Cali", "Colombia", finsc);

    if (numUsuarios == maxUsuarios) redimensionarDirectorio();
    directorioUsuarios[numUsuarios++] = u1;

    if (numUsuarios == maxUsuarios) redimensionarDirectorio();
    directorioUsuarios[numUsuarios++] = u2;

    if (numUsuarios == maxUsuarios) redimensionarDirectorio();
    directorioUsuarios[numUsuarios++] = u3;

    Fecha hoy(17, 10, 2026);
    Album a1("Cartagena2026", "/albums/Cartagena/", "amigos");
    Foto f1(hoy, 2.5f, "/Cartagena/Malecon.png", 10);
    Foto f2(hoy, 3.1f, "/Cartagena/Bocagrande.png", 20);
    Foto f3(hoy, 1.8f, "/Cartagena/Castillo.png", 15);
    a1.agregarFotografia(f1);
    a1.agregarFotografia(f2);
    a1.agregarFotografia(f3);

    u1->crearAlbum(a1);

    Mensaje m1("juanito", "maria", "Hola Maria, bienvenida a la plataforma", hoy);
    u1->registrarMensajeEnviado(m1);
    u2->registrarMensajeRecibido(m1);

    u1->vincularAmigo(u2);
    u2->vincularAmigo(u1);
    u2->recibirSolicitudAmistad("carlos");

    cargarUsuariosDisco();
    cargarAlbumesDisco();
    cargarFotosDisco();
    cargarMensajesDisco();
    cargarAmistadesDisco();
    cargarSolicitudesDisco();

    construirMatriz();
    detenerMedicion("Carga de Datos Iniciales");
}

void RedSocial::guardarUsuariosDisco() {}
void RedSocial::guardarAmistadesDisco() {}
void RedSocial::guardarMensajesDisco() {}
void RedSocial::guardarAlbumesDisco() {}
void RedSocial::guardarSolicitudesDisco() {}

void RedSocial::guardarDatos() {
    iniciarMedicion();
    guardarUsuariosDisco();
    guardarAmistadesDisco();
    guardarMensajesDisco();
    guardarAlbumesDisco();
    guardarSolicitudesDisco();
    detenerMedicion("Guardar Datos en Disco");
}


bool RedSocial::iniciarSesion() {
    iniciarMedicion();
    char correo[100];
    char clv[100];

    cout << "\n=== INICIAR SESIÓN EN LA RED ===" << endl;
    cout << "Correo electrónico: ";
    cin >> correo;
    cout << "Contraseña: ";
    cin >> clv;

    for (int i = 0; i < numUsuarios; i++) {
        registrarIteracion();
        if (directorioUsuarios[i] &&
            strcmp(directorioUsuarios[i]->getCorreoElectronico(), correo) == 0 &&
            strcmp(directorioUsuarios[i]->getClave(), clv) == 0) {
            usuarioSesion = directorioUsuarios[i];
            cout << "\n¡Bienvenido/a, " << usuarioSesion->getNombreUsuario() << "!" << endl;
            mostrarMejoresAmigos();
            detenerMedicion("Inicio de Sesión Exitoso");
            return true;
        }
    }

    cout << "Credenciales no válidas." << endl;
    detenerMedicion("Inicio de Sesión Fallido");
    return false;
}

Usuario* RedSocial::buscarUsuarioPorNombre(const char* nombre) const {
    if (!nombre) return nullptr;
    for (int i = 0; i < numUsuarios; i++) {
        if (directorioUsuarios[i] && strcmp(directorioUsuarios[i]->getNombreUsuario(), nombre) == 0) {
            return directorioUsuarios[i];
        }
    }
    return nullptr;
}

int RedSocial::contarAmigosEnComun(Usuario* u1, Usuario* u2) const {
    if (!u1 || !u2) return 0;

    int idx1 = -1, idx2 = -1;
    for (int i = 0; i < numUsuarios; i++) {
        if (directorioUsuarios[i] == u1) idx1 = i;
        if (directorioUsuarios[i] == u2) idx2 = i;
    }

    if (idx1 == -1 || idx2 == -1) return 0;

    int comunes = 0;
    if (matrizLista && matrizRelaciones != nullptr) {
        for (int i = 0; i < numUsuarios; i++) {
            if (matrizRelaciones[idx1][i] && matrizRelaciones[idx2][i]) {
                comunes++;
            }
        }
    }
    return comunes;
}

void RedSocial::mostrarMejoresAmigos() {
    if (!usuarioSesion) return;

    cout << "\n--- MEJORES AMIGOS (FOTOS DE PERFIL) ---" << endl;
    int cant = usuarioSesion->getNumAmigos();
    if (cant == 0) {
        cout << "Aún no tienes contactos agregados." << endl;
        return;
    }

    for (int i = 0; i < cant && i < 3; i++) {
        registrarIteracion();
        Usuario* amg = usuarioSesion->getAmigoPorIndice(i);
        if (amg) {
            int comunes = contarAmigosEnComun(usuarioSesion, amg);
            float prioridad = (comunes <= 10) ? 1.0f : (comunes <= 20 ? 2.5f : 3.5f);

            cout << "Amigo " << (i + 1) << ": " << amg->getNombreUsuario()
                 << " | Factor Prioridad: " << prioridad << "x"
                 << " | Foto Perfil: " << amg->getFotoPerfil() << endl;
        }
    }
}

void RedSocial::actualizarMejoresAmigos() {
    iniciarMedicion();
    mostrarMejoresAmigos();
    detenerMedicion("Actualización de Mejores Amigos");
}

void RedSocial::enviarSolicitud() {
    iniciarMedicion();
    if (!usuarioSesion) return;

    char destinoNom[100];
    cout << "\nUsuario al que deseas enviar solicitud: ";
    cin >> destinoNom;

    Usuario* dest = buscarUsuarioPorNombre(destinoNom);
    if (!dest) {
        cout << "El usuario '" << destinoNom << "' no existe." << endl;
    } else if (usuarioSesion->esAmigoDe(dest)) {
        cout << "Ya tienes una relación de amistad con " << destinoNom << "." << endl;
    } else {
        dest->recibirSolicitudAmistad(usuarioSesion->getNombreUsuario());
        cout << "Solicitud de amistad enviada a " << destinoNom << "." << endl;
    }
    detenerMedicion("Enviar Solicitud");
}

void RedSocial::aceptarSolicitud() {
    iniciarMedicion();
    if (!usuarioSesion) return;

    int cant = usuarioSesion->getNumSolicitudes();
    if (cant == 0) {
        cout << "\nNo tienes solicitudes pendientes." << endl;
        detenerMedicion("Aceptar Solicitud");
        return;
    }

    cout << "\n=== SOLICITUDES PENDIENTES ===" << endl;
    for (int i = 0; i < cant; i++) {
        registrarIteracion();
        char* em = usuarioSesion->getSolicitudPorIndice(i);
        if (em) cout << (i + 1) << ". " << em << endl;
    }

    cout << "Selecciona el número de la solicitud a aceptar (0 para salir): ";
    int op;
    cin >> op;

    if (op > 0 && op <= cant) {
        char* emisor = usuarioSesion->getSolicitudPorIndice(op - 1);
        if (emisor) {
            Usuario* uEmisor = buscarUsuarioPorNombre(emisor);
            if (uEmisor) {
                usuarioSesion->vincularAmigo(uEmisor);
                uEmisor->vincularAmigo(usuarioSesion);
                construirMatriz();
                cout << "¡Solicitud aceptada! Ahora eres amigo de " << uEmisor->getNombreUsuario() << "." << endl;
            }
        }
        usuarioSesion->borrarSolicitud(op - 1);
    }
    detenerMedicion("Aceptar Solicitud");
}

void RedSocial::visitarPerfilAmigo() {
    iniciarMedicion();
    if (!usuarioSesion) return;

    char nombreAmigo[100];
    cout << "\nNombre del amigo a visitar: ";
    cin >> nombreAmigo;

    Usuario* amg = buscarUsuarioPorNombre(nombreAmigo);
    if (!amg) {
        cout << "El usuario '" << nombreAmigo << "' no existe." << endl;
        detenerMedicion("Visitar Perfil");
        return;
    }

    bool esAmigo = usuarioSesion->esAmigoDe(amg);
    cout << "\n=== PERFIL DE " << amg->getNombreUsuario() << " ===" << endl;
    amg->listarAlbumes();

    int cant = amg->getNumAlbumes();
    if (cant > 0) {
        cout << "Selecciona el álbum a ver en carrusel (0 para volver): ";
        int sel;
        cin >> sel;

        if (sel > 0 && sel <= cant) {
            Album* alb = amg->getAlbumPorIndice(sel - 1);
            if (alb) {
                const char* rol = esAmigo ? "amigo" : "otro";
                if (alb->esVisiblePara(rol)) {
                    abrirCarrusel(*alb);
                } else {
                    cout << "Álbum privado. No cuentas con permisos de visualización." << endl;
                }
            }
        }
    }
    detenerMedicion("Visitar Perfil");
}

void RedSocial::abrirCarrusel(Album& a) {
    int total = a.getNumFotos();
    if (total == 0) {
        cout << "El álbum '" << a.getTitulo() << "' está vacío." << endl;
        return;
    }

    int idx = 0;
    int opcion = 0;

    do {
        Foto* f = a.consultarFoto(idx);
        cout << "\n========================================" << endl;
        cout << "  MODO CARRUSEL - ÁLBUM: " << a.getTitulo() << endl;
        cout << "========================================" << endl;
        cout << "Fotografía [" << (idx + 1) << " de " << total << "]" << endl;
        if (f) f->imprimirDetalle();

        cout << "\nNavegación:" << endl;
        cout << "1. Siguiente foto (Avanzar)" << endl;
        cout << "2. Foto anterior (Retroceder)" << endl;
        cout << "3. Dar Me Gusta" << endl;
        cout << "4. Quitar Me Gusta" << endl;
        cout << "5. Salir del visor" << endl;
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            idx = (idx + 1) % total;
            break;
        case 2:
            idx = (idx - 1 + total) % total;
            break;
        case 3:
            if (f) f->incrementarLike();
            cout << "¡Like guardado!" << endl;
            break;
        case 4:
            if (f) f->decrementarLike();
            cout << "Like eliminado." << endl;
            break;
        case 5:
            cout << "Saliendo del visor..." << endl;
            break;
        }
    } while (opcion != 5);
}

void RedSocial::verSugerencias() {
    iniciarMedicion();
    if (!usuarioSesion) return;

    int K;
    cout << "\nCantidad K de sugerencias a consultar (1 a 20): ";
    cin >> K;
    if (K < 1) K = 1;
    if (K > 20) K = 20;

    cout << "\n=== SUGERENCIAS DE CONEXIÓN (TOP " << K << ") ===" << endl;
    int mostrados = 0;

    for (int i = 0; i < numUsuarios && mostrados < K; i++) {
        registrarIteracion();
        Usuario* pos = directorioUsuarios[i];
        if (pos && pos != usuarioSesion && !usuarioSesion->esAmigoDe(pos)) {
            int comunes = contarAmigosEnComun(usuarioSesion, pos);
            cout << (mostrados + 1) << ". " << pos->getNombreUsuario()
                 << " (" << comunes << " amigos en común)" << endl;
            mostrados++;
        }
    }

    if (mostrados > 0) {
        cout << "\n¿Enviar solicitud a un usuario sugerido? (S/N): ";
        char op;
        cin >> op;
        if (op == 'S' || op == 's') {
            char nomSug[100];
            cout << "Escribe el nombre del usuario: ";
            cin >> nomSug;
            enviarSolicitudSugerencia(nomSug);
        }
    } else {
        cout << "No hay más usuarios para sugerir." << endl;
    }
    detenerMedicion("Ver Sugerencias");
}

void RedSocial::enviarSolicitudSugerencia(const char* nombre) {
    Usuario* dest = buscarUsuarioPorNombre(nombre);
    if (dest && usuarioSesion) {
        dest->recibirSolicitudAmistad(usuarioSesion->getNombreUsuario());
        cout << "Solicitud enviada a " << nombre << "." << endl;
    }
}

void RedSocial::enviarMensaje() {
    iniciarMedicion();
    if (!usuarioSesion) return;

    char receptorNom[100];
    char texto[512];

    cout << "\nNombre del destinatario: ";
    cin >> receptorNom;

    Usuario* receptor = buscarUsuarioPorNombre(receptorNom);
    if (!receptor || !usuarioSesion->esAmigoDe(receptor)) {
        cout << "Solo puedes chatear con usuarios que tengas en tus contactos." << endl;
        detenerMedicion("Enviar Mensaje");
        return;
    }

    cout << "Escribe el mensaje (máximo 512 caracteres): ";
    cin.ignore();
    cin.getline(texto, 512);

    Fecha hoy(17, 10, 2026);
    Mensaje msj(usuarioSesion->getNombreUsuario(), receptorNom, texto, hoy);

    usuarioSesion->registrarMensajeEnviado(msj);
    receptor->registrarMensajeRecibido(msj);

    cout << "¡Mensaje enviado con éxito!" << endl;
    detenerMedicion("Enviar Mensaje");
}

void RedSocial::leerNuevosMensajes() {
    iniciarMedicion();
    if (!usuarioSesion) return;

    cout << "\n=== BANDEJA DE ENTRADA ===" << endl;
    int cant = usuarioSesion->getNumRecibidos();
    int mostrados = 0;

    for (int i = 0; i < cant; i++) {
        registrarIteracion();
        Mensaje* m = usuarioSesion->getMensajeRecibido(i);
        if (m) {
            m->mostrarContenido();
            m->marcarLeido();
            mostrados++;
        }
    }

    if (mostrados == 0) cout << "No tienes mensajes nuevos." << endl;
    detenerMedicion("Leer Mensajes");
}

void RedSocial::buscarMensajePorFecha() {
    iniciarMedicion();
    if (!usuarioSesion) return;

    int d1, m1, a1, d2, m2, a2;
    cout << "\nFecha inicial (Día Mes Año): ";
    cin >> d1 >> m1 >> a1;
    cout << "Fecha final (Día Mes Año): ";
    cin >> d2 >> m2 >> a2;

    Fecha inicio(d1, m1, a1);
    Fecha fin(d2, m2, a2);

    cout << "\n=== FILTRO DE MENSAJES POR FECHA ===" << endl;
    int cant = usuarioSesion->getNumRecibidos();
    for (int i = 0; i < cant; i++) {
        registrarIteracion();
        Mensaje* m = usuarioSesion->getMensajeRecibido(i);
        if (m && m->estaEnRango(inicio, fin)) {
            m->mostrarContenido();
        }
    }
    detenerMedicion("Buscar Mensajes por Fecha");
}

void RedSocial::mostrarMenuAmistades() {
    int op = 0;
    do {
        cout << "\n--- GESTIÓN DE CONTACTOS ---" << endl;
        cout << "1. Ver mejores amigos" << endl;
        cout << "2. Enviar solicitud de amistad" << endl;
        cout << "3. Ver y aceptar solicitudes recibidas" << endl;
        cout << "4. Volver al menú principal" << endl;
        cout << "Opción: ";
        cin >> op;

        switch (op) {
        case 1: mostrarMejoresAmigos(); break;
        case 2: enviarSolicitud(); break;
        case 3: aceptarSolicitud(); break;
        case 4: break;
        default: cout << "Opción inválida." << endl; break;
        }
    } while (op != 4);
}

void RedSocial::mostrarMenuMensajes() {
    int op = 0;
    do {
        cout << "\n--- BANDEJA DE MENSAJERÍA ---" << endl;
        cout << "1. Enviar un nuevo mensaje" << endl;
        cout << "2. Ver mensajes recibidos" << endl;
        cout << "3. Filtrar mensajes por rango de fecha" << endl;
        cout << "4. Volver al menú principal" << endl;
        cout << "Opción: ";
        cin >> op;

        switch (op) {
        case 1: enviarMensaje(); break;
        case 2: leerNuevosMensajes(); break;
        case 3: buscarMensajePorFecha(); break;
        case 4: break;
        default: cout << "Opción inválida." << endl; break;
        }
    } while (op != 4);
}

void RedSocial::mostrarMenu() {
    if (!usuarioSesion) return;
    int opcion = 0;
    do {
        cout << "\n========================================" << endl;
        cout << "          MENÚ PRINCIPAL RED            " << endl;
        cout << "========================================" << endl;
        cout << "1. Gestión de contactos" << endl;
        cout << "2. Visitar perfil de un amigo" << endl;
        cout << "3. Sugerencias de amistad" << endl;
        cout << "4. Mensajería" << endl;
        cout << "5. Cerrar sesión" << endl;
        cout << "Selección: ";
        cin >> opcion;

        switch (opcion) {
        case 1: mostrarMenuAmistades(); break;
        case 2: visitarPerfilAmigo(); break;
        case 3: verSugerencias(); break;
        case 4: mostrarMenuMensajes(); break;
        case 5:
            cout << "Cerrando la sesión de " << usuarioSesion->getNombreUsuario() << "..." << endl;
            usuarioSesion = nullptr;
            break;
        default:
            cout << "Opción inválida." << endl;
            break;
        }
    } while (opcion != 5 && usuarioSesion != nullptr);
}

void RedSocial::iniciarMedicion() {
    iteracionesOperacion = 0;
    memoriaConsumidaRAM = 0;
}

void RedSocial::registrarIteracion() {
    iteracionesOperacion++;
}

void RedSocial::sumarBytesMemoria(long long bytes) {
    memoriaConsumidaRAM += bytes;
}

void RedSocial::detenerMedicion(const char* nombreAccion) {
    long long totalBytes = sizeof(*this);
    totalBytes += maxUsuarios * sizeof(Usuario*);

    for (int i = 0; i < numUsuarios; i++) {
        if (directorioUsuarios[i]) {
            totalBytes += directorioUsuarios[i]->obtenerBytes();
        }
    }

    if (matrizRelaciones != nullptr) {
        totalBytes += numUsuarios * sizeof(bool*);
        totalBytes += (numUsuarios * numUsuarios * sizeof(bool));
    }

    memoriaConsumidaRAM = totalBytes;

    cout << "\n----------------------------------------" << endl;
    cout << "[METRICAS DEL SISTEMA: " << (nombreAccion ? nombreAccion : "Operación") << "]" << endl;
    cout << "-> Número de iteraciones: " << iteracionesOperacion << endl;
    cout << "-> Consumo total en RAM: " << memoriaConsumidaRAM << " Bytes ("
         << (memoriaConsumidaRAM / 1024.0) << " KB)" << endl;
    cout << "----------------------------------------" << endl;
}