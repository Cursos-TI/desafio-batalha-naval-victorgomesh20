#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define OCUPADO 3
#define AGUA 0
#define HABILIDADE 5

// Inicializa o tabuleiro com água
void inicializar_tabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++)
        for (int j = 0; j < TAM_TABULEIRO; j++)
            tabuleiro[i][j] = AGUA;
}

// Verifica se um navio pode ser posicionado sem ultrapassar limites e sem sobreposição
int pode_posicionar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'I') { l += i; c -= i; }

        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO)
            return 0;
        if (tabuleiro[l][c] != AGUA)
            return 0;
    }
    return 1;
}

// Posiciona navio no tabuleiro
void posicionar_navio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'I') { l += i; c -= i; }
        tabuleiro[l][c] = OCUPADO;
    }
}

// Exibe o tabuleiro com caracteres visuais
void imprimir_tabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO; j++)
        printf("%2d", j);
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA) printf(" ~");
            else if (tabuleiro[i][j] == OCUPADO) printf(" N");
            else if (tabuleiro[i][j] == HABILIDADE) printf(" *");
            else printf(" ?");
        }
        printf("\n");
    }
}

// Aplica uma matriz de habilidade ao tabuleiro
void aplicar_habilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int origem_l, int origem_c, int habilidade[][7], int tam) {
    int offset = tam / 2;

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            if (habilidade[i][j] == 1) {
                int l = origem_l + i - offset;
                int c = origem_c + j - offset;
                if (l >= 0 && l < TAM_TABULEIRO && c >= 0 && c < TAM_TABULEIRO) {
                    if (tabuleiro[l][c] == AGUA) // Não sobrescreve navio
                        tabuleiro[l][c] = HABILIDADE;
                }
            }
        }
    }
}

// Gera matriz cone (5x5) — cresce para baixo
void gerar_matriz_cone(int matriz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = (j >= 2 - i && j <= 2 + i) ? 1 : 0;
}

// Gera matriz cruz (5x5)
void gerar_matriz_cruz(int matriz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = (i == 2 || j == 2) ? 1 : 0;
}

// Gera matriz octaedro (5x5) — forma de losango
void gerar_matriz_octaedro(int matriz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = (abs(2 - i) + abs(2 - j) <= 2) ? 1 : 0;
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializar_tabuleiro(tabuleiro);

    // Posicionamento fixo dos navios (2 retos, 2 diagonais)
    int navios[4][3] = {
        {2, 1, 'H'}, // horizontal
        {0, 5, 'V'}, // vertical
        {4, 4, 'D'}, // diagonal ↘
        {1, 8, 'I'}  // diagonal ↙
    };

    for (int i = 0; i < 4; i++) {
        int linha = navios[i][0];
        int coluna = navios[i][1];
        char orientacao = (char)navios[i][2];
        if (pode_posicionar(tabuleiro, linha, coluna, orientacao))
            posicionar_navio(tabuleiro, linha, coluna, orientacao);
        else
            printf("Falha ao posicionar navio %d\n", i + 1);
    }

    // Matrizes de habilidades
    int cone[5][5], cruz[5][5], octaedro[5][5];
    gerar_matriz_cone(cone);
    gerar_matriz_cruz(cruz);
    gerar_matriz_octaedro(octaedro);

    // Aplicando habilidades no tabuleiro (posições escolhidas manualmente)
    aplicar_habilidade(tabuleiro, 6, 2, cone, 5);      // Cone centrado em (6,2)
    aplicar_habilidade(tabuleiro, 3, 3, cruz, 5);      // Cruz centrada em (3,3)
    aplicar_habilidade(tabuleiro, 7, 7, octaedro, 5);  // Octaedro centrado em (7,7)

    // Imprime o tabuleiro com efeitos
    printf("\n=== Tabuleiro com Navios e Habilidades ===\n");
    imprimir_tabuleiro(tabuleiro);

    return 0;
}