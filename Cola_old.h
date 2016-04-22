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
	 * Estructura auxiliar de la cola. Es privada y no debe usarse bajo ningún
	 * concepto en la aplicación.
	 */
	typedef struct TNodoCola
	{
		void* Elem;
		struct TNodoCola *Sig;
	} TNodoCola;
	
	/**
	 * Estructura cabecera, este es el tipo que se deberá instanciar, aunque
	 * nunca acceder a sus campos.
	 */
	typedef struct
	{
		TNodoCola *Primero, *Ultimo;
		int TamanioDato;
	} TColaOLD;
	
	/*C_OLD_CREAR
	Pre: C no fue creada.
	Post: C creada y vacï¿½a. */
	void C_OLD_Crear(TColaOLD *pC, int TamanioDato);
	
	/*C_OLD_VACIAR
	Pre: C creada.
	Post: C vacï¿½a. */
	void C_OLD_Vaciar(TColaOLD *pC);
	
	/*C_OLD_VACIA
	Pre: C creada.
	Post: Si C estï¿½ vacï¿½a devuelve TRUE, sino FALSE. */
	int C_OLD_Vacia(TColaOLD C);
	
	/*C_OLD_AGREGAR
	Pre: C creada.
	Post: E se agregï¿½ como ï¿½ltimo elemento de C.
	Devuelve FALSE si no pudo agregar E, sino devuelve TRUE.*/
	int C_OLD_Agregar(TColaOLD *pC, void* pE);
	
	/*C_OLD_SACAR
	Pre: C creada y no vacï¿½a.
	Post: Se extrajo de C el primer elemento y se devuelve en E.
	Si no pudo extraer el elemento (porque C estaba vacï¿½a) devuelve FALSE,
	sino devuelve TRUE.*/
	int C_OLD_Sacar(TColaOLD *pC, void* pE);
#endif

