#include "../include/coleccionPiezas.h"

struct rep_coleccionpiezas{
    TPieza pieza;
    TColeccionPiezas sig;
};

TColeccionPiezas crearColeccionPiezasVacia(){ 
    TColeccionPiezas nuevaColeccionPieza = NULL;

    return nuevaColeccionPieza; 
}

void insertarPiezaColeccionPiezas(TColeccionPiezas &coleccionPiezas, TPieza pieza) {
    TColeccionPiezas nuevoNodo = new rep_coleccionpiezas;
    nuevoNodo->pieza = pieza;
    nuevoNodo->sig = NULL;

    TColeccionPiezas actualcol = coleccionPiezas;
    TColeccionPiezas anterior = NULL;

    while (actualcol != NULL && idTPieza(actualcol->pieza) <= idTPieza(pieza)) {
        anterior = actualcol;
        actualcol = actualcol->sig;
    }

    if (anterior == NULL) {
        nuevoNodo->sig = coleccionPiezas;
        coleccionPiezas = nuevoNodo;
    } else {
        anterior->sig = nuevoNodo;
        nuevoNodo->sig = actualcol;
    }
}

void imprimirColeccionPiezas(TColeccionPiezas coleccionPiezas){
    while (coleccionPiezas != NULL){
        imprimirTPieza(coleccionPiezas->pieza);
        coleccionPiezas = coleccionPiezas->sig;
    }  
}

bool esVaciaColeccionPiezas(TColeccionPiezas piezas){
    return piezas == NULL;
}

bool existePiezaColeccionPiezas(TColeccionPiezas coleccionPiezas, int idPieza){
    while (coleccionPiezas != NULL && idTPieza(coleccionPiezas->pieza) != idPieza){
        coleccionPiezas = coleccionPiezas->sig;
    }
    return coleccionPiezas != NULL;
}

TPieza obtenerPiezaColeccionPiezas(TColeccionPiezas coleccionPiezas, int idPieza){
    while (idTPieza(coleccionPiezas->pieza) != idPieza){
        coleccionPiezas = coleccionPiezas->sig;
    }
    return coleccionPiezas->pieza;
}

void removerPiezaColeccionPiezas(TColeccionPiezas &coleccionPiezas, int idPieza){
    TColeccionPiezas coleccionactu = coleccionPiezas;
    TColeccionPiezas coleccionante = NULL;
    while (coleccionactu != NULL && idTPieza(coleccionactu->pieza) != idPieza){
        coleccionante = coleccionactu;
        coleccionactu = coleccionactu->sig;
    }
    if (coleccionante == NULL) {
        coleccionPiezas = coleccionactu->sig;
    } else {
        coleccionante->sig = coleccionactu->sig;
    }
    liberarTPieza(coleccionactu->pieza);
    delete coleccionactu;
}

void liberarColeccionPiezas(TColeccionPiezas &coleccionPiezas){
        while(coleccionPiezas != NULL){
            TColeccionPiezas coleccionEliminar = coleccionPiezas;
            coleccionPiezas = coleccionPiezas->sig;
            liberarTPieza(coleccionEliminar->pieza);
            delete coleccionEliminar;
        }
}