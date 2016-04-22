/*
 * ListaCompacta.c
 *
 *  Created on: 25/04/2011
 *      Author: anibal
 */

#include "ListaCompacta.h"

void LC_Crear(TListaCompacta *pLs, int TamanioDato)
{
	pLs->corriente = NULL;
	pLs->primero = NULL;
	pLs->tamanioDato = TamanioDato;
}

void LC_Vaciar(TListaCompacta *pLs)
{
	TNodoListaCompacta *pNodo, *siguiente;
	for(pNodo = pLs->primero;(pNodo);pNodo=siguiente)
	{
		siguiente = pNodo->siguiente;
		free(pNodo);
	}
	pLs->primero=pLs->corriente=NULL;
}

int LC_Vacia(TListaCompacta Ls)
{
	return (Ls.primero == NULL);
}

void LC_Elem_Cte(TListaCompacta Ls, void *pE)
{
	memcpy(pE, (Ls.corriente)+1, Ls.tamanioDato);
}

int LC_Mover_Cte(TListaCompacta *pLs, TMovimiento_Lc M)
{
	switch (M)
	{
		case L_Primero:
			pLs->corriente=pLs->primero;
		break;
		case L_Siguiente:
			if (pLs->corriente->siguiente==NULL)
				return FALSE;
			else
				pLs->corriente=pLs->corriente->siguiente;
		break;
		case L_Anterior:return FALSE;
	}
	return TRUE;
}

void LC_Borrar_Cte(TListaCompacta *pLs)
{
	TNodoListaCompacta *pNodo=pLs->corriente;
	if (pLs->corriente==pLs->primero)
	{
		pLs->primero = pLs->corriente->siguiente;
		pLs->corriente = pLs->primero;
	}
	else
	{
		if(pLs->corriente->siguiente){
			/* En este caso en que el corriente no es el ultimo, puedo evitarme
			 * recorrer toda la lista buscando el anterior */
			pNodo=pLs->corriente->siguiente;
			memcpy((pLs->corriente)+1, (pNodo)+1, pLs->tamanioDato);
			pLs->corriente->siguiente = pNodo->siguiente;
		}else {
			TNodoListaCompacta *pAux=pLs->primero;
			while (pAux->siguiente!=pLs->corriente)
				pAux = pAux->siguiente;
			pAux->siguiente=pLs->corriente->siguiente;
			pLs->corriente = pAux; /*Si es el �ltimo queda en el Anterior al borrado */
		}
	}
	free(pNodo);
}

int LC_Insertar_Cte(TListaCompacta *pLs, TMovimiento_Lc M, void* pE)
{
	TNodoListaCompacta *pNodo = (TNodoListaCompacta*) malloc(sizeof(TNodoListaCompacta) + pLs->tamanioDato);
	if (!pNodo)
		return FALSE; /* No hay memoria disponible */

	memcpy(pNodo+1, pE, pLs->tamanioDato);
	if ((pLs->primero == NULL) || (M==L_Primero) || ((M==L_Anterior) && (pLs->primero==pLs->corriente)))
	{
		/*Si est� vac�a o hay que insertar en el Primero o
		hay que insertar en el Anterior y el actual es el Primero */
		pNodo->siguiente = pLs->primero;
		pLs->primero = pLs->corriente = pNodo;
	}
	else
	{
		/* Siempre inserto como siguiente, el nodo nuevo, porque es más fácil */
		pNodo->siguiente = pLs->corriente->siguiente;
		pLs->corriente->siguiente = pNodo;
		if (M == L_Anterior)
		{
			/* Pero cuando el movimiento es Anterior, entonces swapeo los
			 * elementos */
			void* tmp = malloc(pLs->tamanioDato);
			memcpy(tmp, pNodo+1, pLs->tamanioDato);
			memcpy(pNodo+1, (pLs->corriente)+1, pLs->tamanioDato);
			memcpy((pLs->corriente)+1, tmp, pLs->tamanioDato);
			free(tmp);
		}
	}
	pLs->corriente=pNodo;
	return TRUE;
}

