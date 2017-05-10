#include <stdlib.h>
#include <stdio.h>
#include "crossover.h"
#include "defines.h"
#include "populacao.h"


/**


**/
void CrossOverCiclico(int* pai1,int* pai2,int* filho1,int* filho2)
{
    int i,j;
    int tam_ciclo = 1; //Ciclo começa com tamanho 1
    int *ciclo = (int *) malloc(sizeof(int));
    if(ciclo == NULL) return;

    int posAtual = 0; //posAtual do ciclo
    ciclo[0] = pai1[posAtual];
    int flagCiclo = 0;
    while(!flagCiclo)
    {
        int elementoPai2 = pai2[posAtual]; //desce no pai2
        //Verifica se o ciclo foi completo
        if(elementoPai2 == ciclo[0])
        {
            flagCiclo = 1;
            break;
        }

        //Adiciona elemento no ciclo
        tam_ciclo++;
        ciclo = (int*) realloc(ciclo,sizeof(int)*tam_ciclo); //Realoca vetor
        ciclo[tam_ciclo-1] = pai2[posAtual];

        //procura o elemento em pai1
        for(i=0;i<TAM_INDIVIDUO_TOTAL;i++)
        {
            if(elementoPai2 == pai1[i])
            {
                posAtual = i;
                break;
            }
        }
    }

    //debug
    printf("\n\nP1:\n");
    for(j = 0;j<TAM_INDIVIDUO_TOTAL;j++)
    {
        printf("%i",pai1[j]);
    }
    printf("\nP2:\n");
    for(j = 0;j<TAM_INDIVIDUO_TOTAL;j++)
    {
        printf("%i",pai2[j]);
    }

    //ciclo:
    printf("\n\nCiclo:\n");
    for(j = 0;j<tam_ciclo;j++)
    {
        printf("%d ",ciclo[j]);
    }

}


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
            printf("\n[MUTACAO]: P: %i N: gv%i",pontoMutacao,n);
            flagGerou = 1;
        }
    }
    int i;
    printf("\n[MUTACAO]: ");
    for(i=0;i<TAM_INDIVIDUO;i++)
        printf("%i",ind[i]);

}
/**
    Gera dois filhos com crossover no ponto especificado
**/
void CrossOverSimples(int* pai1,int* pai2,int pontoCrossOver,int* filho1,int* filho2)
{
    int i = 0;

    for(i = 0;i<TAM_INDIVIDUO_TOTAL;i++)
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

    TODO: Retirar alocação
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



