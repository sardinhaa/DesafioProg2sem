/* NOTAS IMPORTANTES

Devem efetuar as seguintes alteracoes:

a.	Alterar o nome do ficheiro, que deve passar a ser o do vosso numero de aluno e mantendo a extensao .c.
    Caso o vosso numero de aluno seja 20251234, devem submeter um ficheiro com nome 20251234.c

b.	Quando efetuarem a alteracao da alinea anterior, tenham cuidado para não alterar o nome dos
    ficheiros de cabeçalho (header files) que surgem no inicio do codigo.
    O refactoring do CLion pode alterar o nome dos ficheiros .h e isso nao pode acontecer no ficheiro que submeterem.
    Confiram a linha 35 do ficheiro que deve continuar a ser #include "lista.h".

c.	Após concluirem a submissao, confirmem que o ficheiro tem o nome correto.
    Se não cumprirem as regras das alineas a) e b) ficarao sem nota atribuida

d.	Completar a vossa identificaca nas linhas 28 e 29 do ficheiro.

e.	Escrever a funcao desafio3(), de acordo com o que é solicitado no enunciado.
    Esta funcao não deve escrever nada na consola, efetuando apenas as operacoes descritas no enunciado.
    Caso julgue relevante, pode criar funçoes auxiliares dentro deste ficheiro .c.

f.	Os restantes ficheiros do projeto nao podem ser alterados.
    Deve garantir que o ficheiro que entrega continua compativel com o resto do projeto.
*/



// Nome completo: Gonçalo Rodrigues Pereira
// Número de aluno: 2025161479

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"


void eliminaLista(pnodr lista){
    pnodr aux;

    while(lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

pnodr criaLista(nodr tab[], int tam){
    int i;
    pnodr lista=NULL, novo;

    for(i=tam-1; i>=0; i--){
        novo = malloc(sizeof(nodr));
        if(novo == NULL){
            eliminaLista(lista);
            return NULL;
        }
        *novo = tab[i];
        novo->prox = lista;
        lista = novo;
    }
    return lista;
}

void mostraLista(pnodr lista){
    printf("{ ");
    while(lista != NULL){
        printf("%s-%d", lista->id, lista->bat);
        lista = lista->prox;
        if(lista!=NULL)
            printf(", ");
    }
    printf(" }");
}



// Se achar necessario, pode escrever aqui funcoes auxiliares







// Final da seccao com funcoes auxiliares

// Escreva a funcao desafio3(), de acordo com o descrito no enunciado
pnodr desafio3(pnodr lista) {
    int tamlista = 0;
    pnodr aux = lista, ant = NULL;
    pnodr max_ant = NULL, max_no = NULL, ultimo = NULL;

    if (lista == NULL)
        return NULL;
    // Conta número de nós
    while (aux != NULL) {
        tamlista++;
        aux = aux->prox;
    }
    //1
    if (tamlista < 2)
        return lista;
    //2
    if (tamlista % 2 == 0) {
        pnodr a_rem = lista->prox;
        lista->prox = a_rem->prox;
        free(a_rem);
    }
    // Procura o nó com maior bat e o último nó
    int max_bat = -1;
    aux = lista;
    ant = NULL;
    while (aux != NULL) {
        if (aux->bat > max_bat) {
            max_bat = aux->bat;
            max_no = aux;
            max_ant = ant;
        }
        ant = aux;
        ultimo = aux;
        aux = aux->prox;
    }
    // se a lista for ímpar E o maior não for já o último, move o maior para o fim
    if (tamlista % 2 != 0 && max_no != ultimo) {
        if (max_ant == NULL) {
            lista = max_no->prox;
        } else {
            max_ant->prox = max_no->prox;
        }
        ultimo->prox = max_no;
        max_no->prox = NULL;
    }
    return lista;
}