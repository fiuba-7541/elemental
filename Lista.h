#ifndef __LISTASIMPLE_h__
	#define __LISTASIMPLE_h__

	#include <stdlib.h>
	#include <memory.h>
	
	#if !defined(NULL)
		#define NULL 0
	#endif
	
	#if !defined(FALSE)
		#define FALSE 0
	#endif
	
	#if !defined(TRUE)
		#define TRUE 1
	#endif
	
	/**
	 * Movimientos que va a manejar la estructura. Son de conocimiento público,
	 * pero sólo deberían usarse para el manejo puntual de esta estructura.
	 */
	typedef enum
	{
		LS_Primero,
		LS_Siguiente,
		LS_Anterior
	} TMovimiento_Ls;
	
	/**
	 * Tipo puntero a función de copia de los elementos de la lista. Esta es la
	 * función que se invocará al recibir un elemento para almacenar en la
	 * estructura, de manera que se admita la posibilidad de almacenar copias
	 * profundas de los elementos en la lista.
	 */
	typedef int (*LS_copiar) (void* destino, void* origen);

	/**
	 * Tipo puntero a función de destrucción de los elementos de la lista. Esta
	 * es la función que se invocará al destruir un elemento. Debe encargarse de
	 * liberar todos los recursos alocados en un elemento cualquiera de la lista
	 * para así evitar cualquier pérdida de memoria.
	 */
	typedef void (*LS_destruir) (void*);

	/**
	 * Estructura auxiliar de la lista simple. Es privada y no debe usarse bajo
	 * ningún concepto en la aplicación.
	 */
	typedef struct TNodoListaSimple
	{
		void* Elem;
		struct TNodoListaSimple *Siguiente;
	} TNodoListaSimple;
	
	/**
	 * Estructura cabecera, este es el tipo que se deberá instanciar, aunque
	 * nunca acceder a sus campos.
	 */
	typedef struct
	{
		TNodoListaSimple *Primero, *Corriente;
		int TamanioDato;
		LS_copiar f_copia;
		LS_destruir f_destruccion;
	} TListaSimple;
	
	/**
	 * LS_CREAR
	 * Pre: Ls no fue creada.
	 * Post: Ls creada y vacia
	 */
	void LS_Crear(TListaSimple *pLs, int TamanioDato, LS_copiar f_copia, LS_destruir f_destruccion);

	/**
	 * LS_DESTRUIR
	 * Pre: Ls creada.
	 * Post: Ls destruida. Todos los recursos utilizados liberados
	 */
	void LS_Destruir(TListaSimple *pLs);
	
	/**
	 * LS_VACIAR
	 * Pre: Ls creada.
	 * Post: Ls vacia.
	 */
	void LS_Vaciar(TListaSimple *pLs);
	
	/**
	 * LS_VACIA
	 * Pre: Ls creada.
	 * Post: Si Ls tiene elementos devuelve FALSE sino TRUE.
	 */
	int LS_Vacia(TListaSimple Ls);
	
	/**
	 * LS_ELEM_CTE
	 * Pre: Ls creada y no vacia.
	 * Post: Se devuelve en E el elemento Corriente de la lista.
	 */
	void LS_Elem_Cte(TListaSimple Ls, void* pE);
	
	/**
	 * LS_MOVER_CTE
	 * Pre: Ls creada y no vacia.
	 * Post: Si Ls esta vacia, devuelve FALSE. Sino:
	 * Si M = LS_Primero, el nuevo elemento Corriente es el Primero. Devuelve TRUE
	 * Si M = LS_Siguiente, el nuevo elemento Corriente es el Siguiente al
	 * Anterior. Si estaba en el ultimo elemento, devuelve FALSE, sino TRUE.
	 * Si M = LS_Anterior, devuelve FALSE.
	 */
	int LS_Mover_Cte(TListaSimple *pLs, TMovimiento_Ls M);
	
	/**
	 * LS_BORRAR_CTE
	 * Pre: Ls creada y no vacia.
	 * Post: Se elimino el elemento Corriente, El nuevo elemento es el Siguiente o
	 * el Anterior si el Corriente era el ultimo elemento.
	 */
	void LS_Borrar_Cte(TListaSimple *pLs);
	
	/**
	 * LS_INSERTAR_CTE
	 * Pre: Ls creada.
	 * Post: E se agrego a la lista y es el actual elemento Corriente.
	 * Si M=LS_Primero: se inserto como Primero de la lista.
	 * Si M=LS_Siguiente: se inserto despues del elemento Corriente.
	 * Si M=LS_Anterior: se inserto antes del elemento Corriente.
	 * Si pudo insertar el elemento devuelve TRUE, sino FALSE.
	 */
	int LS_Insertar_Cte(TListaSimple *pLs, TMovimiento_Ls M, void* E);
	
#endif

