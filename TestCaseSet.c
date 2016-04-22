/*
 * ListaTestCase.c
 *
 *  Created on: 02/04/2011
 *      Author: anibal
 */


#include "TestCaseSet.h"

void testSetFill(){
	StrSet set;
	char *uno = "uno", *dos = "dos", *tres = "tres", *cuatro = "cuatro";
	TS_Crear(&set);

	printf("creacion completa\n");
	fflush(stdout);
	TS_Add(&set, uno);
	TS_Add(&set, dos);
	TS_Add(&set, tres);
	TS_Add(&set, cuatro);

	printf("Todos los elementos agregados correctamente\n");
	fflush(stdout);
	assertEqualsInt(4, TS_Count(&set));

	TS_Destruir(&set);
}


void testSetFillAndScan(){
	StrSet set;
	char *uno = "uno", *dos = "dos", *tres = "tres", *cuatro = "cuatro";
	TS_Crear(&set);

	TS_Add(&set, uno);
	TS_Add(&set, dos);
	TS_Add(&set, tres);
	TS_Add(&set, cuatro);

	assertEqualsInt(4, TS_Count(&set));

	assertTrue(TS_Contains(&set, uno));
	assertTrue(TS_Contains(&set, dos));
	assertTrue(TS_Contains(&set, tres));
	assertTrue(TS_Contains(&set, cuatro));

	TS_Destruir(&set);
}

void testSetFillAndEmpty(){
	StrSet set;
	char *uno = "uno", *dos = "dos", *tres = "tres", *cuatro = "cuatro";
	TS_Crear(&set);

	TS_Add(&set, uno);
	TS_Add(&set, dos);
	TS_Add(&set, tres);
	TS_Add(&set, cuatro);

	assertEqualsInt(4, TS_Count(&set));

	assertTrue(TS_Contains(&set, uno));
	assertTrue(TS_Contains(&set, dos));
	assertTrue(TS_Contains(&set, tres));
	assertTrue(TS_Contains(&set, cuatro));

	TS_Remove(&set, uno);
	assertEqualsInt(3, TS_Count(&set));
	TS_Remove(&set, dos);
	assertEqualsInt(2, TS_Count(&set));
	TS_Remove(&set, tres);
	assertEqualsInt(1, TS_Count(&set));
	TS_Remove(&set, cuatro);
	assertEqualsInt(0, TS_Count(&set));

	TS_Destruir(&set);
}
