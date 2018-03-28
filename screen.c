/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   screen.c
 * Author: Anderson Souza <jair_anderson_bs@hotmail.com>
 *
 * Created on March 27, 2018, 8:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "screen.h"

struct screen {
    int coordinatey;
    int coordinatex;
    Snake* snake;
};

struct snake {
    int coordinatey;
    int coordinatex;
    Snake* next;
};

int draw_menu() {
    //escrever menu
}

int init_mode_cursor() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE); //teclas do teclado funcionarem
    curs_set(0); //desabilitar cursor
    timeout(100);
}

Screen* initGame(int y, int x) {
    Screen* screen = createScreen(y, x);
    screen->snake = createSnake(y, x);
    return screen;
}

int calculateMiddleScreen(int value) {
    return value / 2;
}

Screen* createScreen(int y, int x) {
    Screen* screen = (Screen*) malloc(sizeof (Screen));
    if (screen != NULL) {
        screen->coordinatey = y;
        screen->coordinatex = x;
        return screen;
    }
    return NULL;
}

Snake* createSnake(int y, int x) {
    int middley = calculateMiddleScreen(y);
    int middlex = calculateMiddleScreen(x);
    Snake* snake = (Snake*) malloc(sizeof (Snake));
    if (snake != NULL) {
        snake->coordinatey = middley;
        snake->coordinatex = middlex;
        return snake;
    }
    return NULL;
}

void printSnake(Snake* snake) {
    while (snake != NULL) {
        mvaddch(snake->coordinatey, snake->coordinatex, ACS_DIAMOND);
        snake = snake->next;
    }
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

Snake* createNewSnake(int y, int x) {
    Snake* snake = (Snake*) malloc(sizeof (Snake));
    snake->coordinatey = y;
    snake->coordinatex = x;
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
        freeSnake(screen->snake);
        freeBoard(screen);
        endwin();
    }
}

void freeSnake(Snake* snake) {
    Snake* snakeTemp = snake;
    if ((snakeTemp->next->next) != NULL) {
        // snakeTemp = snakeTemp->next;
        freeSnake(snake->next);
        free(snake);
    }
}

void freeBoard(Screen* screen) {
    free(screen);
}

void endWindow() {
    endwin();
}