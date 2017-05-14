#define N_ITERACOES 1000
#define N_GERACOES 200 //Numero maximo de geracoes

#define TAM_GERACAO 150 //Quantidade de individuos na populacao(Representa 100%)
#define TAM_GERACAO_TOTAL 300 //TAM_GERACAO + FILHOS (DEVE SER PAR)

#define TAM_INDIVIDUO 8
#define TAM_INDIVIDUO_TOTAL 10
#define TAM_TOTAL 12 //TAM_INDIVIDUO + APTIDAO + FREQ. ACUMULADA

#define TX_CROSSOVER 150// 80% dos individuos sao selecionados para crossover
#define TX_ELITISMO 20 //20% dos melhores pais sao mantidos
#define TX_MUTACAO 150 //20% dos individuos sofrem mutacao

#define ROLETA 1
#define TORNEIO 0

#define ELITISMO 0
#define MELHORPAISFILHOS 1

enum individuo
{
    S,E,N,D,M,O,R,Y,D1,D2,AVAL,FA
};

//EAT THAT APPLE
/*enum individuo
{
    E,A,T,H,P,L,D1,D2,D3,D4,AVAL,FA
};*/

//CROSS ROADS DANGER
/*enum individuo
{
    C,R,O,S,A,D,N,G,E,D1,AVAL,FA
};*/

//COCA COLA OASIS
/*enum individuo
{
    C,O,A,L,S,I,D1,D2,D3,D4,AVAL,FA
};*/

//DONALD GERALD ROBERT
/*
enum individuo
{
    D,O,N,A,L,G,E,R,B,T,AVAL,FA
};*/
