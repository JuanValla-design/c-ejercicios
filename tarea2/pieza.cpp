#include "../include/pieza.h"

struct rep_pieza {
    nat id;
    char nombrePieza[MAX_NOMBRE_PIEZA];
    char nombreAutor[MAX_NOMBRE_AUTOR];
    char apellidoAutor[MAX_APELLIDO_AUTOR];
    TFecha fecha;
};

TPieza crearTPieza(int identificador, const char nombrePieza[MAX_NOMBRE_PIEZA], const char nombreAutor[MAX_NOMBRE_AUTOR], const char apellidoAutor[MAX_APELLIDO_AUTOR], TFecha fechaCreacion){
    TPieza nuevaPieza = NULL;

    nuevaPieza = new rep_pieza;
    nuevaPieza->id = identificador;
    strcpy(nuevaPieza->nombrePieza, nombrePieza);
    strcpy(nuevaPieza->nombreAutor, nombreAutor);
    strcpy(nuevaPieza->apellidoAutor, apellidoAutor);
    nuevaPieza->fecha = fechaCreacion;

    return nuevaPieza;
}

int idTPieza(TPieza pieza){ 
    return pieza->id;
}

void imprimirTPieza(TPieza pieza){
    printf ("Pieza: %d\n", pieza->id);
    printf ("%s-%s %s\n", pieza->nombrePieza, pieza->nombreAutor, pieza->apellidoAutor);
    printf ("Creada en: ");
    imprimirTFecha(pieza->fecha);
}

void liberarTPieza(TPieza &pieza){
    liberarTFecha(pieza->fecha); 
    delete pieza;
    pieza = NULL;
}