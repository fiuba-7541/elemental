#ifndef __QUEUE_H__
	#define __QUEUE_H__

	#include <malloc.h>
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
	 * Tipo puntero a funcion de copia de los elementos de la cola. Esta es la
	 * funcion que se invocara al recibir un elemento para almacenar en la
	 * estructura, de manera que se admita la posibilidad de almacenar copias
	 * profundas de los elementos en la cola.
	 */
	typedef int (*queue_copy_t) (void* dst, const void* src);

	/**
	 * Tipo puntero a funcion de destruccion de los elementos de la cola. Esta
	 * es la funcion que se invocara al destruir un elemento. Debe encargarse de
	 * liberar todos los recursos alocados en un elemento cualquiera de la cola
	 * para asi evitar cualquier perdida de memoria.
	 */
	typedef void (*queue_destroy_t) (void*);
	
	/**
	 * Estructura auxiliar de la cola. Es privada y no debe usarse bajo ningun
	 * concepto en la aplicacion.
	 */
	typedef struct queue_node_t
	{
		void* data;
		struct queue_node_t *next;
	} queue_node_t;
	
	/**
	 * Estructura cabecera, este es el tipo que se debera instanciar, aunque
	 * nunca acceder a sus campos.
	 */
	typedef struct
	{
		queue_node_t *first, *last;
		size_t size;
		queue_copy_t copy;
		queue_destroy_t destroy;
	} queue_t;
	
	/*
	 * queue_create
	 * Pre: C no fue creada.
	 * Post: C creada y vacia.
	 */
	int queue_create(queue_t*, size_t, queue_copy_t, queue_destroy_t);
	
	/*
	 * queue_destroy
	 * Pre: C creada.
	 * Post: C destruida. Todos los recursos utilizados liberados
	 */
	void queue_destroy(queue_t*);

	/*
	 * queue_clear
	 * Pre: Cola creada.
	 * Post: Cola vacia.
	 */
	void queue_clear(queue_t*);
	
	/*
	 * queue_empty
	 * Pre: C creada.
	 * Post: Si C esta vacia devuelve TRUE, sino FALSE.
	 */
	int queue_is_empty(const queue_t*);
	
	/*
	 * queue_push
	 * Pre: C creada.
	 * Post: E se agrego como ultimo elemento de C.
	 * Devuelve FALSE si no pudo agregar E, sino devuelve TRUE.
	 */
	int queue_push(queue_t*, const void*);
	
	/*
	 * queue_pop
	 * Pre: C creada y no vacia.
	 * Post: Se extrajo de C el primer elemento y se devuelve en E.
	 * Si no pudo extraer el elemento (porque C estaba vacia) devuelve FALSE,
	 * sino devuelve TRUE.
	 */
	int queue_pop(queue_t*, void*);

#endif

