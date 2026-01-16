#include "../include/conjuntoPiezas.h"

struct rep_conjuntopiezas{
    int max;
    int cant;
    int* conjunto;
};

TConjuntoPiezas crearTConjuntoPiezas(int cantMax){
    TConjuntoPiezas nuevo = new rep_conjuntopiezas;
    nuevo->max = cantMax;
    nuevo->cant = 0;
    nuevo->conjunto = new int[cantMax];
    
    for (int i = 0; cantMax > i; i++){
        nuevo->conjunto[i] = -1;
    }
    return nuevo; 
}

bool esVacioTConjuntoPiezas(TConjuntoPiezas c){ 
    return c->cant == 0; 
}

void insertarTConjuntoPiezas(TConjuntoPiezas &c, int id){
    if ( id >= 0 && c->max > id && !perteneceTConjuntoPiezas(c, id)){
        c->conjunto[id] = id;
        c->cant ++;
    }
}

void borrarDeTConjuntoPiezas(TConjuntoPiezas &c, int id){
    if(perteneceTConjuntoPiezas(c, id)){
        c->conjunto[id] = -1;
        c->cant --;
    }
}

bool perteneceTConjuntoPiezas(TConjuntoPiezas c, int id){
    if(id >= 0 && c->max > id){
        return c->conjunto[id] == id;
    } else {
        return false;
    }
}

int cardinalTConjuntoPiezas(TConjuntoPiezas c){ 
    return c->cant; 
}

int cantMaxTConjuntoPiezas(TConjuntoPiezas c){ 
    return c->max; 
}

void imprimirTConjuntoPiezas(TConjuntoPiezas c){
    for (int i = 0; c->max > i; i++){
        if (c->conjunto[i] > -1){
            printf("%d ", c->conjunto[i]);
        }
    }
    printf("\n");
}

void liberarTConjuntoPiezas(TConjuntoPiezas &c){
    delete[] c->conjunto;
    delete c;
    c = NULL;
}

TConjuntoPiezas unionTConjuntoPiezas(TConjuntoPiezas c1, TConjuntoPiezas c2){
    TConjuntoPiezas aux = crearTConjuntoPiezas(c1->max + c2->max);

    for (int i = 0; i < c1->max; i++) {
        insertarTConjuntoPiezas(aux, c1->conjunto[i]);
    }

    for (int i = 0; i < c2->max; i++) {
        if (!perteneceTConjuntoPiezas(aux, c2->conjunto[i])) {
            insertarTConjuntoPiezas(aux, c2->conjunto[i]);
        }
    }

    return aux;
}

TConjuntoPiezas interseccionTConjuntoPiezas(TConjuntoPiezas c1, TConjuntoPiezas c2){
  TConjuntoPiezas aux = crearTConjuntoPiezas(c1->max);

    for (int i = 0; i < c1->max; i++) {
        int elementoActual = c1->conjunto[i];
        if (perteneceTConjuntoPiezas(c2, elementoActual)) {
            insertarTConjuntoPiezas(aux, elementoActual);
        }
    }

    return aux;
}
TConjuntoPiezas diferenciaTConjuntoPiezas(TConjuntoPiezas c1, TConjuntoPiezas c2){
    TConjuntoPiezas aux = crearTConjuntoPiezas(c1->max);

    for (int i = 0; i < c1->max; i++) {
        int elementoActual = c1->conjunto[i];
        if (!perteneceTConjuntoPiezas(c2, elementoActual)) {
            insertarTConjuntoPiezas(aux, elementoActual);
        }
    }

    return aux;
}