/*
 * pruebas_heap.c
 * Pruebas para el tipo de dato abstracto Heap
 * Muchas gracias por la ayuda a las siguientes personas: Margarita Manterola, Maximiliano Curia
 */

#include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear_heap_vacio()
{
    printf("\nPRUEBAS CREAR heap VACIO\n");
    heap_t* heap = heap_crear(NULL);

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap esta vacio", heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba desencolar en heap vacio es NULL", heap_desencolar(heap) == NULL);
    print_test("Prueba ver maximo es NULL", heap_ver_max(heap) == NULL);

    heap_destruir(heap, NULL);
}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/


void pruebas_heap_estudiante()
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_heap_vacio();
    
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif