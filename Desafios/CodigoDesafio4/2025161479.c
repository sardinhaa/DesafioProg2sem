
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parque.h"

// Nome: Gonçalo Rodrigues Pereira
// Número: 2025161479


void libertaTudo(pCliente p){
    pCliente auxC;
    pAcesso auxA;

    while(p != NULL){
        while(p->lista != NULL){
            auxA = p->lista;
            p->lista = p->lista->prox;
            free(auxA);
        }
        auxC = p;
        p = p->prox;
        free(auxC);
    }
}

pCliente criaExemploED(cliente a[], acesso b[], int totC){
    int i, j, k=-1;

    pCliente lista = NULL, novoC;
    pAcesso novoA;

    for(i=0; i<totC; i++){
        k+=a[i].contador;
    }
    for(i=totC-1; i>=0; i--){
        novoC = malloc(sizeof(cliente));
        if(novoC == NULL){
            libertaTudo(lista);
            return NULL;
        }
        *novoC = a[i];
        novoC->prox = lista;
        lista = novoC;
        for(j=0; j<novoC->contador; j++){
            novoA = malloc(sizeof(acesso));
            if(novoA == NULL){
                libertaTudo(lista);
                return NULL;
            }
            *novoA = b[k--];
            novoA->prox = novoC->lista;
            novoC->lista = novoA;
        }
    }
    return lista;
}

void mostraTudo(pCliente p){
    pAcesso auxA;

    while(p != NULL){
        printf("\nUtilizador com id %d efetuou %d acessos\n", p->id, p->contador);
        auxA = p->lista;
        while(auxA != NULL){
            printf("Entrou as %2.2d:%2.2d. ", auxA->in.h, auxA->in.m);
            if(auxA->out.h == -1)
                printf("Ainda nao saiu do parque\n");
            else
                printf("Saiu as %2.2d:%2.2d\n", auxA->out.h, auxA->out.m);
            auxA = auxA->prox;
        }
        p = p->prox;
    }
}


// Criar funcoes auxiliares aqui



// Final das funcoes auxiliares

pCliente desafio4(pCliente lista, int *id) {
    pCliente atual = lista;
    int maxAcessos = -1, melhorId = -1;
    // P1
    while (atual != NULL) {
        int contaCompletas = 0;
        pAcesso auxA = atual->lista;

        while (auxA != NULL) {
            if (auxA->out.h != -1) 
                contaCompletas++;
            auxA = auxA->prox;
        }
        if (contaCompletas > maxAcessos || (contaCompletas == maxAcessos && atual->id > melhorId)) {
            if (contaCompletas > 0) {
                maxAcessos = contaCompletas;
                melhorId = atual->id;
            }
        }
        atual = atual->prox;
    }
    *id = melhorId;
    // P2
    if (lista != NULL) {
        pAcesso auxAcesso = lista->lista, anteriorA = NULL;
        int m_entradas, m_saidas;

        while (auxAcesso != NULL) {
            if (auxAcesso->out.h != -1) {
                m_entradas = auxAcesso->in.h * 60 + auxAcesso->in.m;
                m_saidas = auxAcesso->out.h * 60 + auxAcesso->out.m;

                if (m_saidas - m_entradas < 30) {
                    pAcesso eliminar = auxAcesso;
                    if (anteriorA == NULL) 
                        lista->lista = auxAcesso->prox;
                    else 
                        anteriorA->prox = auxAcesso->prox;
                    auxAcesso = auxAcesso->prox;
                    free(eliminar);
                    lista->contador--;
                    continue;
                }
            }
            anteriorA = auxAcesso;
            auxAcesso = auxAcesso->prox;
        }
        if (lista->lista == NULL) {
            pCliente tempC = lista;
            lista = lista->prox;
            free(tempC);
        }
    }
    return lista;
}