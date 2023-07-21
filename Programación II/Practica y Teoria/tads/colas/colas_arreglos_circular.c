#include "colas.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static const int TAMANIO_MAXIMO = 100;

struct ColaRep {
    TipoElemento *valores;
    int frente;
    int final;
};

/** Función interna que hace avanzar el frente o el final hacia adelante */
int paso(int posicion);

/** Función interna que calcula la cantidad de elementos de la cola */
int longitud(Cola cola);

/** Función interna que dice si hay lugar para almacenar más elementos o no */
bool c_es_llena(Cola cola);

//-----------------
// Rutinas internas
//-----------------
int paso(int posicion) {
    return posicion % TAMANIO_MAXIMO + 1;
}

bool c_es_llena(Cola cola) {
    return paso(paso(cola->final)) == cola->frente;
}

int longitud(Cola cola) {
    int i = 0;
    int pos = cola->frente;
    while (pos != cola->final) {
        i++;
        pos = paso(pos);
    }
    return i;
}

char *c_to_string(Cola cola) {
    char *resultado = (char *) malloc(sizeof(char) * (longitud(cola) * 10 + 3));
    strcpy(resultado, "[");
    for (int i = cola->frente; i <= cola->final; i = paso(i)) {
        char num_str[10];
        sprintf(num_str, "%d", cola->valores[i]->clave);
        strcat(resultado, num_str);
        if (i != cola->final) {
            strcat(resultado, ", ");
        }
    }
    strcat(resultado, "]");

    return resultado;
}

Cola c_crear() {
    Cola nueva_cola = (Cola) malloc(sizeof(struct ColaRep));
    nueva_cola->valores = calloc((TAMANIO_MAXIMO + 1), sizeof(TipoElemento));
    nueva_cola->frente = 1;
    nueva_cola->final = TAMANIO_MAXIMO;
    return nueva_cola;
}

void c_encolar(Cola cola, TipoElemento elemento) {
    if (c_es_llena(cola)) {
        return;
    }
    cola->final = paso(cola->final);
    cola->valores[cola->final] = elemento;
}

TipoElemento c_desencolar(Cola cola) {
    if (c_es_vacia(cola)) {
        return NULL;
    }
    TipoElemento elemento = cola->valores[cola->frente];
    cola->frente = paso(cola->frente);
    return elemento;
}

bool c_es_vacia(Cola cola) {
    return (paso(cola->final) == cola->frente);
}

void c_mostrar(Cola cola) {
    if (c_es_vacia(cola)) {
        printf("COLA VACIA !!! \n");
        return;
    }

    Cola Caux = c_crear();
    TipoElemento X = te_crear(0);

    printf("Contenido de la cola: \n\n");

    while (c_es_vacia(cola) != true) {
        X = c_desencolar(cola);
        printf("%d ", X->clave);
        c_encolar(Caux, X);
    }
    printf("\n");
    while (c_es_vacia(Caux) != true) {
        X = c_desencolar(Caux);
        c_encolar(cola, X);
    }

    printf("\n");
}

TipoElemento c_recuperar(Cola cola) {
    TipoElemento X;
    if (c_es_vacia(cola)) {
        X = NULL;
    }
    else {
        X = cola->valores[cola->frente];
    }
    return X;
}