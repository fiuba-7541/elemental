#ifndef __ARBOLBINARIO_H__
	#define __ARBOLBINARIO_H__
	
	#include <stdlib.h>
	#include <memory.h>
	
	#define IZQ 1
	#define DER 2
	#define PAD 3
	#define RAIZ 4

	#if !defined(RES_OK)
		#define RES_OK 0
	#endif

	#if !defined(RES_MOV_INVALIDO)
		#define RES_MOV_INVALIDO -1
	#endif

	#if !defined(RES_OUT_OF_MEM)
		#define RES_OUT_OF_MEM -2
	#endif

	#if !defined(RES_ARBOL_VACIO)
		#define RES_ARBOL_VACIO -4
	#endif
	
	#if !defined(NULL)
		#define NULL 0x0
	#endif
	
	#if !defined(FALSE)
		#define FALSE 0
	#endif
	
	#if !defined(TRUE)
		#define TRUE 1
	#endif
	
	/**
	 * Tipo puntero a función de copia de los elementos de la lista. Esta es la
	 * función que se invocará al recibir un elemento para almacenar en la
	 * estructura, de manera que se admita la posibilidad de almacenar copias
	 * profundas de los elementos en la lista.
	 */
	typedef int (*AB_copiar) (void* destino, const void* origen);

	/**
	 * Tipo puntero a función de destrucción de los elementos de la lista. Esta
	 * es la función que se invocará al destruir un elemento. Debe encargarse de
	 * liberar todos los recursos alocados en un elemento cualquiera de la lista
	 * para así evitar cualquier pérdida de memoria.
	 */
	typedef void (*AB_destruir) (void*);

	typedef struct TNodoAB
	{
		void* elem;
		struct TNodoAB *izq, *der;
	} TNodoAB;
	
	typedef struct TAB
	{
		TNodoAB *raiz,*cte;
		size_t tamdato;
		AB_copiar f_copia;
		AB_destruir f_destruccion;
	} TAB;
	
	void AB_Crear(TAB *a, size_t tdato, AB_copiar f_copia, AB_destruir f_destruccion);
	
	void AB_ElemCte(TAB a,void *elem);
	
	void AB_ModifCte(TAB *a, const void *elem);
	
	int AB_MoverCte(TAB *a,int mov);
	
	void AB_Vaciar(TAB *a);
	
	int AB_Vacio(TAB a);
	
	int AB_Insertar(TAB *a,int mov,void *elem);
	
	int AB_BorrarRama(TAB *a);

	int AB_BorrarSubRama(TAB *a, int mov);

#endif

