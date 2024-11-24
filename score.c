#include <stdio.h>
#include "score.h"

typedef struct {
    int score;
} PlayerScore;

// Função para salvar a pontuação no arquivo binário
void saveScore(int score) {
    FILE *file = fopen("scores.bin", "ab");
    if (file == NULL) {
        printf("Erro ao salvar a pontuação\n");
        return;
    }

    PlayerScore ps = {score};
    fwrite(&ps, sizeof(PlayerScore), 1, file);
    fclose(file);
}

// Função para exibir as estatísticas
void displayStats() {
    FILE *file = fopen("scores.bin", "rb");
    if (file == NULL) {
        printf("Nenhuma pontuação salva.\n");
        return;
    }

    PlayerScore ps;
    printf("\n--- Estatísticas ---\n");
    while (fread(&ps, sizeof(PlayerScore), 1, file)) {
        printf("Pontuação: %d\n", ps.score);
    }
    fclose(file);
}
