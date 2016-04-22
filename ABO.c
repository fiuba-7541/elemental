/*
 * ABO.c
 *
 *  Created on: 01/06/2011
 *      Author: anibal
 */

#include "ABO.h"

int buscarElem(TABO* abo, void* elem, int* mov){
	void* currElem;
	int resMov, resCmp;
	resMov = AB_MoverCte(&(abo->a), *mov);
	if(!resMov){
		return resMov; /* Condicion de corte */
	}
	currElem = malloc(abo->tamanio);
	if(!currElem){
		return RES_OUT_OF_MEMORY; /* Condicion de corte por error */
	}
	AB_ElemCte(abo->a, currElem);
	resCmp = abo->fcmp(currElem, elem);
	free(currElem);
	if(resCmp < 0) { /* si curr es menor, debo seguir hacia la derecha */
		*mov = DER;
	}
	if(resCmp > 0){ /* si curr es mayor, debo seguir hacia la izquierda */
		*mov = IZQ;
	}
	if(resCmp == 0){ /* si son iguales, lo encontre */
		return TRUE; /* Condicion de corte */
	} else {
		return buscarElem(abo, elem, mov); /* Llamado recursivo */
	}
}

int elegirResultadoParaRecorrido(int resProcess, int resIzq, int resDer){
	if(resProcess!=RES_OK){
		return resProcess;
	}
	if(resIzq!=RES_OK){
		return resIzq;
	}
	if(resDer!=RES_OK){
		return resDer;
	}
	return RES_OK;
}

int procesadoInternoAbo(TABO abo, aboProcessFunctionPtr process, void *args){
	int resProcess = 0;
	void *elem = malloc(abo.tamanio);
	if(!elem) return RES_OUT_OF_MEMORY;
	AB_ElemCte(abo.a, elem);
	resProcess = process(elem, args);
	AB_ModifCte(&abo.a, elem);
	free(elem);
	return resProcess;
}

int privateAboRecorridoInOrden(TABO abo, aboProcessFunctionPtr process, void* args, int mov){
	int resIzq, resDer, resProcess;
	if(AB_MoverCte(&abo.a, mov)){
		resIzq = privateAboRecorridoInOrden(abo, process, args, IZQ);
		resProcess = procesadoInternoAbo(abo, process, args);
		resDer = privateAboRecorridoInOrden(abo, process, args, DER);
		return elegirResultadoParaRecorrido(resProcess, resIzq, resDer);
	}
	return RES_OK;
}

int privateAboRecorridoPreOrden(TABO abo, aboProcessFunctionPtr process, void* args, int mov){
	int resIzq, resDer, resProcess;
	if(AB_MoverCte(&abo.a, mov)){
		resProcess = procesadoInternoAbo(abo, process, args);
		resIzq = privateAboRecorridoInOrden(abo, process, args, IZQ);
		resDer = privateAboRecorridoInOrden(abo, process, args, DER);
		return elegirResultadoParaRecorrido(resProcess, resIzq, resDer);
	}
	return RES_OK;
}

int privateAboRecorridoPosOrden(TABO abo, aboProcessFunctionPtr process, void* args, int mov){
	int resIzq, resDer, resProcess;
	if(AB_MoverCte(&abo.a, mov)){
		resIzq = privateAboRecorridoInOrden(abo, process, args, IZQ);
		resDer = privateAboRecorridoInOrden(abo, process, args, DER);
		resProcess = procesadoInternoAbo(abo, process, args);
		return elegirResultadoParaRecorrido(resProcess, resIzq, resDer);
	}
	return RES_OK;
}

int privateAboRecorridoEnRangoInOrden(TABO abo, aboProcessFunctionPtr process, void* args, int mov, void* desde, void* hasta){
	int resIzq, resDer, resProcess, resCmpDsd, resCmpHst;
	if(AB_MoverCte(&abo.a, mov)){
		void* elem = malloc(abo.tamanio);
		if(!elem) return RES_OUT_OF_MEMORY;
		AB_ElemCte(abo.a, elem);
		resCmpDsd = abo.fcmp(elem, desde);
		resCmpHst = abo.fcmp(elem, hasta);

		resIzq = resDer = resProcess = RES_OK;

		if(resCmpDsd >= 0){
			resIzq = privateAboRecorridoEnRangoInOrden(abo, process, args, IZQ, desde, hasta);
		}

		if(resCmpDsd >= 0 && resCmpHst <= 0){
			resProcess = process(elem, args);
			AB_ModifCte(&abo.a, elem);
			free(elem);
		}

		if(resCmpHst <= 0){
			resDer = privateAboRecorridoEnRangoInOrden(abo, process, args, DER, desde, hasta);
		}
		return elegirResultadoParaRecorrido(resProcess, resIzq, resDer);
	}
	return RES_OK;
}

