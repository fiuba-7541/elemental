/*
 * TDATestCase.h
 *
 *  Created on: 31/10/2010
 *      Author: anibal
 */

#ifndef TDATESTCASE_H_
#define TDATESTCASE_H_

#include <stdio.h>
#include "var_array.h"

typedef void (*TestPtr) ();

typedef struct TestCase {
	V_Array tests;
} TestCase;

int _init_testcase(TestCase * this);

void addTest(TestCase * this, TestPtr test);

void fireAllTests(TestCase* this);

void assertTrue(int val);

void assertFalse(int val);

void assertEqualsInt(int expected, int actual);

void assertEqualsString(char* expected, char* actual);

void assertEqualsChar(char expected, char actual);

void assertEqualsDouble(double expected, double actual, double tolerance);

#endif /* TDATESTCASE_H_ */
