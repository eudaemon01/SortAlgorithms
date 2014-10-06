#ifndef SORTALGORITHM_H_INCLUDED
#define SORTALGORITHM_H_INCLUDED

#include <stddef.h>

typedef int ElementType;
typedef long int Position;

/* Sort keys in ascending order.*/
void lxSort ( ElementType* keys , Position length );
void lxInsertionSort ( ElementType* keys , Position length );
void lxBubbleSort ( ElementType* keys , Position length );

/*希尔排序(Shell Sort)又叫做缩小增量排序(diminishing increment sort)*/
void lxShellSort ( ElementType* keys , Position length );
void lxShellSort_SedgewickSequence ( Position *incs, Position length);

void lxMergeSort ( ElementType* keys , Position length );

void lxQuickSort ( ElementType* keys , Position length );
void lxQuickSort2 ( ElementType* keys , Position length );

#endif // SORTALGORITHM_H_INCLUDED
