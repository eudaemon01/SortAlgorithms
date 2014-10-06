#include "SortAlgorithm.h"
#include <math.h>
#include <memory.h>

#define MAX_INCREMENTS 32
/* The gap sequence corresponding Worst-case time complexity: O( n^(4/3 ))
   f[k] = 4^k + 3*2^(k-1) + 1 ( k >= 1 )
   f[k] = 1                   ( k == 0 )
  [ref] http://en.wikipedia.org/wiki/Shellsort */
static Position SEDGEWICK_INCREMENTS[MAX_INCREMENTS] =
{
    1, 8, 23, 77, 281, 1073, 4193, 16577, 65921, 262913,
    1050113, 4197377, 16783361, 67121153, 268460033,
    1073790977, 4295065601, 17180065793, 68719869953, 274878693377,
    1099513200641, 4398049656833, 17592192335873, 70368756760577, 281475001876481,
    1125899957174273, 4503599728033793, 18014398710808576, 72057594440581120, 288230376957018112,
    1152921506217459712, 4611686021648613376
};

static void Merge( ElementType* keys, Position left, Position mid, Position right )
{
    Position i, j, k; /* i for leftArray, j for rightArray, k for keys */
    Position left_length = mid - left + 1;
    Position right_length = right - mid;
    ElementType *leftArray, *rightArray;
    ElementType sentinel;

    /* Allocate two temporary arrays. Notes: Both intentionall bigger for storing the sentinel value*/
    leftArray = (ElementType*) malloc( (left_length+1) * sizeof(ElementType) );
    rightArray = (ElementType*) malloc( (right_length+1) * sizeof(ElementType) );
    if( leftArray == NULL || rightArray == NULL )
    {
        perror("Failed to allocate memory for the temporary array!");
        return;
    }
    for ( i = 0; i < left_length; i++ )
        leftArray[i] = keys[left+i];
    for ( j = 0; j < right_length; j++ )
        rightArray[j] = keys[mid+1+j];

    /* Since the two temporary arrays is already oredered independently, it's easy to get the max value
       from the last element. Simply increment the sentinel value to make sure it's bigger than
       any value of the two arrays. */
    sentinel = ( leftArray[left_length - 1]  > rightArray[right_length - 1] ) ?
                    leftArray[left_length - 1] : rightArray[right_length - 1];
    leftArray[left_length] = rightArray[right_length] = ++sentinel;

    for ( i = j = 0, k = left; k <= right ; k++ )
    {
        if( leftArray[i] <= rightArray[j] )
            keys[k] = leftArray[i++];
        else
            keys[k] = rightArray[j++];
    }

    free(rightArray);
    free(leftArray);
}

static void MSort( ElementType* keys, Position left, Position right )
{
    Position mid;
    if( left < right )
    {
        mid = ( left + right ) / 2;
        MSort( keys, left, mid );
        MSort( keys, mid+1, right );
        Merge( keys, left, mid, right);
    }
}

/* 已修复的bug：
    描述：运行时可能产生错误，valgrind提示是 if ( keys[j] <= pivot_element ) 这一行
   Conditional jump or move depends on uninitialised value(s)
    原因：采用size_t作为Position类型，无符号数在减1时发生下溢，因此lxQSort()在递归调用时可能产生right参数为一个
    很大的正数的情况。
    措施：改用long int作为Position类型。 */
static Position PartitionForQsort ( ElementType* keys , Position left, Position right )
{
    Position pivot, j;
    ElementType pivot_element = keys[right], temp;
    pivot = left - 1;
    for ( j = left; j < right; j++ )
    {
        if ( keys[j] <= pivot_element )
        {
            pivot++;
            if ( j != pivot )
            {
                temp = keys[j];
                keys[j] = keys[pivot];
                keys[pivot] = temp;
            }
        }
    }

    pivot++;
    keys[right] = keys[pivot];
    keys[pivot] = pivot_element;
    return pivot;
}

