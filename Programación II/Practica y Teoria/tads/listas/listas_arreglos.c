#include "listas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const int TAMANIO_MAXIMO = 100;

struct ListaRep
{
    TipoElemento *valores;
    int cantidad;
};

struct IteradorRep
{
    Lista lista;
    int posicionActual;
};

//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
// Rutinas del TAD
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------

Lista l_crear()
{
    Lista n_lista = (Lista)malloc(sizeof(struct ListaRep));
    n_lista->valores = calloc(TAMANIO_MAXIMO, sizeof(TipoElemento));
    n_lista->cantidad = 0;
    return n_lista;
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
    if (l_es_llena(lista))
    {
        return;
    }
    lista->valores[lista->cantidad] = elemento;
    lista->cantidad++;
}

void l_borrar(Lista lista, int clave)
{
    if (l_es_vacia(lista))
    {
        return;
    }

    int posicion = 0;
    while (posicion < lista->cantidad)
    {
        if (lista->valores[posicion]->clave == clave)
        {
            for (int i = posicion; i < lista->cantidad - 1; i++)
            {
                lista->valores[i] = lista->valores[i + 1];
            }
            lista->cantidad--;
        }
        else
        {
            posicion++;
        }
    }
}

TipoElemento l_buscar(Lista lista, int clave)
{
    int pos = 0;
    while (pos < lista->cantidad)
    {
        if (lista->valores[pos]->clave == clave)
        {
            return lista->valores[pos];
        }
        pos++;
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
    for (int i = lista->cantidad; i >= pos && i > 0; i--)
    {
        lista->valores[i] = lista->valores[i - 1];
    }
    lista->valores[pos - 1] = elemento;
    lista->cantidad++;
}

void l_eliminar(Lista lista, int pos)
{
    if (pos > l_longitud(lista))
    {
        return;
    }
    // Ahora intento eliminar
    if (1 <= pos && pos <= l_longitud(lista))
    {
        for (int i = pos - 1; i < lista->cantidad; i++)
        {
            lista->valores[i] = lista->valores[i + 1];
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
    return lista->valores[pos - 1];
}

void l_mostrar(Lista lista)
{
    printf("Contenido de la lista: ");
    for (int i = 0; i < lista->cantidad; i++)
    {
        printf("%d ", lista->valores[i]->clave);
    }
    printf("\n");
}

char *l_to_string(Lista lista)
{
    char *resultado = (char *)malloc(sizeof(char) * (lista->cantidad * 10 + 3));
    strcpy(resultado, "[");
    for (int i = 0; i < lista->cantidad; i++)
    {
        char num_str[10];
        sprintf(num_str, "%d", lista->valores[i]->clave);
        strcat(resultado, num_str);
        if (i < (lista->cantidad - 1))
        {
            strcat(resultado, ", ");
        }
    }
    strcat(resultado, "]");

    return resultado;
}

//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
// Rutinas del Iterador
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
Iterador iterador(Lista lista)
{
    Iterador iter = (Iterador)malloc(sizeof(struct IteradorRep));
    iter->lista = lista;
    iter->posicionActual = 0;
    return iter;
}

bool hay_siguiente(Iterador iterador)
{
    return iterador->posicionActual < iterador->lista->cantidad;
}

TipoElemento siguiente(Iterador iterador)
{
    return iterador->lista->valores[iterador->posicionActual++];
}
