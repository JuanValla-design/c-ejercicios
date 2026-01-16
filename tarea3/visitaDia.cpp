#include "../include/visitaDia.h"
struct lista {
    TGrupoABB grupo;
    lista* sig;
    lista* ant;
};

struct rep_visitadia {
    TFecha fecha;
    int cant;
    lista* fin;
    lista* ini;
};

TVisitaDia crearTVisitaDia(TFecha fecha){
    TVisitaDia nuevo = new rep_visitadia;

    nuevo->fecha = fecha;
    nuevo->cant = 0;
    nuevo->fin = NULL;
    nuevo->ini = NULL;

    return nuevo; 
}

void encolarGrupoTVisitaDia(TVisitaDia &visitaDia, TGrupoABB grupo){
    lista* aux = new lista;
    aux->grupo = grupo;
    aux->sig = NULL;
    aux->ant = NULL;

    if (visitaDia->fin == NULL){
        visitaDia->fin = aux;
        visitaDia->ini = aux;
    } else {
        aux->sig = visitaDia->ini;
        visitaDia->ini->ant = aux;
        visitaDia->ini = aux;
    }
    visitaDia->cant ++;
}

int cantidadGruposTVisitaDia(TVisitaDia visitaDia){ 
    return visitaDia->cant; 
}

void imprimirVisitaDia(TVisitaDia visitaDia){
    printf("Visita para dia: ");
    imprimirTFecha(visitaDia->fecha);
    printf("\n");
    lista* aux = visitaDia->ini;
    while (aux != NULL){
        imprimirTGrupoABB(aux->grupo);
        aux = aux->sig;
    }
}

TGrupoABB desencolarGrupoTVisitaDia(TVisitaDia &visitaDia){
    if (visitaDia == NULL){
        return NULL;
    }

    TGrupoABB grupo = visitaDia->fin->grupo;
    lista* aux = visitaDia->fin;
    visitaDia->fin = visitaDia->fin->ant;
    if (visitaDia->fin == NULL){
        visitaDia->ini = NULL;
    } else {
        visitaDia->fin->sig = NULL;
    }

    delete aux;
    return grupo; 
}

void liberarTVisitaDia(TVisitaDia &visitaDia){
    while (visitaDia->ini != NULL){
        lista* aBorrar = visitaDia->ini;
        visitaDia->ini = visitaDia->ini->sig;
        liberarTGrupoABB(aBorrar->grupo);
        delete aBorrar;
    }
    visitaDia->fin = NULL;
    liberarTFecha(visitaDia->fecha);
    delete visitaDia;
    visitaDia = NULL;
}

