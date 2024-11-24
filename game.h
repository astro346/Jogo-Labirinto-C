#ifndef GAME_H
#define GAME_H

// Definição da struct Player
typedef struct {
    int x, y;   // Posições do jogador
    int score;  // Pontuação do jogador
} Player;

void initializeBoard(int **board);        
void loadPhase(int phase, int **board);  
void printBoard(int **board, Player player, int timeLeft); // Imprime o tabuleiro e o tempo restante
int moverPlayer(int **board, Player *player, char move);    
void startGame();   

#endif 

