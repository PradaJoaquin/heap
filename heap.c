#include <stdlib.h>
#include "vector.h"
#include "heap.h"
#define SIZE_MINIMO 8
#define FACTOR_REDIMENSION 2

typedef int (*cmp_func_t) (const void *a, const void *b);

typedef struct heap{
    vector_t* arreglo;
    cmp_func_t comparar;
}heap_t;

heap_t *heap_crear(cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if(!heap){
        return NULL;
    }
    heap->arreglo = vector_crear_vacio();
    if(!heap->arreglo){
        free(heap);
        return NULL;
    }
    heap->comparar = cmp;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if(!heap){
        return NULL;
    }
    heap->arreglo = vector_crear(arreglo, n);
    if(!arreglo){
        free(heap);
        return NULL;
    }
    heap->comparar = cmp;
    return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
    vector_destruir(heap->arreglo, destruir_elemento);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap){
    return vector_cantidad(heap->arreglo);
}

bool heap_esta_vacio(const heap_t *heap){
    return vector_cantidad(heap->arreglo) == 0;
}

/* Se guarda al final del array se hace upheap */
bool heap_encolar(heap_t *heap, void *elem){
    vector_guardar(heap->arreglo, elem);
    size_t pos_hijo = vector_cantidad(heap->arreglo);
    upheap(heap, (pos_hijo - 1) / 2, pos_hijo);
}

void *heap_ver_max(const heap_t *heap){
    if(heap_esta_vacio(heap))
        return NULL;
    return vector_obtener(heap->arreglo, 0);
}

/* Lo primero que hace es swappear con el ultimo elemento ya que el vector elimina el ultimo, se hace downheap de la nueva raiz despues*/
void *heap_desencolar(heap_t *heap){
    vector_swap(heap,0, vector_cantidad(heap->arreglo));
    void* dato = vector_eliminar(heap->arreglo);
    downheap(heap, 0, 1, 2);
    return dato;
}

void upheap(heap_t* heap, size_t padre, size_t hijo){
    if(hijo == 0){
        return;
    }
    if(comparar(vector_obtener(heap->arreglo, padre), vector_obtener(heap->arreglo, hijo)) >= 0){
        return;
    }
    vector_swap(heap->arreglo, padre, hijo);
    size_t nuevo_padre = (hijo - 1) / 2;
    upheap(heap->arreglo, nuevo_padre, padre);
}

void downheap(heap_t* heap, size_t padre, size_t hijo_izq, size_t hijo_der){
    if(hijo_izq >= vector_cantidad(heap->arreglo)){
        return;
    }
    //Si el hijo derecho no existe en el arreglo toma el valor del hijo izquierdo (Probablemente ahorre casos borde esto)
    hijo_der = hijo_der >= vector_cantidad(heap->arreglo) ? hijo_izq : hijo_der; 
    size_t maximo = vector_obtener(heap->arreglo, hijo_izq) > vector_obtener(heap->arreglo, hijo_der) ? hijo_izq : hijo_der;
    if(comparar(vector_obtener(heap->arreglo, padre), vector_obtener(heap->arreglo, maximo) > 0)){
        return;
    }
    vector_swap(heap->arreglo, padre, maximo);
    size_t nuevo_hijo_izq = maximo * 2 + 1;
    size_t nuevo_hijo_der = maximo * 2 + 2;
    downheap(heap, maximo, nuevo_hijo_izq, nuevo_hijo_der);
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    
}