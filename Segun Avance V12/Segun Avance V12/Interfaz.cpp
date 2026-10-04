#include "Interfaz.h"
#include "Utilidades.h"
#include "Archivos.h"
#include "Ordenamientos.h"
#include "DatosIniciales.h"
#include "Configuracion.h"
#include "ListaSimple.h"
#include "ListaDoble.h"
#include "Cola.h"
#include "Usuario.h"
#include "Administrador.h"
#include "Ruta.h"
#include "RutaCombinada.h"
#include "ReporteTrafico.h"
#include "PuntoInteres.h"
#include "Sede.h"
#include "BusquedaRuta.h"
#include "HistorialBusqueda.h"
#include "Notificacion.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include <iomanip>

using namespace std;

namespace {

void mostrarPantallaDeCarga() {
    limpiarPantalla();
    cout << "    ..:---===========================================---:..    \n";
    cout << "  ..-=====================================================-..  \n";
    cout << " .-=========================================================-..\n";
    cout << ".-===========================================================-.\n";
    cout << ":=============================================================:\n";
    cout << "===========================+#@@@@@@@@@%#+======================\n";
    cout << "=======================+%@@@%*=::::::=*%@@@%+==================\n";
    cout << "=====================#@@%-..           ...=@@@#================\n";
    cout << "===================#@@+.                     *@@#==============\n";
    cout << "=================+@@#.                        .*@%+============\n";
    cout << "================*@@=                            -@@*===========\n";
    cout << "===============*@@:         ...           ...    =%@+==========\n";
    cout << "==============+%@-         .*@#:.       .+@@-.    =@@==========\n";
    cout << "==============#@#.         #@@@+.       =@@@@.    .#@*=========\n";
    cout << "==============%@-.          *#+.         =**:      +@@=========\n";
    cout << "=============+%@:                                  =@@=========\n";
    cout << "=============+%@:           ..            ...      =@@=========\n";
    cout << "=============+%@:           @@*          :%@:      *@%=========\n";
    cout << "=============#@%:           :%@#-.     :*@@+.     :#@+=========\n";
    cout << "=========+#%@@#:.            .=#@@%**#@@@*:.     .*@%==========\n";
    cout << "=========+@@*:.                ..-====-:..      .+@%+==========\n";
    cout << "==========*@%=                                 :#@%+===========\n";
    cout << "===========+@@#:                              +@@#=============\n";
    cout << "=============#@@%. .-%@@@@%*               .*@@%+==============\n";
    cout << "===============*@@@@@@@@@@@@%           -#@@@#=================\n";
    cout << "==================*@@@@@@@@@@@@@@@@@@@@@@@@@@==================\n";
    cout << "==================*@@@@@@@@@@@####@@@@@@@@@@@==================\n";
    cout << "===================%@@@@@@@@%=====+@@@@@@@@@+==================\n";
    cout << "====================+%@@@@@+========*@@@@@#====================\n";
    cout << ":=============================================================:\n";
    cout << ".-===========================================================-.\n";
    cout << " .-=========================================================-..\n";
    cout << "  ..-=====================================================-:.  \n";
    cout << "    ..:--=============================================--:..    \n";
    cout << "\n\t       Cargando Waze - Segundo Avance...";
    this_thread::sleep_for(chrono::seconds(1));
    limpiarPantalla();
}

bool menuPerfilUsuario(Usuario& usuarioActivo, ListaSimple<Usuario>& listaUsuarios) {
    int opcPerfil = 0;
    do {
        limpiarPantalla();
        cout << "=============================================\n";
        cout << "            PERFIL DE USUARIO                \n";
        cout << "=============================================\n";
        cout << " Nombre de Usuario : " << usuarioActivo.getUsuario() << "\n";
        cout << " Correo Electronico: " << usuarioActivo.getCorreo() << "\n";
        cout << " Telefono          : " << usuarioActivo.getTelefono() << "\n";
        cout << " Anio Nacimiento   : " << (usuarioActivo.getAnioNacimiento() > 0 ? to_string(usuarioActivo.getAnioNacimiento()) : string("No registrado")) << "\n";
        cout << " Preferencia Ruta  : " << usuarioActivo.getPerfil().getPreferenciaRuta() << "\n";
        cout << "=============================================\n";
        cout << "1. Cambiar nombre de usuario\n";
        cout << "2. Cambiar contrasena\n";
        cout << "3. Eliminar cuenta\n";
        cout << "4. Volver al menu de navegacion\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcPerfil)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcPerfil == 1) {
            string nuevoUser;
            cout << "\nIngrese el nuevo nombre de usuario: ";
            cin >> nuevoUser;
            usuarioActivo.setUsuario(nuevoUser);
            guardarUsuarios(listaUsuarios);
            cout << "\n[+] Nombre de usuario actualizado con exito.\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
        else if (opcPerfil == 2) {
            string passActual, passNueva;
            cout << "\nIngrese su contrasena actual: ";
            cin >> passActual;
            if (passActual == usuarioActivo.getContrasena()) {
                cout << "Ingrese la nueva contrasena: ";
                cin >> passNueva;
                usuarioActivo.setContrasena(passNueva);
                guardarUsuarios(listaUsuarios);
                cout << "\n[+] Contrasena actualizada con exito.\n";
            }
            else cout << "\n[!] Contrasena incorrecta.\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
        else if (opcPerfil == 3) {
            char confirm;
            cout << "\nEsta seguro que desea eliminar su cuenta? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                string u = usuarioActivo.getUsuario();
                string p = usuarioActivo.getContrasena();

                // Mathias Raul Grovas Ormachea
                listaUsuarios.eliminar([&u, &p](const Usuario& usr) {
                    return usr.getUsuario() == u && usr.getContrasena() == p;
                });

                guardarUsuarios(listaUsuarios);
                cout << "\n[+] Cuenta eliminada correctamente. Redirigiendo...\n";
                this_thread::sleep_for(chrono::seconds(1));
                return true;
            }
        }
    } while (opcPerfil != 4);

    return false;
}

void explorarPOI(const ListaDoble<PuntoInteres>& listaPOI) {
    NodoDoble<PuntoInteres>* actual = listaPOI.getCabeza();
    char opc = 'x';

    if (actual == nullptr) {
        cout << "[!] No hay puntos de interes registrados.\n";
        pausar();
        return;
    }

    do {
        limpiarPantalla();
        cout << "=============================================\n";
        cout << "     PUNTOS DE INTERES CERCANOS (POI)        \n";
        cout << "=============================================\n\n";
        actual->dato.mostrar();
        cout << "\n=============================================\n";
        cout << " [A] Anterior  |  [S] Siguiente  |  [X] Salir\n";
        cout << "Opcion: ";
        cin >> opc;

        if ((opc == 's' || opc == 'S') && actual->siguiente != nullptr)
            actual = actual->siguiente;
        else if ((opc == 'a' || opc == 'A') && actual->anterior != nullptr)
            actual = actual->anterior;
    } while (opc != 'x' && opc != 'X');
}

string seleccionarSede(const string& titulo) {
    int opcion = 0;
    do {
        cout << "\n" << titulo << "\n";
        cout << "1. " << SEDE_VILLA << "\n";
        cout << "2. " << SEDE_MONTERRICO << "\n";
        cout << "3. " << SEDE_SAN_MIGUEL << "\n";
        cout << "4. " << SEDE_SAN_ISIDRO << "\n";
        cout << "Seleccione una sede: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = 0;
        }
    } while (opcion < 1 || opcion > 4);

