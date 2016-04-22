#ifndef __COLA_H__
	#define __COLA_H__

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
	 * Estructura auxiliar de la cola. Es privada y no debe usarse bajo ning�n
	 * concepto en la aplicaci�n.
	 */
	typedef struct TNodoCola
	{
		void* Elem;
		struct TNodoCola *Sig;
	} TNodoCola;
	
	/**
	 * Estructura cabecera, este es el tipo que se deber� instanciar, aunque
	 * nunca acceder a sus campos.
	 */
	typedef struct
	{
		TNodoCola *Primero, *Ultimo;
		int TamanioDato;
	} TColaOLD;
	
	/*C_OLD_CREAR
	Pre: C no fue creada.
	Post: C creada y vac�a. */
	void C_OLD_Crear(TColaOLD *pC, int TamanioDato);
	
	/*C_OLD_VACIAR
	Pre: C creada.
	Post: C vac�a. */
	void C_OLD_Vaciar(TColaOLD *pC);
	
	/*C_OLD_VACIA
	Pre: C creada.
	Post: Si C est� vac�a devuelve TRUE, sino FALSE. */
	int C_OLD_Vacia(TColaOLD C);
	
	/*C_OLD_AGREGAR
	Pre: C creada.
	Post: E se agreg� como �ltimo elemento de C.
	Devuelve FALSE si no pudo agregar E, sino devuelve TRUE.*/
	int C_OLD_Agregar(TColaOLD *pC, void* pE);
	
	/*C_OLD_SACAR
	Pre: C creada y no vac�a.
	Post: Se extrajo de C el primer elemento y se devuelve en E.
	Si no pudo extraer el elemento (porque C estaba vac�a) devuelve FALSE,
	sino devuelve TRUE.*/
	int C_OLD_Sacar(TColaOLD *pC, void* pE);
#endif

