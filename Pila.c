#include "Pila.h"

/*P_CREAR
Pre: P no fue creada.
Post: P creada y vacía. */
void P_Crear(TPila *pP, int TamanioDato, P_copiar f_copia, P_destruir f_destruccion)
{
	pP->Tope = NULL;
	pP->TamanioDato = TamanioDato;
	pP->f_copia = f_copia;
	pP->f_destruccion = f_destruccion;
}

void P_Destruir(TPila *pP)
{
	P_Vaciar(pP);
}

/*P_VACIAR
Pre: P creada.
Post: P vacía. */
void P_Vaciar(TPila *pP)
{
	TNodoPila *pSig=pP->Tope;
	while (pSig)
	{
		pSig = pP->Tope->Siguiente;
		pP->f_destruccion(pP->Tope->Elem);
		free(pP->Tope->Elem);
		free(pP->Tope);
		pP->Tope = pSig;
	}
	pP->Tope= NULL;
}

/*P_VACIA
Pre: P creada.
Post: Si P está vacía devuelve TRUE, sino FALSE. */
int P_Vacia(TPila P)
{
	return (P.Tope==NULL);
}

/*P_PONER
Pre: P creada.
Post: E se agregó como Tope de P.
Devuelve FALSE si no pudo agregar E, sino devuelve TRUE.*/
int P_Poner(TPila *pP, void* pE)
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
		pP->f_copia(pNodo->Elem, pE);
		return TRUE;
	}
}

/*P_SACAR
Pre: P creada y no vacía.
Post: Se extrajo de P el Tope y se devuelve en E.
Si no pudo extraer el elemento (porque la Stack estaba vacía) devuelve FALSE,
sino devuelve TRUE.*/
int P_Sacar(TPila *pP, void* pE)
{
	TNodoPila *pAux = pP->Tope;
	pP->Tope = pP->Tope->Siguiente;
	pP->f_copia(pE, pAux->Elem);
	pP->f_destruccion(pAux->Elem);
	free(pAux->Elem);
	free(pAux);
	return TRUE;
}

