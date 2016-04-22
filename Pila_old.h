#ifndef __PILA_H__
	#define __PILA_H__
	
	#include <malloc.h>
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
	 * Estructura auxiliar de la pila. Es privada y no debe usarse bajo ningún
	 * concepto en la aplicación.
	 */
	typedef struct TNodoPila
	{
		void* Elem;
		struct TNodoPila *Siguiente;
	} TNodoPila;
	
	/**
	 * Estructura cabecera, este es el tipo que se deberá instanciar, aunque
	 * nunca acceder a sus campos.
	 */
	typedef struct
	{
		TNodoPila *Tope;
		int TamanioDato;
	} TPilaOLD;
	
	/*P_CREAR
	Pre: P no fue creada.
	Post: P creada y vacía. */
	void P_OLD_Crear(TPilaOLD *pP, int TamanioDato);
	
	/*P_OLD_VACIAR
	Pre: P creada.
	Post: P vacía. */
	void P_OLD_Vaciar(TPilaOLD *pP);
	
	/*P_OLD_VACIA
	Pre: P creada.
	Post: Si P está vacía devuelve TRUE, sino FALSE. */
	int P_OLD_Vacia(TPilaOLD P);
	
	/*P_OLD_PONER
	Pre: P creada.
	Post: E se agregó como Tope de P.
	Devuelve FALSE si no pudo ADD E, sino devuelve TRUE.*/
	int P_OLD_Poner(TPilaOLD *pP, void* pE);
	
	/*P_OLD_SACAR
	Pre: P creada y no Vacía.
	Post: Se extrajo de P el Tope y se devuelve en E.
	Si no pudo extraer el elemento (porque la Stack estaba vacía) devuelve FALSE,
	sino devuelve TRUE.*/
	int P_OLD_Sacar(TPilaOLD *pP, void* pE);

#endif

