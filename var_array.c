#include "var_array.h"

/** Initializes the structure and set it ready to be used */
int VA_create(V_Array* a, int elemsize){
    a->e_size = elemsize;
    a->array = malloc (10 * elemsize);
    if(!(a->array)) return -1;
    a->a_size = 10;
    a->a_count = 0;
    return 0;
}

/** Returns the number of elements in the array */
int VA_count(V_Array a){return a.a_count;}

/** Adds a new element to the end of the array */
int VA_add(V_Array* a, void* elem){
    char* aux;
    void* aux2;
    if(a->a_count == a->a_size){
        void* t;
        t=malloc((a->a_size)*(a->e_size)*2);
        if(!t) return -1;
        memcpy(t, a->array, a->a_count * a->e_size);
        free(a->array);
        a->array = t;
        a->a_size *= 2;
    }
    aux = (char*) a->array;
    aux2 = aux+(a->a_count * a->e_size);
    memcpy(aux2, elem, a->e_size);
    a->a_count++;
    return 0;
}

/** Gets the ith element in the array into "elem", return 0 if could and -1 if
    the "epos" is out of range */
int VA_get_i(V_Array a, int epos, void* elem){
    char* aux;
    void* aux2;
    if((epos<0) || (epos >= a.a_count)) return -1;
    aux = (char*) a.array;
    aux2 = aux+(epos*a.e_size);
    memcpy(elem, aux2, a.e_size);
    return 0;
}

/** Returns the array itself */
void* VA_get(const V_Array* a){
    void* res;
    res = malloc(a->a_count * a->e_size);
    if(!res) return NULL;
    memcpy(res, a->array, a->a_count * a->e_size);
    return res;
}

/** Updates the ith element of the array, replacing it with "elem" */
int VA_set(V_Array* a, int epos, void* elem){
    char* aux;
    void* aux2;
    if((epos<0) || (epos >= a->a_count)) return -1;
    aux = (char*) a->array;
    aux2 = aux+(epos*a->e_size);
    memcpy(aux2, elem, a->e_size);
    return 0;
}

/** Removes the ith element in the array, pointed by "epos". In the case the
    array shrinks to a certain size, it should reduce the size of the memory
    in use */
int VA_remove(V_Array* a, int epos){
    char* aux;
    void* aux1;
    void* aux2;

    if((epos<0)||(epos>=a->a_count)) return -1;
    aux = (char*) a->array;
    aux1= aux + (epos * a->e_size);
    aux2= aux + ((epos+1) * a->e_size);
    if(epos< (a->a_count - 1)){
        void* aux3;
        aux3 = malloc (a->e_size * (a->a_count - (epos+1)));
        if(!aux3) return -1;
        memcpy(aux3, aux2, a->e_size * (a->a_count - (epos+1)));
        memcpy(aux1, aux3, a->e_size * (a->a_count - (epos+1)));
        free(aux3);
    }
    a->a_count--;
    if((a->a_count <= (a->a_size/2))&&(a->a_size > 10)){
        /*resize the array to a shorter space */
        aux1 = malloc ((a->a_size/2) * a->e_size);
        if(aux1){
            memcpy(aux1, a->array, a->a_count*a->e_size);
            free(a->array);
            a->array = aux1;
            a->a_size = a->a_size/2;
        }
    }
    return 0;
}

/** Releases the resources used by the Abstract Data Type */
void VA_destroy(V_Array* a){
    free(a->array);
    a->array = NULL;
}


int VA_sort(V_Array* a, funccmp cmp){
    char* mobile;
    void* eswap;
    void* aj0;
    void* aj1;
    int i, j;
    mobile = (char*) a->array;
    eswap=malloc(a->e_size);
    if(!eswap) return -1;
    for(i=1; i<a->a_count; i++)
        for(j=0; j<a->a_count-i; j++){
            aj0 = mobile+(j*a->e_size);
            aj1 = mobile+((j+1)*a->e_size);
            if (cmp(aj0, aj1)==1){
                memcpy(eswap, mobile+(j*a->e_size), a->e_size);
                memcpy(mobile+(j*a->e_size), mobile+((j+1)*a->e_size), a->e_size);
                memcpy(mobile+((j+1)*a->e_size), eswap, a->e_size);
            }
        }
    free(eswap);
    return 0;
}

void VA_qsort(V_Array* a, funccmp cmp, int inicio, int fin){
    char* mobile;
    void* eswap;
    void* pivote;
    int i, j, ppos;

    if (fin<=inicio) return;

    eswap=malloc(a->e_size);
    if(!eswap){
        fprintf(stderr, "out of mem\n");
        return;
    }

    ppos = inicio;
    mobile = (char*) a->array;
    pivote = mobile+(a->e_size * ppos);

    i=inicio+1; j=fin;
    do{
        while( (i<=j) && (cmp( (mobile+(a->e_size * i)) , pivote) == -1) ) i++;
        while( (i<=j) && (cmp( (mobile+(a->e_size * j)) , pivote) ==  1) ) j--;
        if(i<j){
            memcpy(eswap, (mobile+(i*a->e_size)), a->e_size);
            memcpy((mobile+(i*a->e_size)), (mobile+(j*a->e_size)), a->e_size);
            memcpy((mobile+(j*a->e_size)), eswap, a->e_size);
        }
    } while (i<j);

    memcpy(eswap, (mobile+(inicio*a->e_size)), a->e_size);
    memcpy((mobile+(inicio*a->e_size)), (mobile+(j*a->e_size)), a->e_size);
    memcpy((mobile+(j*a->e_size)), eswap, a->e_size);

    free(eswap);
    VA_qsort(a, cmp, i, fin);
    VA_qsort(a, cmp, inicio, j-1);
}


