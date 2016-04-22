/*
 * set.h
 *
 *  Created on: 15/08/2012
 *      Author: Anibal
 */

#ifndef SET_H_
#define SET_H_

#include <stdio.h>

#include "var_array.h"
#include <string.h>

#ifndef RES_OK
	#define RES_OK 0
#endif
#ifndef RES_ENCONTRADO
	#define RES_ENCONTRADO 1
#endif
#ifndef RES_NO_ENCONTRADO
	#define RES_NO_ENCONTRADO 0
#endif

typedef struct T_STR_SET {
	V_Array array;
} StrSet;

/*
 * Primitiva de Creacion del TDA.
 *
 * @pre StrSet no creado
 * @post StrSet creado y listo para ser utilizado
 *
 * @param set El StrSet que se quiere crear
 * @return RES_OK si pudo crear e inicializar el StrSet
 */
int TS_Crear(StrSet* set);

/*
 * Primitiva de destruccion del TDA. Se encarga de liberar todos los recursos utilizados por el tipo
 *
 * @pre StrSet creado
 * @post StrSet destruido y todos los recursos han sido liberados
 *
 * @param set El StrSet que se quiere destruir
 * @return RES_OK si pudo destruir el StrSet y liberar todos los recursos
 */
int TS_Destruir(StrSet *set);

/*
 * Esta primitiva permite agregar elementos al StrSet. Solo pueden agregarse cadenas de caracteres.
 *
 * @pre StrSet creado
 * @pre e es una direccion valida de memoria que contiene una cadena de caracteres bien formada.
 * @post El elemento pasado por parametro se ha agregado al conjunto de cadenas de caracteres. Si ya existía no se agrega
 * 		 nuevamente
 *
 * @param set El StrSet al que se desea agregar un nuevo dato
 * @param e El dato que se desea agregar
 * @return RES_OK en caso de que se haya podido agregar el elemento exitosamente
 */
int TS_Add(StrSet *set, char* e);

/*
 * Permite quitar un elemento del conjunto. Para poder remover un elemento se deberá indicar un elemente previamente
 * insertado en el conjunto. En caso de no existir el elemento a remover, devolverá el código de error RES_NO_ENCONTRADO
 *
 * @pre StrSet creado
 * @pre e es una direccion valida de memoria que contiene una cadena de caracteres bien formada.
 * @post En caso de existir, se ha quitado el elemento indicado, en caso de no existir, no se ha modificado el conjunto
 *
 * @param set El StrSet del que se desea quitar un dato
 * @param e El valor del elemento que se quiere quitar. Si este valor es encontrado entre el conjunto, será quitado.
 * @return RES_OK si pudo quitar el elemento o RES_NO_ENCONTRADO en caso de que no existiera el dato
 */
int TS_Remove(StrSet *set, char* e);

/*
 * Primitiva de consulta. Permite consultar la existencia de un elemento en el conjunto. Devolvera RES_ENCONTRADO si el
 * conjunto contiene el dato indicado o RES_NO_ENCONTRADO en caso contrario.
 *
 * @pre StrSet creado
 * @pre e es una direccion valida de memoria que contiene una cadena de caracteres bien formada.
 * @post El resultado de esta primitiva será RES_ENCONTRADO o RES_NO_ENCONTRADO dado el caso de que encuentre o no el
 * 		 dato buscado
 *
 * @param set El StrSet que se quiere consultar
 * @param e La cadena de texto cuya existencia en el conjunto se quiere verificar
 * @return encontrado o no encontrado segun sea el caso bajo las constantes RES_ENCONTRADO y RES_NO_ENCONTRADO
 * 		   respectivamente. Los resultados también podrán se evaluados como TRUE o FALSE
 */
int TS_Contains(const StrSet *set, char* e);

/*
 * Indica la cantidad de elementos contenidos en el conjunto de cadenas de texto.
 *
 * @pre StrSet creado
 * @post La primitiva devolvera la cantidad de elementos que contiene el conjunto
 *
 * @param set StrSet cuyo tamaño se quiere evaluar
 * @return el valor entero no negativo correspondiente a la cantidad de elementos que tiene el conjunto
 */
int TS_Count(const StrSet *set);

#endif /* SET_H_ */
