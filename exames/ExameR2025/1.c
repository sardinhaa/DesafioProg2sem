#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct drone {
    char id[20];
    int entregas;
    float km;
    char eficiente;
};

int processarDrones(char *nomeTxt, char *nomeBin) {
    FILE *ft = fopen(nomeTxt, "r");
    if (!ft) return 0;
    // Reservar espaço dinâmico (assumindo um limite máximo ou usando realloc)
    // Para simplificar, assumimos um limite razoável ou realocação
    int capacidade = 10, total = 0;
    struct drone *lista = malloc(sizeof(struct drone) * capacidade);
    float somaMediasIndividuais = 0;
    // Leitura do ficheiro de texto
    while (fscanf(ft, "%s %d %f", lista[total].id, &lista[total].entregas, &lista[total].km) == 3) {
        somaMediasIndividuais += (lista[total].km / lista[total].entregas);
        total++;
        if (total == capacidade) {
            capacidade *= 2;
            lista = realloc(lista, sizeof(struct drone) * capacidade);
        }
    }
    fclose(ft);
    if (total == 0) {
        free(lista);
        return 0;
    }
    // Calcular média geral
    float mediaGeral = somaMediasIndividuais / total;
    // Determinar eficiência
    for (int i = 0; i < total; i++) {
        float mediaDrone = lista[i].km / lista[i].entregas;
        lista[i].eficiente = (mediaDrone < mediaGeral) ? 'S' : 'N';
    }
    // Escrita no ficheiro binário
    FILE *fb = fopen(nomeBin, "wb");
    if (!fb) {
        free(lista);
        return 0;
    }
    fwrite(&total, sizeof(int), 1, fb);
    fwrite(lista, sizeof(struct drone), total, fb);
    fclose(fb);
    free(lista);
    return 1;
}