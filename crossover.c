#include <stdlib.h>
#include <stdio.h>
#include "crossover.h"
#include "defines.h"
#include "populacao.h"


/**
    Gera dois filhos usando CrossOver Ciclico
**/
void CrossOverCiclico(int* pai1,int* pai2,int* filho1,int* filho2)
{
    int i;

    int tam_ciclo = 1; //Ciclo começa com tamanho 1
    int *ciclo = (int *) malloc(sizeof(int));
    if(ciclo == NULL) return;

    int mascara[TAM_INDIVIDUO_TOTAL]; //Mascara para ser usada no crossover em si
    for(i=0;i<TAM_INDIVIDUO_TOTAL;i++) mascara[i] = 0;

    int posAtual = 0; //posAtual do ciclo
    ciclo[0] = 0;
    mascara[0] = 1;
    int flagCiclo = 0;
    while(!flagCiclo)
    {
        int elementoPai2 = pai2[posAtual]; //desce no pai2

        if(elementoPai2 == pai1[ciclo[0]])//Verifica se o ciclo foi completo
        {
            flagCiclo = 1;
            break;
        }

        //procura o elemento em pai1
        for(i=0;i<TAM_INDIVIDUO_TOTAL;i++)
        {
            if(elementoPai2 == pai1[i])
            {
                posAtual = i;
                break;
            }
        }

        //Adiciona elemento no ciclo
        tam_ciclo++;
        ciclo = (int*) realloc(ciclo,sizeof(int)*tam_ciclo); //Realoca vetor
        ciclo[tam_ciclo-1] = posAtual; //Pega posicao
        mascara[posAtual] = 1;
    }

    for(i = 0;i<TAM_INDIVIDUO_TOTAL;i++)
    {
        if(mascara[i] == 1)
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
    filho1[AVAL] = -1;
    filho1[AVAL] = -1;
}

/**
    Faz mutação em qtdInd indivíduos(Entre as posições dos filhos)
**/
void MutacaoFilhos(int **geracao,int qtdInd,int qtdFilhos)
{
    int i;

    for(i=TAM_GERACAO;i<(TAM_GERACAO + qtdInd);i++)
    {
        int rdm = (rand() % (qtdFilhos)) + TAM_GERACAO;
        Mutacao(geracao[rdm]);
    }
}
/**
    Faz mutação em uma das posições do indíviduo.
**/
void Mutacao(int *ind)
{
    int pontoMutacao = rand() % TAM_INDIVIDUO;
    int pontoMutacao2 = rand() % TAM_INDIVIDUO;
    while(pontoMutacao2 == pontoMutacao) pontoMutacao2 = rand() % TAM_INDIVIDUO;

    int aux = ind[pontoMutacao];
    ind[pontoMutacao] = ind[pontoMutacao2];
    ind[pontoMutacao2] = aux;

    CalculaAvaliacao(ind);

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



