#include "../include/galeria.h"

struct rep_galeria{
    TColeccionPiezas pieza;
    TFecha fecha;
    TListaExposiciones finalizada;
    TListaExposiciones activas;
    TListaExposiciones futuras;
};

TGaleria crearTGaleria(TFecha fecha){
    TGaleria nuevo = new rep_galeria;

    nuevo->pieza = NULL;
    nuevo->fecha = fecha;
    nuevo->finalizada = NULL;
    nuevo->activas = NULL;
    nuevo->futuras = NULL;

    return nuevo; 
}

void agregarPiezaTGaleria(TGaleria galeria, TPieza pieza){
    insertarPiezaColeccionPiezas(galeria->pieza, pieza);
}

void agregarExposicionTGaleria(TGaleria galeria, TExposicion expo){
    if (compararTFechas(galeria->fecha, fechaInicioTExposicion(expo)) == -1){
        agregarExposicionTListaExposiciones(galeria->futuras, expo);
    } else if (compararTFechas(galeria->fecha, fechaFinTExposicion(expo)) == 1) {
        agregarExposicionTListaExposiciones(galeria->finalizada, expo);
    } else {
        agregarExposicionTListaExposiciones(galeria->activas, expo);
    }
}

void agregarPiezaAExposicionTGaleria(TGaleria galeria, int idPieza, int idExpo){
    TPieza pieza = obtenerPiezaColeccionPiezas(galeria->pieza, idPieza);
    TExposicion exposi = NULL;
    if (perteneceExposicionTListaExposiciones(galeria->finalizada, idExpo)){
        exposi = obtenerExposicionTListaExposiciones(galeria->finalizada, idExpo);
    } else if (perteneceExposicionTListaExposiciones(galeria->activas, idExpo)){
        exposi = obtenerExposicionTListaExposiciones(galeria->activas, idExpo);
    } else {
        exposi = obtenerExposicionTListaExposiciones(galeria->futuras, idExpo);
    }
    agregarATExposicion(exposi, pieza);
}

void avanzarAFechaTGaleria(TGaleria galeria, TFecha fecha) {
    liberarTFecha(galeria->fecha);
    galeria->fecha = fecha;

    TListaExposiciones finalizadas = obtenerExposicionesFinalizadas(galeria->activas, fecha);
    galeria->finalizada = unirListaExposiciones(galeria->finalizada, finalizadas);
    liberarTListaExposiciones(finalizadas, false); 

    TListaExposiciones activasNuevas = obtenerExposicionesActivas(galeria->activas, fecha);
    TListaExposiciones futurasNuevas = obtenerExposicionesActivas(galeria->futuras, fecha);
    galeria->activas = unirListaExposiciones(activasNuevas, futurasNuevas);
    liberarTListaExposiciones(activasNuevas, false); 

    TListaExposiciones futurasfinalizadas = obtenerExposicionesFinalizadas(galeria->futuras, fecha);
    liberarTListaExposiciones(futurasfinalizadas, false);
    liberarTListaExposiciones(futurasNuevas, false); 
}

void imprimirExposicionesFinalizadasTGaleria(TGaleria galeria){
    imprimirTListaExposiciones(galeria->finalizada);
}

void imprimirExposicionesActivasTGaleria(TGaleria galeria){
    imprimirTListaExposiciones(galeria->activas);
}

void imprimirExposicionesFuturasTGaleria(TGaleria galeria){
    imprimirTListaExposiciones(galeria->futuras);
}

bool esCompatibleExposicionTGaleria(TGaleria galeria, TExposicion expo){
    return esCompatibleTListaExposiciones(galeria->futuras, expo) && esCompatibleTListaExposiciones(galeria->activas, expo) && esCompatibleTListaExposiciones(galeria->finalizada, expo);
}

void liberarTGaleria(TGaleria &galeria){
    liberarColeccionPiezas(galeria->pieza);
    liberarTListaExposiciones(galeria->finalizada, true);
    liberarTListaExposiciones(galeria->activas, true);
    liberarTListaExposiciones(galeria->futuras, true);
    liberarTFecha(galeria->fecha);
    delete galeria;
    galeria = NULL;
}
