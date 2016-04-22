/*
 * tda_set.c
 *
 *  Created on: 15/08/2012
 *      Author: Aníbal
 */

#include "set.h"

int TS_Crear(StrSet *set){
	return VA_create(&(set->array), sizeof(char*));
}

int TS_Destruir(StrSet *set){
	int i, count;
	char** baseArray;
	count = VA_count(set->array);
	baseArray = (char**) VA_get(&(set->array));
	for (i = 0; i < count; ++i) {
		free(baseArray[i]);
	}
	VA_destroy(&(set->array));
	return RES_OK;
}

int txtcmp (void* a, void* b) {
	return strcmp( *((char**)a), *((char**)b) );
}

int TS_Add(StrSet *set, char* e) {
	char *tmp;
	int res;
	/* hago una copia defensiva del dato que inserto en el set */
	tmp = (char*) malloc( (strlen(e)+1) * sizeof(char) );
	strcpy(tmp, e);
	res = VA_add(&(set->array), &tmp);

	printf("TS_Add: VA added\n");
	fflush(stdout);

	VA_sort(&(set->array), txtcmp);

	return res;
}

int TS_Remove(StrSet *set, char* e) {
	int i, count = VA_count(set->array);
	/* FIXME: cambiar por una búsqueda binaria, utilizada también en el TS_Contains */
	for(i=0; i < count; i++) {
		char* current;
		int res = 0;
		VA_get_i(set->array, i, &current);
		res = strcmp(current, e);
		if (!res) {
			free(current);
			VA_remove(&(set->array), i);
			return RES_OK; /* si lo encontré, lo borro y estamos, así que salgo*/
		} else if (res > 0) {
			return RES_NO_ENCONTRADO; /* si me pasé (está ordenado) no sigo recorriendo */
		}
	}
	return RES_NO_ENCONTRADO; /* si llegué hasta acá, es porque no lo encontré */
}

int TS_Contains(const StrSet *set, char* e) {
	int i, count = VA_count(set->array);
	for(i=0; i < count; i++) {
		char* current;
		int res = 0;
		VA_get_i(set->array, i, &current);
		res = strcmp(current, e);
		if (!res) {
			return RES_ENCONTRADO; /* si lo encontré, lo borro y estamos, así que salgo*/
		} else if (res > 0) {
			return RES_NO_ENCONTRADO; /* si me pasé (está ordenado) no sigo recorriendo */
		}
	}
	return RES_NO_ENCONTRADO; /* si llegué hasta acá, es porque no lo encontré */
}

int TS_Count(const StrSet *set) {
	return VA_count(set->array);
}
