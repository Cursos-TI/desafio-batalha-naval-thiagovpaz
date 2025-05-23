#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


// Desafio Batalha Naval - MateCheck

#define TAMANHO_TABULEIRO 10
#define TOTAL_NAVIOS 4


void desenhaCone(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                 int linha, int coluna, int tamanho, int id) {
    for (int i = 0; i < tamanho; i++) {
        int atual_linha = linha + i;
        int inicio_coluna = coluna - i;
        int fim_coluna = coluna + i;

        for (int j = inicio_coluna; j <= fim_coluna; j++) {
            if (atual_linha >= 0 && atual_linha < TAMANHO_TABULEIRO &&
                j >= 0 && j < TAMANHO_TABULEIRO) {
                tabuleiro[atual_linha][j] = id;
            }
        }
    }
}

void desenhaCruz(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                 int linha, int coluna, int tamanho, int id) {
    int offset = tamanho / 2;
    for (int i = -offset; i <= offset; i++) {
        if (linha + i >= 0 && linha + i < TAMANHO_TABULEIRO)
            tabuleiro[linha + i][coluna] = id;
        if (coluna + i >= 0 && coluna + i < TAMANHO_TABULEIRO)
            tabuleiro[linha][coluna + i] = id;
    }
}

void desenhaOctaedro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linha, int coluna, int tamanho, int id) {
    int offset = tamanho / 2;
    for (int i = -offset; i <= offset; i++) {
        for (int j = -offset; j <= offset; j++) {
            if (abs(i) + abs(j) <= offset) {
                int l = linha + i;
                int c = coluna + j;
                if (l >= 0 && l < TAMANHO_TABULEIRO && c >= 0 && c < TAMANHO_TABULEIRO) {
                    tabuleiro[l][c] = id;
                }
            }
        }
    }
}


bool posicao_valida(int linha, int coluna) {
    return linha >= 0 && linha < TAMANHO_TABULEIRO &&
           coluna >= 0 && coluna < TAMANHO_TABULEIRO;
}

bool posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                      int linha_inicio, int coluna_inicio,
                      int tamanho, char direcao, int id_navio) {
    int d_linha = 0, d_coluna = 0;

    
    switch (direcao) {
        case 'H': d_coluna = 1; break;         // Horizontal
        case 'V': d_linha = 1; break;          // Vertical
        case 'D': d_linha = 1; d_coluna = 1; break; // Diagonal ↘
        case 'E': d_linha = 1; d_coluna = -1; break; // Diagonal ↙
        default: return false;
    }

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
    
    int linhas[TOTAL_NAVIOS]        =  { 0, 0, 5, 2 };
    char colunas[TOTAL_NAVIOS]      =  { 'A', 'H', 'F', 'C' };
    int tamanhos[TOTAL_NAVIOS]      =  { 3, 3, 3, 3 };
    char direcoes[TOTAL_NAVIOS]     =  { 'H', 'V', 'D', 'E' };
    int ids[TOTAL_NAVIOS]      =  { 1, 2, 3, 4 };

    // Posiciona os navios
    for (int i = 0; i < TOTAL_NAVIOS; i++) {
        int linha = linhas[i];
        int coluna = colunas[i] - 'A';

        if (!posicionar_navio(tabuleiro, linha, coluna, tamanhos[i], direcoes[i], ids[i + 1])) {
            printf("Falha ao posicionar navio %d.\n", ids[i +1]);
        }
    }

    // Com inicio em 0 e centro em 0
    desenhaCone(tabuleiro, 0, 0, 3, 1);
    // Com inicio em 5 e centro em 5
    desenhaCruz(tabuleiro, 5, 5, 5, 1);  
    // Com inicio em 7 e centro em 2    
    desenhaOctaedro(tabuleiro, 7, 2, 5, 1);
     
    printf("\nTabuleiro:\n");
    imprimir_tabuleiro(tabuleiro);

    return 0;
}
