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
#include <ncurses.h>

#define size_screen_y getmaxy(stdscr)
#define size_screen_x getmaxx(stdscr)

#define down 0402  
#define up 0403  
#define left 0404  
#define right 0405

typedef struct screen Screen;
typedef struct snake Snake;


int calculateMiddleScreen(int value);
//return some error e.g.
Snake* createSnake();

void killScreen();

void freeSnake(Snake* snake);

void freeBoard(Screen* screen);

Snake* createNewSnake(int y, int x);

Snake* calculateCoordinate(int y, int x, int newDirection);

int keyPressed(int previous);

void d(Snake* snake, Snake* snakeTemp);


int keyPressed(int previous);

//novo cálculo passando as coordenadas

Snake* calculateNextCell(Screen* screen, Snake* newSnake);

void isEdge(Screen* screen);

int nextMovement(Screen* screen, int movement);



