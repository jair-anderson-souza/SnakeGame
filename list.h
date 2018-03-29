/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   list.h
 * Author: Anderson Souza <jair_anderson_bs@hotmail.com>
 *
 * Created on March 27, 2018, 7:11 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>

#define size_screen_y getmaxy(stdscr)
#define size_screen_x getmaxx(stdscr)

#define down 0402  
#define up 0403  
#define left 0404  
#define right 0405

typedef struct screen Screen;
typedef struct food Food;
typedef struct snake Snake;


Screen* init_game(int y, int x);

Screen* create_screen(int y, int x);

int calculate_middle_screen(int value);

void print_snake(Screen* screen);

void print_food(Screen * screen);
//return some error e.g.
Snake* create_snake(int y, int x);

void kill_screen();

void free_snake(Snake* snake);

void free_screen(Screen* screen);


Snake* calculate_coordinate(int y, int x, int newDirection);

bool checkTail(Screen* screen, Snake* snakeTemp);
//novo cálculo passando as coordenadas
Screen* calculate_next_cell(Screen* screen, Snake* newSnake);

bool movement_is_valid(Snake* snake);

bool find_food(Screen* screen, Snake* snake, int movement);

bool next_movement(Screen* screen, int movement);

void create_food(Screen* screen);