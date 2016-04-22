#include "TDATestCase.h"

int _init_testcase(TestCase* this){
	return VA_create(&(this->tests), sizeof(TestPtr));
}

void fireAllTests(TestCase* this){
	int i=0;
	int n = VA_count(this->tests);
	TestPtr currentTest;
	for (i=0; i<n; i++){
		VA_get_i(this->tests, i, &currentTest);
		currentTest();
		printf("test nro: %d ejecutado correctamente\n", i);
		fflush(stdout);
	}
}

void assertTrue(int val){
	if(!val){
		fprintf(stderr, "Assertion failed. True value expected and resulted false.\n");
		fflush(stderr);
		exit(-1);
	}
}

void assertFalse(int val){
	if(val){
		fprintf(stderr, "Assertion failed. False value expected and resulted true.\n");
		fflush(stderr);
		exit(-1);
	}
}

void assertEqualsInt(int expected, int actual){
	if(expected!=actual){
		fprintf(stderr, "Assertion failed. Expected value %d and resulted %d.\n", expected, actual);
		fflush(stderr);
		exit(-1);
	}
}

void assertEqualsString(char* expected, char* actual){
	int cmp = strcmp(expected, actual);
	if(cmp){
		fprintf(stderr, "Assertion failed. Expected value %s and resulted %s.\n", expected, actual);
		fflush(stderr);
		exit(-1);
	}
}

void assertEqualsDouble(double expected, double actual, double tolerance){
	int cmp = actual<(expected-tolerance) || actual>(expected+tolerance);
	if(cmp){
		fprintf(stderr, "Assertion failed. Expected value %f and resulted %f.\n", expected, actual);
		fflush(stderr);
		exit(-1);
	}
}

void assertEqualsChar(char expected, char actual){
	int cmp = expected!=actual;
	if(cmp){
		fprintf(stderr, "Assertion failed. Expected value %c and resulted %c.\n", expected, actual);
		fflush(stderr);
		exit(-1);
	}
}

void addTest(TestCase* this, TestPtr aTest){
	VA_add(&(this->tests), &aTest);
}
