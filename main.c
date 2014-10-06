#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SortAlgorithm.h"
const int MAX_ARRAY_LENGTH = 697687; /* 可能造成内存读错误，原因未明 */

typedef enum { FALSE = 0, TRUE = 1 } BOOL;
typedef void (*pSort) ( ElementType*, Position );
double test_sort ( pSort pf, ElementType* keys, Position length )
{
    clock_t start, end;
    double duration;

    start = clock();
    pf( keys, length );
    end = clock();
    duration = (double)( end - start ) / CLOCKS_PER_SEC ;

    return duration;
}

int compare_qsort(const void * a, const void * b)
{
  return ( *(ElementType*)a - *(ElementType*)b );
}
double test_stdlib_qsort ( ElementType* keys, Position length )
{
    clock_t start, end;
    double duration;

    start = clock();
    qsort( keys, length, sizeof(ElementType), compare_qsort);
    end = clock();
    duration = (double)( end - start ) / CLOCKS_PER_SEC ;

    return duration;
}

void testAllSortAlgorithms( void );
void testQuickSortAlgorithm( void );
int main()
{
    /*testAllSortAlgorithms();*/
    testQuickSortAlgorithm();
    return EXIT_SUCCESS;
}

void testQuickSortAlgorithm( void )
{
    int i;
    double duration_v1, duration_v2, duration_qsort;
    BOOL isAllSame = TRUE, isSingleSame = FALSE;
    int array_v1[MAX_ARRAY_LENGTH];
    int array_v2[MAX_ARRAY_LENGTH];
    int array_qsort[MAX_ARRAY_LENGTH];

    srand(time(NULL));
    for( i =0; i < MAX_ARRAY_LENGTH; i++)
        array_qsort[i] = array_v2[i] = array_v1[i] = rand() % 999999 + 1;

    printf("Input finished: %d elements.\t\t[OK]\n", MAX_ARRAY_LENGTH );
    duration_qsort = test_stdlib_qsort ( array_qsort, MAX_ARRAY_LENGTH );
    printf("stdlib qsort: %f seconds\t\t[OK]\n", duration_qsort );
    duration_v1 = test_sort ( lxQuickSort,        array_v1, MAX_ARRAY_LENGTH );
    printf("Quick Sort v1: %f seconds\t\t[OK]\n", duration_v1 );
    duration_v2 = test_sort ( lxQuickSort2,        array_v2, MAX_ARRAY_LENGTH );
    printf("Quick Sort v2: %f seconds\t\t[OK]\n", duration_v2 );

    for ( i = 0; i < MAX_ARRAY_LENGTH; i++ )
    {
        isSingleSame = (array_v1[i]==array_v2[i]) && (array_v1[i]==array_qsort[i]) ;
        isAllSame = isAllSame && isSingleSame;
        /*printf("(%3d)%8d%16d%14d\n ", i, array_v1[i], array_v2[i], array_qsort[i];*/
    }

    if( isAllSame )
        printf("All sort results are the same\t\t[OK]\n");
    else
        printf("Not All sort results are the same\t\t[FAILED]\n");
    printf("----------------------------------------------------------------------------\n");
}

void testAllSortAlgorithms()
{
    int i;
    double duration, duration2, duration3, duration4, duration5, duration_qsort;
    BOOL isAllSame = TRUE, isSingleSame = FALSE;
    int array_random[MAX_ARRAY_LENGTH];
    int array_random2[MAX_ARRAY_LENGTH];
    int array_random3[MAX_ARRAY_LENGTH];
    int array_random4[MAX_ARRAY_LENGTH];
    int array_random5[MAX_ARRAY_LENGTH];
    int array_random_qsort[MAX_ARRAY_LENGTH];

/*    size_t SW_INC[MAX_ARRAY_LENGTH];  */

    srand(time(NULL));
    for( i =0; i<MAX_ARRAY_LENGTH; i++)
        array_random_qsort[i] = array_random5[i] = array_random4[i] = array_random3[i]
            = array_random2[i] = array_random[i] = rand() % 999999 + 1;
    /*for ( i = 0; i < MAX_ARRAY_LENGTH; i++ )
        printf("%d, ", array_random[i]); */
    printf("Input finished: %d elements.\t\t[OK]\n", MAX_ARRAY_LENGTH );

    duration  = test_sort ( lxBubbleSort,       array_random,  MAX_ARRAY_LENGTH );
    printf("Bubble Sort: %f seconds\t\t[OK]\n", duration );
    duration2 = test_sort ( lxInsertionSort,    array_random2, MAX_ARRAY_LENGTH );
    printf("Insertion Sort: %f seconds\t[OK]\n", duration2 );
    duration3 = test_sort ( lxShellSort,        array_random3, MAX_ARRAY_LENGTH );
    printf("Shell Sort: %f seconds\t\t[OK]\n", duration3 );
    duration4 = test_sort ( lxMergeSort,        array_random4, MAX_ARRAY_LENGTH );
    printf("Merge Sort: %f seconds\t\t[OK]\n", duration4 );
    duration5 = test_sort ( lxQuickSort,        array_random5, MAX_ARRAY_LENGTH );
    printf("Quick Sort: %f seconds\t\t[OK]\n", duration5 );
    duration_qsort = test_stdlib_qsort ( array_random_qsort, MAX_ARRAY_LENGTH );
    printf("stdlib qsort: %f seconds\t\t[OK]\n", duration_qsort );
    /*printf("----------------------------------------------------------------------------\n");
    printf("index [BubbleSort] [InsertionSort] [ShellSort] [MergeSort] [QuickSort] SAME?\n");
    printf("----------------------------------------------------------------------------\n");*/

    for ( i = 0; i < MAX_ARRAY_LENGTH; i++ )
    {
        isSingleSame = (array_random[i]==array_random2[i]) && (array_random[i]==array_random2[i])
            && (array_random[i]==array_random4[i]) && (array_random[i]==array_random5[i]) &&
             (array_random_qsort[i] == array_random[i]) ;
        isAllSame = isAllSame && isSingleSame;
        /*printf("(%3d)%8d%16d%14d%12d%12d%8d\n ", i, array_random[i], array_random2[i],
            array_random3[i], array_random4[i], array_random5[i], isSingleSame );*/
    }

    /*printf("seconds [%10.4f] [%10.4f] [%10.4f] [%10.4f] [%10.4f]\n",
                duration, duration2, duration3, duration4, duration5);
    printf("index [BubbleSort] [InsertionSort] [ShellSort] [MergeSort] [QuickSort] %d\n", isAllSame);*/
    if( isAllSame )
        printf("All sort results are the same\t\t[OK]\n");
    else
        printf("Not All sort results are the same\t\t[FAILED]\n");
    printf("----------------------------------------------------------------------------\n");

/*
    lx_ShellSort_SedgewickIncrements(SW_INC, MAX_ARRAY_LENGTH);
    for ( i = 0; i < MAX_ARRAY_LENGTH; i++ )
        printf("%lu, ", SW_INC[i]);
*/
}
