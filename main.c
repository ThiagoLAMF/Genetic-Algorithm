#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "selecao.h"
#include "defines.h"
#include "crossover.h"

/** DEC. FUNÇÕES **/
int **GeraPopulacao(int *somaAvaliacao);
void FreePopulacao(int** geracao);
int *GeraIndividuo();
int CalculaAvaliacao(int *ind);

/** MAIN **/
int main()
{
    int i;
    int j;
    srand(time(NULL));

    // GERA POPULAÇÃO:
    int somaAvaliacao;
    int **geracao = GeraPopulacao(&somaAvaliacao);

    for(j = 0; j< N_GERACOES;j++)
    {
        // AG:
        //CalculaFrequenciaAcumulada(geracao,somaAvaliacao); //Calcula FREQ para seleção. //METODO ROLETA

        int qtdFilhos = TAM_GERACAO_TOTAL - TAM_GERACAO; //QTD de filhos a serem gerados
        for(i=0;i<qtdFilhos;i= i+2)
        {
            //SELECIONA PAIS PARA CROSSOVER
            int pai1 = SelecionaTorneio(geracao,4);
            int pai2 = SelecionaTorneio(geracao,4);

            //CROSSOVER
            int pontoCrossOver = rand() % TAM_INDIVIDUO; //Sorteio ponto Crossover
            CrossOverSimples(geracao[pai1],geracao[pai2],pontoCrossOver,geracao[TAM_GERACAO + i],geracao[TAM_GERACAO + (i+1)] );
            //printf("\n[CROSSOVER] %i \tX %i \tPOS: %i",pai1,pai2,pontoCrossOver);

            //MUTAÇÃO
            Mutacao(geracao[TAM_GERACAO + i]);
            Mutacao(geracao[TAM_GERACAO + (i+1)] );

        }
        //SELECIONA MELHORES:
        quickSort(geracao, 0,TAM_GERACAO_TOTAL-1);
    }

    // PRINT POPULAÇÃO FINAL:
    printf("\n\n---GERACAO---\n");
    printf("SOMA AVAL: %i\n",somaAvaliacao);
    for(i=0;i<TAM_GERACAO_TOTAL;i++)
    {
        printf("[%i]:\t",i);
        for(j = 0;j<TAM_INDIVIDUO;j++)
        {
            printf("%i",geracao[i][j]);
        }
        printf("\tA: %i)\t(FA: %i)\n",geracao[i][AVAL],geracao[i][FA]);
    }

    FreePopulacao(geracao);
    return 0;
}

/** FUNÇÕES **/

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
/**
    Gera 8 números aleatórios únicos entre 0 e 9 e retorna.
**/
int* GeraIndividuo()
{
    int *ind = (int*) malloc(sizeof(int)*TAM_TOTAL);
    int i = 0;

    for(i = 0;i<TAM_TOTAL;i++) //Inicializa vetor.
        ind[i] = -1;

    i = 0;
    while(i < TAM_INDIVIDUO)
    {
        int n = rand() % 10; //Gera número aleatório.
        int flagExiste = 0;
        int j;

        for(j=0;j<TAM_INDIVIDUO;j++) //Verifica se o número gerado não está no array.
        {
            if(ind[j] == n) flagExiste = 1;
        }
        if(!flagExiste) //Se o número não está no array.
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

