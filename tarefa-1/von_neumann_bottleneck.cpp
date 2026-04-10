#include <iostream>
#using namespace std;

/*
Tarefa 1:
Implemente duas versões da
multiplicação de matriz por vetor (MxV)
em C: uma com acesso à matriz por
linhas (laço interno variando coluna) e
outra por colunas (laço interno variando
linha). Meça o tempo de execução de
cada versão com uma função apropriada
e execute testes com diferentes
tamanhos de matriz. Identifique a partir
de que tamanho os tempos passam a
divergir significativamente e explique por
que isso ocorre, relacionando suas
observações com o uso da memória
cache e o padrão de acesso à memória.
*/

int* multi_ColumnMajorOrder(int *m, int *v, int n){
    int *res = new int[n]();
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            res[j] += m[j*n+i] * v[i]; 
        }
    }

    return res;
}

int* multi_LineMajorOrder(int *m, int *v, int n){
    int *res = new int[n]();
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            res[i] += m[i*n+j] * v[j]; 
        }
    }

    return res;
}