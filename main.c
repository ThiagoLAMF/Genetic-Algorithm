#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "selecao.h"
#include "defines.h"
#include "crossover.h"
#include "populacao.h"

/** DEC. FUNÇÕES **/
int ag();
/** MAIN **/
int main()
{
    srand(time(NULL));
    int i;
    int contador = 0;

    for(i = 0; i< N_ITERACOES;i++)
    {
        if(ag())
        {
            contador++;
        }
    }

    printf("\n----------AG-----------------\n");
    printf("GERACOES: %d\n",N_GERACOES);
    printf("ITERACOES: %d\n",N_ITERACOES);
    printf("RESULTADO: %d PC\n",(contador));
    return 0;
}

/** FUNÇÕES **/
int ag()
{
    int i;
    int j;

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

        if(ROLETA)
        {
            //Calcula FREQ para seleção. //Usado METODO ROLETA
            CalculaFrequenciaAcumulada(geracao);
        }

        int qtdFilhos = TX_CROSSOVER; //QTD de filhos a serem gerados

        for(i=0;i<qtdFilhos;i= i+2)
        {
            //SELECIONA PAIS PARA CROSSOVER
            int pai1;
            int pai2;
            //TORNEIO:
            if(TORNEIO)
            {
                pai1 = SelecionaTorneio(geracao,3);
                pai2 = SelecionaTorneio(geracao,3);
            }
            if(ROLETA)
            {
                pai1 = SelecionaRoleta(geracao);
                pai2 = SelecionaRoleta(geracao);
                //printf("ROLETA: %d %d\n",pai1,pai2);
            }

            //CROSSOVER
            CrossOverCiclico(geracao[pai1],geracao[pai2],geracao[TAM_GERACAO + i],geracao[TAM_GERACAO + (i+1)] );
            //printf("\n[CROSSOVER] %i \tX %i \tPOS: %i",pai1,pai2,pontoCrossOver);

            //CalculaAvaliacao(geracao[TAM_GERACAO + i]);//alteracao questao 2
            //CalculaAvaliacao(geracao[TAM_GERACAO + (i+1)]);//alteracao questao 2
            //alteracao questao 2
            Mutacao(geracao[TAM_GERACAO + i]);
            Mutacao(geracao[TAM_GERACAO + (i+1)] );
        }
        //MUTAÇÃO
        //MutacaoFilhos(geracao,TX_MUTACAO,qtdFilhos);//alteracao questao 2

        //Elitismo
        if(ELITISMO)
        {
            //Vetor de pais já está ordenado// Mantem os 20 primeiros
            SobeFilhos(geracao,TX_ELITISMO,qtdFilhos,TAM_GERACAO);
        }

        if(MELHORPAISFILHOS)
        {
            //SELECIONA MELHORES:
            quickSort(geracao, 0,TAM_GERACAO+qtdFilhos-1);
        }

        //printg(geracao);
        //getchar();
        if(geracao[0][AVAL] == 0)
        {
            //printind(geracao[0]);
            FreePopulacao(geracao);
            return 1;
        }
    }




    if(VerificaMatriz(geracao))
    {
        //printind(geracao[0]);
        //getchar();
        FreePopulacao(geracao);
        return 1;
    }

    FreePopulacao(geracao);
    return 0;
}
