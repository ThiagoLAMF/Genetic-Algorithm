#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "util.h"


void printg(int **geracao)
{
    int i,j;
    // PRINT POPULAÇÃO:
    printf("\n\n---------------------GERACAO------------------------\n");
    //printf("SOMA AVAL: %i\n",somaAvaliacao);
    printf("INDEX\tIND.\t\tAVAL.\t\tF.A.\n");
    for(i=0;i<TAM_GERACAO_TOTAL;i++)
    {
        printf("[%i]:\t",i);
        for(j = 0;j<TAM_INDIVIDUO_TOTAL;j++)
        {
            printf("%i",geracao[i][j]);
        }
        printf("\t[%i]\t\t[%i]\n",geracao[i][AVAL],geracao[i][FA]);
    }

}

void printind(int *ind)
{
    int j;
    printf("[?]:\t");
    for(j = 0;j<TAM_INDIVIDUO_TOTAL;j++)
    {
        printf("%i",ind[j]);
    }
    printf("\t[%i]\t\t[%i]\n",ind[AVAL],ind[FA]);


}

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

/**
    Ordena com quick sort os indivíduos da população de acordo com a avaliação:
**/
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

/**
    Sobe os filhos na matriz
    posFilho = posição do primeiro filho
    posIni = índice da posição inicial de inserção
**/
void SobeFilhos(int **geracao,int posIni,int qtdFilhos,int posFilho)
{
    int i;

    for(i=0;i<qtdFilhos;i++)
    {
        geracao[posIni] = geracao[posFilho];
        posFilho++;
        posIni++;
    }
}

int VerificaMatriz(int **geracao)
{
    int i;

    for(i=0;i<TAM_GERACAO_TOTAL;i++)
    {
        if(geracao[i][AVAL] == 0) return 1;
    }
    return 0;
}


