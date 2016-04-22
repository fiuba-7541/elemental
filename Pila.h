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
	 * Tipo puntero a funci�n de copia de los elementos de la pila. Esta es la
	 * funci�n que se invocar� al recibir un elemento para almacenar en la
	 * estructura, de manera que se admita la posibilidad de almacenar copias
	 * profundas de los elementos en la pila.
	 */
	typedef int (*P_copiar) (void* destino, void* origen);

	/**
	 * Tipo puntero a funci�n de destrucci�n de los elementos de la pila. Esta
	 * es la funci�n que se invocar� al destruir un elemento. Debe encargarse de
	 * liberar todos los recursos alocados en un elemento cualquiera de la pila
	 * para as� evitar cualquier p�rdida de memoria.
	 */
	typedef void (*P_destruir) (void*);

	/**
	 * Estructura auxiliar de la pila. Es privada y no debe usarse bajo ning�n
	 * concepto en la aplicaci�n.
	 */
	typedef struct TNodoPila
	{
		void* Elem;
		struct TNodoPila *Siguiente;
	} TNodoPila;
	
	/**
	 * Estructura cabecera, este es el tipo que se deber� instanciar, aunque
	 * nunca acceder a sus campos.
	 */
	typedef struct
	{
		TNodoPila *Tope;
		int TamanioDato;
		P_copiar f_copia;
		P_destruir f_destruccion;
	} TPila;
	
	/*P_CREAR
	Pre: P no fue creada.
	Post: P creada y vac�a. */
	void P_Crear(TPila *pP, int TamanioDato, P_copiar f_copia, P_destruir f_destruccion);
	
	/*P_DESTRUIR
	Pre: P creada.
	Post: P destruida. Todos los recursos utilizados liberados */
	void P_Destruir(TPila *pP);

	/*P_VACIAR
	Pre: P creada.
	Post: P vac�a. */
	void P_Vaciar(TPila *pP);
	
	/*P_VACIA
	Pre: P creada.
	Post: Si P est� vac�a devuelve TRUE, sino FALSE. */
	int P_Vacia(TPila P);
	
	/*P_PONER
	Pre: P creada.
	Post: E se agreg� como Tope de P.
	Devuelve FALSE si no pudo ADD E, sino devuelve TRUE.*/
	int P_Poner(TPila *pP, void* pE);
	
	/*P_SACAR
	Pre: P creada y no Vac�a.
	Post: Se extrajo de P el Tope y se devuelve en E.
	Si no pudo extraer el elemento (porque la Stack estaba vac�a) devuelve FALSE,
	sino devuelve TRUE.*/
	int P_Sacar(TPila *pP, void* pE);

#endif

