#ifndef __STRAIGHT_LIST_H__
	#define __STRAIGHT_LIST_H__

	#include <stdlib.h>
	#include <memory.h>
	
	#if !defined(NULL)
		#define NULL 0x0
	#endif
	
	#if !defined(FALSE)
		#define FALSE 0
	#endif
	
	#if !defined(TRUE)
		#define TRUE 1
	#endif

	#if !defined(RES_OK)
		#define RES_OK 0
	#endif

	/**
	 * Movimientos que va a manejar la estructura. Son de conocimiento publico,
	 * pero solo deberian usarse para el manejo puntual de esta estructura.
	 */
	typedef enum
	{
		straight_list_first,
		straight_list_next,
		straight_list_previous
	} straight_list_movement_t;
	
	/**
	 * Tipo puntero a funcion de copia de los elementos de la lista. Esta es la
	 * funcion que se invocara al recibir un elemento para almacenar en la
	 * estructura, de manera que se admita la posibilidad de almacenar copias
	 * profundas de los elementos en la lista.
	 * Debe devolver TRUE si pudo copiar src en dst o FALSE si hubo algún
	 * problema y no pudo.
	 */
	typedef int (*straight_list_copy_t) (void* dst, const void* src);

	/**
	 * Tipo puntero a funcion de destruccion de los elementos de la lista. Esta
	 * es la funcion que se invocara al destruir un elemento. Debe encargarse de
	 * liberar todos los recursos alocados en un elemento cualquiera de la lista
	 * para asi evitar cualquier perdida de memoria.
	 */
	typedef void (*straight_list_destroy_t) (void*);

	/**
	 * Estructura auxiliar de la lista simple. Es privada y no debe usarse bajo
	 * ningun concepto en la aplicacion.
	 */
	typedef struct straight_list_node_t
	{
		void* data;
		struct straight_list_node_t *next;
	} straight_list_node_t;
	
	/**
	 * Estructura cabecera, este es el tipo que se debera instanciar, aunque
	 * nunca acceder a sus campos.
	 */
	typedef struct
	{
		straight_list_node_t *first, *current;
		size_t size;
		straight_list_copy_t copy;
		straight_list_destroy_t destroy;
	} straight_list_t;
	
	/**
	 * CREAR
	 * Pre: Ls no fue creada.
	 * Post: Ls creada y vacia
	 */
	int straight_list_create(straight_list_t*, size_t, straight_list_copy_t, straight_list_destroy_t);

	/**
	 * DESTRUIR
	 * Pre: Ls creada.
	 * Post: Ls destruida. Todos los recursos utilizados liberados
	 */
	void straight_list_destroy(straight_list_t*);
	
	/**
	 * VACIAR
	 * Pre: Ls creada.
	 * Post: Ls vacia.
	 */
	void straight_list_clear(straight_list_t*);
	
	/**
	 * VACIA?
	 * Pre: Ls creada.
	 * Post: Si Ls tiene elementos devuelve FALSE sino TRUE.
	 */
	int straight_list_is_empty(const straight_list_t*);
	
	/**
	 * OBTENER CORRIENTE
	 * Pre: Ls creada y no vacia.
	 * Post: Se devuelve en E el elemento Corriente de la lista.
	 */
	void straight_list_get(const straight_list_t*, void*);
	
	/**
	 * MOVER
	 * Pre: Ls creada y no vacia.
	 * Post: Si Ls esta vacia, devuelve FALSE. Sino:
	 * Si M = LS_Primero, el nuevo elemento Corriente es el Primero. Devuelve TRUE
	 * Si M = LS_Siguiente, el nuevo elemento Corriente es el Siguiente al
	 * Anterior. Si estaba en el ultimo elemento, devuelve FALSE, sino TRUE.
	 * Si M = LS_Anterior, devuelve FALSE.
	 */
	int straight_list_move(straight_list_t*, straight_list_movement_t);
	
	/**
	 * BORRAR
	 * Pre: Ls creada y no vacia.
	 * Post: Se elimino el elemento Corriente, El nuevo elemento es el Siguiente o
	 * el Anterior si el Corriente era el ultimo elemento.
	 */
	void straight_list_delete(straight_list_t*);
	
	/**
	 * INSERTAR (respecto al elemento corriente)
	 * Pre: Ls creada.
	 * Post: E se agrego a la lista y es el actual elemento Corriente.
	 * Si M=LS_Primero: se inserto como Primero de la lista.
	 * Si M=LS_Siguiente: se inserto despues del elemento Corriente.
	 * Si M=LS_Anterior: se inserto antes del elemento Corriente.
	 * Si pudo insertar el elemento devuelve TRUE, sino FALSE.
	 */
	int straight_list_insert(straight_list_t*, straight_list_movement_t, const void*);
	
	/**
	 * ACTUALIZAR (el elemento corriente)
	 * Pre: Lista creada.
	 * Post: Se actualizó el elemento corriente, destruyendo el que estaba y
	 *       cambiándolo por el pasado por parámetro.
	 * Si pudo actualizar el elemento devuelve TRUE, sino FALSE.
	 */
	int straight_list_update(straight_list_t*, const void*);

#endif /* __STRAIGHT_LIST_H__ */

