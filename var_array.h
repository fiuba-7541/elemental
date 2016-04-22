/**
 *	Author: 	Aníbal Lovaglio
 *	Date:		21/03/2008
 *	Comments:	Ejercicio de ANSI C. Tipo de Dato Abstracto "Variable Array".
 *
 * Emulador de vector de tamaño variable genérico. Soporta agregados,
 * modificaciones y eliminaciones, además de acceso por posición como cualquier
 * vector. También puede entregar una copia del vector con el tamaño exacto
 * requerido para que se lo manipule externamente.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifndef _VAR_ARRAY_H_
#define _VAR_ARRAY_H_

#define RES_OK 0
#define RES_OUT_OF_BOUNDS -1
#define RES_OUT_OF_MEM -2

/**
 *
 * Definición de la estructura del TDA
 * Campos:
 *        array (void*): puntero con el que mantengo los datos almacenados, es
 *                       decir, el vector
 *        a_size (int) : Capacidad reservada con la que cuenta el vector en
 *                       cantidad de lugares p/elementos
 *        a_count(int) : Cantidad de elementos almacenados (Posiciones ocupadas)
 *        e_size(int)  : Tamaño en bytes de los elementos del vector
*/
typedef struct Var_Array{
    void* array;
    int a_size, a_count, e_size;
}V_Array;

typedef int (*funccmp)(void*, void*);

/**
 * Inicializa la estructura, los contadores, y pide la primer tanda de memoria
 * para comenzar. Arranca con lugar para 10 elementos, a partir de allí,
 * duplicará su tamaño cada vez que necesite más lugar.
 *
 * Devolverá 0 si pudo inicializar sin problemas, o -1 si no pudo alocar la
 * memoria para los primeros 10 elementos.
 */
int VA_create(V_Array* a, int elemsize);

/**
 * Devuelve la cantidad de elementos que tiene ocupados el vector.
 *
 * Espera que la estructura haya sido creada (Precondición)
 */
int VA_count(V_Array a);


/**
 * Agrega al final del vector un nuevo elemento recibido en elem (append)
 *
 * Espera que la estructura haya sido creada (Precondición)
 */
int VA_add(V_Array* a, void* elem);

/**
 * Obtiene el i-ésimo elemento del vector, siempre que exista.
 * Espera que la estructura haya sido creada (Precondición)
 * Si está vacía o se pide un elemento fuera de los que hay, devuelve el error -1
 */
int VA_get_i(V_Array a, int epos, void* elem);

/**
 * Entrega una copia del vector completo con el tamaño exacto. Espera que la
 * estructura haya sido inicializada.
 *
 * Cuidado: Devuelve una dirección de memoria que se alocó dentro de la función,
 * pero es externa e independiente de la estructura del TDA y debe liberarse
 * externamente.
 */
void* VA_get(const V_Array* a);

/**
 * Modifica un elemento del vector, a la posición que se indica en epos si es
 * que tal posición ya existe en la estructura. Espera estructura creada.
 */
int VA_set(V_Array* a, int epos, void* elem);

/**
 * Quita el iésimo elemento del vector. Devuelve lo mismo que VA_get_i
 */
int VA_remove(V_Array* a, int epos);

/**
 * Libera todos los recursos consumidos por la estructura. Debe estar creada.
 */
void VA_destroy(V_Array* a);

/**
 * Ordena internamete los elementos en el vector utilizando burbujeo.
 */
int VA_sort(V_Array* a, funccmp cmp);

/**
 * Ordena internamete los elementos en el vector utilizando Quick-sort,
 * limitándose a los elementos entre los índices "inicio" y "fin".
 */
void VA_qsort(V_Array* a, funccmp cmp, int inicio, int fin);

#endif /* _VAR_ARRAY_H_ */