    if (opcion == 1) return SEDE_VILLA;
    if (opcion == 2) return SEDE_MONTERRICO;
    if (opcion == 3) return SEDE_SAN_MIGUEL;
    return SEDE_SAN_ISIDRO;
}

void buscarRutasAlternativas(const Usuario& usuarioActivo, const ListaSimple<Ruta>& rutas) {
    limpiarPantalla();
    cout << "=============================================\n";
    cout << "       BUSQUEDA RECURSIVA DE RUTAS           \n";
    cout << "=============================================\n";

    string origen = seleccionarSede("ORIGEN");
    string destino;
    do {
        destino = seleccionarSede("DESTINO");
        if (textoIgual(origen, destino))
            cout << "\n[!] El destino debe ser diferente del origen.\n";
    } while (textoIgual(origen, destino));

    Sede sedeOrigen(origen);
    Sede sedeDestino(destino);
    Ruta* primeraRuta = rutas.buscar([&origen, &destino](const Ruta& r) {
        return textoIgual(r.getOrigen(), origen) && textoIgual(r.getDestino(), destino);
    });

    BusquedaRuta busqueda = (primeraRuta != nullptr)
        ? BusquedaRuta(usuarioActivo, sedeOrigen, sedeDestino, *primeraRuta)
        : BusquedaRuta(usuarioActivo, sedeOrigen, sedeDestino);
    HistorialBusqueda historial(busqueda, fechaHoraActual());

    cout << "\nOrigen seleccionado : " << historial.getOrigen() << "\n";
    cout << "Destino seleccionado: " << historial.getDestino() << "\n";
    cout << "\nRutas registradas para este trayecto:\n";
    cout << "---------------------------------------------\n";

    int encontradas = rutas.buscarTodosRecursivo(
        [&origen, &destino](const Ruta& r) {
            return textoIgual(r.getOrigen(), origen) && textoIgual(r.getDestino(), destino);
        },
        [](const Ruta& r) {
            r.mostrarInfo();
            cout << "---------------------------------------------\n";
        }
    );

    if (encontradas == 0)
        cout << "[!] No existen rutas registradas para esas sedes.\n";
    else
        cout << "Total de alternativas: " << encontradas << "\n";

    pausar();
}

