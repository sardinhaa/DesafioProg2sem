#include <stdio.h>

// Assumindo as estruturas conforme fornecidas no enunciado
typedef struct disciplina no, *pno; 
typedef struct pessoa aluno, *pAluno; 
struct pessoa{ 
    char nome[100]; // Nome do aluno 
    int num;  // Número do aluno    
    pno v[3];  // Ponteiros para as disciplinas a que está inscrito 
}; 
struct disciplina{ 
    char nome[100]; // Nome da disciplina 
    int id, conta; // ID da disciplina e contador de alunos inscritos 
    pno prox; 
}; 
void mostrarAlunosPenultimaDisciplina(pno inicioLista, pAluno vetorAlunos, int dimVetor) {
    // 1. Verificar se a lista tem pelo menos 2 disciplinas
    if (inicioLista == NULL || inicioLista->prox == NULL) {
        printf("Não aplicável\n");
        return;
    }
    // 2. Encontrar a penúltima disciplina
    pno atual = inicioLista;
    // Percorre até que o próximo do próximo seja NULL (parando na penúltima)
    while (atual->prox->prox != NULL) {
        atual = atual->prox;
    }
    // 'atual' aponta agora para a penúltima disciplina
    pno penultima = atual;
    // 3. Percorrer o vetor de alunos
    printf("Alunos inscritos na disciplina %s:\n", penultima->nome);
    for (int i = 0; i < dimVetor; i++) {
        // Verificar se o aluno está inscrito na penúltima disciplina
        // Verifica cada um dos 3 slots de inscrição
        for (int j = 0; j < 3; j++) {
            if (vetorAlunos[i].v[j] == penultima) {
                printf("Nome: %s, Número: %d\n", vetorAlunos[i].nome, vetorAlunos[i].num);
                break; // Encontrou a disciplina, passa para o próximo aluno
            }
        }
    }
}

pno adicionarDisciplina(char *nome, int id, pno inicio, pAluno vetor, int dim) {
    // 1. Verificar se o ID já existe
    pno atual = inicio;
    while (atual != NULL) {
        if (atual->id == id) return inicio;
        atual = atual->prox;
    }

    // 2. Criar e inicializar novo nó
    pno novo = (pno)malloc(sizeof(struct disciplina));
    if (novo == NULL) return inicio;
    strcpy(novo->nome, nome);
    novo->id = id;
    novo->conta = 0;
    novo->prox = NULL;

    // 3. Inserir ordenadamente
    if (inicio == NULL || id < inicio->id) {
        novo->prox = inicio;
        inicio = novo;
    } else {
        pno ant = inicio;
        while (ant->prox != NULL && ant->prox->id < id) {
            ant = ant->prox;
        }
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    // 4. Atualizar inscrições dos alunos
    for (int i = 0; i < dim; i++) {
        int contInscricoes = 0;
        int primeiroVazio = -1;

        for (int j = 0; j < 3; j++) {
            if (vetor[i].v[j] != NULL) contInscricoes++;
            else if (primeiroVazio == -1) primeiroVazio = j;
        }

        if (contInscricoes < 2 && primeiroVazio != -1) {
            vetor[i].v[primeiroVazio] = novo;
            novo->conta++;
        }
    }

    return inicio;
}