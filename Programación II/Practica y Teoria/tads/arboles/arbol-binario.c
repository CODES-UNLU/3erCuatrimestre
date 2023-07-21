#include <stdlib.h>
#include <string.h>
#include "arbol-binario.h"
#include "nodo.h"

struct ArbolBinarioRep {
    NodoArbol raiz;
    int cantidad_elementos;
};

ArbolBinario a_crear() {
    ArbolBinario nuevo_arbol = (ArbolBinario) malloc(sizeof(struct ArbolBinarioRep));
    nuevo_arbol->raiz = NULL;
    nuevo_arbol->cantidad_elementos = 0;
    return nuevo_arbol;
}

bool a_es_vacio(ArbolBinario a) {
    return a->raiz == NULL;
}

int a_cantidad_elementos(ArbolBinario a) {
    return a->cantidad_elementos;
}

bool a_es_rama_nula(NodoArbol pa) {
    return pa == NULL;
}

NodoArbol a_raiz(ArbolBinario a) {
    return a->raiz;
}

NodoArbol a_establecer_raiz(ArbolBinario a, TipoElemento te) {
    if (a->raiz != NULL) {
        // TODO Acá debería ser un error
        // No se puede l_insertar la raíz de un árbol que ya tiene raíz
        return a->raiz;
    }

    NodoArbol na = crear_nodo_arbol(te);
    a->raiz = na;
    a->cantidad_elementos++;
    a->raiz->altura=0;
    return na;
}

NodoArbol a_conectar_hi(ArbolBinario a, NodoArbol pa, TipoElemento te) {
    // TODO Acá tenemos que chequear que la posición árbol efectivamente esté en el árbol
    if (pa == NULL) {
        return NULL;
    }
    // TODO Chequeamos que la posición árbol no tenga ya la rama que están solicitando insertar
    if (pa->hi != NULL) {
        // TODO Deberíamos devolver error
        return pa->hi;
    }
    NodoArbol na = crear_nodo_arbol(te);
    a->cantidad_elementos++;

    pa->hi = na;
    pa->hi->altura=pa->altura+1;

    return na;
}

NodoArbol a_conectar_hd(ArbolBinario a, NodoArbol pa, TipoElemento te) {
    // TODO Acá tenemos que chequear que la posición árbol efectivamente esté en el árbol
    if (pa == NULL) {
        return NULL;
    }
    // TODO Chequeamos que la posición árbol no tenga ya la rama que están solicitando insertar
    if (pa->hd != NULL) {
        // TODO Deberíamos devolver error
        return pa->hd;
    }
    NodoArbol na = crear_nodo_arbol(te);
    a->cantidad_elementos++;

    pa->hd = na;
    pa->hd->altura=pa->altura+1;
    return na;
}

