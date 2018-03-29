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

#include "screen.h"

struct snake {
    int coordinatey;
    int coordinatex;
    Snake* next;
};

struct screen {
    int coordinatey;
    int coordinatex;
    Snake* snake;
};

int draw_menu() {
//    clear();
//    mvprintw(LINES / 2, COLS / 2, "Snake Game");
//    printw("%d", LINES);
//    printw("%d", COLS);
}

int init_mode_cursor() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE); //teclas do teclado funcionarem
    curs_set(0); //desabilitar cursor
    timeout(100);
}

int key_pressed(int old_dir) {
    int new_dir = getch();
    switch (new_dir) {
        case left:
            if (old_dir != right) {
                return left;
            }
        case right:
            if (old_dir != left) {
                return right;
            }
        case down:
            if (old_dir != up) {
                return down;
            }
        case up:
            if (old_dir != down) {
                return up;
            }
        default:
            return old_dir;
    }
}

void end_window() {
    endwin();
}