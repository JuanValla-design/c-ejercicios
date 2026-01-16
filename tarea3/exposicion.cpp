#include "../include/exposicion.h"

struct rep_exposicion {
    int id;
    TConjuntoPiezas conjunto;
    TFecha ini;
    TFecha fin;
    int max;
};

TExposicion crearTExposicion(int idExp, TFecha ini, TFecha fin, int cantMax){
    TExposicion nuevo = new rep_exposicion;
    
    nuevo->max = cantMax;
    nuevo->id = idExp;
    nuevo->ini = ini;
    nuevo->fin = fin;
    nuevo->conjunto = crearTConjuntoPiezas(cantMax); 
    
    return nuevo; 
}

void agregarATExposicion(TExposicion &exp, TPieza p){
    insertarTConjuntoPiezas(exp->conjunto, idTPieza(p));
}

bool perteneceATExposicion(TExposicion exp, TPieza p){ 
    return perteneceTConjuntoPiezas(exp->conjunto, idTPieza(p)); 
}

int idTExposicion(TExposicion exp){ 
    return exp->id; 
}

void imprimirTExposicion(TExposicion exp){
    printf("Exposicion #%d del ", exp->id);
    imprimirTFecha(exp->ini);
    printf(" al ");
    imprimirTFecha(exp->fin);
    printf("\nPiezas: ");
    imprimirTConjuntoPiezas(exp->conjunto);
}

TFecha fechaInicioTExposicion(TExposicion exp){ 
    return exp->ini;
}

TFecha fechaFinTExposicion(TExposicion exp){ 
    return exp->fin; 
}

bool sonExposicionesCompatibles(TExposicion exp1, TExposicion exp2){
    if (exp1 == NULL || exp2 == NULL){
        return true;
    }
    if (compararTFechas(exp1->fin, exp2->ini) == -1 || compararTFechas(exp1->ini, exp2->fin) == 1){
        return true;
    } else {
        TConjuntoPiezas aux = interseccionTConjuntoPiezas(exp1->conjunto, exp2->conjunto);
        if (cardinalTConjuntoPiezas(aux) == 0){
            liberarTConjuntoPiezas(aux);
            return true;
        } else {
            liberarTConjuntoPiezas(aux);
            return false;
        }
    }
}

void liberarTExposicion(TExposicion &exp){
    liberarTFecha(exp->ini);
    liberarTFecha(exp->fin);
    liberarTConjuntoPiezas(exp->conjunto);
    delete exp;
    exp = NULL;
}

