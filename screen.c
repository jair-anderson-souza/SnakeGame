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

Screen* createScreen() {
    Screen* screen = (Screen*) malloc(sizeof (Screen));
    return screen;
}


