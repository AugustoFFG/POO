#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "estruturas.h"

extern Lista* lista;

int main() {
    lerArquivo("agenda.txt");
    
    printf("\n=== Imprimindo durações de todas as posições da lista ===\n");
    if (lista != NULL) {
        // chama a função que soma durações a partir do arquivo de posições
        somarDuracoes("posicoes.txt");
        
        printf("\n=== Imprimindo prioridades finais de todos os itens ===\n");
        prioridadeFinal();
    }
    else{
        printf("Lista vazia. Nenhum item lido.\n");
    }
    
    return 0;
}