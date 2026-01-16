#include "../include/listaExposiciones.h"

struct rep_listaexposiciones{
    TExposicion exposi;
    TListaExposiciones sig;
};

TListaExposiciones crearTListaExposicionesVacia(){
    return NULL; 
}

void agregarExposicionTListaExposiciones(TListaExposiciones &listaExposiciones, TExposicion expo) {
    TListaExposiciones nuevoNodo = new rep_listaexposiciones;
    nuevoNodo->exposi = expo;
    nuevoNodo->sig = NULL;

    if (esVaciaTListaExposiciones(listaExposiciones) || compararTFechas(fechaInicioTExposicion(expo), fechaInicioTExposicion(listaExposiciones->exposi)) == -1) {      
        nuevoNodo->sig = listaExposiciones;
        listaExposiciones = nuevoNodo;
    } else {
        TListaExposiciones actual = listaExposiciones;
        while (actual->sig != NULL && compararTFechas(fechaInicioTExposicion(expo), fechaInicioTExposicion(actual->sig->exposi)) != -1) {
            actual = actual->sig;
        }
        nuevoNodo->sig = actual->sig;
        actual->sig = nuevoNodo;
    }
}

bool perteneceExposicionTListaExposiciones(TListaExposiciones listaExposiciones, int idExpo){
    if (listaExposiciones == NULL){
        return false;
    } else {
        TListaExposiciones aux = listaExposiciones;
        while (aux != NULL && idTExposicion(aux->exposi) != idExpo){
            aux = aux->sig;
        }
        return aux != NULL;
    }
}

TExposicion obtenerExposicionTListaExposiciones(TListaExposiciones listaExposiciones, int idExpo){ 
    TListaExposiciones aux = listaExposiciones;
    while (idTExposicion(aux->exposi) != idExpo){
        aux = aux->sig;
    }
    return aux->exposi; 
}

bool esVaciaTListaExposiciones(TListaExposiciones listaExposiciones){ 
    return listaExposiciones == NULL; 
}

void imprimirTListaExposiciones(TListaExposiciones listaExposiciones){
    TListaExposiciones aux = listaExposiciones;
    while (aux != NULL){
        imprimirTExposicion(aux->exposi);
        aux = aux->sig;
    }
}

void liberarTListaExposiciones(TListaExposiciones &listaExposiciones, bool liberarExposiciones) {
    while (listaExposiciones != NULL) {
        TListaExposiciones borrar = listaExposiciones;
        listaExposiciones = listaExposiciones->sig;
        if (liberarExposiciones) {
            liberarTExposicion(borrar->exposi);
        }
        delete borrar;
    }
}

void agregarAlFinal(TListaExposiciones &lista, TExposicion expo) {
    TListaExposiciones nuevoNodo = new rep_listaexposiciones;
    nuevoNodo->exposi = expo;
    nuevoNodo->sig = NULL;

    if (lista == NULL) {
        lista = nuevoNodo;
    } else {
        TListaExposiciones ultimo = lista;
        while (ultimo->sig != NULL) {
            ultimo = ultimo->sig;
        }
        ultimo->sig = nuevoNodo;
    }
}

TListaExposiciones obtenerExposicionesFinalizadas(TListaExposiciones &listaExposiciones, TFecha fecha) {
    TListaExposiciones finalizada = crearTListaExposicionesVacia();
    TListaExposiciones aux = listaExposiciones;
    TListaExposiciones ante = NULL;

    while (aux != NULL) {
        if (aux->exposi != NULL && compararTFechas(fechaFinTExposicion(aux->exposi), fecha) == -1) {
            TListaExposiciones aBorrar = aux;
            if (ante == NULL) { 
                listaExposiciones = aux->sig;
            } else {
                ante->sig = aux->sig;
            }
            aux = aux->sig;

            agregarAlFinal(finalizada, aBorrar->exposi);
            delete aBorrar;
        } else {
            ante = aux;
            aux = aux->sig;
        }
    }

    return finalizada;
}             

TListaExposiciones obtenerExposicionesActivas(TListaExposiciones &listaExposiciones, TFecha fecha){
    TListaExposiciones activas = crearTListaExposicionesVacia();
    TListaExposiciones aux = listaExposiciones;
    TListaExposiciones ante = NULL;

    while (aux != NULL) {
        if (aux->exposi != NULL && compararTFechas(fechaFinTExposicion(aux->exposi), fecha) != -1 && compararTFechas(fechaInicioTExposicion(aux->exposi), fecha) != 1) {
            TListaExposiciones aBorrar = aux;
            if (ante == NULL) { 
                listaExposiciones = aux->sig;
            } else {
                ante->sig = aux->sig;
            }
            aux = aux->sig;

            agregarAlFinal(activas, aBorrar->exposi);
            delete aBorrar;
        } else {
            ante = aux;
            aux = aux->sig;
        }
    }

    return activas;
} 

bool esCompatibleTListaExposiciones(TListaExposiciones listaExposiciones, TExposicion expo){ 
    TListaExposiciones iter = listaExposiciones;
    while (iter != NULL && sonExposicionesCompatibles(iter->exposi, expo)){
        iter = iter->sig;
    }
    return iter == NULL; 
}

TListaExposiciones unirListaExposiciones(TListaExposiciones listaExpo1, TListaExposiciones listaExpo2) {
    TListaExposiciones unidad = crearTListaExposicionesVacia();

    while (listaExpo1 != NULL && listaExpo2 != NULL) {
        TListaExposiciones nuevoNodo = new rep_listaexposiciones;
        if (compararTFechas(fechaInicioTExposicion(listaExpo1->exposi), fechaInicioTExposicion(listaExpo2->exposi)) == -1) {
            nuevoNodo->exposi = listaExpo1->exposi;
            listaExpo1 = listaExpo1->sig;
        } else if (compararTFechas(fechaInicioTExposicion(listaExpo1->exposi), fechaInicioTExposicion(listaExpo2->exposi)) == 1) {
            nuevoNodo->exposi = listaExpo2->exposi;
            listaExpo2 = listaExpo2->sig;
        } else if (idTExposicion(listaExpo1->exposi) != idTExposicion(listaExpo2->exposi)){
            nuevoNodo->exposi = listaExpo1->exposi;
            listaExpo1 = listaExpo1->sig;
        } else {
            nuevoNodo->exposi = listaExpo1->exposi;
            listaExpo1 = listaExpo1->sig;
            listaExpo2 = listaExpo2->sig;
        }
        nuevoNodo->sig = NULL;

        agregarAlFinal(unidad, nuevoNodo->exposi);
        delete nuevoNodo;
    }
    while (listaExpo1 != NULL){
        agregarAlFinal(unidad, listaExpo1->exposi);
        listaExpo1 = listaExpo1->sig;
    }

    while (listaExpo2 != NULL){
        agregarAlFinal(unidad, listaExpo2->exposi);
        listaExpo2 = listaExpo2->sig;
    }
    
    return unidad; 
}



