

#include <time.h>
#include "list.h"
#include <ncurses.h>

struct snake {
    int coordinatey;
    int coordinatex;
    Snake* next;
};

struct screen {
    Snake* snake;
    int coordinatey;
    int coordinatex;
};

Screen* init_game(int y, int x) {
    Screen* screen = create_screen(y, x);
    int middley = calculate_middle_screen(y);
    int middlex = calculate_middle_screen(x);
    screen->snake = create_snake(middley, middlex);
    return screen;
}

Screen* create_screen(int y, int x) {
    Screen* screen = (Screen*) malloc(sizeof (Screen));
    if (screen != NULL) {
        screen->coordinatey = y;
        screen->coordinatex = x;
        return screen;
    }
    //lembrar de pesquisar como mandar erro pra tela
    return NULL;
}

int calculate_middle_screen(int value) {
    return value / 2;
}

void print_snake(Screen* screen) {
    Snake* snake = screen->snake;
    while (snake != NULL) {
        mvaddch(snake->coordinatey, snake->coordinatex, ACS_DIAMOND);
        snake = snake->next;
    }
}

//return some error e.g.

Snake* create_snake(int y, int x) {
    //    int middley = calculate_middle_screen(y);
    //    int middlex = calculate_middle_screen(x);
    Snake* snake = (Snake*) malloc(sizeof (Snake));
    if (snake != NULL) {
        snake->coordinatey = y;
        snake->coordinatex = x;
        return snake;
    }
}

void kill_screen() {
    endwin();
}

void free_snake(Snake* snake) {
    Snake* p = snake;
    while (p != NULL) {
        Snake* t = p->next; /* guarda refer�ncia p/ pr�x. elemento */
        free(p); /* libera a mem�ria apontada por p */
        p = snake; /* faz p apontar para o pr�ximo */
    }

}

void free_board(Screen* screen) {
    free(screen);
}

Snake* calculate_coordinate(int y, int x, int newDirection) {
    printf("%d", newDirection);
    switch (newDirection) {
        case left:
            x = x - 1;
            break;
        case right:
            x = x + 1;
            break;
        case up:
            y = y - 1;
            break;
        case down:
            y = y + 1;
            break;
        default:
            break;
    }
    return create_snake(y, x);
}

void d(Snake* snake, Snake* snakeTemp) {
    while (snake != NULL) {
        snake->coordinatey == snakeTemp->coordinatey && snake->coordinatex == snakeTemp->coordinatex;
        snake = snake->next;
    }
}

//novo cálculo passando as coordenadas

Snake* calculate_next_cell(Screen* screen, Snake* newSnake) {
    newSnake->next = screen->snake;
    screen->snake = newSnake;
    Snake* snakeTemp = screen->snake;

    while (snakeTemp->next->next) {
        snakeTemp = snakeTemp->next;
    }

    free(snakeTemp->next);
    snakeTemp->next = NULL;
}

void is_edge(Screen* screen) {
    // 43, 130
    if (screen->snake->coordinatey < 1 || screen->snake->coordinatex < 1 ||
            screen->snake->coordinatey > 42 || screen->snake->coordinatex > 129) {
        //        freeSnake(screen->snake);
        free_board(screen);
        endwin();
    }
}

int next_movement(Screen* screen, int movement) {
    Snake* snakeTemp = calculate_coordinate(screen->snake->coordinatey, screen->snake->coordinatex, movement);

    //checkNextMovementIsTheSame
    //checkIfCrashOnTheWall

    //checkTail
    //d(snake, snakeTemp);

    //check food

    //finally, move snake

    calculate_next_cell(screen, snakeTemp);

    is_edge(screen);

    print_snake(screen);
}
