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
	 * Tipo puntero a funci�n de copia de los elementos de la cola. Esta es la
	 * funci�n que se invocar� al recibir un elemento para almacenar en la
	 * estructura, de manera que se admita la posibilidad de almacenar copias
	 * profundas de los elementos en la cola.
	 */
	typedef int (*C_copiar) (void* destino, void* origen);

	/**
	 * Tipo puntero a funci�n de destrucci�n de los elementos de la cola. Esta
	 * es la funci�n que se invocar� al destruir un elemento. Debe encargarse de
	 * liberar todos los recursos alocados en un elemento cualquiera de la cola
	 * para as� evitar cualquier p�rdida de memoria.
	 */
	typedef void (*C_destruir) (void*);
	
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
		C_copiar f_copia;
		C_destruir f_destruccion;
	} TCola;
	
	/*C_CREAR
	Pre: C no fue creada.
	Post: C creada y vac�a. */
	void C_Crear(TCola *pC, int TamanioDato, C_copiar f_copia, C_destruir f_destruccion);
	
	/*C_DESTRUIR
	Pre: C creada.
	Post: C destruida. Todos los recursos utilizados liberados */
	void C_Destruir(TCola *pC);

	/*C_VACIAR
	Pre: C creada.
	Post: C vac�a. */
	void C_Vaciar(TCola *pC);
	
	/*C_VACIA
	Pre: C creada.
	Post: Si C est� vac�a devuelve TRUE, sino FALSE. */
	int C_Vacia(TCola C);
	
	/*C_AGREGAR
	Pre: C creada.
	Post: E se agreg� como �ltimo elemento de C.
	Devuelve FALSE si no pudo agregar E, sino devuelve TRUE.*/
	int C_Agregar(TCola *pC, void* pE);
	
	/*C_SACAR
	Pre: C creada y no vac�a.
	Post: Se extrajo de C el primer elemento y se devuelve en E.
	Si no pudo extraer el elemento (porque C estaba vac�a) devuelve FALSE,
	sino devuelve TRUE.*/
	int C_Sacar(TCola *pC, void* pE);
#endif

