/*
 * pruebas_heap.c
 * Pruebas para el tipo de dato abstracto Heap
 * Muchas gracias por la ayuda a las siguientes personas: Margarita Manterola, Maximiliano Curia
 */

#include "heap.h"
#include "testing.h"
#include "strutil.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.

int intcmp(const void *n1, const void *n2){
    if(n1 && !n2){
        return 1;
    }
    if(!n1 && n2){
        return -1;
    }
    if(!n1 && !n2){
        return 0;
    }
    int cmp1 = *(int*)n1;
    int cmp2 = *(int*)n2;
    if(cmp1 == cmp2){
        return 0;
    }
    return cmp1 > cmp2 ? 1 : -1;
}

int strcmp_prestado(const void *X, const void *Y)
{
    if(X && !Y){
        return 1;
    }
    if(!X && Y){
        return -1;
    }
    if(!X && !Y){
        return 0;
    }
    char* X2 = (char*)X;
    char* Y2 = (char*)Y;
    while(*X2)
    {
        // if characters differ or end of second string is reached
        if (*X2 != *Y2)
            break;
 
        // move to next pair of characters
        X2++;
        Y2++;
    }

    // return the ASCII difference after converting char* to unsigned char*
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear_heap_vacio()
{
    printf("\nPRUEBAS CREAR HEAP VACIO\n");
    heap_t* heap = heap_crear(NULL);

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap esta vacio", heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba ver maximo es NULL", heap_ver_max(heap) == NULL);
    print_test("Prueba desencolar en heap vacio es NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
}

static void prueba_encolar_desencolar_heap()
{
    printf("\nPRUEBAS ENCOLAR DESENCOLAR HEAP\n");
    heap_t* heap = heap_crear(strcmp_prestado);
    
    char* s = "hola";
    print_test("Prueba heap encolar", heap_encolar(heap, s));

    print_test("Prueba heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba ver maximo es el correcto", strcmp_prestado((char*)heap_ver_max(heap), s) == 0);

    print_test("Prueba desencolar heap es el correcto", strcmp_prestado((char*)heap_desencolar(heap), s) == 0);

    print_test("Prueba heap esta vacio", heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba ver maximo es NULL", heap_ver_max(heap) == NULL);
    print_test("Prueba desencolar heap es NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
}

static void prueba_volumen_heap_cambiando_max(){
    printf("\nPRUEBAS VOLUMEN HEAP CAMBIANDO MAX\n");
    heap_t* heap = heap_crear(intcmp);

    size_t largo = 100;
    int n[100];
    //Insertar elementos en el heap
    bool ok = true;
    bool ok2 = true;
    for (int i = 0; i < largo; i++) {
        n[i] = i;
        ok = heap_encolar(heap, &n[i]);
        ok2 = *(int*)heap_ver_max(heap) == n[i];

        if (!ok || !ok2) break;
    }

    print_test("Prueba heap encolar muchos elementos", ok);
    print_test("Prueba heap se cambiaron correctamente los max", ok2);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        int* max = heap_ver_max(heap);
        ok = (int*)heap_desencolar(heap) == max;
        if(!heap_cantidad(heap) == 0){
            ok2 = *(int*)heap_ver_max(heap) == *max - 1;
        }
        if (!ok || !ok2) break;
    }

    print_test("Prueba heap borrar muchos elementos", ok);
    print_test("Prueba heap se cambiaron correctamente los max", ok2);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    /* Destruye el heap */
    heap_destruir(heap, NULL);
}

static void prueba_volumen_heap_variado(){
    printf("\nPRUEBAS VOLUMEN HEAP VARIADO\n");
    heap_t* heap = heap_crear(strcmp_prestado);
    
    char* rick_astley = "We're no strangers tO love YOu knOw tHe rules And sO do I A full commitment's what I'm thinking of You wouldn't get this from any oTher guy i just wanna tEll YOou hOw i'm fEeling Gotta maKe yoU understand Never gOnna give yOu up NEver goNna let yOU down NEVer Gonna run around aNd desert yoou NEVEr GonNa make yoOu cry NEVER GONna say goodbye NeVer GONNa teLl a lie and hurt yooou We've known each other for so long Your heart's beEn aching but yOu're tOo shy To sAy it Inside we both knOW what's been going on We know the game anD we're gonna play iT aND if you ask mE how I'M feeling Don't tell me yOU're toO blind TO see";
    char** claves = split(rick_astley, ' ');
    size_t largo = 125;
    //Insertar elementos en el heap
    bool ok = true;
    for (int i = 0; claves[i] != NULL; i++) {
        ok = heap_encolar(heap, claves[i]);
        if (!ok) break;
    }

    print_test("Prueba heap encolar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        char* max = heap_ver_max(heap);
        ok = (char*)heap_desencolar(heap) == max;
        if (!ok) break;
    }

    print_test("Prueba heap borrar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    /* Destruye el heap */
    free_strv(claves);
    heap_destruir(heap, NULL);
}

static void prueba_crear_heap_arreglo(){
    printf("\nPRUEBAS CREAR HEAP ARREGLO\n");
    int n[] = {0, 4, 1, 2, 5, 3};
    int** n2 = malloc(sizeof(int*) * 6);
    size_t largo = 6;
    for(int i = 0; i < largo; i++){
        n2[i] = &n[i];
    }
    heap_t* heap = heap_crear_arr((void*)n2, largo, intcmp);

    print_test("Prueba heap crear heap arreglo", heap);
    print_test("Prueba heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es la correcta", heap_cantidad(heap) == largo);
    print_test("Prueba ver maximo es el correcto", *(int*)heap_ver_max(heap) == 5);
    print_test("Prueba desencolar en heap vacio es el correcto", *(int*)heap_desencolar(heap) == 5);

    heap_destruir(heap, NULL);
    free(n2);
}

static void prueba_heapsort(){
    printf("\nPRUEBAS HEAPSORT\n");
    
    int n[] = {0, 4, 1, 2, 5, 3};
    int** n2 = malloc(sizeof(int*) * 6);
    size_t largo = 6;
    for(int i = 0; i < largo; i++){
        n2[i] = &n[i];
    }

    heap_sort((void*)n2, largo, intcmp);
    bool ok = true;
    for(int i = 0; i < largo; i++){
        ok = *n2[i] == i;
        if(!ok){
            break;
        }
    }
    print_test("Se ordenaron correctamente todos los elementos", ok);
    free(n2);
}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/


void pruebas_heap_estudiante()
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_heap_vacio();
    prueba_encolar_desencolar_heap();
    prueba_crear_heap_arreglo();
    prueba_volumen_heap_cambiando_max();
    prueba_volumen_heap_variado();
    prueba_heapsort();
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif