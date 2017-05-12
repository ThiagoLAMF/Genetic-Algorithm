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
        //Ordena os pais(Usado no Elitismo):
        if(ELITISMO)
        {
            quickSort(geracao, 0,TAM_GERACAO-1);
            //printg(geracao);
            //getchar();
        }

        //Calcula FREQ para seleção. //Usado METODO ROLETA
        //CalculaFrequenciaAcumulada(geracao);

        int qtdFilhos;
        if(ELITISMO)
        {
            qtdFilhos = TAM_GERACAO - TX_ELITISMO; //QTD de filhos a serem gerados
        }
        else
        {
            qtdFilhos = TX_CROSSOVER; //QTD de filhos a serem gerados
        }

        for(i=0;i<qtdFilhos;i= i+2)
        {
            //SELECIONA PAIS PARA CROSSOVER
            //TORNEIO:
            int pai1 = SelecionaTorneio(geracao,3);
            int pai2 = SelecionaTorneio(geracao,3);

            //ROLETA:
            //int pai1 = SelecionaRoleta(geracao);
            //int pai2 = SelecionaRoleta(geracao);

            //CROSSOVER
            CrossOverCiclico(geracao[pai1],geracao[pai2],geracao[TAM_GERACAO + i],geracao[TAM_GERACAO + (i+1)] );
            //printf("\n[CROSSOVER] %i \tX %i \tPOS: %i",pai1,pai2,pontoCrossOver);
            //CalculaAvaliacao(geracao[TAM_GERACAO + i]);
            //CalculaAvaliacao(geracao[TAM_GERACAO + (i+1)]);
            Mutacao(geracao[TAM_GERACAO + i]);
            Mutacao(geracao[TAM_GERACAO + (i+1)] );

        }
        //MUTAÇÃO
        //Mutacao(geracao[TAM_GERACAO + i]);
        //Mutacao(geracao[TAM_GERACAO + (i+1)] );
        //rprintg(geracao);
        //getchar();


        //Elitismo
        if(ELITISMO)
        {
            //Vetor de pais já está ordenado// Mantem os 20 primeiros
            quickSort(geracao,19,TAM_GERACAO+qtdFilhos-1);
        }

        if(MELHORPAISFILHOS)
        {
            //SELECIONA MELHORES:
            quickSort(geracao, 0,TAM_GERACAO+qtdFilhos-1);
        }

        //CalculaFrequenciaAcumulada(geracao); //Calcula FREQ para seleção. //METODO ROLETA
    }



    printg(geracao);

    FreePopulacao(geracao);
    return 0;
}

/** FUNÇÕES **/
