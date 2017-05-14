void Mutacao(int *ind);
void CrossOverSimples(int* ind1,int* ind2,int pontoCrossOver,int* filho1,int* filho2);
int **CrossOverMultiplo(int* pai1,int* pai2,int *pontosCrossOver,int n);
void CrossOverCiclico(int* pai1,int* pai2,int* filho1,int* filho2);
void MutacaoFilhos(int **geracao,int qtdInd,int qtdFilhos);
