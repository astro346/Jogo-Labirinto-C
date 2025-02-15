#include "game.h"
#include "score.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define MAX_LINHAS 10
#define MAX_COLUNAS 10
#define NUM_PHASES 5

void initializeBoard(int **board) {
    for (int i = 0; i < MAX_LINHAS; i++) {
        for (int j = 0; j < MAX_COLUNAS; j++) {
            board[i][j] = 0; // Espa�o vazio
        }
    }

    // Adiciona paredes ao redor do tabuleiro
    for (int i = 0; i < MAX_LINHAS; i++) {
        for (int j = 0; j < MAX_COLUNAS; j++) {
            if (i == 0 || i == MAX_LINHAS - 1 || j == 0 || j == MAX_COLUNAS - 1) {
                board[i][j] = 1; // Paredes
            }
        }
    }
}

void loadPhase(int phase, int **board) {
    FILE *file;
    char filename[20];

    // L� o nome do arquivo da fase de forma din�mica
    snprintf(filename, sizeof(filename), "fase%d.txt", phase);
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Erro ao carregar a fase %d\n", phase);
        return;
    }

    for (int i = 0; i < MAX_LINHAS; i++) {
        for (int j = 0; j < MAX_COLUNAS; j++) {
            fscanf(file, "%d", &board[i][j]); // Preenche o tabuleiro
        }
    }

    fclose(file);
}

// Fun��o para posicionar o jogador em um espa�o v�lido.
void positionPlayer(int **board, Player *player) {
    int validPositionFound = 0;
    while (!validPositionFound) {
        int x = rand() % (MAX_LINHAS - 2) + 1;
        int y = rand() % (MAX_COLUNAS - 2) + 1;

        if (board[x][y] == 0) { // Se for um espa�o vazio (0), vai colocar o jogador
            player->x = x;
            player->y = y;
            validPositionFound = 1;
        }
    }
}
// Fun��o para colocar a sa�da em uma posi��o aleat�ria nas bordas que seja um (0)
void positionExit(int **board) {
    int validPositions[MAX_LINHAS + MAX_COLUNAS * 2][2]; // Array para armazenar posi��es v�lidas nas bordas
    int count = 0;

    // Verifica a borda superior
    for (int j = 0; j < MAX_COLUNAS; j++) {
        if (board[0][j] == 0) { // Borda superior
            validPositions[count][0] = 0;
            validPositions[count][1] = j;
            count++;
        }
    }

    // Verifica a borda inferior 
    for (int j = 0; j < MAX_COLUNAS; j++) {
        if (board[MAX_LINHAS - 1][j] == 0) { // Borda inferior
            validPositions[count][0] = MAX_LINHAS - 1;
            validPositions[count][1] = j;
            count++;
        }
    }

    // Verifica a borda esquerda 
    for (int i = 1; i < MAX_LINHAS - 1; i++) {  // Evita duplicar os cantos superior e inferior
        if (board[i][0] == 0) { // Borda esquerda
            validPositions[count][0] = i;
            validPositions[count][1] = 0;
            count++;
        }
    }

    // Verifica a borda direita 
    for (int i = 1; i < MAX_LINHAS - 1; i++) {  // Evita duplicar os cantos superior e inferior
        if (board[i][MAX_COLUNAS - 1] == 0) { // Borda direita
            validPositions[count][0] = i;
            validPositions[count][1] = MAX_COLUNAS - 1;
            count++;
        }
    }

    // Se houver posi��es v�lidas, escolhe uma aleatoriamente
    if (count > 0) {
        int randomIndex = rand() % count; 
        int x = validPositions[randomIndex][0];
        int y = validPositions[randomIndex][1];
        board[x][y] = 2; 
    } else {
        printf("Erro: N�o h� posi��es v�lidas nas bordas para colocar a sa�da.\n");
    }
}
// Fun��o para imprimir o tabuleiro
void printBoard(int **board, Player player, int stepsLeft) {
    printf("\nPassos restantes: %d\n", stepsLeft);
    printf("Score: %d\n", player.score);
    for (int i = 0; i < MAX_LINHAS; i++) {
        for (int j = 0; j < MAX_COLUNAS; j++) {
            if (i == player.x && j == player.y) {
                printf("J  "); // Jogador
            } else if (board[i][j] == 0) {
                printf("-  "); // Espa�o vazio
            } else if (board[i][j] == 1) {
                printf("|  "); // Paredes
            } else if (board[i][j] == 2) {
                printf("S  "); // Sa�da
            }
        }
        printf("\n");
    }
}

