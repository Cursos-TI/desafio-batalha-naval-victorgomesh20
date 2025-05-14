#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define OCUPADO 3
#define AGUA 0

// Função para verificar se um navio pode ser posicionado sem ultrapassar os limites ou sobrepor outro
int pode_posicionar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (orientacao == 'H') {  // Horizontal
            if (coluna + i >= TAM_TABULEIRO || tabuleiro[linha][coluna + i] != AGUA) {
                return 0; // Fora do limite ou já ocupado
            }
        } else if (orientacao == 'V') {  // Vertical
            if (linha + i >= TAM_TABULEIRO || tabuleiro[linha + i][coluna] != AGUA) {
                return 0; // Fora do limite ou já ocupado
            }
        }
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionar_navio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (orientacao == 'H') {
            tabuleiro[linha][coluna + i] = OCUPADO;
        } else if (orientacao == 'V') {
            tabuleiro[linha + i][coluna] = OCUPADO;
        }
    }
}

// Função para imprimir o tabuleiro
void imprimir_tabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa o tabuleiro com 0 (água)
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Coordenadas iniciais dos navios (podem ser alteradas conforme o desejado)
    int linhaH = 2, colunaH = 3; // Navio horizontal começa na linha 2, coluna 3
    int linhaV = 5, colunaV = 7; // Navio vertical começa na linha 5, coluna 7

    // Verifica e posiciona o navio horizontal
    if (pode_posicionar(tabuleiro, linhaH, colunaH, 'H')) {
        posicionar_navio(tabuleiro, linhaH, colunaH, 'H');
    } else {
        printf("Não foi possível posicionar o navio horizontal.\n");
    }

    // Verifica e posiciona o navio vertical
    if (pode_posicionar(tabuleiro, linhaV, colunaV, 'V')) {
        posicionar_navio(tabuleiro, linhaV, colunaV, 'V');
    } else {
        printf("Não foi possível posicionar o navio vertical.\n");
    }

    // Exibe o tabuleiro com os navios posicionados
    imprimir_tabuleiro(tabuleiro);

    return 0;
}
