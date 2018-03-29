

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

void print_food(Screen* screen) {
    Food* food = screen->food;
    mvaddch(food->coordinatey, food->coordinatex, ACS_BLOCK);
}

//return some error e.g.

Snake* create_snake(int y, int x) {
    Snake* snake = (Snake*) malloc(sizeof (Snake));
    if (snake != NULL) {
        snake->coordinatey = y;
        snake->coordinatex = x;
        return snake;
    }
    return NULL;
}

void kill_screen() {
    endwin();
}

void free_snake(Snake* snake) {
    if (snake->next != NULL) {
        free_snake(snake->next);
    }
    free(snake);

}

void free_screen(Screen* screen) {
    free(screen);
}

Snake * calculate_coordinate(int y, int x, int newDirection) {
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

bool d(Screen* screen, Snake* snakeTemp) {
    Snake* snake = screen->snake;
    while (snake != NULL) {
        if (snake->coordinatey == snakeTemp->coordinatey && snake->coordinatex == snakeTemp->coordinatex) {
            return TRUE;
        }
        snake = snake->next;
    }
    return FALSE;
}

//novo cálculo passando as coordenadas

Screen* calculate_next_cell(Screen* screen, Snake* newSnake) {
    newSnake->next = screen->snake;
    screen->snake = newSnake;
    Snake* snakeTemp = screen->snake;
    while (snakeTemp->next->next) {
        snakeTemp = snakeTemp->next;
    }
    free(snakeTemp->next);
    snakeTemp->next = NULL;
    return screen;
}

bool movement_is_valid(Snake* snake) {
    if (snake->coordinatey < 1 || snake->coordinatex < 1 || snake->coordinatey > size_screen_y || snake->coordinatex > size_screen_x) {
        return FALSE;
    }
    return TRUE;
}

bool find_food(Screen* screen, Snake* snake, int movement) {
    if (snake->coordinatey == screen->food->coordinatey && snake->coordinatex == screen->food->coordinatex) {
        Snake* snakeTemp = calculate_coordinate(screen->snake->coordinatey, screen->snake->coordinatex, movement);
        snakeTemp->next = screen->snake;
        screen->snake = snakeTemp;
        return TRUE;
    }
    return FALSE;
}

bool next_movement(Screen* screen, int movement) {
    bool v = TRUE;
    Snake* snakeTemp = calculate_coordinate(screen->snake->coordinatey, screen->snake->coordinatex, movement);

    //checkIfCrashOnTheWall
    v = movement_is_valid(snakeTemp);
    //checkNextMovementIsTheSame

    //checkTail
    if (d(screen, snakeTemp)) {
        v = FALSE;
    }
    screen = calculate_next_cell(screen, snakeTemp);
    //check food
    if (find_food(screen, snakeTemp, movement)) {
        create_food(screen);
    }

    //finally, move snake
    print_snake(screen);
    return v;
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
}