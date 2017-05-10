#include <stdlib.h>
#include <stdio.h>
#include "populacao.h"
#include "defines.h"
#include "util.h"


/**
    Avalia um indiv�duo com a equa��o: (SEND + MORE) - MONEY = AVALIACAO
    Melhor valor � o mais pr�ximo de 0.
**/
int CalculaAvaliacao(int *ind)
{
    //Calcula SEND:
    int sendArray[4] = {ind[S], ind[E], ind[N], ind[D]};
    int send = ConcatenaArray(sendArray,4);

    //Calcula MORE:
    int moreArray[4] = {ind[M], ind[O], ind[R], ind[E]};
    int more = ConcatenaArray(moreArray,4);

    //Calcula MONEY:
    int moneyArray[5] = {ind[M], ind[O], ind[N], ind[E], ind[Y]};
    int money = ConcatenaArray(moneyArray,5);

    int avaliacao = abs((send+more)-money);
    ind[AVAL] = avaliacao;

    //printf("\nSEND: %i",send);
    //printf("\nMORE: %i",more);
    //printf("\nMONEY: %i",money);
    //printf("\n\nSEND + MORE - MONEY = %i",avaliacao);
    return avaliacao;

}

/**
    Gera 8 n�meros aleat�rios �nicos entre 0 e 9 e retorna.
**/
int* GeraIndividuo()
{
    int *ind = (int*) malloc(sizeof(int)*TAM_TOTAL);
    int i = 0;

    for(i = 0;i<TAM_TOTAL;i++) //Inicializa vetor.
        ind[i] = -1;

    i = 0;
    while(i < TAM_INDIVIDUO_TOTAL)
    {
        int n = rand() % 10; //Gera n�mero aleat�rio.
        int flagExiste = 0;
        int j;

        for(j=0;j<TAM_INDIVIDUO_TOTAL;j++) //Verifica se o n�mero gerado n�o est� no array.
        {
            if(ind[j] == n) flagExiste = 1;
        }
        if(!flagExiste) //Se o n�mero n�o est� no array.
        {
            ind[i] = n;
            i++;
        }

    }

    /*printf("\nGerado: ");
    for(i=0;i<TAM_INDIVIDUO;i++)
        printf("%i",ind[i]);*/
    return ind;
}
int **GeraPopulacao(int *somaAvaliacao)
{
    int i;
    int **geracao = (int**) malloc(sizeof(int*)*TAM_GERACAO_TOTAL);
    *somaAvaliacao = 0;
    for(i=0;i<TAM_GERACAO_TOTAL;i++)
    {
        if(i< TAM_GERACAO)
        {
            int *ind = GeraIndividuo();
            *somaAvaliacao += CalculaAvaliacao(ind);
            geracao[i] = ind;
        }
        else //Aloca posi��o dos filhos
        {
            geracao[i] = (int*) malloc(sizeof(int)*TAM_TOTAL);
        }

    }
    return geracao;
}

void FreePopulacao(int** geracao)
{
    int i;
    for(i=0;i<TAM_GERACAO_TOTAL;i++)
    {
        free(geracao[i]);
    }
    free(geracao);

}


