#include "Pila_old.h"

/*P_OLD_CREAR
Pre: P no fue creada.
Post: P creada y vacía. */
void P_OLD_Crear(TPilaOLD *pP, int TamanioDato)
{
	pP->Tope = NULL;
	pP->TamanioDato = TamanioDato;
}

/*P_OLD_VACIAR
Pre: P creada.
Post: P vacía. */
void P_OLD_Vaciar(TPilaOLD *pP)
{
	TNodoPila *pSig=pP->Tope;
	while (pSig)
	{
		pSig = pP->Tope->Siguiente;
		free(pP->Tope->Elem);
		free(pP->Tope);
		pP->Tope = pSig;
	}
	pP->Tope= NULL;
}

/*P_OLD_VACIA
Pre: P creada.
Post: Si P está vacía devuelve TRUE, sino FALSE. */
int P_OLD_Vacia(TPilaOLD P)
{
	return (P.Tope==NULL);
}

/*P_OLD_PONER
Pre: P creada.
Post: E se agregó como Tope de P.
Devuelve FALSE si no pudo agregar E, sino devuelve TRUE.*/
int P_OLD_Poner(TPilaOLD *pP, void* pE)
{
	TNodoPila *pNodo = (TNodoPila*) malloc(sizeof(TNodoPila));
	if (!pNodo)
		return FALSE;
	else
	{
		pNodo->Siguiente = pP->Tope;
		pP->Tope = pNodo;
		pNodo->Elem = malloc (pP->TamanioDato);
		if(!pNodo->Elem)
		{
			free(pNodo);
			return FALSE;
		}
		memcpy(pNodo->Elem, pE, pP->TamanioDato);
		return TRUE;
	}
}

/*P_OLD_SACAR
Pre: P creada y no vacía.
Post: Se extrajo de P el Tope y se devuelve en E.
Si no pudo extraer el elemento (porque la Stack estaba vacía) devuelve FALSE,
sino devuelve TRUE.*/
int P_OLD_Sacar(TPilaOLD *pP, void* pE)
{
	TNodoPila *pAux = pP->Tope;
	pP->Tope = pP->Tope->Siguiente;
	memcpy(pE, pAux->Elem, pP->TamanioDato);
	free(pAux->Elem);
	free(pAux);
	return TRUE;
}

