/*
 * ColaTestCase.c
 *
 *  Created on: 02/04/2011
 *      Author: anibal
 */

#include "queue.h"
#include "TDATestCase.h"

void destruir_int(void* e);
int copiar_int(void* destino, const void* origen);

void test_queue_fill_and_empty(){
	queue_t qp;

	queue_create(&qp, sizeof(int), copiar_int, destruir_int);
	int i;
	for(i=0; i<100; i++){
		queue_push(&qp, &i);
	}
	assertFalse(queue_is_empty(&qp));
	for(i=0; i<100; i++){
		int j;
		queue_pop(&qp, &j);
		assertEqualsInt(i, j);
	}
	assertTrue(queue_is_empty(&qp));

	queue_destroy(&qp);
}
