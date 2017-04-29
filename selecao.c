#include "defines.h"
#include "selecao.h"
#include <inttypes.h>
#include <stdlib.h>

/**
    Calcula a frequencia acumulada e coloca na posição [FA] do vetor.
**/
void CalculaFrequenciaAcumulada(int **geracao)
{
    int i;
    int freq = 0;

    for(i=0;i<TAM_GERACAO_TOTAL;i++)
    {
        if(i < TAM_GERACAO)
        {
            freq += geracao[i][AVAL];
            geracao[i][FA] = freq;
        }
        else
        {
            geracao[i][FA] = -1;
        }
    }
}

/**
    Seleciona um individuo baseado no método da Roleta e retorna o índice.
    É necessário que a Frequencia Acumulada esteja calculada na posicao [FA].
**/
int SelecionaRoleta(int **geracao)
{
    int somaAvaliacao;
    somaAvaliacao = geracao[TAM_GERACAO][FA];//Como a FQ. Acumulada já está calculada, a soma está no último elemento da geracao

    int i;
    //int rdm = rand() % somaAvaliacao; // Gera um número aleatório entre 0 e somaAvaliacao
    uint64_t rdm = (rand() * RAND_MAX) % somaAvaliacao; //VERIFICAR GERAÇÃO

    //printf("\nRANDOM: %i",rdm);

    for(i=0;i<TAM_GERACAO;i++)
        if(geracao[i][FA] > rdm)
        {
            return i; //Retorna índice
        }

    return -1;
}

/**
    Seleciona um indivíduo baseado no método do torneio e retorna o índice.
**/
int SelecionaTorneio(int **geracao,int tamTorneio)
{
    int melhor = -1;
    int indexMelhor = -1;
    int rdm,i;

    for(i = 0; i< tamTorneio;i++) //Seleciona k individuos
    {
        rdm = rand() % TAM_GERACAO;
        if(melhor == -1 || geracao[rdm][AVAL] < melhor)
        {
            melhor = geracao[rdm][AVAL];
            indexMelhor = rdm;
        }
    }
    return indexMelhor; //Melhor dentre os selecionados
}

