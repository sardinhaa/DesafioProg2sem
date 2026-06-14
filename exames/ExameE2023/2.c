#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct sala no, *pno; 
struct sala{ 
    char id[10]; 
    int total; 
    pno prox; 
}; 
 
typedef struct pessoa{ 
    char nome[100], num[20]; 
    pno p; 
}aluno; 


int trocaSalas(char *nome1, char *nome2, pno listaSalas, aluno *v, int dim) {
    int aux1 = -1;
    int aux2 = -1; 
    for (int i = 0; i < dim; i++){
        if (strcmp(v[i].nome, nome1)==0) aux1 = i;
        if (strcmp(v[i].nome, nome2)==0) aux2 = i;
    }
    if ( aux1 == -1 || aux2 == -1) return -1;
    pno aux = v[aux1].p;
    v[aux1].p = v[aux2].p;
    v[aux2].p = aux;
}

aluno* adicionaAl(aluno* v, int *tot, pno p, char *nome, char *num){

    // 1. Encontrar a sala com menos alunos
    pno melhorSala = p;
    pno aux = p->prox;
    while (aux != NULL) {
        if (aux->total < melhorSala->total) melhorSala = aux;
        aux = aux->prox;}
    // 2. Aumentar o array (realloc)
    v = (aluno*)realloc(v, (*tot + 1) * sizeof(aluno));
    if (!v) return NULL;
    // 3. Inserir ordenado (mover elementos para a frente)
    int i = *tot - 1;
    while (i >= 0 && strcmp(v[i].nome, nome) > 0) {
        v[i + 1] = v[i];
        i--;}
    // 4. Colocar o novo aluno e associar à sala
    strcpy(v[i + 1].nome, nome);
    strcpy(v[i + 1].num, num);
    v[i + 1].p = melhorSala;
    // 5. Atualizar contadores
    melhorSala->total++;
    (*tot)++;
    return v;
}