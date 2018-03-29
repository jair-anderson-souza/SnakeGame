/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Anderson Souza <jair_anderson_bs@hotmail.com>
 *
 * Created on March 27, 2018, 7:32 PM
 */
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "screen.h"
#include "list.h"

#define size_screen_y getmaxy(stdscr)
#define size_screen_x getmaxx(stdscr)

int main(int argc, char** argv) {

    init_mode_cursor();
    int key = default_dir;
    bool next = TRUE;

    Screen* screen = init_game(size_screen_y, size_screen_x);

    create_food(screen);

    while (next) {
        clear();
        print_snake(screen);
        print_food(screen);
        //moveSnake(screen->snake, key);
        key = key_pressed(key);
        next = next_movement(screen, key);
        refresh();
    }
    //free snake
    //    Snake* snake = screen->snake;
    //    freeSnake(screen->snake);
    free_screen(screen);
    end_window();
    return 0;
}