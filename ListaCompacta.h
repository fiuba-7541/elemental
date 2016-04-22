/*
 * ListaCompacta.h
 *
 *  Created on: 25/04/2011
 *      Author: anibal
 */

#ifndef _LISTACOMPACTA_H_
#define _LISTACOMPACTA_H_


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
		L_Primero,
		L_Siguiente,
		L_Anterior
	} TMovimiento_Lc;

	/**
	 * Estructura auxiliar de la lista simple. Es privada y no debe usarse bajo
	 * ningún concepto en la aplicación.
	 */
	typedef struct TNodoListaCompacta
	{
		struct TNodoListaCompacta *siguiente;
	} TNodoListaCompacta;

	/**
	 * Estructura cabecera, este es el tipo que se deberá instanciar, aunque
	 * nunca acceder a sus campos.
	 */
	typedef struct
	{
		TNodoListaCompacta *primero, *corriente;
		int tamanioDato;
	} TListaCompacta;

	/**
	 * L_CREAR
	 * Pre: Ls no fue creada.
	 * Post: Ls creada y vacia
	 */
	void LC_Crear(TListaCompacta *pLs, int tamanioDato);

	/**
	 * L_VACIAR
	 * Pre: Ls creada.
	 * Post: Ls vacia.
	 */
	void LC_Vaciar(TListaCompacta *pLs);

	/**
	 * L_VACIA
	 * Pre: Ls creada.
	 * Post: Si Ls tiene elementos devuelve FALSE sino TRUE.
	 */
	int LC_Vacia(TListaCompacta lista);

	/**
	 * L_ELEM_CTE
	 * Pre: Ls creada y no vacia.
	 * Post: Se devuelve en E el elemento Corriente de la lista.
	 */
	void LC_Elem_Cte(TListaCompacta lista, void* e);

	/**
	 * L_MOVER_CTE
	 * Pre: Ls creada y no vacia.
	 * Post: Si Ls esta vacia, devuelve FALSE. Sino:
	 * Si M = L_Primero, el nuevo elemento Corriente es el Primero. Devuelve TRUE
	 * Si M = L_Siguiente, el nuevo elemento Corriente es el Siguiente al
	 * Anterior. Si estaba en el ultimo elemento, devuelve FALSE, sino TRUE.
	 * Si M = L_Anterior, devuelve FALSE.
	 */
	int LC_Mover_Cte(TListaCompacta *pLs, TMovimiento_Lc m);

	/**
	 * L_BORRAR_CTE
	 * Pre: Ls creada y no vacia.
	 * Post: Se elimino el elemento Corriente, El nuevo elemento es el Siguiente o
	 * el Anterior si el Corriente era el ultimo elemento.
	 */
	void LC_Borrar_Cte(TListaCompacta *pLs);

	/**
	 * L_INSERTAR_CTE
	 * Pre: Ls creada.
	 * Post: E se agrego a la lista y es el actual elemento Corriente.
	 * Si M=L_Primero: se inserto como Primero de la lista.
	 * Si M=L_Siguiente: se inserto despues del elemento Corriente.
	 * Si M=L_Anterior: se inserto antes del elemento Corriente.
	 * Si pudo insertar el elemento devuelve TRUE, sino FALSE.
	 */
	int LC_Insertar_Cte(TListaCompacta *pLs, TMovimiento_Lc m, void* e);


#endif /* _LISTACOMPACTA_H_ */
