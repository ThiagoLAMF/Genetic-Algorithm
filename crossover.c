#include <stdlib.h>
#include <stdio.h>
#include "defines.h"
/**
    Faz mutação em uma das posições do indíviduo.
**/
void Mutacao(int *ind)
{
    int pontoMutacao = rand() % TAM_INDIVIDUO;
    int valorAtual = ind[pontoMutacao];

    int flagGerou = 0;

    while(!flagGerou)
    {
        int n = rand() % 10; //Gera número aleatório.
        int flagExiste = 0;
        int j;

        for(j=0;j<TAM_INDIVIDUO;j++) //Verifica se o número gerado não está no array.
        {
            if(n == valorAtual || ind[j] == n) flagExiste = 1;
        }
        if(!flagExiste) //Se o número não está no array.
        {
            ind[pontoMutacao] = n;
            flagGerou = 1;
        }
    }

}
/**
    Gera dois filhos com crossover no ponto especificado
**/
void CrossOverSimples(int* pai1,int* pai2,int pontoCrossOver,int* filho1,int* filho2)
{
    int i = 0;

    for(i = 0;i<TAM_INDIVIDUO;i++)
    {
        if(i <= pontoCrossOver)
        {
            filho1[i] = pai1[i];
            filho2[i] = pai2[i];
        }
        else
        {
            filho1[i] = pai2[i];
            filho2[i] = pai1[i];
        }
    }

    CalculaAvaliacao(filho1);
    CalculaAvaliacao(filho2);

    /*printf("\nFilho1: ");
    for(i=0;i<TAM_INDIVIDUO;i++)
        printf("%i",filhos[0][i]);

    printf("\nFilho2: ");
    for(i=0;i<TAM_INDIVIDUO;i++)
        printf("%i",filhos[1][i]);*/
}

/**
    Gera dois filhos com crossover nos pontos especificados
    N = numero de pontos no array *pontosCrossOver
    O array *pontosCrossOver deve estar ordenado
**/
int **CrossOverMultiplo(int* pai1,int* pai2,int *pontosCrossOver,int n)
{
    int **filhos = (int**) malloc(sizeof(int*)*2);
    filhos[0] = (int*) malloc(sizeof(int)*TAM_INDIVIDUO);
    filhos[1] = (int*) malloc(sizeof(int)*TAM_INDIVIDUO);

    if(filhos == NULL || filhos[0] == NULL || filhos[1] == NULL) return NULL;

    int i = 0;
    int j = 0; //Percorre *pontosCrossOver
    int flagInd = 0;

    for(i = 0;i<TAM_INDIVIDUO;i++)
    {
        if(!flagInd)
        {
            filhos[0][i] = pai1[i];
            filhos[1][i] = pai2[i];
        }
        else
        {
            filhos[0][i] = pai2[i];
            filhos[1][i] = pai1[i];
        }
        if(i == pontosCrossOver[j])
        {
            flagInd = !flagInd;
            j++;
        }
    }

    printf("\nFilho1: ");
    for(i=0;i<TAM_INDIVIDUO;i++)
        printf("%i",filhos[0][i]);

    printf("\nFilho2: ");
    for(i=0;i<TAM_INDIVIDUO;i++)
        printf("%i",filhos[1][i]);

    return filhos;
}



