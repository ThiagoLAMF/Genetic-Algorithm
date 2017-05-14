#include <stdlib.h>
#include <stdio.h>
#include "populacao.h"
#include "defines.h"
#include "util.h"

/**
//DONALD GERALD ROBERT
**/
/*int CalculaAvaliacao(int *ind)
{
    //Calcula SEND:
    int eatArray[6] = {ind[D], ind[O], ind[N],ind[A],ind[L],ind[D]};
    int eat = ConcatenaArray(eatArray,6);

    //Calcula MORE:
    int thatArray[6] = {ind[G], ind[E], ind[R], ind[A],ind[L],ind[D]};
    int that = ConcatenaArray(thatArray,6);

    //Calcula MONEY:
    int appleArray[6] = {ind[R], ind[O], ind[B], ind[E], ind[R],ind[T]};
    int apple = ConcatenaArray(appleArray,6);

    int avaliacao = abs((eat+that)-apple);
    ind[AVAL] = avaliacao;

    return avaliacao;

}*/
/**
//COCA COLA OASIS
**/
/*int CalculaAvaliacao(int *ind)
{
    //Calcula SEND:
    int eatArray[4] = {ind[C], ind[O], ind[C],ind[A]};
    int eat = ConcatenaArray(eatArray,4);

    //Calcula MORE:
    int thatArray[4] = {ind[C], ind[O], ind[L], ind[A]};
    int that = ConcatenaArray(thatArray,4);

    //Calcula MONEY:
    int appleArray[5] = {ind[O], ind[A], ind[S], ind[I], ind[S]};
    int apple = ConcatenaArray(appleArray,5);

    int avaliacao = abs((eat+that)-apple);
    ind[AVAL] = avaliacao;

    return avaliacao;

}*/
/**
//CROSS ROADS DANGER
**/
/*int CalculaAvaliacao(int *ind)
{
    //Calcula SEND:
    int eatArray[5] = {ind[C], ind[R], ind[O],ind[S],ind[S]};
    int eat = ConcatenaArray(eatArray,5);

    //Calcula MORE:
    int thatArray[5] = {ind[R], ind[O], ind[A], ind[D],ind[S]};
    int that = ConcatenaArray(thatArray,5);

    //Calcula MONEY:
    int appleArray[6] = {ind[D], ind[A], ind[N], ind[G], ind[E], ind[R]};
    int apple = ConcatenaArray(appleArray,6);

    int avaliacao = abs((eat+that)-apple);
    ind[AVAL] = avaliacao;

    return avaliacao;

}*/
/**
//EAT + THAT = APPLE
**/
/*int CalculaAvaliacao(int *ind)
{
    //Calcula SEND:
    int eatArray[3] = {ind[E], ind[A], ind[T]};
    int eat = ConcatenaArray(eatArray,3);

    //Calcula MORE:
    int thatArray[4] = {ind[T], ind[H], ind[A], ind[T]};
    int that = ConcatenaArray(thatArray,4);

    //Calcula MONEY:
    int appleArray[5] = {ind[A], ind[P], ind[P], ind[L], ind[E]};
    int apple = ConcatenaArray(appleArray,5);

    int avaliacao = abs((eat+that)-apple);
    ind[AVAL] = avaliacao;

    return avaliacao;

}*/
/**
    Avalia um indivíduo com a equação: (SEND + MORE) - MONEY = AVALIACAO
    Melhor valor é o mais próximo de 0.
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
    Gera 10 números aleatórios únicos entre 0 e 9 e retorna.
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
        int n = rand() % 10; //Gera número aleatório.
        int flagExiste = 0;
        int j;

        for(j=0;j<TAM_INDIVIDUO_TOTAL;j++) //Verifica se o número gerado não está no array.
        {
            if(ind[j] == n) flagExiste = 1;
        }
        if(!flagExiste) //Se o número não está no array.
        {
            ind[i] = n;
            i++;
        }

    }
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
        else //Aloca posição dos filhos
        {
            geracao[i] = (int*) malloc(sizeof(int)*TAM_TOTAL);
            geracao[i][AVAL] = -1;
            geracao[i][FA] = -1;
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


