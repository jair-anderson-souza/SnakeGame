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

int key_pressed(int previous) {
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