

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
    int middlex = calculate_middle_screen(x = x);
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

void freeSnake(Snake* snake) {
    if (snake->next != NULL) {
        freeSnake(snake->next);
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

int snake_touched_itself(Screen* screen, Snake* snakeTemp) {
    Snake* snake = screen->snake;
    while (snake != NULL) {
        if (snake->coordinatey == snakeTemp->coordinatey && snake->coordinatex == snakeTemp->coordinatex) {
            return 1;
        }
        snake = snake->next;
    }
    return 0;
}

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

int movement_not_crash_in_the_wall(Snake* snake) {
    if (snake->coordinatey < 1 || snake->coordinatex < 1 || snake->coordinatey > size_screen_y || snake->coordinatex > size_screen_x) {
        return 0;
    }
    return 1;
}


//refatorar esse método

int find_food(Screen* screen, Snake* snake, int movement) {
    if (snake->coordinatey == screen->food->coordinatey && snake->coordinatex == screen->food->coordinatex) {
        Snake* snakeTemp = calculate_coordinate(screen->snake->coordinatey, screen->snake->coordinatex, movement);
        snakeTemp->next = screen->snake;
        screen->snake = snakeTemp;
        return 1;
    }
    return 0;
}

//refatorar esse método, está uma porcaria

int next_movement(Screen* screen, int movement) {
    int movement_is_valid = 1;
    Snake* snakeTemp = calculate_coordinate(screen->snake->coordinatey, screen->snake->coordinatex, movement);

    movement_is_valid = movement_not_crash_in_the_wall(snakeTemp);

    if (snake_touched_itself(screen, snakeTemp)) {
        movement_is_valid = 0;
    }
    //colocar aqui uma condição ou método pra evitar segurar na direção e a cobra ficar indo sem parar
    screen = calculate_next_cell(screen, snakeTemp);

    if (find_food(screen, snakeTemp, movement)) {
        create_food(screen);
    }
    //finally, move snake
    return movement_is_valid;
}

void create_food(Screen* screen) {
    srand((unsigned) time(&t));
    int random_y = rand() % 43;
    int random_x = rand() % 130;
    Food* food = (Food*) malloc(sizeof (Food));
    food->coordinatey = random_y;
    food->coordinatex = random_x;
    screen->food = food;
}