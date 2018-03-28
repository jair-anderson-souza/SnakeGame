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
    Snake* snake;
    int coordinatey;
    int coordinatex;
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

void endWindow() {
    endwin();
}