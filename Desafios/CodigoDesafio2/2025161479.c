
/* NOTAS IMPORTANTES

Devem efetuar as seguintes alteracoes:

a.	Alterar o nome do ficheiro, que deve passar a ser o do vosso numero de aluno e mantendo a extensao .c.
    Caso o vosso numero de aluno seja 20251234, devem submeter um ficheiro com nome 20251234.c

b.	Quando efetuarem a alteracao da alinea anterior, tenham cuidado para não alterar o nome dos
    ficheiros de cabeçalho (header files) que surgem no inicio do codigo.
    O refactoring do CLion pode alterar o nome dos ficheiros .h e isso nao pode acontecer no ficheiro que submeterem.
    Confiram a linha 35 do ficheiro que deve continuar a ser #include "voo.h".

c.	Após concluirem a submissao, confirmem que o ficheiro tem o nome correto.
    Se não cumprirem as regras das alineas a) e b) ficarao sem nota atribuida

d.	Completar a vossa identificaca nas linhas 28 e 29 do ficheiro.

e.	Escrever a funcao desafio2(), de acordo com o que é solicitado no enunciado.
    Esta funcao não deve escrever nada na consola, efetuando apenas as operacoes descritas no enunciado.
    Caso julgue relevante, pode criar funçoes auxiliares dentro deste ficheiro .c.

f.	Os restantes ficheiros do projeto nao podem ser alterados.
    Deve garantir que o ficheiro que entrega continua compativel com o resto do projeto.

*/

// Nome completo:Gonçalo Rodrigues Pereira
// Número de aluno:2025161479


#include <stdio.h>
#include <string.h>

#include "voo.h"

void printVoo(voo a) {
    int i;

    printf("%s (%2.2d-%2.2d): %s - %s - %d\n",
        a.codigo, a.partida.dia, a.partida.mes, a.origem, a.destino, a.lugares);
}

void printTab(voo a[], int tam) {
    int i;

    for (i=0; i<tam; i++)
        printVoo(a[i]);

}



// Se achar necessario, pode escrever aqui funcoes auxiliares




 



 /* Escreva a funcao desafio 2.
 Esta funcao recebe uma tabela de estruturas do tipo voo.
 Quando entra na funcao, a tabela nao esta ordenada por nenhum criterio.

 A funcao deve efetuar as seguintes operacoes:

1. Encontrar voo com menos lugares livres. Em caso de empate selecionar o que tem codigo alfabeticamente menor.
 Este voo deve ser colocado na primeira posicao da tabela, efetuando uma troca direta com o que lá se encontra.

2. Contar quantos voos existem entre duas cidades num determinado intervalo de tempo:
   por exemplo, contabilizar quantos voos existem que partam da Lisboa e aterrem no Porto entre 12/03 e 18/4.

   A função recebe os seguintes parâmetros:
   - Endereço inicial da tabela de voos (tab);
   - Dimensão da tabela de voos (tam);
   - Cidades origem e destino a considerar na contabilização de voos (or e dest)
   - Datas limites a considerar na contabilização de voos (lInf e lSup).

   A função devolve o numero de voos contabilizados na operação 2.
*/

int desafio2(voo tab[], int tam, char *or, char *dest, data lInf, data lSup){
    int i;
    int menorlugar = 0;
    voo aux;
//1
    for (i=1; i<tam-1;i++){
        if (tab[i].lugares < tab[menorlugar].lugares) {
                menorlugar = i;
            }
            // strcmp compara o numero de caracteres do tab[i] do codigo e do menor lugar,
            // se o tab i for menor que zero, sendo alfabeticamente maior, o menor lugra fica com o valor do indice. 
        else if (tab[i].lugares == tab[menorlugar].lugares) {
                if (strcmp(tab[i].codigo, tab[menorlugar].codigo) < 0) {
                    menorlugar = i;
                }
            }
    }
    aux = tab[0];
    tab[0] = tab[menorlugar];
    tab[menorlugar] = aux;
//2
    int contador = 0;
    for (i = 0; i < tam; i++) {
        // Verificar Cidades
        if (strcmp(tab[i].origem, or) == 0 && strcmp(tab[i].destino, dest) == 0) {
            // Verificar se Data >= lInf
            int inf = (tab[i].partida.mes > lInf.mes) || (tab[i].partida.mes == lInf.mes && tab[i].partida.dia >= lInf.dia);
            // Verificar se Data <= lSup
            int sup = (tab[i].partida.mes < lSup.mes) || (tab[i].partida.mes == lSup.mes && tab[i].partida.dia <= lSup.dia);
            //se as duas condições forem verdadeiras, incrementa o contador
            if (inf && sup) {
                contador++;
            }
        }
    }
    return contador; // A função deve devolver o valor contabilizado
}
