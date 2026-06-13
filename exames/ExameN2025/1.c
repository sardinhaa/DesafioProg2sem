#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[20];
    int qnt;
    int alerta;
} item;

int ex1(char *nomeI, char *nomeE) {
    FILE *fi = fopen(nomeI, "r+b");
    FILE *fe = fopen(nomeE, "r");

    if (!fi || !fe) {
        if (fi) fclose(fi);
        if (fe) fclose(fe);
        return 0;
    }

    int id, qnt;
    char nome[100], coment[200];
    item temp;

    while (fscanf(fe, "%d : %s : %d : %s", &id, nome, &qnt, coment) == 4) {
        fseek(fi, (id - 1) * sizeof(item), SEEK_SET);
        fread(&temp, sizeof(item), 1, fi);

        temp.qnt -= qnt;

        fseek(fi, (id - 1) * sizeof(item), SEEK_SET);
        fwrite(&temp, sizeof(item), 1, fi);

        if (temp.qnt < temp.alerta)
            printf("ALERTA: %s (ID %d) abaixo do minimo.\n", temp.nome, temp.id);
    }

    fclose(fi);
    fclose(fe);
    return 1;
}