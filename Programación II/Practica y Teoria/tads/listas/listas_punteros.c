#include "listas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const int TAMANIO_MAXIMO = 100;

struct Nodo
{
    TipoElemento datos;
    struct Nodo *siguiente;
};

struct ListaRep
{
    struct Nodo *inicio;
    int cantidad;
};

struct IteradorRep
{
    struct Nodo *posicionActual;
};

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
// Rutinas del TAD
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------

Lista l_crear()
{
    Lista nueva_lista = (Lista)malloc(sizeof(struct ListaRep));
    nueva_lista->inicio = NULL;
    nueva_lista->cantidad = 0;
    return nueva_lista;
}

bool l_es_vacia(Lista lista)
{
    return lista->cantidad == 0;
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
    if (l_es_llena(lista))
    {
        return;
    }
    struct Nodo *nuevo_nodo = malloc(sizeof(struct Nodo));
    nuevo_nodo->datos = elemento;
    nuevo_nodo->siguiente = NULL;
    if (lista->inicio == NULL)
    {
        lista->inicio = nuevo_nodo;
    }
    else
    {
        struct Nodo *temp2 = lista->inicio;
        while (temp2->siguiente != NULL)
        {
            temp2 = temp2->siguiente;
        }
        temp2->siguiente = nuevo_nodo;
    }
    lista->cantidad++;
}

void l_borrar(Lista lista, int clave)
{
    if (l_es_vacia(lista))
    {
        return;
    }
    struct Nodo *actual = lista->inicio;

    while (actual != NULL && actual->datos->clave == clave)
    {
        lista->inicio = actual->siguiente;
        free(actual);
        lista->cantidad--;
        actual = lista->inicio;
    }
    while (actual != NULL && actual->siguiente != NULL)
    {
        if (actual->siguiente->datos->clave == clave)
        {
            struct Nodo *temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            free(temp);
            lista->cantidad--;
        }
        else
        {
            actual = actual->siguiente;
        }
    }
}

TipoElemento l_buscar(Lista lista, int clave)
{
    struct Nodo *actual = lista->inicio;
    while (actual != NULL)
    {
        if (actual->datos->clave == clave)
        {
            return actual->datos;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

void l_insertar(Lista lista, TipoElemento elemento, int pos)
{
    if (l_es_llena(lista))
    {
        return;
    }
    if (pos > l_longitud(lista))
    {
        l_agregar(lista, elemento);
        return;
    }
    struct Nodo *nuevo_nodo = malloc(sizeof(struct Nodo));
    nuevo_nodo->datos = elemento;
    nuevo_nodo->siguiente = NULL;

    if (pos == 1)
    {
        nuevo_nodo->siguiente = lista->inicio;
        lista->inicio = nuevo_nodo;
    }
    else
    {
        struct Nodo *temp2 = lista->inicio;
        for (int i = 0; i < pos - 2; i++)
        {
            temp2 = temp2->siguiente;
        }
        nuevo_nodo->siguiente = temp2->siguiente;
        temp2->siguiente = nuevo_nodo;
    }
    lista->cantidad++;
}

void l_eliminar(Lista lista, int pos)
{
    if (l_es_vacia(lista))
    {
        return;
    }

    struct Nodo *actual = lista->inicio;
    if (1 <= pos && pos <= l_longitud(lista))
    {
        if (pos == 1)
        {
            lista->inicio = actual->siguiente;
            free(actual);
        }
        else
        {
            for (int i = 0; i < pos - 2; i++)
            {
                actual = actual->siguiente;
            }
            struct Nodo *temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            free(temp);
        }
        lista->cantidad--;
    }
}

TipoElemento l_recuperar(Lista lista, int pos)
{
    if (pos > l_longitud(lista))
    {
        return NULL;
    }
    struct Nodo *temp2 = lista->inicio;
    for (int i = 0; i < pos - 1; i++)
    {
        temp2 = temp2->siguiente;
    }
    return temp2->datos;
}

void l_mostrar(Lista lista)
{
    struct Nodo *temp2 = lista->inicio;
    printf("Contenido de la lista: ");
    while (temp2 != NULL)
    {
        printf("%d ", temp2->datos->clave);
        temp2 = temp2->siguiente;
    }
    printf("\n");
}

char *l_to_string(Lista lista)
{
    char *resultado = (char *)malloc(sizeof(char) * (lista->cantidad * 10 + 3));
    strcpy(resultado, "[");
    struct Nodo *temp = lista->inicio;
    int i = 0;
    while (temp != NULL)
    {
        char num_str[10];
        sprintf(num_str, "%d", temp->datos->clave);
        strcat(resultado, num_str);
        if (i < (lista->cantidad - 1))
        {
            strcat(resultado, ", ");
        }
        temp = temp->siguiente;
        i++;
    }
    strcat(resultado, "]");

    return resultado;
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
// Rutinas del Iterador
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
Iterador iterador(Lista lista)
{
    Iterador iter = (Iterador)malloc(sizeof(struct IteradorRep));
    iter->posicionActual = lista->inicio;
    return iter;
}

bool hay_siguiente(Iterador iterador)
{
    return (iterador->posicionActual != NULL);
}

TipoElemento siguiente(Iterador iterador)
{
    TipoElemento actual = iterador->posicionActual->datos;
    iterador->posicionActual = iterador->posicionActual->siguiente;
    return actual;
}