void registrarRutaAlternativa(ListaSimple<Ruta>& rutas) {
    limpiarPantalla();
    cout << "=============================================\n";
    cout << "        REGISTRAR RUTA ALTERNATIVA           \n";
    cout << "=============================================\n";

    string nombre, origen, destino;
    double distancia;
    int tiempo;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nombre de la ruta : "; getline(cin, nombre);
    origen = seleccionarSede("ORIGEN");
    do {
        destino = seleccionarSede("DESTINO");
        if (textoIgual(origen, destino))
            cout << "\n[!] El destino debe ser diferente del origen.\n";
    } while (textoIgual(origen, destino));

    cout << "Distancia (km)       : "; cin >> distancia;
    cout << "Tiempo estimado (min): "; cin >> tiempo;

    if (nombre.empty() || distancia <= 0 || tiempo <= 0) {
        cout << "\n[!] Datos de ruta invalidos.\n";
    }
    else {
        Sede sedeOrigen(origen);
        Sede sedeDestino(destino);
        Avenida avenidaPrincipal("Via principal de " + nombre);
        Interseccion cruce(avenidaPrincipal, Avenida("Conexion de " + nombre), "Cruce principal");
        TramoRuta tramo(nombre, avenidaPrincipal, cruce, distancia, 1);
        EstadoRuta estado(nombre, 0, true);
        Ruta nuevaRuta(nombre, sedeOrigen, sedeDestino, distancia, tiempo, estado, tramo);

        rutas.insertarFinal(nuevaRuta);
        guardarRutas(rutas);
        cout << "\n[+] Ruta alternativa registrada correctamente.\n";
    }
    pausar();
}

void mostrarTodasLasRutas(const ListaSimple<Ruta>& rutas) {
    limpiarPantalla();
    cout << "=============================================\n";
    cout << "            RUTAS REGISTRADAS                \n";
    cout << "=============================================\n\n";

    int contador = 0;
    rutas.recorrerConLambda([&contador](const Ruta& r) {
        contador++;
        cout << contador << ".\n";
        r.mostrarInfo();
        cout << "---------------------------------------------\n";
    });

    if (contador == 0) cout << "[!] No hay rutas registradas.\n";
    pausar();
}

