#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "pilas.h"

static const int TAMANIO_MAXIMO = 100;
struct Nodo {
    TipoElemento datos;
    struct Nodo *siguiente;
};

struct PilaRep {
    struct Nodo *tope;
};

Pila p_crear() {
    Pila nueva_pila = (Pila) malloc(sizeof(struct PilaRep));
    nueva_pila->tope = NULL;
    return nueva_pila;
}

int longitud(Pila pila) {
    int i = 0;
    struct Nodo *nodo = pila->tope;
    while (nodo != NULL) {
        i++;
        nodo = nodo->siguiente;
    }
    return i;
}

bool p_es_llena(Pila pila) {
    return (longitud(pila) == TAMANIO_MAXIMO);
}
void p_apilar(Pila pila, TipoElemento elemento) {
    struct Nodo *nuevo_nodo = malloc(sizeof(struct Nodo));
    nuevo_nodo->datos = elemento;
    nuevo_nodo->siguiente = pila->tope;
    pila->tope = nuevo_nodo;
}

TipoElemento p_desapilar(Pila pila) {
    if (p_es_vacia(pila))
    {
        return NULL;
    }
    struct Nodo *tope_actual = pila->tope;
    TipoElemento elemento = tope_actual->datos;
    pila->tope = tope_actual->siguiente;
    free(tope_actual);

    return elemento;
}

TipoElemento p_tope(Pila pila) {
    if (p_es_vacia(pila))
    {
        return NULL;
    }
    struct Nodo *tope_actual = pila->tope;
    return tope_actual->datos;
}

bool p_es_vacia(Pila pila) {
    return pila->tope == NULL;
}

//-----------------------------------------------------------
// Rutina interna que calcula los elementos de la pila
//-----------------------------------------------------------


void p_mostrar(Pila pila) {
    if (p_es_vacia(pila))
    {
        printf("PILA VACIA !!! \n");
        return;
    }
    
    Pila Paux = p_crear();
    TipoElemento X = te_crear(0);

    printf("Contenido de la pila: ");

    //Recorro la pila desapilandola y pasandola al auxiliar
    while (p_es_vacia(pila) != true)
    {
        X = p_desapilar(pila);
        printf("%d ", X->clave);
        p_apilar(Paux, X);
    }
    
    //Recorro la pila auxiliar para pasarla a la original
    while (p_es_vacia(Paux) != true)
    {
        X = p_desapilar(Paux);
        p_apilar(pila, X);
    }
    
    printf("\n");
}

char *p_to_string(Pila pila) {
    int cantidad = longitud(pila);

    char *resultado = (char *) malloc(sizeof(char) * (cantidad * 10 + 3));
    strcpy(resultado, "[");
    struct Nodo *temp = pila->tope;
    int i = 0;
    while (temp != NULL) {
        char num_str[10];
        sprintf(num_str, "%d", temp->datos->clave);
        strcat(resultado, num_str);
        if (i < (cantidad - 1)) {
            strcat(resultado, ", ");
        }
        temp = temp->siguiente;
        i++;
    }
    strcat(resultado, "]");

    return resultado;
}