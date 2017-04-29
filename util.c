#include "defines.h"

/**
    Ordena com quick sort os indivíduos da população de acordo com a avaliação:
**/
int partition(int **geracao, int l, int r)
{
    int *t;
    int i = l-1;
    int j;
    int pivot = geracao[r][AVAL];

    for(j = l;j<=r-1;j++)
    {
        if(geracao[j][AVAL] <= pivot)
        {
            i++;
            t = geracao[i];
            geracao[i] = geracao[j];
            geracao[j] = t;
        }
    }

   t = geracao[i+1];
   geracao[i+1] = geracao[r];
   geracao[r] = t;
   return i+1;
}
void quickSort(int **geracao, int l, int r)
{
   int j;

   if( l < r )
   {
        j = partition( geracao, l, r);// divide and conquer
        quickSort( geracao, l, j-1);
        quickSort( geracao, j+1, r);
   }

}
/**
    Converte um array de inteiros em um inteiro e retorna.
**/
int ConcatenaArray(int* arr, int len)
{
    int result = 0,i;

    for (i=0; i < len; i++)
    {
        result = result*10 + arr[i];
    }
    return result;
}
