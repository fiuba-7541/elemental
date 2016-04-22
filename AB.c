#include "AB.h"

void AB_Crear(TAB *a, size_t tdato, AB_copiar f_copia, AB_destruir f_destruccion)
{
	a->tamdato = tdato;
	a->raiz = NULL;
	a->cte = NULL;
	a->f_copia = f_copia;
	a->f_destruccion = f_destruccion;
}

void AB_ElemCte(TAB a,void *elem)
{
	a.f_copia(elem, a.cte->elem);
}

void AB_ModifCte(TAB *a, const void *elem)
{
	a->f_destruccion(a->cte->elem);
	a->f_copia(a->cte->elem, elem);
}

TNodoAB* BuscarPadre(TNodoAB *padre,TNodoAB *hijo)
{
	TNodoAB *paux = NULL;
	if ((padre->izq == hijo) || (padre->der == hijo))
		return padre;
	else
	{
		if (padre->izq != NULL)
			paux = BuscarPadre(padre->izq,hijo);
		if ((padre->der != NULL) && (paux == NULL))
			paux = BuscarPadre(padre->der,hijo);
		return paux;
	}
}

int AB_MoverCte(TAB *a,int mov)
{
	int movio = TRUE;
	switch (mov)
	{
		case IZQ : if (a->cte->izq != NULL)
						a->cte = a->cte->izq;
					else
						movio = FALSE;
					break;
		case DER : if (a->cte->der != NULL)
						a->cte = a->cte->der;
					else
						movio = FALSE;
					break;
		case PAD : if (a->cte != a->raiz)
						a->cte = BuscarPadre(a->raiz,a->cte);
					else
						movio = FALSE;
					break;
		case RAIZ : if (a->raiz != NULL)
						a->cte = a->raiz;
					else
						movio = FALSE;
					break;
		default : movio = FALSE;
	}
	return movio;
}

void VaciarSub(TNodoAB *pnodo, AB_destruir f_destruccion)
{
	if (!pnodo) {
		return;
	}
	VaciarSub(pnodo->izq, f_destruccion);
	VaciarSub(pnodo->der, f_destruccion);
	f_destruccion(pnodo->elem);
	free(pnodo);
}

void AB_Vaciar(TAB *a)
{
	VaciarSub(a->raiz, a->f_destruccion);
	a->raiz = NULL;
	a->cte = NULL;
}

int AB_Insertar(TAB *a,int mov,void *elem)
{
	TNodoAB *paux, **tmpcte;
	paux = (TNodoAB*) malloc(sizeof(TNodoAB));
	if (!paux) {
		return RES_OUT_OF_MEM;
	}
	paux->izq = NULL;
	paux->der = NULL;
	paux->elem = malloc(a->tamdato);
	if (! (paux->elem)) {
		free(paux);
		return RES_OUT_OF_MEM;
	}

	a->f_copia(paux->elem,elem);

	switch(mov) {
		case IZQ :
			tmpcte = &(a->cte->izq);
			break;
		case DER :
			tmpcte = &(a->cte->der);
			break;
		case RAIZ :
			tmpcte = &(a->raiz);
			break;
		default : tmpcte = NULL;
	}
	if((tmpcte) && !(*tmpcte)) {
		a->cte = *tmpcte = paux;
		return RES_OK;
	} else {
		a->f_destruccion(paux->elem);
		free(paux->elem);
		free(paux);
		return RES_MOV_INVALIDO;
	}
}

int AB_Vacio(TAB a)
{	
	return (a.raiz == NULL);
}


int AB_BorrarRama(TAB *a){
	if(a->raiz!=NULL){
		TNodoAB* padre;
		if(a->raiz!=a->cte){
			padre = BuscarPadre(a->raiz, a->cte);
			if(padre->izq==a->cte){
				padre->izq = NULL;
			} else {
				padre->der = NULL;
			}
		} else {
			padre = a->raiz = NULL;
		}
		VaciarSub(a->cte, a->f_destruccion);
		a->cte = padre;
		return RES_OK;
	}
	return RES_ARBOL_VACIO;
}

int AB_BorrarSubRama(TAB *a, int mov){
	if(mov==IZQ){
		VaciarSub(a->cte->izq, a->f_destruccion);
		a->cte->izq = NULL;
	} else if(mov==DER) {
		VaciarSub(a->cte->der, a->f_destruccion);
		a->cte->der = NULL;
	} else {
		return RES_MOV_INVALIDO;
	}
	return RES_OK;
}
