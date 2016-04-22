#include "queue.h"

int queue_create(queue_t* qp, size_t size, queue_copy_t copy, queue_destroy_t destroy)
{
	qp->first = qp->last = NULL;
	qp->size = size;
	qp->copy = copy;
	qp->destroy = destroy;
	return RES_OK;
}

void queue_destroy(queue_t *qp)
{
	queue_clear(qp);
}

void queue_clear(queue_t *qp)
{
	queue_node_t* aux = qp->first;
	queue_node_t* next;
	while (aux)
	{
		next = aux->next;
		qp->destroy(aux->data);
		free(aux->data);
		free(aux);
		aux = next;
	}
	qp->first = qp->last = NULL;
}

int queue_is_empty(const queue_t* qp)
{
	return (qp->first == NULL);
}

int queue_push(queue_t *qp, const void* data)
{
	queue_node_t* new_node = (queue_node_t*) malloc(sizeof(queue_node_t));
	if (!new_node) {
		return FALSE;
	}

	new_node->data = malloc (qp->size);
	if(!new_node->data)
	{
		free(new_node);
		return FALSE;
	}
	if(qp->copy(new_node->data, data) != RES_OK) {
		free(new_node->data);
		free(new_node);
		return FALSE;
	}

	if (!qp->first) { /*Esta vacia*/
		qp->first = qp->last = new_node;
	} else {
		qp->last->next = new_node;
	}
	new_node->next = NULL;
	qp->last = new_node;
	return TRUE;
}

int queue_pop(queue_t *qp, void* data)
{
	queue_node_t* aux = qp->first;
	if (!aux || qp->copy(data, aux->data) != RES_OK) {
		return FALSE;
	}
	qp->first = aux->next;
	if (!qp->first) {
		qp->last = NULL;
	}
	qp->destroy(aux->data);
	free(aux->data);
	free(aux);
	return TRUE;
}

