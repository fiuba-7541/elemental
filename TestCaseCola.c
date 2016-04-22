/*
 * ColaTestCase.c
 *
 *  Created on: 02/04/2011
 *      Author: anibal
 */

#include "Cola.h"
#include "TDATestCase.h"

void destruirInt(void* e);
int copiarInt(void* destino, void* origen);

void testColaFillAndEmpty(){
	TCola c;

	C_Crear(&c, sizeof(int), copiarInt, destruirInt);
	int i;
	for(i=0; i<100; i++){
		C_Agregar(&c, &i);
	}
	assertFalse(C_Vacia(c));
	for(i=0; i<100; i++){
		int j;
		C_Sacar(&c, &j);
		assertEqualsInt(i, j);
	}
	assertTrue(C_Vacia(c));

	C_Vaciar(&c);
}
