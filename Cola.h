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
	 * Tipo puntero a función de copia de los elementos de la cola. Esta es la
	 * función que se invocará al recibir un elemento para almacenar en la
	 * estructura, de manera que se admita la posibilidad de almacenar copias
	 * profundas de los elementos en la cola.
	 */
	typedef int (*C_copiar) (void* destino, void* origen);

	/**
	 * Tipo puntero a función de destrucción de los elementos de la cola. Esta
	 * es la función que se invocará al destruir un elemento. Debe encargarse de
	 * liberar todos los recursos alocados en un elemento cualquiera de la cola
	 * para así evitar cualquier pérdida de memoria.
	 */
	typedef void (*C_destruir) (void*);
	
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
		C_copiar f_copia;
		C_destruir f_destruccion;
	} TCola;
	
	/*C_CREAR
	Pre: C no fue creada.
	Post: C creada y vacï¿½a. */
	void C_Crear(TCola *pC, int TamanioDato, C_copiar f_copia, C_destruir f_destruccion);
	
	/*C_DESTRUIR
	Pre: C creada.
	Post: C destruida. Todos los recursos utilizados liberados */
	void C_Destruir(TCola *pC);

	/*C_VACIAR
	Pre: C creada.
	Post: C vacï¿½a. */
	void C_Vaciar(TCola *pC);
	
	/*C_VACIA
	Pre: C creada.
	Post: Si C estï¿½ vacï¿½a devuelve TRUE, sino FALSE. */
	int C_Vacia(TCola C);
	
	/*C_AGREGAR
	Pre: C creada.
	Post: E se agregï¿½ como ï¿½ltimo elemento de C.
	Devuelve FALSE si no pudo agregar E, sino devuelve TRUE.*/
	int C_Agregar(TCola *pC, void* pE);
	
	/*C_SACAR
	Pre: C creada y no vacï¿½a.
	Post: Se extrajo de C el primer elemento y se devuelve en E.
	Si no pudo extraer el elemento (porque C estaba vacï¿½a) devuelve FALSE,
	sino devuelve TRUE.*/
	int C_Sacar(TCola *pC, void* pE);
#endif

