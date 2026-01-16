#include "../include/visitante.h"

struct rep_visitante {
    int id;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    int edad;
};

TVisitante crearTVisitante(int id, const char nombre[MAX_NOMBRE], const char apellido[MAX_APELLIDO], int edad){
    TVisitante crearVisita = NULL;
    
    crearVisita = new rep_visitante;
    crearVisita->id = id;
    strcpy(crearVisita->nombre, nombre);
    strcpy(crearVisita->apellido, apellido);
    crearVisita->edad = edad;
    
    return crearVisita; 
}

void nombreTVisitante(TVisitante visitante, char nombre[MAX_NOMBRE]){
    strcpy(nombre, visitante->nombre);
}

void apellidoTVisitante(TVisitante visitante, char apellido[MAX_APELLIDO]){
    strcpy(apellido, visitante->apellido);
}

int idTVisitante(TVisitante visitante){
    return visitante->id;
}

int edadTVisitante(TVisitante visitante){
    return visitante->edad;
}

void liberarTVisitante(TVisitante &visitante){
    if (visitante != NULL){
        delete visitante;
        visitante = NULL;
    }
}

TVisitante copiarTVisitante(TVisitante visitante){
    TVisitante Visita = NULL;
    
    Visita = new rep_visitante;
    Visita->id = visitante->id;
    strcpy(Visita->nombre, visitante->nombre);
    strcpy(Visita->apellido, visitante->apellido);
    Visita->edad = visitante->edad;
    
    return Visita;
}

void imprimirTVisitante(TVisitante visitante){
    printf("Visitante %s %s\n", visitante->nombre, visitante->apellido);
    printf("Id: %d\n", visitante->id);
    printf("Edad: %d\n", visitante->edad);
}