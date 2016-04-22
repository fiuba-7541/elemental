/*
 * ABO.h
 *
 *  Created on: 01/06/2011
 *      Author: anibal
 */

#ifndef ABO_H_
#define ABO_H_

#include "AB.h"
#include <stdlib.h>

#define RES_DELETED 1
#define RES_OK 0
#define RES_ELEMENTO_YA_EXISTE -1
#define RES_OUT_OF_MEMORY -2
#define RES_ELEMENTO_NO_EXISTE -3

/* Definiciones de punteros a funci�n necesarios para la manipulaci�n del ABO */

/*
 * Tipo Puntero a funci�n de comparaci�n para que el ABO mantenga el orden de la
 * estructura y pueda realizar las operaci�nes de ABM y Obtenci�n de datos
 */
typedef int (*taboCmp) (void*, void*);

/*
 * Funci�n de procesamiento de todos los elementos de un ABO. El primer puntero
 * void debe usarse para pasar el elemento contenido en el ABO, y el segundo
 * est� presente para admitir la utilizaci�n de argumentos, ya sean est�ticos, o
 * variables, a cada invocaci�n de procesamiento.
 */
typedef int (*aboProcessFunctionPtr) (void*, void*);

/* Fin definiciones de punteros a funci�n */

typedef struct T_ABO {
	int tamanio;
	taboCmp fcmp;
	TAB a;
	AB_copiar f_copia;
	AB_destruir f_destruccion;
}TABO;

/*
 * Inicializa la estructura y registra la cantidad de bytes que ocupan los
 * elementos que en ella se guarden.
 * PRE : abo no creado, o en su defecto, se destruyó.
 * POST: abo creado.
 */
int ABO_Crear(TABO* abo, taboCmp paf, size_t tam, AB_copiar f_copia, AB_destruir f_destruccion);

/*
 * Destruye la estructura liberando los recursos que estaba utilizando.
 * PRE : abo creado.
 * POST: abo destruido y todos sus recursos liberados.
 */
int ABO_Destruir(TABO* abo);

/*
 * Agrega el elemento pasado en "elem" a la estructura, preservando el orden
 * PRE : abo creado, elem es comparable con otros de su mismo tipo mediante la
 * 	     funcion indicada en la primitiva de creacion del ABO.
 * POST: de ser posible, se agrega el nuevo elemento en la estructura, de lo
 * 	     contrario, se retorna el codigo de error correspondiente:
 * 	      - RES_ELEMENTO_YA_EXISTE
 * 	      - RES_OUT_OF_MEMORY
 */
int ABO_Insertar(TABO* abo, void* elem);

/*
 * Navega la estructura buscando el elemento cuya clave esta cargada en el
 * puntero elem. Tomese en cuenta que elem, en principio, no tiene cargados los
 * datos asociados a la clave, sino solamente la clave, para poder compararse
 * mediante la funcion de comparacion indicada en la creacion del tda.
 * Esta primitiva cargara los datos del elemento de la estructura en el espacio
 * de memoria apuntado por elem.
 * PRE : abo creado
 * POST: si el elemento con la clave indicada existia, retorna RES_OK y elem
 *       cargado con los datos, en caso contrario retorna el error
 *       RES_ELEMENTO_NO_EXISTE, y elem no se modifica.
 */
int ABO_Obtener(TABO* abo, void* elem);

/*
 * Navega la estructura buscando el elemento cuya clave esta cargada en el
 * puntero elem.
 * Esta primitiva cargara los datos del elemento recibido en elem, y actualizara
 * el elemento correspondiente (segun la clave lo indique) con los datos que
 * contenga el parametro elem.
 * PRE : abo creado
 * POST: si el elemento con la clave indicada existia, retorna RES_OK y se
 *       actualizan los datos en la estructura, en caso contrario retorna el
 *       error RES_ELEMENTO_NO_EXISTE, y no se modifica nada en la estructura.
 */
int ABO_Actualizar(TABO* abo, void* elem);

/*
 * Elimina, en caso de que exista, el elemento que se compare con los datos
 * pasados en el parametro elem resultando igual.
 * PRE : abo creado
 * POST: si el elemento con la clave indicada existia, retorna RES_OK y se
 *       elimina el elemento de la estructura, en caso contrario retorna el
 *       error RES_ELEMENTO_NO_EXISTE, y no se modifica nada en la estructura.
 */
int ABO_Borrar(TABO* abo, void* elem);

/*
 * Aplica la función process a todos los elementos de la estructura, segun el
 * orden correspondiente a la forma de recorrer indicada en el nombre de la
 * primitiva. El valor recibido en args se pasará, como esté, a cada invocación
 * de la función de procesar, permitiendo mantener un estado y transferir datos
 * entre los sucesivos llamados de la funcion de procesamiento.
 */
int ABO_ProcesarInOrden(TABO* a, aboProcessFunctionPtr process, void* args);
int ABO_ProcesarPreOrden(TABO* a, aboProcessFunctionPtr process, void* args);
int ABO_ProcesarPosOrden(TABO* a, aboProcessFunctionPtr process, void* args);

/*
 * Idem a ABO_ProcesarInOrden pero permitiendo indicar un rango, con los
 * parametros desde y hasta. No se recorreran ni procesaran los elementos que
 * queden fuera del rango indicado.
 */
int ABO_ProcesarEnRangoInOrden(TABO* a, aboProcessFunctionPtr process, void* args, void* desde, void* hasta);

#endif /* ABO_H_ */
