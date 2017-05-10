#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "selecao.h"
#include "defines.h"
#include "crossover.h"
#include "populacao.h"

/** DEC. FUNÇÕES **/

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
        CalculaFrequenciaAcumulada(geracao); //Calcula FREQ para seleção. //METODO ROLETA

        int qtdFilhos = TAM_GERACAO_TOTAL - TAM_GERACAO; //QTD de filhos a serem gerados
        for(i=0;i<qtdFilhos;i= i+2)
        {
            //SELECIONA PAIS PARA CROSSOVER
            //Torneio:
            int pai1 = SelecionaTorneio(geracao,4);
            int pai2 = SelecionaTorneio(geracao,4);

            //Roleta:
            //int pai1 = SelecionaRoleta(geracao);
            //int pai2 = SelecionaRoleta(geracao);

            //CROSSOVER
            int pontoCrossOver = rand() % TAM_INDIVIDUO; //Sorteio ponto Crossover
            //CrossOverSimples(geracao[pai1],geracao[pai2],pontoCrossOver,geracao[TAM_GERACAO + i],geracao[TAM_GERACAO + (i+1)] );
            CrossOverCiclico(geracao[pai1],geracao[pai2],geracao[TAM_GERACAO + i],geracao[TAM_GERACAO + (i+1)] );
             getchar();
            //printf("\n[CROSSOVER] %i \tX %i \tPOS: %i",pai1,pai2,pontoCrossOver);

            //MUTAÇÃO
            //Mutacao(geracao[TAM_GERACAO + i]);
            //Mutacao(geracao[TAM_GERACAO + (i+1)] );

        }
        printg(geracao);
        getchar();
        //SELECIONA MELHORES:
        quickSort(geracao, 0,TAM_GERACAO_TOTAL-1);
        //CalculaFrequenciaAcumulada(geracao); //Calcula FREQ para seleção. //METODO ROLETA
    }



    printg(geracao);

    FreePopulacao(geracao);
    return 0;
}

/** FUNÇÕES **/