int aboBorrarCorriente(TABO* abo);

int replaceOrDelete(TABO* ca, void* elem, int movBase, int movAlt){
	int resMov, nextMov = movAlt;
	TAB abAux;
	memcpy(&abAux, &(ca->a), sizeof(TAB));

	resMov = AB_MoverCte(&(ca->a), movBase);
	if(!resMov){ /* no tiene hijos menores */
		resMov = AB_MoverCte(&(ca->a), movAlt);
		if(!resMov){ /* es una hoja */
			AB_BorrarRama(&(ca->a));
			return RES_DELETED;
		} else {
			nextMov = movBase;
		}
	}
	while(AB_MoverCte(&(ca->a), nextMov));
	AB_ElemCte(ca->a, elem);
	resMov = aboBorrarCorriente(ca);
	memcpy(&(ca->a), &abAux, sizeof(TAB));
	return RES_OK;
}

int aboBorrarCorriente(TABO* abo){
	int res = 0;
	void *substitute;
	substitute = malloc(abo->tamanio);
	if(!substitute){
		return RES_OUT_OF_MEMORY;
	}

	res = replaceOrDelete(abo, substitute, IZQ, DER);
	if(res!=RES_DELETED){
		AB_ModifCte(&(abo->a), substitute);
	}
	free(substitute);
	return RES_OK;
}

/******************************************************************************/
/*	PRIMITIVAS                                                                */
/******************************************************************************/

int ABO_Crear(TABO* abo, taboCmp paf, size_t tam, AB_copiar f_copia, AB_destruir f_destruccion){
	abo->fcmp = paf;
	abo->tamanio = tam;
	AB_Crear(&(abo->a), tam, f_copia, f_destruccion);
	abo->f_copia = f_copia;
	abo->f_destruccion = f_destruccion;
	return RES_OK;
}

int ABO_Destruir(TABO* abo){
	abo->fcmp = NULL;
	AB_Vaciar(&(abo->a));
	return RES_OK;
}

int ABO_Insertar(TABO* abo, void* elem){
	int resBusqueda=FALSE, mov=RAIZ;
	resBusqueda = buscarElem(abo, elem, &mov);
	if(!resBusqueda){
		return AB_Insertar(&(abo->a), mov, elem);
	}
	return RES_ELEMENTO_YA_EXISTE;
}

int ABO_Obtener(TABO* abo, void* elem){
	int resBusqueda=FALSE, mov=RAIZ;
	resBusqueda = buscarElem(abo, elem, &mov);
	if(!resBusqueda){
		return RES_ELEMENTO_NO_EXISTE;
	}
	AB_ElemCte(abo->a, elem);
	return RES_OK;
}

int ABO_Actualizar(TABO* abo, void* elem){
	int resBusqueda=FALSE, mov=RAIZ;
	resBusqueda = buscarElem(abo, elem, &mov);
	if(!resBusqueda){
		return RES_ELEMENTO_NO_EXISTE;
	}
	AB_ModifCte(&(abo->a), elem);
	return RES_OK;
}

int ABO_Borrar(TABO* abo, void* elem){
	int resBusqueda=FALSE, mov=RAIZ;
	resBusqueda = buscarElem(abo, elem, &mov);
	if(!resBusqueda){
		return RES_ELEMENTO_NO_EXISTE;
	}

	resBusqueda = aboBorrarCorriente(abo);
	if(resBusqueda==RES_DELETED){
		AB_MoverCte(&(abo->a), RAIZ);
	}
	return RES_OK;
}

int ABO_ProcesarInOrden(TABO* a, aboProcessFunctionPtr process, void* args){
	return privateAboRecorridoInOrden(*a, process, args, RAIZ);
}

int ABO_ProcesarPreOrden(TABO* a, aboProcessFunctionPtr process, void* args){
	return privateAboRecorridoInOrden(*a, process, args, RAIZ);
}

int ABO_ProcesarPosOrden(TABO* a, aboProcessFunctionPtr process, void* args){
	return privateAboRecorridoInOrden(*a, process, args, RAIZ);
}

int ABO_ProcesarEnRangoInOrden(TABO* a, aboProcessFunctionPtr process, void* args, void* desde, void* hasta){
	return privateAboRecorridoEnRangoInOrden(*a, process, args, RAIZ, desde, hasta);
}
