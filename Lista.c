#include "Lista.h"

void LS_Crear(TListaSimple *pLs, int TamanioDato, LS_copiar f_copia, LS_destruir f_destruccion)
{
	pLs->Corriente = NULL;
	pLs->Primero = NULL;
	pLs->TamanioDato = TamanioDato;
	pLs->f_copia = f_copia;
	pLs->f_destruccion = f_destruccion;
}

void LS_Destruir(TListaSimple *pLs)
{
	LS_Vaciar(pLs);
}

void LS_Vaciar(TListaSimple *pLs)
{
	TNodoListaSimple *pNodo, *Siguiente;
	for(pNodo = pLs->Primero;(pNodo);pNodo=Siguiente)
	{
		Siguiente = pNodo->Siguiente;
		pLs->f_destruccion(pNodo->Elem);
		free(pNodo->Elem);
		free(pNodo);
	}
	pLs->Primero=pLs->Corriente=NULL;
}

int LS_Vacia(TListaSimple Ls)
{
	return (Ls.Primero == NULL);
}

void LS_Elem_Cte(TListaSimple Ls, void *pE)
{
	Ls.f_copia(pE, Ls.Corriente->Elem);
}

int LS_Mover_Cte(TListaSimple *pLs, TMovimiento_Ls M)
{
	switch (M)
	{
		case LS_Primero:
			pLs->Corriente=pLs->Primero;
		break;
		case LS_Siguiente:
			if (pLs->Corriente->Siguiente==NULL)
				return FALSE;
			else
				pLs->Corriente=pLs->Corriente->Siguiente;
		break;
		case LS_Anterior:return FALSE;
	}
	return TRUE;
}

void LS_Borrar_Cte(TListaSimple *pLs)
{
	TNodoListaSimple *pNodo=pLs->Corriente;
	if (pLs->Corriente==pLs->Primero)
	{
		pLs->Primero = pLs->Corriente->Siguiente;
		pLs->Corriente = pLs->Primero;
	}
	else
	{
		if(pLs->Corriente->Siguiente){
			/* En este caso en que el corriente no es el ultimo, puedo evitarme
			 * recorrer toda la lista buscando el anterior */
			pNodo=pLs->Corriente->Siguiente;
			memcpy(pLs->Corriente->Elem, pNodo->Elem, pLs->TamanioDato);
			pLs->Corriente->Siguiente = pNodo->Siguiente;
		}else {
			TNodoListaSimple *pAux=pLs->Primero;
			while (pAux->Siguiente!=pLs->Corriente)
				pAux = pAux->Siguiente;
			pAux->Siguiente=pLs->Corriente->Siguiente;
			pLs->Corriente = pAux; /*Si es el �ltimo queda en el Anterior al borrado */
		}
	}
	pLs->f_destruccion(pNodo->Elem);
	free(pNodo->Elem);
	free(pNodo);
}

int LS_Insertar_Cte(TListaSimple *pLs, TMovimiento_Ls M, void* pE)
{
	TNodoListaSimple *pNodo = (TNodoListaSimple*) malloc(sizeof(TNodoListaSimple));
	if (!pNodo)
		return FALSE; /* No hay memoria disponible */
	pNodo->Elem = malloc (pLs->TamanioDato);
	if(!pNodo->Elem)
	{
		free(pNodo);
		return FALSE;
	}
	pLs->f_copia(pNodo->Elem, pE);
	if ((pLs->Primero == NULL) || (M==LS_Primero) || ((M==LS_Anterior) && (pLs->Primero==pLs->Corriente)))
	{
		/*Si est� vac�a o hay que insertar en el Primero o
		hay que insertar en el Anterior y el actual es el Primero */
		pNodo->Siguiente = pLs->Primero;
		pLs->Primero = pLs->Corriente = pNodo;
	}
	else
	{
		/* Siempre inserto como siguiente, el nodo nuevo, porque es más fácil */
		pNodo->Siguiente = pLs->Corriente->Siguiente;
		pLs->Corriente->Siguiente = pNodo;
		if (M == LS_Anterior)
		{
			/* Pero cuando el movimiento es Anterior, entonces swapeo los
			 * elementos */
			void* tmp = pNodo->Elem;
			pNodo->Elem = pLs->Corriente->Elem;
			pLs->Corriente->Elem = tmp;
		}
	}
	pLs->Corriente=pNodo;
	return TRUE;
}

