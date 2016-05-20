/*
 * PilaTestCase.c
 *
 *  Created on: 02/04/2011
 *      Author: anibal
 */

#include "stack.h"
#include "TDATestCase.h"

void destruir_int(void* e);
int copiar_int(void* destino, const void* origen);

void test_stack_fill_and_empty(){
	stack_t p;

	stack_create(&p, sizeof(int), copiar_int, destruir_int);
	int i;
	for(i=0; i<100; i++){
		stack_push(&p, &i);
	}
	assertFalse(stack_is_empty(&p));
	for(i=99; i>=0; i--){
		int j = 0;
		stack_pop(&p, &j);
		assertEqualsInt(i, j);
	}
	assertTrue(stack_is_empty(&p));

	stack_destroy(&p);
}
