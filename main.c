/*
 * main.c
 *
 *  Created on: 31/10/2010
 *      Author: anibal
 */

#include <stdio.h>

#include "TDATestCase.h"

#include "test_case_stack.h"
#include "test_case_queue.h"
#include "test_case_straight_list.h"


#include "TestCasePila.h"
#include "TestCaseCola.h"
#include "TestCaseLista.h"
#include "TestCaseAB.h"
#include "TestCaseABO.h"
#include "TestCaseSet.h"

void destruir_int(void* e){}

int copiar_int(void* destino, void* origen)
{
	int* d = (int*) destino;
	int* o = (int*) origen;
	*d = *o;
	return 0;
}

void destruirInt(void* e){}

int copiarInt(void* destino, void* origen)
{
	int* d = (int*) destino;
	int* o = (int*) origen;
	*d = *o;
	return 0;
}

void destruir_string(void* e){
	char** d = (char**) e;
	free(*d);
}

int copiar_string(void* destino, void* origen)
{
	char** d = (char**) destino;
	char** o = (char**) origen;
	int len = strlen(*o);
	*d = malloc((len+1) * sizeof(char));
	strcpy(*d, *o);
	return 0;
}

void destruirString(void* e){
	char** d = (char**) e;
	free(*d);
}

int copiarString(void* destino, void* origen)
{
	char** d = (char**) destino;
	char** o = (char**) origen;
	int len = strlen(*o);
	*d = malloc((len+1) * sizeof(char));
	strcpy(*d, *o);
	return 0;
}

void testLPC(TestCase *testcase)
{
	TestPtr test;
    test = testPilaFillAndEmpty; /* 00 */
    addTest(testcase, test);
    test = testColaFillAndEmpty; /* 01 */
    addTest(testcase, test);
    test = testListaFillAndScan; /* 02 */
    addTest(testcase, test);
    test = testListaFillAndEmpty; /* 03 */
    addTest(testcase, test);

    test = test_stack_fill_and_empty; /* 00' */
    addTest(testcase, test);
    test = test_queue_fill_and_empty; /* 01' */
    addTest(testcase, test);
    test = test_straight_list_fill_and_scan; /* 02' */
    addTest(testcase, test);
    test = test_straight_list_fill_and_empty; /* 03' */
    addTest(testcase, test);
}

void testAB(TestCase *testcase)
{
    TestPtr test;
    test = testArbolFillAndPrintInOrden; /* 04 */
    addTest(testcase, test);
    test = testArbolFillAndPrintPreOrden; /* 05 */
    addTest(testcase, test);
}

void testABO(TestCase *testcase)
{
	TestPtr test;
	test = testAboFillAndPrint;		/* 06 */
	addTest(testcase, test);
	test = testAboFillAndDelete; 	/* 07 */
	addTest(testcase, test);
	test = testAboFillAndDelete2;	/* 08 */
	addTest(testcase, test);
	test = testAboFillAndDelete3;	/* 09 */
	addTest(testcase, test);
	test = testAboRecorrerInOrder;	/* 10 */
	addTest(testcase, test);
	test = testAboRecorrerPreOrder;	/* 11 */
	addTest(testcase, test);
	test = testAboRecorrerPosOrder;	/* 12 */
	addTest(testcase, test);
	test = testAboRecorrerEnRangoInOrder;	/* 13 */
	addTest(testcase, test);
}

void testSet(TestCase *testcase) {
	TestPtr test;
    test = testSetFill; /* 17 */
    addTest(testcase, test);
    test = testSetFillAndScan; /* 18 */
    addTest(testcase, test);
    test = testSetFillAndEmpty; /* 19 */
    addTest(testcase, test);
}

int main(int argc, char** argv){
	TestCase testcase;
	_init_testcase(&testcase);

	printf("LPC tests...\n");
	fflush(stdout);
    testLPC(&testcase);

    /*
	printf("AB tests...\n");
	fflush(stdout);
	testAB(&testcase);

	printf("ABO tests...\n");
	fflush(stdout);
	testABO(&testcase);

	printf("set tests...\n");
	fflush(stdout);
    testSet(&testcase);
	*/
	printf("all tests loaded.\n");
	printf("firing tests now...\n");
	fflush(stdout);

	fireAllTests(&testcase);

	printf("all tests passed ok.\n");

	return 0;
}
