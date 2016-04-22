/*
 * TestCaseAB.c
 *
 *  Created on: 01/06/2011
 *      Author: anibal
 */

#include "TestCaseAB.h"

int cloneInt(void* dst, const void* src){
	*((int*)dst) = *((int*)src);
	return RES_OK;
}

void destroyInt(void* e) {
	/*do nothing*/
}

void testArbolFillAndPrintInOrden(){
	int i, j;
	TAB a;
	AB_Crear(&a, sizeof(int), cloneInt, destroyInt);

	i=0;
	AB_Insertar(&a, RAIZ, &i);

	for(i=1; i<100; i++){
		AB_Insertar(&a, DER, &i);
	}

	AB_MoverCte(&a, RAIZ);

	for(i=0; i<100; i++){
		AB_ElemCte(a, &j);
		assertEqualsInt(i, j);
		AB_MoverCte(&a, DER);
	}
}

void testArbolFillAndPrintPreOrden(){
	int i, j;
	TAB a;
	AB_Crear(&a, sizeof(int), cloneInt, destroyInt);

	i=0;
	AB_Insertar(&a, RAIZ, &i);
	i=1;
	AB_Insertar(&a, IZQ, &i);
	AB_MoverCte(&a, PAD);
	i=2;
	AB_Insertar(&a, DER, &i);

	AB_MoverCte(&a, RAIZ);
	AB_ElemCte(a, &j);
	i=0;
	assertEqualsInt(i, j);

	AB_MoverCte(&a, IZQ);
	AB_ElemCte(a, &j);
	AB_MoverCte(&a, PAD);
	i=1;
	assertEqualsInt(i, j);

	AB_MoverCte(&a, DER);
	AB_ElemCte(a, &j);
	AB_MoverCte(&a, PAD);
	i=2;
	assertEqualsInt(i, j);

}
