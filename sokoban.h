#ifndef SOKOBAN_H
#define SOKOBAN_H

#define WIDTH 10
#define HEIGHT 10

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    char grid[HEIGHT][WIDTH]; 
    Position player;          
    Position box;             
    Position goal;            
} Game;

void init_game(Game *game);
void display_game(const Game *game);
void process_input(Game *game, char input);
int is_game_won(const Game *game);
int is_game_lost(const Game *game);

#endif