void eliminarRuta(ListaSimple<Ruta>& rutas) {
    limpiarPantalla();
    cout << "=============================================\n";
    cout << "              ELIMINAR RUTA                  \n";
    cout << "=============================================\n\n";

    int total = rutas.longitud();
    if (total == 0) {
        cout << "[!] No hay rutas registradas.\n";
        pausar();
        return;
    }

    for (int i = 0; i < total; i++) {
        const Ruta* r = rutas.obtenerPos(i);
        cout << i + 1 << ". " << r->getNombre() << " | "
             << r->getOrigen() << " -> " << r->getDestino()
             << " | " << r->getTiempoMin() << " min\n";
    }

    int opcion = 0;
    cout << "\nSeleccione la ruta a eliminar (0 para cancelar): ";
    if (!(cin >> opcion)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (opcion == 0) return;
    if (opcion < 1 || opcion > total) {
        cout << "\n[!] Opcion invalida.\n";
        pausar();
        return;
    }

    const Ruta* elegida = rutas.obtenerPos(opcion - 1);
    string nombre = elegida->getNombre();
    string origen = elegida->getOrigen();
    string destino = elegida->getDestino();
    int tiempo = elegida->getTiempoMin();

    bool eliminada = rutas.eliminar([&](const Ruta& r) {
        return r.getNombre() == nombre && r.getOrigen() == origen &&
               r.getDestino() == destino && r.getTiempoMin() == tiempo;
    });

    if (eliminada) {
        guardarRutas(rutas);
        cout << "\n[+] Ruta eliminada correctamente.\n";
    }
    else {
        cout << "\n[!] No se pudo eliminar la ruta.\n";
    }
    pausar();
}

Ruta* elegirRutaEntreSedes(ListaSimple<Ruta>& rutas, const string& origen, const string& destino) {
    int cantidad = rutas.contarSi([&](const Ruta& r) {
        return textoIgual(r.getOrigen(), origen) && textoIgual(r.getDestino(), destino);
    });

    if (cantidad == 0) return nullptr;

    Ruta** candidatas = new Ruta*[cantidad];
    int pos = 0;
    for (int i = 0; i < rutas.longitud(); i++) {
        Ruta* r = rutas.obtenerPos(i);
        if (r != nullptr && textoIgual(r->getOrigen(), origen) && textoIgual(r->getDestino(), destino)) {
            candidatas[pos++] = r;
        }
    }

    int opcion = 1;
    if (cantidad > 1) {
        cout << "\nHay " << cantidad << " rutas para " << origen << " -> " << destino << ":\n";
        for (int i = 0; i < cantidad; i++) {
            cout << i + 1 << ". " << candidatas[i]->getNombre()
                 << " | " << candidatas[i]->getDistanciaKm() << " km"
                 << " | " << candidatas[i]->getTiempoMin() << " min\n";
        }
        do {
            cout << "Seleccione el tramo que desea usar: ";
            cin >> opcion;
        } while (opcion < 1 || opcion > cantidad);
    }

    Ruta* seleccionada = candidatas[opcion - 1];
    delete[] candidatas;
    return seleccionada;
}

void mostrarRutaCombinadaVisual(const RutaCombinada& combinada) {
    cout << "\n=============================================\n";
    cout << " RUTA COMBINADA: " << combinada.getNombre() << "\n";
    cout << "=============================================\n";

    const ListaDoble<Ruta>& tramos = combinada.getTramos();
    NodoDoble<Ruta>* actual = tramos.getCabeza();

    if (actual == nullptr) {
        cout << "[!] La ruta combinada no contiene tramos.\n";
        return;
    }

    cout << "\nRecorrido hacia adelante (siguiente):\n";
    cout << "  [" << actual->dato.getOrigen() << "]";
    while (actual != nullptr) {
        cout << " <=> [" << actual->dato.getDestino() << "]";
        actual = actual->siguiente;
    }
    cout << "\n";

    cout << "\nTramos almacenados en ListaDoble<Ruta>:\n";
    actual = tramos.getCabeza();
    int numero = 1;
    while (actual != nullptr) {
        cout << "  " << numero++ << ". " << actual->dato.getNombre()
             << " | " << actual->dato.getOrigen() << " -> " << actual->dato.getDestino()
             << " | " << actual->dato.getTiempoMin() << " min\n";
        actual = actual->siguiente;
    }

    cout << "\nRecorrido inverso (anterior):\n  ";
    actual = tramos.getCola();
    if (actual != nullptr) {
        cout << "[" << actual->dato.getDestino() << "]";
        while (actual != nullptr) {
            cout << " <=> [" << actual->dato.getOrigen() << "]";
            actual = actual->anterior;
        }
    }
    cout << "\n";

    cout << fixed << setprecision(1);
    cout << "\nDistancia total: " << combinada.getDistanciaTotal() << " km\n";
    cout << "Tiempo total   : " << combinada.getTiempoTotal() << " min\n";
}

void registrarRutaCombinada(ListaSimple<Ruta>& rutas,
                            ListaSimple<RutaCombinada>& rutasCombinadas) {
    limpiarPantalla();
    cout << "=============================================\n";
    cout << "          REGISTRAR RUTA COMBINADA           \n";
    cout << "          (LISTA DOBLE ENLAZADA)             \n";
    cout << "=============================================\n";

    if (rutas.longitud() < 2) {
        cout << "\n[!] Se necesitan por lo menos dos rutas registradas.\n";
        pausar();
        return;
    }

    string nombre;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nombre para la ruta combinada: ";
    getline(cin, nombre);
    if (nombre.empty()) {
        cout << "\n[!] El nombre no puede estar vacio.\n";
        pausar();
        return;
    }

    if (rutasCombinadas.existeSi([&](const RutaCombinada& rc) {
        return textoIgual(rc.getNombre(), nombre);
    })) {
        cout << "\n[!] Ya existe una ruta combinada con ese nombre.\n";
        pausar();
        return;
    }

    int cantidadSedes = 0;
    do {
        cout << "Cantidad de sedes del recorrido (3 o 4): ";
        if (!(cin >> cantidadSedes)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cantidadSedes = 0;
        }
    } while (cantidadSedes < 3 || cantidadSedes > 4);

    string sedes[4];
    for (int i = 0; i < cantidadSedes; i++) {
        do {
            sedes[i] = seleccionarSede("SEDE " + to_string(i + 1));
            if (i > 0 && textoIgual(sedes[i], sedes[i - 1]))
                cout << "\n[!] No puede repetir la misma sede de forma consecutiva.\n";
        } while (i > 0 && textoIgual(sedes[i], sedes[i - 1]));
    }

    RutaCombinada nueva(nombre);
    for (int i = 0; i < cantidadSedes - 1; i++) {
        cout << "\nBuscando tramo: " << sedes[i] << " -> " << sedes[i + 1] << "\n";
        Ruta* tramo = elegirRutaEntreSedes(rutas, sedes[i], sedes[i + 1]);
        if (tramo == nullptr) {
            cout << "[!] No existe una ruta registrada para ese tramo.\n";
            cout << "    Registre primero la ruta alternativa necesaria.\n";
            pausar();
            return;
        }

        if (!nueva.agregarTramo(*tramo)) {
            cout << "[!] Los tramos seleccionados no son consecutivos.\n";
            pausar();
            return;
        }
    }

    rutasCombinadas.insertarFinal(nueva);
    guardarRutasCombinadas(rutasCombinadas);

    cout << "\n[+] Ruta combinada registrada correctamente.\n";
    mostrarRutaCombinadaVisual(nueva);
    pausar();
}

void buscarRutasCombinadas(const ListaSimple<RutaCombinada>& rutasCombinadas) {
    limpiarPantalla();
    cout << "=============================================\n";
    cout << "          BUSCAR RUTAS COMBINADAS            \n";
    cout << "=============================================\n";

    if (rutasCombinadas.esVacia()) {
        cout << "\n[!] No hay rutas combinadas registradas.\n";
        pausar();
        return;
    }

    string origen = seleccionarSede("ORIGEN");
    string destino;
    do {
        destino = seleccionarSede("DESTINO FINAL");
        if (textoIgual(origen, destino))
            cout << "\n[!] El destino debe ser diferente del origen.\n";
    } while (textoIgual(origen, destino));

    int encontradas = 0;
    rutasCombinadas.recorrerConLambda([&](const RutaCombinada& rc) {
        if (textoIgual(rc.getOrigen(), origen) && textoIgual(rc.getDestino(), destino)) {
            encontradas++;
            cout << "\n" << encontradas << ". ";
            mostrarRutaCombinadaVisual(rc);
        }
    });

    if (encontradas == 0)
        cout << "\n[!] No existen rutas combinadas para ese origen y destino.\n";
    else
        cout << "\nTotal de rutas combinadas encontradas: " << encontradas << "\n";

    pausar();
}

void mostrarTodasLasRutasCombinadas(const ListaSimple<RutaCombinada>& rutasCombinadas) {
    limpiarPantalla();
    cout << "=============================================\n";
    cout << "          RUTAS COMBINADAS REGISTRADAS       \n";
    cout << "=============================================\n";

    int contador = 0;
    rutasCombinadas.recorrerConLambda([&](const RutaCombinada& rc) {
        contador++;
        cout << "\nRUTA COMBINADA #" << contador << "\n";
        mostrarRutaCombinadaVisual(rc);
    });

    if (contador == 0) cout << "\n[!] No hay rutas combinadas registradas.\n";
    pausar();
}

void registrarReporte(const Usuario& usuarioActivo, Cola<ReporteTrafico>& colaReportes) {
    limpiarPantalla();
    cout << "=============================================\n";
    cout << "          REGISTRAR REPORTE TRAFICO          \n";
    cout << "=============================================\n";

    string tipo, ubicacion;
    int gravedad;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Tipo de reporte (Accidente, Trafico, Obras...): "; getline(cin, tipo);
    ubicacion = seleccionarSede("UBICACION DEL REPORTE");
    cout << "Nivel de congestion (1-5): "; cin >> gravedad;

    if (tipo.empty() || gravedad < 1 || gravedad > 5) {
        cout << "\n[!] Datos invalidos. La gravedad debe estar entre 1 y 5.\n";
    }
    else {
        Sede sedeReporte(ubicacion);
        ReporteTrafico nuevo(tipo, sedeReporte, gravedad);
        colaReportes.enqueue(nuevo);
        guardarReportesPendientes(colaReportes);
        registrarEnHistorial(nuevo, "REGISTRADO");

        Notificacion aviso(usuarioActivo, "Nuevo reporte de trafico registrado", nuevo);
        cout << "\n[+] Reporte agregado al final de la cola FIFO.\n";
        cout << "[+] Notificacion generada para " << aviso.getUsuario() << ".\n";
    }
    pausar();
}

void mostrarReportesPendientes(const Cola<ReporteTrafico>& colaReportes, bool soloGraves) {
    limpiarPantalla();
    cout << "=============================================\n";
    if (soloGraves) cout << "       ALERTAS IMPORTANTES (GRAVEDAD >= 3)   \n";
    else cout << "          COLA DE REPORTES PENDIENTES        \n";
    cout << "=============================================\n\n";

    int contador = 0;
    colaReportes.recorrerConLambda([&contador, soloGraves](const ReporteTrafico& r) {
        if (!soloGraves || r.getGravedad() >= 3) {
            contador++;
            cout << contador << ". ";
            r.mostrarInfo();
        }
    });

    if (contador == 0) cout << "[!] No hay reportes que mostrar.\n";
    else if (!soloGraves) cout << "\nTotal en cola: " << colaReportes.size() << "\n";
    pausar();
}

void procesarReporteMasAntiguo(Cola<ReporteTrafico>& colaReportes) {
    limpiarPantalla();
    cout << "=============================================\n";
    cout << "          PROCESAR REPORTE MAS ANTIGUO       \n";
    cout << "=============================================\n\n";

    ReporteTrafico reporte;
    if (colaReportes.dequeue(reporte)) {
        cout << "Reporte procesado siguiendo FIFO:\n";
        reporte.mostrarInfo();
        guardarReportesPendientes(colaReportes);
        registrarEnHistorial(reporte, "PROCESADO");
        cout << "\n[+] El reporte fue retirado del frente de la cola.\n";
    }
    else cout << "[!] La cola de reportes esta vacia.\n";
    pausar();
}

void menuCentroAlertasUsuario(const Usuario& usuarioActivo, Cola<ReporteTrafico>& colaReportes) {
    int opcion = 0;
    do {
        limpiarPantalla();
        cout << "=============================================\n";
        cout << "       CENTRO DE ALERTAS - USUARIO           \n";
        cout << "=============================================\n";
        cout << "1. Registrar nuevo reporte\n";
        cout << "2. Ver reportes pendientes (FIFO)\n";
        cout << "3. Ver alertas importantes\n";
        cout << "4. Volver\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcion == 1) registrarReporte(usuarioActivo, colaReportes);
        else if (opcion == 2) mostrarReportesPendientes(colaReportes, false);
        else if (opcion == 3) mostrarReportesPendientes(colaReportes, true);
    } while (opcion != 4);
}

void menuCentroAlertasAdministrador(Cola<ReporteTrafico>& colaReportes) {
    int opcion = 0;
    do {
        limpiarPantalla();
        cout << "=============================================\n";
        cout << "     GESTION DE ALERTAS - ADMINISTRADOR      \n";
        cout << "=============================================\n";
        cout << "1. Ver reportes pendientes (FIFO)\n";
        cout << "2. Ver alertas importantes\n";
        cout << "3. Procesar reporte mas antiguo\n";
        cout << "4. Volver\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcion == 1) mostrarReportesPendientes(colaReportes, false);
        else if (opcion == 2) mostrarReportesPendientes(colaReportes, true);
        else if (opcion == 3) procesarReporteMasAntiguo(colaReportes);
    } while (opcion != 4);
}

void menuSistemaUsuario(Usuario& usuarioActivo,
                        ListaSimple<Usuario>& listaUsuarios,
                        ListaSimple<Ruta>& listaRutas,
                        ListaSimple<RutaCombinada>& rutasCombinadas,
                        ListaDoble<PuntoInteres>& listaPOI,
                        Cola<ReporteTrafico>& colaReportes) {
    int opcion = 0;
    do {
        limpiarPantalla();
        cout << "=============================================\n";
        cout << "          WAZE - MENU DE USUARIO             \n";
        cout << "=============================================\n";
        cout << "  Bienvenido, " << usuarioActivo.getUsuario() << "!\n";
        cout << "=============================================\n";
        cout << "1. Buscar rutas alternativas (recursividad)\n";
        cout << "2. Buscar rutas combinadas (lista doble)\n";
        cout << "3. Ver todas las rutas\n";
        cout << "4. Ordenar rutas por tiempo (QuickSort)\n";
        cout << "5. Puntos de Interes Cercanos (lista doble)\n";
        cout << "6. Centro de Alertas de Trafico (cola FIFO)\n";
        cout << "7. Historial de Trafico (archivo)\n";
        cout << "8. Mi Perfil de Usuario\n";
        cout << "9. Cerrar Sesion\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcion == 1) buscarRutasAlternativas(usuarioActivo, listaRutas);
        else if (opcion == 2) buscarRutasCombinadas(rutasCombinadas);
        else if (opcion == 3) mostrarTodasLasRutas(listaRutas);
        else if (opcion == 4) mostrarRutasOrdenadas(listaRutas);
        else if (opcion == 5) explorarPOI(listaPOI);
        else if (opcion == 6) menuCentroAlertasUsuario(usuarioActivo, colaReportes);
        else if (opcion == 7) mostrarHistorialTrafico();
        else if (opcion == 8) {
            bool cuentaEliminada = menuPerfilUsuario(usuarioActivo, listaUsuarios);
            if (cuentaEliminada) return;
        }
    } while (opcion != 9);
}

void menuSistemaAdministrador(Administrador& administradorActivo,
                              ListaSimple<Usuario>& listaUsuarios,
                              ListaSimple<Ruta>& listaRutas,
                              ListaSimple<RutaCombinada>& rutasCombinadas,
                              Cola<ReporteTrafico>& colaReportes) {
    int opcion = 0;
    do {
        limpiarPantalla();
        cout << "=============================================\n";
        cout << "       WAZE - MENU DE ADMINISTRADOR          \n";
        cout << "=============================================\n";
        cout << "  Administrador: " << administradorActivo.getUsuario() << "\n";
        cout << "=============================================\n";
        cout << "1. Registrar ruta alternativa\n";
        cout << "2. Registrar ruta combinada (ListaDoble<Ruta>)\n";
        cout << "3. Eliminar ruta\n";
        cout << "4. Ver todas las rutas\n";
        cout << "5. Ver rutas combinadas\n";
        cout << "6. Ordenar rutas por tiempo (QuickSort)\n";
        cout << "7. Ordenar usuarios por anio de nacimiento (Counting Sort)\n";
        cout << "8. Ordenar rutas por distancia (Merge Sort)\n";
        cout << "9. Gestionar alertas de trafico\n";
        cout << "10. Historial de trafico\n";
        cout << "11. Cerrar sesion\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcion == 1) registrarRutaAlternativa(listaRutas);
        else if (opcion == 2) registrarRutaCombinada(listaRutas, rutasCombinadas);
        else if (opcion == 3) eliminarRuta(listaRutas);
        else if (opcion == 4) mostrarTodasLasRutas(listaRutas);
        else if (opcion == 5) mostrarTodasLasRutasCombinadas(rutasCombinadas);
        else if (opcion == 6) mostrarRutasOrdenadas(listaRutas);
        else if (opcion == 7) mostrarUsuariosOrdenadosPorAnio(listaUsuarios);
        else if (opcion == 8) mostrarRutasOrdenadasPorDistancia(listaRutas);
        else if (opcion == 9) menuCentroAlertasAdministrador(colaReportes);
        else if (opcion == 10) mostrarHistorialTrafico();
    } while (opcion != 11);
}

void crearCuentaUsuario(ListaSimple<Usuario>& listaUsuarios) {
    limpiarPantalla();
    string correo, usuario, pass1, pass2, telefono;
    int anioNac = 0;
    cout << "=============================================\n";
    cout << "          CREAR CUENTA DE USUARIO            \n";
    cout << "=============================================\n";
    cout << "Correo electronico: "; cin >> correo;
    cout << "Nombre de usuario: "; cin >> usuario;

    do {
        cout << "Anio de nacimiento (AAAA): ";
        if (!(cin >> anioNac)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            anioNac = 0;
        }
        if (anioNac < 1900 || anioNac > 2026)
            cout << "[!] Ingrese un anio valido entre 1900 y 2026.\n";
    } while (anioNac < 1900 || anioNac > 2026);

    cout << "Contrasena: "; cin >> pass1;
    cout << "Confirme su contrasena: "; cin >> pass2;

    while (pass1 != pass2) {
        cout << "\n[!] Las contrasenas no coinciden. Intente de nuevo.\n";
        cout << "Contrasena: "; cin >> pass1;
        cout << "Confirme su contrasena: "; cin >> pass2;
    }

    cout << "Numero de celular: "; cin >> telefono;

    Usuario* existente = listaUsuarios.buscar([&usuario](const Usuario& u) {
        return u.getUsuario() == usuario;
    });

    if (existente != nullptr) cout << "\n[!] Ese nombre de usuario ya esta registrado.\n";
    else {
        listaUsuarios.insertarFinal(Usuario(correo, usuario, anioNac, pass1, telefono));
        guardarUsuarios(listaUsuarios);
        cout << "\n[+] Cuenta de usuario creada exitosamente.\n";
    }
    pausar();
}

void crearCuentaAdministrador(ListaSimple<Administrador>& administradores) {
    limpiarPantalla();
    string correo, usuario, pass1, pass2, telefono;
    cout << "=============================================\n";
    cout << "       CREAR CUENTA DE ADMINISTRADOR         \n";
    cout << "=============================================\n";
    cout << "No existe una contrasena preestablecida: se guardara la que registre aqui.\n\n";
    cout << "Correo electronico: "; cin >> correo;
    cout << "Nombre de administrador: "; cin >> usuario;
    cout << "Contrasena: "; cin >> pass1;
    cout << "Confirme su contrasena: "; cin >> pass2;

    while (pass1 != pass2) {
        cout << "\n[!] Las contrasenas no coinciden. Intente de nuevo.\n";
        cout << "Contrasena: "; cin >> pass1;
        cout << "Confirme su contrasena: "; cin >> pass2;
    }

    cout << "Numero de celular: "; cin >> telefono;

    Administrador* existente = administradores.buscar([&usuario](const Administrador& a) {
        return a.getUsuario() == usuario;
    });

    if (existente != nullptr) cout << "\n[!] Ese administrador ya esta registrado.\n";
    else {
        administradores.insertarFinal(Administrador(correo, usuario, pass1, telefono));
        guardarAdministradores(administradores);
        cout << "\n[+] Cuenta de administrador creada exitosamente.\n";
    }
    pausar();
}

void iniciarSesionUsuario(ListaSimple<Usuario>& listaUsuarios,
                          ListaSimple<Ruta>& listaRutas,
                          ListaSimple<RutaCombinada>& rutasCombinadas,
                          ListaDoble<PuntoInteres>& listaPOI,
                          Cola<ReporteTrafico>& colaReportes) {
    limpiarPantalla();
    cout << "=============================================\n";
    cout << "       INICIAR SESION COMO USUARIO           \n";
    cout << "=============================================\n";

    if (listaUsuarios.esVacia()) {
        cout << "\n[!] No hay cuentas de usuario registradas.\n";
        pausar();
        return;
    }

    string user, pass;
    cout << "Nombre de usuario: "; cin >> user;
    cout << "Contrasena: "; cin >> pass;

    Usuario* encontrado = listaUsuarios.buscar([&](const Usuario& u) {
        return u.getUsuario() == user && u.getContrasena() == pass;
    });

    if (encontrado != nullptr) {
        cout << "\n[+] Inicio de sesion de usuario exitoso.";
        this_thread::sleep_for(chrono::seconds(1));
        menuSistemaUsuario(*encontrado, listaUsuarios, listaRutas,
                           rutasCombinadas, listaPOI, colaReportes);
    }
    else {
        cout << "\n[!] Usuario o contrasena incorrectos.\n";
        pausar();
    }
}

void iniciarSesionAdministrador(ListaSimple<Administrador>& administradores,
                                ListaSimple<Usuario>& listaUsuarios,
                                ListaSimple<Ruta>& listaRutas,
                                ListaSimple<RutaCombinada>& rutasCombinadas,
                                Cola<ReporteTrafico>& colaReportes) {
    limpiarPantalla();
    cout << "=============================================\n";
    cout << "    INICIAR SESION COMO ADMINISTRADOR        \n";
    cout << "=============================================\n";

    if (administradores.esVacia()) {
        cout << "\n[!] No hay cuentas de administrador registradas.\n";
        cout << "    Cree una cuenta de administrador desde el menu principal.\n";
        pausar();
        return;
    }

    string user, pass;
    cout << "Nombre de administrador: "; cin >> user;
    cout << "Contrasena: "; cin >> pass;

    Administrador* encontrado = administradores.buscar([&](const Administrador& a) {
        return a.getUsuario() == user && a.getContrasena() == pass;
    });

    if (encontrado != nullptr) {
        cout << "\n[+] Inicio de sesion de administrador exitoso.";
        this_thread::sleep_for(chrono::seconds(1));
        menuSistemaAdministrador(*encontrado, listaUsuarios, listaRutas, rutasCombinadas, colaReportes);
    }
    else {
        cout << "\n[!] Administrador o contrasena incorrectos.\n";
        pausar();
    }
}

} // namespace

