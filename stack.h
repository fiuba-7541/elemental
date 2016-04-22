#ifndef __STACK_H__
	#define __STACK_H__
	
	#include <malloc.h>
	#include <memory.h>
	#include <stdlib.h>

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
	 * Tipo puntero a funcion de copia de los elementos de la pila. Esta es la
	 * funcion que se invocara al recibir un elemento (src) para almacenar en la
	 * estructura, de manera que se admita la posibilidad de almacenar copias
	 * profundas de los elementos en la pila. En dst queda guardada una copia de
	 * src.
	 */
	typedef int (*stack_copy_t) (void* dst, const void* src);

	/**
	 * Tipo puntero a funcion de destruccion de los elementos de la pila. Esta
	 * es la funcion que se invocara al destruir un elemento. Debe encargarse de
	 * liberar todos los recursos alocados en un elemento cualquiera de la pila
	 * para asi evitar cualquier perdida de memoria.
	 */
	typedef void (*stack_destroy_t) (void*);

	/**
	 * Estructura auxiliar de la pila. Es privada y no debe usarse bajo ningun
	 * concepto en la aplicacion.
	 */
	typedef struct stack_node_t
	{
		void* data;
		struct stack_node_t *next;
	} stack_node_t;
	
	/**
	 * Estructura cabecera, este es el tipo que se debera instanciar, aunque
	 * nunca acceder a sus campos.
	 */
	typedef struct
	{
		stack_node_t *top;
		size_t size;
		stack_copy_t copy;
		stack_destroy_t destroy;
	} stack_t;
	
	/*
	 * stack_create
	 * Pre: stack no fue creada o ya fue destruida
	 * Post: stack creada y vacia.
	 */
	void stack_create(stack_t*, size_t, stack_copy_t, stack_destroy_t);
	
	/*
	 * stack_destroy
	 * Pre: stack creada.
	 * Post: stack destruida. Todos los recursos utilizados liberados
	 */
	void stack_destroy(stack_t*);

	/*
	 * stack_clear
	 * Pre: stack creada.
	 * Post: stack vacia.
	 */
	void stack_clear(stack_t*);
	
	/*
	 * stack_is_empty
	 * Pre: stack creada.
	 * Post: Si stack esta vacia devuelve TRUE, sino FALSE.
	 */
	int stack_is_empty(const stack_t*);
	
	/*
	 * stack_push
	 * Pre: stack creada.
	 * Post: se agrego un nuevo elemento como tope de stack.
	 *       Devuelve FALSE si no pudo ADD E, sino devuelve TRUE.
	 */
	int stack_push(stack_t*, const void*);
	
	/*
	 * stack_pop
	 * Pre: P creada y no vacia.
	 * Post: Se extrajo del stack el tope y se devuelve clonado en el segundo
	 *       argumento que ya debe tener memoria asignada. Si no pudo extraer
	 *       el elemento (porque la stack estaba vacia) devuelve FALSE, sino
	 *       devuelve TRUE.
	 */
	int stack_pop(stack_t*, void*);

#endif

