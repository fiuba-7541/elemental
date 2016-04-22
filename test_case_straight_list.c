/*
 * ListaTestCase.c
 *
 *  Created on: 02/04/2011
 *      Author: anibal
 */


#include "straight_list.h"
#include "test_case_straight_list.h"
#include "TDATestCase.h"

void destruir_int(void* e);
int copiar_int(void* destino, const void* origen);

void destruir_string(void* e);
int copiar_string(void* destino, const void* origen);

void test_straight_list_fill_and_scan(){
	straight_list_t l;

	straight_list_create(&l, sizeof(int), copiar_int, destruir_int);
	int i;
	for(i=0; i<100; i++){
		straight_list_insert(&l, straight_list_next, &i);
	}
	assertFalse(straight_list_is_empty(&l));

	straight_list_move(&l, straight_list_first);
	for(i=0; i<100; i++){
		int j = 0;
		straight_list_get(&l, &j);
		straight_list_move(&l, straight_list_next);
		assertEqualsInt(i, j);
	}
	assertFalse(straight_list_is_empty(&l));

	straight_list_clear(&l);
	assertTrue(straight_list_is_empty(&l));
}

void test_straight_list_fill_and_empty(){
	straight_list_t l;
	char** cadenas;
	char* cadena;
	int i=0;

	straight_list_create(&l, sizeof(char*), copiar_string, destruir_string);
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
		straight_list_insert(&l, straight_list_next, cadenas+i);
	}

	straight_list_move(&l, straight_list_first);
	for(i=0; i<5; i++){
		straight_list_get(&l, &cadena);
		assertEqualsString(cadenas[i], cadena);
		straight_list_delete(&l);
	}

	assertTrue(straight_list_is_empty(&l));

	for(i=0; i<5; i++){
		free(cadenas[i]);
	}
	free(cadenas);
}
