/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   screen.h
 * Author: Anderson Souza <jair_anderson_bs@hotmail.com>
 *
 * Created on March 27, 2018, 8:15 PM
 */

#include <ncurses.h>

#define down 0402  
#define up 0403  
#define left 0404  
#define right 0405
#define default_dir right;

typedef struct snake Snake;
typedef struct screen Screen;


int draw_menu();

int init_mode_cursor();

int key_pressed(int previous);

void end_window();
