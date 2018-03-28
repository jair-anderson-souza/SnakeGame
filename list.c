

#include <time.h>
#include "list.h"
#include <ncurses.h>
#define size_screen_y getmaxy(stdscr)
#define size_screen_x getmaxx(stdscr)

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

Screen* createScreen(Snake* snake) {
    Screen* screen = (Screen*) malloc(sizeof (Screen));
    if (screen != NULL) {
        screen->coordinatey = size_screen_y;
        screen->coordinatex = size_screen_x;
        screen->snake = snake;
        return screen;
    }
    //lembrar de pesquisar como mandar erro pra tela
    return NULL;
}

int calculateMiddleScreen(int value) {
    return value / 2;
}

//return some error e.g.

Snake* createSnake() {
    int middley = calculateMiddleScreen(size_screen_y);
    int middlex = calculateMiddleScreen(size_screen_x);
    Snake* snake = (Snake*) malloc(sizeof (Snake));
    if (snake != NULL) {
        snake->coordinatey = middley;
        snake->coordinatex = middlex;
        return snake;
    }
}

void killScreen() {
    endwin();
}

void freeSnake(Snake* snake) {
    Snake* p = snake;
    while (p != NULL) {
        Snake* t = p->next; /* guarda refer�ncia p/ pr�x. elemento */
        free(p); /* libera a mem�ria apontada por p */
        p = snake; /* faz p apontar para o pr�ximo */
    }

}

void freeBoard(Screen* screen) {
    free(screen);
}

Snake* createNewSnake(int y, int x) {
    Snake* snake = (Snake*) malloc(sizeof (Snake));
    snake->coordinatey = y;
    snake->coordinatex = x;
}

Snake* calculateCoordinate(int y, int x, int newDirection) {
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
    return createNewSnake(y, x);
}

int keyPressed(int previous) {
    int keyPressed = getch();
    switch (keyPressed) {
        case left:
            if (previous != right) {
                return left;
            }
        case right:
            if (previous != left) {
                return right;
            }
        case down:
            if (previous != up) {
                return down;
            }
        case up:
            if (previous != down) {
                return up;
            }
        default:
            return previous;
    }
}

void d(Snake* snake, Snake* snakeTemp) {
    while (snake != NULL) {
        snake->coordinatey == snakeTemp->coordinatey && snake->coordinatex == snakeTemp->coordinatex;
        snake = snake->next;
    }
}

//novo cálculo passando as coordenadas

Snake* calculateNextCell(Screen* screen, Snake* newSnake) {
    newSnake->next = screen->snake;
    screen->snake = newSnake;
    Snake* snakeTemp = screen->snake;

    while (snakeTemp->next->next) {
        snakeTemp = snakeTemp->next;
    }

    free(snakeTemp->next);
    snakeTemp->next = NULL;
}

void isEdge(Screen* screen) {
    // 43, 130
    if (screen->snake->coordinatey < 1 || screen->snake->coordinatex < 1 ||
            screen->snake->coordinatey > 42 || screen->snake->coordinatex > 129) {
        //        freeSnake(screen->snake);
        freeBoard(screen);
        endwin();
    }
}

int nextMovement(Screen* screen, int movement) {

    Snake* snakeTemp = calculateCoordinate(screen->snake->coordinatey, screen->snake->coordinatex, movement);

    // printw("%d\n", snakeTemp->coordinatey);
    int a = getch();
    //checkNextMovementIsTheSame
    //checkIfCrashOnTheWall

    //checkTail
    //d(snake, snakeTemp);

    //check food

    //finally, move snake

    calculateNextCell(screen, snakeTemp);

    isEdge(screen);

    printSnake(screen->snake);
}
