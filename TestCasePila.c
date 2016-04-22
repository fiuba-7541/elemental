/*
 * PilaTestCase.c
 *
 *  Created on: 02/04/2011
 *      Author: anibal
 */

#include "Pila.h"
#include "TDATestCase.h"

void destruirInt(void* e);
int copiarInt(void* destino, void* origen);

void testPilaFillAndEmpty(){
	TPila p;

	P_Crear(&p, sizeof(int), copiarInt, destruirInt);
	int i;
	for(i=0; i<100; i++){
		P_Poner(&p, &i);
	}
	assertFalse(P_Vacia(p));
	for(i=99; i>=0; i--){
		int j = 0;
		P_Sacar(&p, &j);
		assertEqualsInt(i, j);
	}
	assertTrue(P_Vacia(p));

	P_Vaciar(&p);
}
