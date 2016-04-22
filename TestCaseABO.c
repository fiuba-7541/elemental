/*
 * TestCaseAB.c
 *
 *  Created on: 01/06/2011
 *      Author: anibal
 */

#include "TestCaseABO.h"

int cloneIntABO(void* dst, const void* src){
	*((int*)dst) = *((int*)src);
	return RES_OK;
}

void destroyIntABO(void* e) {
	/*do nothing*/
}

int intAsVoidCompare(void* a, void* b){
	int i = *((int*) a);
	int j = *((int*) b);
	return i - j;
}

void aboRecorrerImprimiendo(TABO a){
	int i=0, j, k=1, resCmp=0;
	for(j=1; i<100; i++){ /* genero unos numeros desordenados */
		k=j=(j+37)%100;
		resCmp = ABO_Obtener(&a, &k);
		assertEqualsInt(RES_OK, resCmp);
		assertEqualsInt(k, j);
	}

}

void testAboFillAndPrint(){
	int i=0, j=0;
	TABO a;
	ABO_Crear(&a, intAsVoidCompare, sizeof(int), cloneIntABO, destroyIntABO);
	for(j=1; i<100; i++){ /* genero unos numeros desordenados */
		j=(j+37)%100;
		ABO_Insertar(&a, &j);
	}
	aboRecorrerImprimiendo(a);
}

void testAboFillAndDelete(){
	int i=0, j=0, k=0, resCmp=0;
	TABO a;
	ABO_Crear(&a, intAsVoidCompare, sizeof(int), cloneIntABO, destroyIntABO);
	j=0;
	for(i=0; i<10; i++){ /* genero unos numeros desordenados */
		j=(j+37)%100;
		ABO_Insertar(&a, &j);
	}
	j=0;
	for(i=0; i<10; i++){
		k=j=(j+37)%100;
		resCmp = ABO_Obtener(&a, &k);
		assertEqualsInt(RES_OK, resCmp);
		assertEqualsInt(k, j);
	}

	j=0;
	for(i=0; i<10; i++){
		k=j=(j+37)%100;
		resCmp = ABO_Borrar(&a, &k);
		assertEqualsInt(RES_OK, resCmp);
		resCmp = ABO_Obtener(&a, &k);
		assertEqualsInt(RES_ELEMENTO_NO_EXISTE, resCmp);
	}

}

void recorridoInOrden(TAB ab, int* valorPrevio, int movimiento){
	int valorCorriente;
	if(!AB_MoverCte(&ab, movimiento)){
		return;
	}
	recorridoInOrden(ab, valorPrevio, IZQ);

	AB_ElemCte(ab, &valorCorriente);
/*	printf("%d\t%d\n", *valorPrevio, valorCorriente); */
	assertTrue(valorCorriente > *valorPrevio);
	*valorPrevio = valorCorriente;

	recorridoInOrden(ab, valorPrevio, DER);
}

void testAboFillAndDelete2(){
	int i=0, j=0;
	TABO a;
	ABO_Crear(&a, intAsVoidCompare, sizeof(int), cloneIntABO, destroyIntABO);
	j=0;
	for(i=0; i<10; i++){ /* genero unos numeros desordenados */
		j=(j+37)%100;
		ABO_Insertar(&a, &j);
	}

	/* para ver si realmente qued� ordenado como quer�a violo abstracci�n
	 * pero porque se trata de una prueba de la capa ABO*/
	{
		TAB* ab = &(a.a);
		j=0;
		recorridoInOrden(*ab, &j, RAIZ);
	}
}

void testAboFillAndDelete3(){
	int i=0, j=0;
	TABO a;
	ABO_Crear(&a, intAsVoidCompare, sizeof(int), cloneIntABO, destroyIntABO);
	j=0;
	for(i=0; i<10; i++){ /* genero unos numeros desordenados */
		j=(j+37)%100;
		ABO_Insertar(&a, &j);
	}

	/* para ver si realmente qued� ordenado como quer�a violo abstracci�n
	 * pero porque se trata de una prueba de la capa ABO*/
	{
		TAB* ab = &(a.a);
		j=70;
		ABO_Borrar(&a, &j);
		j=0;
		recorridoInOrden(*ab, &j, RAIZ);
	}
}

int addRecursively(void* elem, void* args){
	int value = *((int*)elem);
	int* partialSum = (int*) args;
	*partialSum += value;
	return RES_OK;
}

void testAboRecorrerInOrder(){
	int i=0, j=0, sum=0;
	TABO a;
	ABO_Crear(&a, intAsVoidCompare, sizeof(int), cloneIntABO, destroyIntABO);
	j=0;
	for(i=0; i<10; i++){ /* genero unos numeros desordenados */
		j=(j+37)%100;
		sum+=j;
		ABO_Insertar(&a, &j);
	}

	j=0;
	ABO_ProcesarInOrden(&a, addRecursively, &j);
	assertEqualsInt(sum, j);

}

void testAboRecorrerPreOrder(){
	int i=0, j=0, sum=0;
	TABO a;
	ABO_Crear(&a, intAsVoidCompare, sizeof(int), cloneIntABO, destroyIntABO);
	j=0;
	for(i=0; i<10; i++){ /* genero unos numeros desordenados */
		j=(j+37)%100;
		sum+=j;
		ABO_Insertar(&a, &j);
	}

	j=0;
	ABO_ProcesarPreOrden(&a, addRecursively, &j);
	assertEqualsInt(sum, j);

}

void testAboRecorrerPosOrder(){
	int i=0, j=0, sum=0;
	TABO a;
	ABO_Crear(&a, intAsVoidCompare, sizeof(int), cloneIntABO, destroyIntABO);
	j=0;
	for(i=0; i<10; i++){ /* genero unos numeros desordenados */
		j=(j+37)%100;
		sum+=j;
		ABO_Insertar(&a, &j);
	}

	j=0;
	ABO_ProcesarPosOrden(&a, addRecursively, &j);
	assertEqualsInt(sum, j);

}

void testAboRecorrerEnRangoInOrder(){
	int i=0, j=0, sum=0;
	int desde=40, hasta=80;
	TABO a;
	ABO_Crear(&a, intAsVoidCompare, sizeof(int), cloneIntABO, destroyIntABO);
	j=0;
	for(i=0; i<10; i++){ /* genero unos numeros desordenados */
		j=(j+37)%100;
		sum+=( (j>=desde) && (j<=hasta) )?j:0;
		ABO_Insertar(&a, &j);
	}

	j=0;
	ABO_ProcesarEnRangoInOrden(&a, addRecursively, &j, &desde, &hasta);
	assertEqualsInt(sum, j);

}
