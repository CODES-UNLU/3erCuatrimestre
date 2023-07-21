#include "listas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const int TAMANIO_MAXIMO = 100;
static const int NULO = -1;

struct Nodo
{
    TipoElemento datos;
    int siguiente;
};

struct ListaRep
{
    struct Nodo *cursor;
    int inicio;
    int libre;
    int cantidad;
};

struct IteradorRep
{
    Lista lista;
    int posicionActual;
};

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
// Rutinas del TAD de Lista
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

Lista l_crear()
{
    int i = 0;
    Lista nueva_lista = (Lista)malloc(sizeof(struct ListaRep));
    nueva_lista->cursor = calloc(TAMANIO_MAXIMO, sizeof(struct Nodo));
    nueva_lista->cantidad = 0;
    nueva_lista->inicio = NULO;

    for (i = 0; i <= (TAMANIO_MAXIMO - 2); i++)
    {
        nueva_lista->cursor[i].siguiente = i + 1;
    }
    nueva_lista->libre = 0;
    nueva_lista->cursor[TAMANIO_MAXIMO - 1].siguiente = NULO;
    nueva_lista->inicio = NULO;

    return nueva_lista;
}

bool l_es_vacia(Lista lista)
{
    return (lista->cantidad == 0);
}

bool l_es_llena(Lista lista)
{
    return (lista->cantidad == TAMANIO_MAXIMO);
}

int l_longitud(Lista lista)
{
    return lista->cantidad;
}

void l_agregar(Lista lista, TipoElemento elemento)
{
    int p;
    int q, anteq;
    p = lista->libre;
    lista->libre = lista->cursor[p].siguiente;
    lista->cursor[p].datos = elemento;
    lista->cursor[p].siguiente = NULO;
    if (l_es_vacia(lista))
    {
        lista->inicio = p;
    }
    else
    {

        q = lista->inicio;
        while (q != NULO)
        {
            anteq = q;
            q = lista->cursor[q].siguiente;
        }
        lista->cursor[anteq].siguiente = p;
    }
    lista->cantidad++;
}

void l_borrar(Lista lista, int clave)
{
    if (l_es_vacia(lista))
    {
        return;
    }

    int q;
    int p = lista->inicio;
    while ((p != NULO) && (lista->cursor[p].datos->clave == clave))
    {
        q = p;
        lista->inicio = lista->cursor[p].siguiente;

        lista->cursor[q].siguiente = lista->libre;
        lista->libre = q;
        lista->cantidad--;
        p = lista->inicio;
    }
    int qant;
    p = lista->inicio;
    while (p != NULO)
    {
        if (lista->cursor[p].datos->clave == clave)
        {
            q = p;
            lista->cursor[qant].siguiente = lista->cursor[p].siguiente;
            lista->cursor[q].siguiente = lista->libre;
            lista->libre = q;
            lista->cantidad--;
            p = qant;
        }
        else
        {
            qant = p;
            p = lista->cursor[p].siguiente;
        }
    }
}

TipoElemento l_buscar(Lista lista, int clave)
{
    int p = lista->inicio;
    while (p != NULO)
    {
        if (lista->cursor[p].datos->clave == clave)
        {
            return lista->cursor[p].datos;
        }
        p = lista->cursor[p].siguiente;
    }
    return NULL;
}

void l_insertar(Lista lista, TipoElemento elemento, int pos)
{
    if (pos > l_longitud(lista))
    {
        l_agregar(lista, elemento);
        return;
    }
    int p = lista->libre;
    lista->libre = lista->cursor[p].siguiente;
    lista->cursor[p].datos = elemento;
    lista->cursor[p].siguiente = NULO;
    if (pos == 1)
    {
        lista->cursor[p].siguiente = lista->inicio;
        lista->inicio = p;
    }
    else
    {
        int temp2 = lista->inicio;
        for (int i = 0; i < pos - 2; i++)
        {
            temp2 = lista->cursor[temp2].siguiente;
        }
        lista->cursor[p].siguiente = lista->cursor[temp2].siguiente;
        lista->cursor[temp2].siguiente = p;
    }
    lista->cantidad++;
}

void l_eliminar(Lista lista, int pos)
{
    int p;
    int actual = lista->inicio;

    if (1 <= pos && pos <= l_longitud(lista))
    {
        if (pos == 1)
        {
            p = actual;
            lista->inicio = lista->cursor[actual].siguiente;
            lista->cursor[p].siguiente = lista->libre;
            lista->libre = p;
        }
        else
        {
            for (int i = 0; i < pos - 2; i++)
            {
                actual = lista->cursor[actual].siguiente;
            }
            // actual apunta al nodo en posición (pos - 1)
            p = lista->cursor[actual].siguiente;                          // nodo en pos
            lista->cursor[actual].siguiente = lista->cursor[p].siguiente; // nodo en pos + 1
            lista->cursor[lista->libre].siguiente = p;
            lista->libre = p;
        }
        lista->cantidad--;
    }
}

TipoElemento l_recuperar(Lista lista, int pos)
{
    int temp2 = lista->inicio;
    for (int i = 0; i < pos - 1; i++)
    {
        temp2 = lista->cursor[temp2].siguiente;
    }
    return lista->cursor[temp2].datos;
}

void l_mostrar(Lista lista)
{
    int temp2 = lista->inicio;
    printf("Contenido de la lista: ");
    while (temp2 != NULO)
    {
        printf("%d ", lista->cursor[temp2].datos->clave);
        temp2 = lista->cursor[temp2].siguiente;
    }
    printf("\n");
}

char *l_to_string(Lista lista)
{
    char *resultado = (char *)malloc(sizeof(char) * (lista->cantidad * 10 + 3));
    strcpy(resultado, "[");
    int temp = lista->inicio;
    int i = 0;
    while (temp != NULO)
    {
        char num_str[10];
        sprintf(num_str, "%d", lista->cursor[temp].datos->clave);
        strcat(resultado, num_str);
        if (i < (lista->cantidad - 1))
        {
            strcat(resultado, ", ");
        }
        temp = lista->cursor[temp].siguiente;
        i++;
    }
    strcat(resultado, "]");

    return resultado;
}

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
// Rutinas del ITERADOR
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------

Iterador iterador(Lista lista)
{
    Iterador iter = (Iterador)malloc(sizeof(struct IteradorRep));
    iter->lista = lista;
    iter->posicionActual = lista->inicio;
    return iter;
}

bool hay_siguiente(Iterador iterador)
{
    return (iterador->posicionActual != NULO);
}

TipoElemento siguiente(Iterador iterador)
{
    TipoElemento actual = iterador->lista->cursor[iterador->posicionActual].datos;
    iterador->posicionActual = iterador->lista->cursor[iterador->posicionActual].siguiente;
    return actual;
}
