#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sokoban.h"


void init_game(Game *game) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                game->grid[i][j] = '#'; // Mur
            else
                game->grid[i][j] = ' '; // Espace vide
        }
    }

    srand(time(NULL));
    game->player.x = rand() % (HEIGHT - 2) + 1;
    game->player.y = rand() % (WIDTH - 2) + 1;

    game->box.x = rand() % (HEIGHT - 2) + 1;
    game->box.y = rand() % (WIDTH - 2) + 1;

    game->goal.x = rand() % (HEIGHT - 2) + 1;
    game->goal.y = rand() % (WIDTH - 2) + 1;

    game->grid[game->player.x][game->player.y] = 'o'; // Joueur
    game->grid[game->box.x][game->box.y] = 'X';       // Boîte
    game->grid[game->goal.x][game->goal.y] = '.';     // Objectif
}

void display_game(const Game *game) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", game->grid[i][j]);
        }
        printf("\n");
    }
}

void process_input(Game *game, char input) {
    int new_x = game->player.x;
    int new_y = game->player.y;

    if (input == 'z') new_x--;    // Haut
    if (input == 's') new_x++;    // Bas
    if (input == 'q') new_y--;    // Gauche
    if (input == 'd') new_y++;    // Droite

    if (game->grid[new_x][new_y] == ' ' || game->grid[new_x][new_y] == '.') {
        game->grid[game->player.x][game->player.y] = ' ';
        game->player.x = new_x;
        game->player.y = new_y;
        game->grid[game->player.x][game->player.y] = 'o';
    } else if (new_x == game->box.x && new_y == game->box.y) { // Si la boîte est là
        int new_box_x = game->box.x + (new_x - game->player.x);
        int new_box_y = game->box.y + (new_y - game->player.y);

        if (game->grid[new_box_x][new_box_y] == ' ' || game->grid[new_box_x][new_box_y] == '.') {
            game->grid[game->box.x][game->box.y] = ' ';
            game->box.x = new_box_x;
            game->box.y = new_box_y;
            game->grid[game->box.x][game->box.y] = 'X';

            game->grid[game->player.x][game->player.y] = ' ';
            game->player.x = new_x;
            game->player.y = new_y;
            game->grid[game->player.x][game->player.y] = 'o';
        }
    }
}

int is_game_won(const Game *game) {
    return (game->box.x == game->goal.x && game->box.y == game->goal.y);
}

int is_game_lost(const Game *game) {
    int up = game->grid[game->box.x - 1][game->box.y] == '#';
    int down = game->grid[game->box.x + 1][game->box.y] == '#';
    int left = game->grid[game->box.x][game->box.y - 1] == '#';
    int right = game->grid[game->box.x][game->box.y + 1] == '#';
    return ((up && left) || (up && right) || (down && left) || (down && right));
}

int main() {
    Game game;
    char input;
    int playing = 1;

    init_game(&game);

    // Boucle principale du jeu
    while (playing) {
#ifdef _WIN32
        system("cls"); // Nettoyer le terminal pour Windows
#else
        system("clear"); // Nettoyer le terminal pour Unix/Linux/Mac
#endif
        display_game(&game); // Afficher la grille

        // Vérifier si le joueur a gagné ou perdu
        if (is_game_won(&game)) {
            printf("Bravo, vous avez gagné !\n");
            break;
        }
        if (is_game_lost(&game)) {
            printf("Dommage, vous avez perdu.\n");
            break;
        }

        // Demander à l'utilisateur de saisir un mouvement
        printf("Entrez un mouvement (z=haut, s=bas, q=gauche, d=droite) : ");
        scanf(" %c", &input);

        // Gérer le mouvement
        process_input(&game, input);
    }

    return 0;
}

