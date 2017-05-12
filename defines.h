#define TAM_INDIVIDUO 8
#define TAM_INDIVIDUO_TOTAL 10
#define TAM_TOTAL 12 //TAM_INDIVIDUO + APTIDAO + FREQ. ACUMULADA

#define TAM_GERACAO 100 //Quantidade de indivíduos na população //Representa 100%
#define TAM_GERACAO_TOTAL 200 //TAM_GERACAO + FILHOS (DEVE SER PAR)
#define N_GERACOES 100 //Número máximo de gerações

#define TX_CROSSOVER 80 // 80% dos individuos são selecionados para crossover
#define TX_MUTACAO 20 //20% dos individuos sofrem crossover

#define ROLETA 1
#define TORNEIO 0

#define ELITISMO 1
#define TX_ELITISMO 20 //20% dos melhores pais são mantidos
#define MELHORPAISFILHOS 0

enum individuo
{
    S,E,N,D,M,O,R,Y,D1,D2,AVAL,FA
};
