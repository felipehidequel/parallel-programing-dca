/*

Tarefa 2:​
Implemente três laços em C para investigar os efeitos do paralelismo ao nível de
instrução (ILP): 1) inicialize um vetor com um cálculo simples; 2) some seus
elementos de forma acumulativa, criando dependência entre as iterações; e 3)
quebre essa dependência utilizando múltiplas variáveis. Compare o tempo de
execução das versões compiladas com diferentes níveis de otimização (O0, O2, O3)
e analise como o estilo do código e as dependências influenciam o
desempenho.​


*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 111111111

int main() {
    double *v = (double *)malloc(N * sizeof(double));
    double soma = 0;
    clock_t start, end;

    // 1) Inicialização
    start = clock();
    for (int i = 0; i < N; i++) {
        v[i] = i * 2.0;
    }
    end = clock();
    printf("Tempo Inicializacao: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 2) Soma Acumulativa
    soma = 0;
    start = clock();
    for (int i = 0; i < N; i++) {
        soma += v[i];
    }
    end = clock();
    printf("Tempo Soma: %f s | Resultado: %f\n", (double)(end - start) / CLOCKS_PER_SEC, soma);

    // 3) Quebra de Dependência
    double s1 = 0, s2 = 0, s3 = 0, s4 = 0;
    start = clock();
    for (int i = 0; i < N; i += 4) {
        s1 += v[i];
        s2 += v[i+1];
        s3 += v[i+2];
        s4 += v[i+3];
    }
    soma = s1 + s2 + s3 + s4;
    end = clock();
    printf("Tempo Soma (ILP/Independente): %f s | Resultado: %f\n", (double)(end - start) / CLOCKS_PER_SEC, soma);

    free(v);
    return 0;
}