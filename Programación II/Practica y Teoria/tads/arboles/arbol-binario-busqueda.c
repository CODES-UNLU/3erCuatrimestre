#include "arbol-binario-busqueda.h"
#include "nodo.h"

static const int TAMANIO_MAXIMO = 100;


struct ArbolBinarioBusquedaRep {
    NodoArbol raiz;
    int cantidad_elementos;
};

ArbolBinarioBusqueda abb_crear() {
    ArbolBinarioBusqueda nuevo_arbol = (ArbolBinarioBusqueda) malloc(sizeof(struct ArbolBinarioBusquedaRep));
    nuevo_arbol->raiz = NULL;
    nuevo_arbol->cantidad_elementos = 0;
    return nuevo_arbol;
}

bool abb_es_vacio(ArbolBinarioBusqueda a) {
    return (a->raiz == NULL);
}

int abb_cantidad_elementos(ArbolBinarioBusqueda a) {
    return (a->cantidad_elementos == TAMANIO_MAXIMO);
}

NodoArbol abb_raiz(ArbolBinarioBusqueda a) {
    return a->raiz;
}


NodoArbol abb_insertar_recursivo(ArbolBinarioBusqueda a, NodoArbol pa, TipoElemento te) {
    if (pa == NULL) {
        a->cantidad_elementos++;
        NodoArbol nuevo_nodo = crear_nodo_arbol(te);
        if (a->cantidad_elementos == 1) {
            a->raiz = nuevo_nodo;
        }
        return nuevo_nodo;
    } else if (te->clave > pa->datos->clave) {
        pa->hd = abb_insertar_recursivo(a, pa->hd, te);
    } else if (te->clave < pa->datos->clave) {
        pa->hi = abb_insertar_recursivo(a, pa->hi, te);
    }
    return pa;
}

void abb_insertar(ArbolBinarioBusqueda a, TipoElemento te) {
    abb_insertar_recursivo(a, abb_raiz(a), te);
}

NodoArbol abb_buscar_minimo(NodoArbol nodoArbol) {
    NodoArbol actual = nodoArbol;

    while (actual && actual->hi != NULL)
        actual = actual->hi;

    return actual;
}

NodoArbol abb_eliminar_recursivo(ArbolBinarioBusqueda arbol, NodoArbol root, int claveABorrar) {
    if (root == NULL) {
        return root;
    }

    if (claveABorrar < root->datos->clave)
        root->hi = abb_eliminar_recursivo(arbol,root->hi, claveABorrar);
    else if (claveABorrar > root->datos->clave)
        root->hd = abb_eliminar_recursivo(arbol,root->hd, claveABorrar);
    else {
        if (root->hi == NULL) {
            NodoArbol temp = root->hd;
            free(root);
            return temp;
        } else if (root->hd == NULL) {
            NodoArbol temp = root->hi;
            free(root);
            return temp;
        }

        NodoArbol temp = abb_buscar_minimo(root->hd);
        root->datos->clave = temp->datos->clave;
        root->datos->valor = temp->datos->valor;

        root->hd = abb_eliminar_recursivo(arbol,root->hd, temp->datos->clave);
    }
    return root;
}

void abb_eliminar(ArbolBinarioBusqueda a, int claveABorrar) {
    a->raiz = abb_eliminar_recursivo(a, abb_raiz(a), claveABorrar);
}

TipoElemento abb_buscar_recursivo(NodoArbol nodoArbol, int clave) {
    if (nodoArbol == NULL)
        return NULL;
    else if (clave < nodoArbol->datos->clave)
        return abb_buscar_recursivo(nodoArbol->hi, clave);
    else if (clave > nodoArbol->datos->clave)
        return abb_buscar_recursivo(nodoArbol->hd, clave);
    else
        return nodoArbol->datos;
}

TipoElemento abb_buscar(ArbolBinarioBusqueda a, int clave) {
    return abb_buscar_recursivo(abb_raiz(a), clave);
}