#include "../include/grupoABB.h"

struct rep_grupoABB {
    TVisitante visitante;
    TGrupoABB izq;
    TGrupoABB der;
};

TGrupoABB crearTGrupoABBVacio(){
    TGrupoABB nuevogrupo = NULL;
    
    return nuevogrupo;
}

void insertarTVisitanteTGrupoABB(TGrupoABB &grupoABB, TVisitante visitante){
    if (grupoABB == NULL){
        grupoABB = new rep_grupoABB;
        grupoABB->visitante = visitante;
        grupoABB->izq = NULL;
        grupoABB->der = NULL;
    } else if (idTVisitante(grupoABB->visitante) > idTVisitante(visitante)){
        insertarTVisitanteTGrupoABB(grupoABB->izq, visitante); 
    } else if (idTVisitante(grupoABB->visitante) < idTVisitante(visitante)){
        insertarTVisitanteTGrupoABB(grupoABB->der, visitante);
    }
}

void imprimirTGrupoABB(TGrupoABB grupoABB){
    if (grupoABB != NULL){
        imprimirTGrupoABB(grupoABB->izq);
        imprimirTVisitante(grupoABB->visitante);
        imprimirTGrupoABB(grupoABB->der);
    }   
}

bool existeTVisitanteTGrupoABB(TGrupoABB grupoABB, int idVisitante){
    while ((grupoABB != NULL) && (idTVisitante(grupoABB->visitante) != idVisitante)){
        if (idTVisitante(grupoABB->visitante) > idVisitante){
            grupoABB = grupoABB->izq;
        } else {
            grupoABB = grupoABB->der;
        }
    }
    return grupoABB != NULL;
}

TVisitante obtenerTVisitanteTGrupoABB(TGrupoABB grupoABB, int idVisitante){
    while ((grupoABB != NULL) && (idTVisitante(grupoABB->visitante) != idVisitante)){
        if (idTVisitante(grupoABB->visitante) > idVisitante){
            grupoABB = grupoABB->izq;
        } else {
            grupoABB = grupoABB->der;
        }
    }
    return grupoABB->visitante;
}

void removerTVisitanteTGrupoABB(TGrupoABB &grupoABB, int idVisitante){
    if (grupoABB != NULL) {
        if (idTVisitante(grupoABB->visitante) > idVisitante){
            removerTVisitanteTGrupoABB(grupoABB->izq, idVisitante);
        } else if (idTVisitante(grupoABB->visitante) < idVisitante){
            removerTVisitanteTGrupoABB(grupoABB->der, idVisitante);
        } else {
            if (grupoABB->der == NULL){
                TGrupoABB eliminar = grupoABB;
                grupoABB = grupoABB->izq;
                liberarTVisitante(eliminar->visitante);
                delete eliminar;
            } else if (grupoABB->izq == NULL){
                TGrupoABB eliminar = grupoABB;
                grupoABB = grupoABB->der;
                liberarTVisitante(eliminar->visitante);
                delete eliminar;
            } else {
                liberarTVisitante(grupoABB->visitante);
                grupoABB->visitante = copiarTVisitante(maxIdTVisitanteTGrupoABB(grupoABB->izq));
                removerTVisitanteTGrupoABB(grupoABB->izq, idTVisitante(grupoABB->visitante));
            }
        }
    }
}

nat alturaTGrupoABB(TGrupoABB grupoABB){
    if (grupoABB == NULL){
        return 0;
    } else {
        nat izquierdo = alturaTGrupoABB(grupoABB->izq);
        nat derecho = alturaTGrupoABB(grupoABB->der);
        if (izquierdo < derecho){
            return 1 + derecho;
        } else {
            return 1 + izquierdo;
        }
    }
}

int cantidadVisitantesTGrupoABB(TGrupoABB grupoABB){
    if (grupoABB == NULL){
        return 0;
    } else {
        return 1 + cantidadVisitantesTGrupoABB(grupoABB->izq) + cantidadVisitantesTGrupoABB(grupoABB->der);
    }
}

float edadPromedioTGrupoABB(TGrupoABB grupoABB) {
    if (grupoABB == NULL) {
        return 0;
    } else {
        float edades = edadTVisitante(grupoABB->visitante);
        float cantvisitante = 1;

        edades += edadPromedioTGrupoABB(grupoABB->izq) * cantidadVisitantesTGrupoABB(grupoABB->izq);
        cantvisitante += cantidadVisitantesTGrupoABB(grupoABB->izq);

        edades += edadPromedioTGrupoABB(grupoABB->der) * cantidadVisitantesTGrupoABB(grupoABB->der);
        cantvisitante += cantidadVisitantesTGrupoABB(grupoABB->der);

        return (edades / cantvisitante);
    }
}

void liberarTGrupoABB(TGrupoABB &grupoABB){
    if (grupoABB != NULL){
        liberarTGrupoABB(grupoABB->izq);
        liberarTGrupoABB(grupoABB->der);
        liberarTVisitante(grupoABB->visitante);
        delete grupoABB;
        grupoABB = NULL;
    }
}

TVisitante maxIdTVisitanteTGrupoABB(TGrupoABB grupoABB){
    while (grupoABB->der != NULL){
        grupoABB = grupoABB->der;
    }
    return grupoABB->visitante;
}

TVisitante obtenerNesimoVisitanteTGrupoABB(TGrupoABB grupoABB, int n){
    int contador = 0;
    return obtenerNesimoVisitantesTGrupoABB(grupoABB, n, contador);
}

TVisitante obtenerNesimoVisitantesTGrupoABB(TGrupoABB grupoABB, int n, int& contador) {
    if (grupoABB == NULL) {
        return NULL; 
    }   
    TVisitante encontrado = obtenerNesimoVisitantesTGrupoABB(grupoABB->izq, n, contador);
    if (encontrado != NULL) {
        return encontrado; 
    }   
    contador++;
    if (contador == n) {
        return grupoABB->visitante; 
    }    
    return obtenerNesimoVisitantesTGrupoABB(grupoABB->der, n, contador);
}