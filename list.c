

#include "list.h"

struct snake {
    int coordinatey;
    int coordinatex;
    Snake* next;
};

struct food {
    int coordinatey;
    int coordinatex;
};

struct screen {
    Snake* snake;
    Food* food;
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
        Snake* t = p->next;
        free(p);
        p = snake;
    }

}

void free_board(Screen* screen) {
    free(screen);
}

Snake* calculate_coordinate(int y, int x, int newDirection) {
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

bool movement_is_valid(Snake* snake) {
    // 43, 130
    if (snake->coordinatey < 1 || snake->coordinatex < 1 || snake->coordinatey > size_screen_y || snake->coordinatex > size_screen_x) {
        return FALSE;
    }
    return TRUE;
}

bool next_movement(Screen* screen, int movement) {
    Snake* snakeTemp = calculate_coordinate(screen->snake->coordinatey, screen->snake->coordinatex, movement);

    calculate_next_cell(screen, snakeTemp);

    print_snake(screen);

    return movement_is_valid(snakeTemp);
    //checkNextMovementIsTheSame

    //checkIfCrashOnTheWall

    //checkTail
    //d(snake, snakeTemp);

    //check food

    //finally, move snake


    //    return TRUE;
}

void create_food(Screen* screen) {
    time_t t;
    srand((unsigned) time(&t));
    int random_y = rand() % 43;
    int random_x = rand() % 130;
    Food* food = (Food*) malloc(sizeof (Food));
    food->coordinatey = random_y;
    food->coordinatex = random_x;
    screen->food = food;
    mvaddch(screen->food->coordinatey, screen->food->coordinatex, ACS_DIAMOND);
}