#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct projeto proj, *pproj; 
typedef struct pessoa gestor, *pgest; 
 
struct pessoa{ 
    int id;   // Identificador único do gestor 
    char nome[100];  // Nome do gestor 
    int total;   // Número de projetos que está a gerir 
};
struct projeto{ 
    int id;     // Identificador único do projeto 
    struct {int dia, mes, ano;} inicio;  // Data de início do projeto 
    pgest p;    // Ponteiro para o gestor deste projeto 
    pproj prox; 
}; 


int comparaDatas(int d1, int m1, int a1, int d2, int m2,int a2){
if (a1 != a2) return a1 - a2;
    if (m1 != m2) return m1 - m2;
    return d1 - d2;
}

void ex2(int idG, pproj inicioL, gestor *vetG, int dim) {
    pgest gestorA = NULL;

    for (int i = 0; i < dim; i++) {
        if (vetG[i].id == idG) {
            gestorA = &vetG[i];
            break;
        }
    }
    if (gestorA == NULL || gestorA->total < 2) {
        printf("Não aplicável\n");
        return;
    }

    pproj atual = inicioL;
    int primeiro=0; 


    int dAntigo, mAntigo , aAntigo, dNovo, mNovo, aNovo;

while (atual != NULL) {
        // Verifica se o projeto pertence ao gestor alvo
        if (atual->p == gestorA) {
            if (!primeiro) {
                // Primeira ocorrência encontrada, inicializa extremos
                dAntigo = dNovo = atual->inicio.dia;
                mAntigo = mNovo = atual->inicio.mes;
                aAntigo = aNovo = atual->inicio.ano;
                primeiro = 1;
            } else {
                // Compara com a mais antiga
                if (compararDatas(atual->inicio.dia, atual->inicio.mes, atual->inicio.ano, dAntigo, mAntigo, aAntigo) < 0) {
                    dAntigo = atual->inicio.dia; mAntigo = atual->inicio.mes; aAntigo = atual->inicio.ano;
                }
                // Compara com a mais recente
                if (compararDatas(atual->inicio.dia, atual->inicio.mes, atual->inicio.ano, dNovo, mNovo, aNovo) > 0) {
                    dNovo = atual->inicio.dia; mNovo = atual->inicio.mes; aNovo = atual->inicio.ano;
                }
            }
        }
        atual = atual->prox;
    }

    printf("Projeto mais antigo: %d/%d/%d\n", dAntigo, mAntigo, aAntigo);
    printf("Projeto mais recente: %d/%d/%d\n", dNovo, mNovo, aNovo);
}