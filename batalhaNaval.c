#include <stdio.h>
#include <stdbool.h>

// Desafio Batalha Naval - MateCheck

#define TAMANHO_TABULEIRO 10
#define TOTAL_NAVIOS 2

bool posicao_valida(int linha, int coluna) {
    return linha >= 0 && linha < TAMANHO_TABULEIRO &&
           coluna >= 0 && coluna < TAMANHO_TABULEIRO;
}

bool posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                      int linha_inicio, int coluna_inicio,
                      int tamanho, char direcao, int id_navio) {
    int d_linha = 0, d_coluna = 0;

    if (direcao == 'H') d_coluna = 1;     // Horizontal
    else if (direcao == 'V') d_linha = 1; // Vertical
    else return false;

    // Verifica se cabe no tabuleiro
    for (int i = 0; i < tamanho; i++) {
        int linha = linha_inicio + i * d_linha;
        int coluna = coluna_inicio + i * d_coluna;

        if (!posicao_valida(linha, coluna)) {
            printf("Erro: navio %d sai dos limites do tabuleiro.\n", id_navio);
            return false;
        }

        if (tabuleiro[linha][coluna] != 0) {
            printf("Erro: navio %d colide com outro navio.\n", id_navio);
            return false;
        }
    }

    // Posiciona o navio
    for (int i = 0; i < tamanho; i++) {
        int linha = linha_inicio + i * d_linha;
        int coluna = coluna_inicio + i * d_coluna;
        tabuleiro[linha][coluna] = 3; // Definido como 3
    }

    return true;
}

void imprimir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf(" %c", 'A' + i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};
    
    int linhas[TOTAL_NAVIOS]        =  { 0, 0 };
    char colunas[TOTAL_NAVIOS]      =  { 'A', 'H' };
    int tamanhos[TOTAL_NAVIOS]      =  { 3, 3 };
    char direcoes[TOTAL_NAVIOS]     =  { 'H', 'V' };
    int ids[TOTAL_NAVIOS]      =  { 1, 2 };

    // Posiciona os navios
    for (int i = 0; i < TOTAL_NAVIOS; i++) {
        int linha = linhas[i];
        int coluna = colunas[i] - 'A';

        if (!posicionar_navio(tabuleiro, linha, coluna, tamanhos[i], direcoes[i], ids[1])) {
            printf("Falha ao posicionar navio %d.\n", ids[1]);
        }
    }

     
    printf("\nTabuleiro:\n");
    imprimir_tabuleiro(tabuleiro);

    return 0;
}
