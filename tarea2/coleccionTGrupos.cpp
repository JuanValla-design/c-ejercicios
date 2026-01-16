#include "../include/coleccionTGrupos.h"

struct cabezal {
	TGrupoABB grupo;
    cabezal* ant;
	cabezal* sig;
};

struct rep_coleccionTGrupos {
	cabezal* final;
	cabezal* inicio;
};

TColeccionTGrupos crearTColeccionTGruposVacia(){
	TColeccionTGrupos nuevaColeccion;
    
	nuevaColeccion = new rep_coleccionTGrupos;
	nuevaColeccion->final = NULL;
	nuevaColeccion->inicio = NULL;
	return nuevaColeccion;
}

void insertarGrupoTColeccionTGrupos(TColeccionTGrupos coleccion, TGrupoABB grupo){
	cabezal* colector = new cabezal;
	colector->grupo = grupo;
	colector->ant = NULL;
	colector->sig = NULL;

	if (coleccion->final == NULL){
		coleccion->inicio = colector;
		coleccion->final = colector;
		return;
	}
	cabezal* actual = coleccion->inicio; 
	while (actual != NULL && edadPromedioTGrupoABB(actual->grupo) <= edadPromedioTGrupoABB(grupo)){
		actual = actual->sig;
	}
	if (actual != NULL){
	    colector->sig = actual;
	    colector->ant = actual->ant;
	    if (actual->ant != NULL){
	        actual->ant->sig = colector;
	    } else {
		    coleccion->inicio = colector;
	    }
	    actual->ant = colector;
	} else {
		coleccion->final->sig = colector;
		colector->ant = coleccion->final;
		coleccion->final = colector;
	}
}

void imprimirTColeccionTGrupos(const TColeccionTGrupos coleccion){
    printf("Coleccion de grupos:\n");
    cabezal* actual = coleccion->inicio;
    while (actual != NULL){
        printf("Grupo con edad promedio %.2f:\n", edadPromedioTGrupoABB(actual->grupo));
        imprimirTGrupoABB(actual->grupo);
        actual = actual->sig;
    }
}

void imprimirInvertidoTColeccionTGrupos(const TColeccionTGrupos coleccion){
    printf("Coleccion de grupos:\n");
    cabezal* actual = coleccion->final;
    while (actual != NULL){
        printf("Grupo con edad promedio %.2f:\n", edadPromedioTGrupoABB(actual->grupo));
        imprimirTGrupoABB(actual->grupo);
        actual = actual->ant;
    }
}

nat cantidadTGruposColeccionTGrupos(TColeccionTGrupos coleccion){
	nat contador = 0;
	cabezal* temp = coleccion->final;
	while (temp != NULL){
		temp = temp->ant;
		contador ++;
	} 
	return contador;
}

TGrupoABB obtenerNesimoColeccionTGrupos(const TColeccionTGrupos coleccion, int n){
    int contador = 1;
    cabezal* temp = coleccion->inicio;
    while (temp != NULL && contador != n){
        contador++;
        temp = temp->sig;
    }
    if(temp != NULL){
        return temp->grupo;
    } else {
        return NULL;
    }
}

TGrupoABB obtenerPrimeroColeccionTGrupos(TColeccionTGrupos coleccion){
	return coleccion->inicio->grupo;
}

TGrupoABB removerUltimoColeccionTGrupos(TColeccionTGrupos coleccion){
	TGrupoABB grupo = coleccion->final->grupo;
	cabezal* temp = coleccion->final;
    coleccion->final = temp->ant;
    
	if (temp->ant == NULL){
        coleccion->inicio = NULL;
	} else {
		temp->ant->sig = NULL;
	} 
    
	delete temp;
	return grupo;
}

TGrupoABB removerNesimoColeccionTGrupos(TColeccionTGrupos coleccion, int n){
	int contador = 1;
    cabezal* temp = coleccion->inicio;
    while (temp != NULL && contador != n){
        contador++;
        temp = temp->sig;
    }
    
	if (temp->ant == NULL && temp->sig == NULL){
		coleccion->inicio = NULL;
		coleccion->final = NULL;
	} else if (temp->ant == NULL){
		coleccion->inicio = temp->sig;
		temp->sig->ant = NULL; 
	} else if (temp->sig == NULL){
		coleccion->final = temp->ant;
		temp->ant->sig = NULL;
	} else {
		temp->ant->sig = temp->sig;
		temp->sig->ant = temp->ant;
	}

    TGrupoABB grupo = temp->grupo;
	delete temp;
	return grupo;
}

void liberarTColeccionTGrupos(TColeccionTGrupos &coleccion) {
    cabezal* actual = coleccion->inicio;
    while (actual != NULL) {
        cabezal* siguiente = actual->sig;
        liberarTGrupoABB(actual->grupo);
        delete actual;
        actual = siguiente;
    }
    delete coleccion;
	coleccion = NULL;
}

TGrupoABB obtenerVisitantesRepetidos(TColeccionTGrupos coleccion) {
    TGrupoABB grupo = NULL;

    cabezal* temp = coleccion->inicio;
    while (temp != NULL) {
        for (int j = 1; j <= cantidadVisitantesTGrupoABB(temp->grupo); j++) {
            TVisitante actu = obtenerNesimoVisitanteTGrupoABB(temp->grupo, j);
            if (existeTVisitanteTGrupoABB(grupo, idTVisitante(actu))) {
                continue; 
            }
            int grupoaparicion = 0;
            cabezal* temp2 = coleccion->inicio;
            while (temp2 != NULL) {
                if (existeTVisitanteTGrupoABB(temp2->grupo, idTVisitante(actu))){
                    grupoaparicion ++;
                }
                temp2 = temp2->sig;
            }
             if (grupoaparicion > 1) {
                insertarTVisitanteTGrupoABB(grupo, copiarTVisitante(actu));
            }
        }
        temp = temp->sig;
    }
    return grupo;
}

TVisitante visitanteMasRepetido(TColeccionTGrupos coleccion) {
    if (coleccion->inicio == NULL) {
        return NULL; 
    }

    TVisitante visitanteMasRepetido = NULL;
    int maxRepeticiones = 0;
    cabezal* temp = coleccion->inicio;

    while (temp != NULL) {
        for (int j = 1; j <= cantidadVisitantesTGrupoABB(temp->grupo); j++) {
            TVisitante visitanteActual = obtenerNesimoVisitanteTGrupoABB(temp->grupo, j);
            int contador = 0;
            cabezal* temp2 = coleccion->inicio;
            while (temp2 != NULL) {
                for (int i = 1; i <= cantidadVisitantesTGrupoABB(temp2->grupo); i++) {
                    TVisitante otroVisitante = obtenerNesimoVisitanteTGrupoABB(temp2->grupo, i);
                    if (idTVisitante(visitanteActual) == idTVisitante(otroVisitante)) {
                        contador++;
                        break;
                    }
                }
                temp2 = temp2->sig;
            }

            if (contador > maxRepeticiones || (contador == maxRepeticiones && (visitanteMasRepetido == NULL || idTVisitante(visitanteActual) < idTVisitante(visitanteMasRepetido)))) {
                visitanteMasRepetido = visitanteActual;
                maxRepeticiones = contador;
            }
        }
        temp = temp->sig;
    }
    return visitanteMasRepetido;
}
