#include "Cola_old.h"

/*C_OLD_CREAR
Pre: C no fue creada.
Post: C creada y vac�a. */
void C_OLD_Crear(TColaOLD *pC, int TamanioDato)
{
	pC->Primero = pC->Ultimo = NULL;
	pC->TamanioDato = TamanioDato;
}

/*C_OLD_VACIAR
Pre: C creada.
Post: C vac�a. */
void C_OLD_Vaciar(TColaOLD *pC)
{
	TNodoCola *pAux = pC->Primero;
	TNodoCola *pSig;
	while (pAux)
	{
		pSig = pAux->Sig;
		free(pAux->Elem);
		free(pAux);
		pAux = pSig;
	}
	pC->Primero = pC->Ultimo = NULL;
}

/*C_OLD_VACIA
Pre: C creada.
Post: Si C est� vac�a devuelve TRUE, sino FALSE. */
int C_OLD_Vacia(TColaOLD C)
{
	return (C.Primero==NULL);
}

/*C_OLD_AGREGAR
Pre: C creada.
Post: E se agreg� como �ltimo elemento de C.
Devuelve FALSE si no pudo agregar E, sino devuelve TRUE.*/
int C_OLD_Agregar(TColaOLD *pC, void* pE)
{
	TNodoCola *pNodo = (TNodoCola*) malloc(sizeof(TNodoCola));
	if (!pNodo)
		return FALSE;
	else
	{
		if (pC->Ultimo)
			pC->Ultimo->Sig = pNodo;
		if (!pC->Primero) /*Est� vac�a*/
			pC->Primero = pNodo;
		pNodo->Sig = NULL;
		pC->Ultimo = pNodo;
		pNodo->Elem = malloc (pC->TamanioDato);
		if(!pNodo->Elem)
		{
			free(pNodo);
			return FALSE;
		}
		memcpy(pNodo->Elem, pE, pC->TamanioDato);
		return TRUE;
	}
}

/*C_OLD_SACAR
Pre: C creada y no vac�a.
Post: Se extrajo de C el primer elemento y se devuelve en E.
Si no pudo extraer el elemento (porque C estaba vac�a) devuelve FALSE,
sino devuelve TRUE.*/
int C_OLD_Sacar(TColaOLD *pC, void* pE)
{
	TNodoCola *pAux = pC->Primero;
	if (!pC->Primero)
		return FALSE;
	pC->Primero = pC->Primero->Sig;
	if (!pC->Primero)
	{
		pC->Ultimo = NULL;
	}
	memcpy(pE, pAux->Elem, pC->TamanioDato);
	free(pAux->Elem);
	free(pAux);
	return TRUE;
}