// Fun��o para mover o jogador
int moverPlayer(int **board, Player *player, char move) {
    int newX = player->x;
    int newY = player->y;

    // Processa o movimento baseado na entrada
    if (move == 'w') newX--; // Subir
    else if (move == 's') newX++; // Descer
    else if (move == 'a') newY--; // Esquerda
    else if (move == 'd') newY++; // Direita

    // Verifica se o movimento n�o sai dos limites e n�o colide com as paredes
    if (newX >= 0 && newX < MAX_LINHAS && newY >= 0 && newY < MAX_COLUNAS && board[newX][newY] != 1) {
        player->x = newX;
        player->y = newY;

        // Verifica se o jogador chegou � sa�da
        if (board[player->x][player->y] == 2) {
            return 1; // Chegou � sa�da
        }
    }

    return 0; // N�o chegou ainda
}

// Fun��o para come�ar o jogo com limite de passos
void startGame() {
    int **board;
    board = (int **)malloc(MAX_LINHAS * sizeof(int *));
    for (int i = 0; i < MAX_LINHAS; i++) {
        board[i] = (int *)malloc(MAX_COLUNAS * sizeof(int));
    }

    Player player = {0, 0, 0}; // Jogador come�a na posi��o (0, 0)
    int phase = 1;
    char move;
    int levelComplete;
    int stepsLeft;

    // A cada fase, o jogador passa para a pr�xima fase ap�s atingir a sa�da
    while (phase <= NUM_PHASES) {
        initializeBoard(board); // Inicializa o tabuleiro
        loadPhase(phase, board); // Carrega a fase
        positionPlayer(board, &player); // Posiciona o jogador

        // Define o limite de passos para cada fase (agora 30 passos para cada fase)
        stepsLeft = 30;

        // Posiciona a sa�da de forma v�lida
        positionExit(board);

        levelComplete = 0;
        while (!levelComplete) {
            printBoard(board, player, stepsLeft); // Exibe o tabuleiro e os passos restantes
            printf("Movimente-se (W - Cima, S - Baixo, A - Esquerda, D - Direita): ");
            scanf(" %c", &move); // Leitura do movimento com limpeza de buffer

            levelComplete = moverPlayer(board, &player, move); // Movimenta o jogador

            // Decrementa os passos restantes a cada movimento
            stepsLeft--;

            // Se o jogador esgotar os passos, ele perde a fase
            if (stepsLeft <= 0) {
                printf("Voc� ficou sem passos! Voc� perdeu a fase %d!\n", phase);
                levelComplete = -1; // Perde a fase
                break;
            }

            if (levelComplete) {
                printf("Voc� completou a fase %d!\n", phase);
                player.score += 100; // Pontua��o por completar a fase
                phase++; // Avan�a para a pr�xima fase
                break; // Sai do loop interno para iniciar a pr�xima fase
            }
        }

        if (levelComplete == -1) {
            break; // Se o jogador perdeu, o jogo termina
        }
    }

    // Final do jogo
    printf("Jogo Finalizado! Pontua��o Final: %d\n", player.score);
    saveScore(player.score); // Salva o placar

    // Libera a mem�ria
    for (int i = 0; i < MAX_LINHAS; i++) {
        free(board[i]);
    }
    free(board);
}
