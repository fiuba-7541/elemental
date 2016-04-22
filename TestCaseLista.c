/*
 * ListaTestCase.c
 *
 *  Created on: 02/04/2011
 *      Author: anibal
 */


#include "Lista.h"
#include "TDATestCase.h"

void destruirInt(void* e);
int copiarInt(void* destino, void* origen);

void destruirString(void* e);
int copiarString(void* destino, void* origen);

void testListaFillAndScan(){
	TListaSimple l;

	LS_Crear(&l, sizeof(int), copiarInt, destruirInt);
	int i;
	for(i=0; i<100; i++){
		LS_Insertar_Cte(&l, LS_Siguiente, &i);
	}
	assertFalse(LS_Vacia(l));

	LS_Mover_Cte(&l, LS_Primero);
	for(i=0; i<100; i++){
		int j = 0;
		LS_Elem_Cte(l, &j);
		LS_Mover_Cte(&l, LS_Siguiente);
		assertEqualsInt(i, j);
	}
	assertFalse(LS_Vacia(l));

	LS_Vaciar(&l);
	assertTrue(LS_Vacia(l));
}

void testListaFillAndEmpty(){
	TListaSimple l;
	char** cadenas;
	char* cadena;
	int i=0;

	LS_Crear(&l, sizeof(char*), copiarString, destruirString);
	cadenas = (char**) malloc (5 * sizeof(char*));
	for(i=0; i<5; i++){
		cadenas[i] = (char*) malloc(16 * sizeof(char));
	}
	strcpy(cadenas[0], "cadena 0");
	strcpy(cadenas[1], "cadena 1");
	strcpy(cadenas[2], "cadena 2");
	strcpy(cadenas[3], "cadena 3");
	strcpy(cadenas[4], "cadena 4");

	for(i=0; i<5; i++){
		LS_Insertar_Cte(&l, LS_Siguiente, cadenas+i);
	}

	LS_Mover_Cte(&l, LS_Primero);
	for(i=0; i<5; i++){
		LS_Elem_Cte(l, &cadena);
		assertEqualsString(cadenas[i], cadena);
		LS_Borrar_Cte(&l);
	}

	assertTrue(LS_Vacia(l));

	for(i=0; i<5; i++){
		free(cadenas[i]);
	}
	free(cadenas);
}
