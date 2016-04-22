#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifndef _VAR_ARRAY_H_
#define _VAR_ARRAY_H_

typedef struct Var_Array{
    void* array;
    int a_size, a_count, e_size;
}V_Array;

typedef int (*funccmp)(void*, void*);

int VA_create(V_Array* a, int elemsize);
int VA_count(V_Array a);
int VA_add(V_Array* a, void* elem);
int VA_get_i(V_Array a, int epos, void* elem);
void* VA_get(const V_Array* a);
int VA_set(V_Array* a, int epos, void* elem);
int VA_remove(V_Array* a, int epos);
void VA_destroy(V_Array* a);

int VA_sort(V_Array* a, funccmp cmp);
void VA_qsort(V_Array* a, funccmp cmp, int inicio, int fin);

#endif /* _VAR_ARRAY_H_ */