void ejecutarAplicacion() {
    ListaSimple<Usuario> listaUsuarios;
    ListaSimple<Administrador> listaAdministradores;
    ListaSimple<Ruta> listaRutas;
    ListaSimple<RutaCombinada> listaRutasCombinadas;
    ListaDoble<PuntoInteres> listaPOI;
    Cola<ReporteTrafico> colaReportes;

    cargarUsuarios(listaUsuarios);
    cargarAdministradores(listaAdministradores);
    cargarRutas(listaRutas);
    cargarRutasCombinadas(listaRutasCombinadas);
    cargarPOI(listaPOI);
    cargarReportesPendientes(colaReportes);

    cargarRutasIniciales(listaRutas);
    cargarPOIIniciales(listaPOI);
    cargarReportesIniciales(colaReportes);

    int opcion = 0;
    mostrarPantallaDeCarga();

    do {
        limpiarPantalla();
        cout << "=============================================\n";
        cout << "       SISTEMA WAZE - SEGUNDO AVANCE         \n";
        cout << "=============================================\n";
        cout << "1. Iniciar sesion como usuario\n";
        cout << "2. Iniciar sesion como administrador\n";
        cout << "3. Crear cuenta de usuario\n";
        cout << "4. Crear cuenta de administrador\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcion == 1)
            iniciarSesionUsuario(listaUsuarios, listaRutas, listaRutasCombinadas, listaPOI, colaReportes);
        else if (opcion == 2)
            iniciarSesionAdministrador(listaAdministradores, listaUsuarios, listaRutas, listaRutasCombinadas, colaReportes);
        else if (opcion == 3)
            crearCuentaUsuario(listaUsuarios);
        else if (opcion == 4)
            crearCuentaAdministrador(listaAdministradores);
        else if (opcion == 5) {
            limpiarPantalla();
            cout << "\nGracias por usar Waze. Buen viaje!\n\n";
        }
    } while (opcion != 5);
}
