#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct a autor; 
typedef struct b livro;

struct a{ 
    char nome[100]; // Nome do autor 
    int idA;  // Identificador numérico do autor 
    int nLivros;  // Número de títulos no catálogo da livraria 
};

struct b{
    char titulo[100], isbn[20];
    int idA;
    float preco;
};

int processarLivraria(char *nomeBin, char *nomeTxt, int idAutorAlvo) {
    FILE *fb = fopen(nomeBin, "r+b");
    if (!fb) return 0;

    int X, Y;
    // 1. Ler cabeçalhos e dados dos autores
    if (fread(&X, sizeof(int), 1, fb) != 1) { fclose(fb); return 0; }
    autor *listaAutores = malloc(sizeof(autor) * X);
    fread(listaAutores, sizeof(autor), X, fb);
    
    // 2. Ler cabeçalhos e dados dos livros
    if (fread(&Y, sizeof(int), 1, fb) != 1) { free(listaAutores); fclose(fb); return 0; }
    livro *listaLivros = malloc(sizeof(livro) * Y);
    fread(listaLivros, sizeof(livro), Y, fb);
    // i) Encontrar autor com mais livros e verificar empates
    int maxLivros = -1, idMax = -1, empate = 0;
    for (int i = 0; i < X; i++) {
        if (listaAutores[i].nLivros > maxLivros) {
            maxLivros = listaAutores[i].nLivros;
            idMax = listaAutores[i].idA;
            empate = 0;
        } else if (listaAutores[i].nLivros == maxLivros && maxLivros != -1) {
            empate = 1;
        }
    }

    // Se não houver empate, atualizamos o array na memória e gravamos no binário
    if (!empate && idMax != -1) {
        for (int i = 0; i < Y; i++) {
            if (listaLivros[i].idA == idMax) {
                listaLivros[i].preco *= 1.10f;
            }
        }
        // Reposicionar ponteiro para o início da lista de livros no ficheiro
        fseek(fb, sizeof(int) + (sizeof(autor) * X) + sizeof(int), SEEK_SET);
        fwrite(listaLivros, sizeof(livro), Y, fb);
    }
    // ii) Criar ficheiro de texto
    FILE *ft = fopen(nomeTxt, "w");
    if (!ft) { free(listaAutores); free(listaLivros); fclose(fb); return 0; }

    int autorEncontrado = 0;
    char nomeAutorAlvo[100];
    for (int i = 0; i < X; i++) {
        if (listaAutores[i].idA == idAutorAlvo) {
            autorEncontrado = 1;
            strcpy(nomeAutorAlvo, listaAutores[i].nome);
            break;
        }
    }

    if (!autorEncontrado) {
        fprintf(ft, "Autor Inexistente");
    } else {
        for (int i = 0; i < Y; i++) {
            if (listaLivros[i].idA == idAutorAlvo) {
                fprintf(ft, "%s - %s, %s\n", listaLivros[i].isbn, listaLivros[i].titulo, nomeAutorAlvo);
            }
        }
    }

    // Limpeza final
    free(listaAutores);
    free(listaLivros);
    fclose(fb);
    fclose(ft);
    return 1;
}