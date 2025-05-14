#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define OCUPADO 3
#define AGUA 0

// Função para verificar se o navio pode ser posicionado sem ultrapassar os limites ou sobrepor outro navio
int pode_posicionar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;

        if (orientacao == 'H') {
            c += i;
        } else if (orientacao == 'V') {
            l += i;
        } else if (orientacao == 'D') { // Diagonal ↘
            l += i;
            c += i;
        } else if (orientacao == 'I') { // Diagonal ↙ (inversa)
            l += i;
            c -= i;
        }

        // Verifica limites
        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO) {
            return 0;
        }

        // Verifica sobreposição
        if (tabuleiro[l][c] != AGUA) {
            return 0;
        }
    }

    return 1; // Pode posicionar
}

// Função para posicionar o navio na matriz do tabuleiro
void posicionar_navio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;

        if (orientacao == 'H') {
            c += i;
        } else if (orientacao == 'V') {
            l += i;
        } else if (orientacao == 'D') {
            l += i;
            c += i;
        } else if (orientacao == 'I') {
            l += i;
            c -= i;
        }

        tabuleiro[l][c] = OCUPADO;
    }
}

// Função para imprimir o tabuleiro de forma clara e alinhada
void imprimir_tabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d", j);
    }
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%2d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa o tabuleiro com água (0)
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Define os navios com coordenadas e orientações
    int navios[4][3] = {
        {2, 1, 'H'}, // horizontal na linha 2
        {0, 5, 'V'}, // vertical na coluna 5
        {4, 4, 'D'}, // diagonal ↘
        {1, 8, 'I'}  // diagonal ↙
    };

    // Posiciona os 4 navios
    for (int i = 0; i < 4; i++) {
        int linha = navios[i][0];
        int coluna = navios[i][1];
        char orientacao = (char)navios[i][2];

        if (pode_posicionar(tabuleiro, linha, coluna, orientacao)) {
            posicionar_navio(tabuleiro, linha, coluna, orientacao);
        } else {
            printf("Não foi possível posicionar o navio %d na posição (%d,%d) orientação '%c'.\n", i + 1, linha, coluna, orientacao);
        }
    }

    // Exibe o tabuleiro final com os navios
    imprimir_tabuleiro(tabuleiro);

    return 0;
}
