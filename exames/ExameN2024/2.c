#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dadosUc   uc, *pUc; 
typedef struct dadosSala sala, *pSala; 
typedef struct {int dia, mes, ano;} data; 
 
struct dadosUc{ 
    char refUc[100];   //  Nome da Unidade Curricular 
    data dataEx;       //  Data do exame 
    pSala lista;         // Ponteiro para a lista de salas 
};

struct dadosSala{ 
    char refSala[100];  //  Nome da sala 
    int capacidade;     // Capacidade de sala 
    pSala prox; 
};

void listarUcsComSala(pUc v, int dim, char *ns) {
    int encontrouAlguma = 0;
    // 1. Percorrer o vetor de unidades curriculares
    for (int i = 0; i < dim; i++) {
        // 2. Para cada UC, percorrer a sua lista ligada de salas
        pSala salaAtual = v[i].lista;
        while (salaAtual != NULL) {
            // Verifica se o nome da sala coincide
            if (strcmp(salaAtual->refSala, ns) == 0) {
                printf("Unidade Curricular: %s\n", v[i].refUc);
                encontrouAlguma = 1;
                // Uma vez encontrada a sala na lista da UC, 
                // não precisamos de verificar as restantes salas desta UC
                break; 
            }
            salaAtual = salaAtual->prox;
        }
    }
    if (!encontrouAlguma) {
        printf("Nenhuma unidade curricular tem essa sala reservada.\n");
    }
}
// Função para comparar se a data 1 é anterior à data 2
int eAnterior(data d1, data d2) {
    if (d1.ano != d2.ano) return d1.ano < d2.ano;
    if (d1.mes != d2.mes) return d1.mes < d2.mes;
    return d1.dia < d2.dia;
}
// dada uma data, ve se algum exame tem a data anterior a estipulada e apaga da estrutura
pUc elimina(pUc v, int *nUcs, data d) {
    int i, count = 0;
    // 1. Identificar quantas UCs devem ser eliminadas
    for (i = 0; i < *nUcs; i++) {
        if (eAnterior(v[i].dataEx, d)) {
            count++;
        } 
        else {
            break;} // Como está ordenado, paramos na primeira que não deve ser eliminada
    }
    if (count == 0) return v;
    // 2. Libertar listas de salas das UCs a eliminar
    for (i = 0; i < count; i++) {
        pSala atual = v[i].lista;
        while (atual != NULL) {
            pSala temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    int novoTamanho = *nUcs - count;    // 3. Reorganizar vetor (deslocar elementos restantes para o início)
    if (novoTamanho > 0) {
        for (i = 0; i < novoTamanho; i++) {
            v[i] = v[i + count];
        }// 4. Redimensionar o vetor
        pUc vNovo = realloc(v, sizeof(uc) * novoTamanho);
        if (vNovo == NULL) return v; // Em caso de erro, devolve o original
        *nUcs = novoTamanho;
        return vNovo;
    } else {
        free(v);        // Se todas foram eliminadas
        *nUcs = 0;
        return NULL;
    }
}