static Position PartitionForQsort2 ( ElementType* keys , Position left, Position right )
{
    Position pivot, j;
    ElementType pivot_element = keys[right], temp;
    pivot = left - 1;
    for ( j = left; j < right; j++ )
    {
        if ( keys[j] <= pivot_element )
        {
            pivot++;
            if ( j != pivot )
            {
                temp = keys[j];
                keys[j] = keys[pivot];
                keys[pivot] = temp;
            }
        }
    }

    pivot++;
    keys[right] = keys[pivot];
    keys[pivot] = pivot_element;
    return pivot;
}

static void lxQSort ( ElementType* keys , Position left, Position right )
{
    Position pivot;
    if ( left < right )
    {
        pivot = PartitionForQsort( keys, left, right );
        lxQSort( keys, left, pivot - 1 );
        lxQSort( keys, pivot + 1, right );
    }
}

static void lxQSort2 ( ElementType* keys , Position left, Position right )
{
    register Position pivot;
    if ( left < right )
    {
        pivot = PartitionForQsort2( keys, left, right );
        lxQSort2( keys, left, pivot - 1 );
        lxQSort2( keys, pivot + 1, right );
    }
}

void lxSort ( ElementType* keys , Position length )
{
    if ( length < 10 )
        lxInsertionSort( keys, length );
    else if ( length < 10000 )
        lxShellSort( keys, length );
    else
        lxQuickSort( keys, length );
}

void lxMergeSort ( ElementType* keys , Position length )
{
    if ( ( keys == NULL ) || ( length < 2 ) )
        return;

    MSort(keys, 0, length-1 );
}

void lxInsertionSort ( ElementType* keys , Position length )
{
    Position i, j;
    ElementType tmp;
    if ( ( keys == NULL ) || ( length < 2 ) )
        return;

    for ( i = 1; i < length; i++ )
    {
        tmp = keys[i];
        for ( j = i ; j > 0 ; j-- )
        {
            if ( tmp < keys[j-1] )
                keys[j] = keys[j-1];
            else
                break;
        }
        keys[j] = tmp;
    }
}

void lxBubbleSort ( ElementType* keys , Position length )
{
    Position i, j;
    ElementType tmp;
    if ( ( keys == NULL ) || ( length < 2 ) )
        return;

    for ( i = 0; i < length - 1; i++ )
    {
        for ( j = length - 1 ; j > i  ; j-- )
        {
            if ( keys[j-1] > keys[j] )
            {
                tmp = keys[j-1];
                keys[j-1] = keys[j];
                keys[j] = tmp;
            }
        }
    }
}

void lxShellSort ( ElementType* keys , Position length )
{
    Position i, j, increment, max_seq_index;
    int k;  /* k shall not be of unsigned type, or may downflow while decrement*/
    ElementType tmp;
    if ( ( keys == NULL ) || ( length < 2 ) )
        return;

    /* Find the proper element in the gap sequence */
    for ( max_seq_index = 0; max_seq_index < MAX_INCREMENTS &&
            SEDGEWICK_INCREMENTS[max_seq_index] < length; max_seq_index++ )
        ;
    max_seq_index--;

    /*for ( increment = length / 2 ; increment > 0; increment /= 2 )*/
    for( k = max_seq_index ; k >= 0 ; k-- )  /* in reverse order */
    {
        increment = SEDGEWICK_INCREMENTS[k];
        for ( i = increment; i < length; i++ )
        {
            tmp = keys[i];
            for ( j = i ; j >= increment ; j -= increment )
            {
                if ( tmp < keys[j-increment] )
                    keys[j] = keys[j-increment];
                else
                    break;
            }
            keys[j] = tmp;
        }
    }
}

void lxQuickSort ( ElementType* keys , Position length )
{
    if ( ( keys == NULL ) || ( length < 2 ) )
        return;

    lxQSort( keys, 0, length-1 );
}

void lxQuickSort2 ( ElementType* keys , Position length )
{
    if ( ( keys == NULL ) || ( length < 2 ) )
        return;

    lxQSort2( keys, 0, length-1 );
}
void lxShellSort_SedgewickSequence ( Position * incs, Position length)
{
    Position i;
    if ( incs == NULL )
        return;

    incs[0] = 1;
    for ( i = 1 ; i < length; i++ )
    {
        incs[i] = pow(4, i) +  3 * pow(2, i-1) + 1;
    }
}
