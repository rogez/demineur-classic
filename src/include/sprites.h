// 
// Démineur Classic 
// https://github.com/rogez/demineur-classic
// 
// MIT License - Copyright (C) 2020 Fredy Rogez (rogez.net)
// This file is subject to the terms and conditions defined in
// file "LICENSE", which is part of this source code package.

#ifndef __SPRITES_H__
#define __SPRITES_H__

#include "common.h"

// SPRITES
void draw_cell_sprite(Cell_sprite sprite, SDL_Rect *rd);
void draw_emot_sprite(Emot_sprite sprite, SDL_Rect *rd);
void draw_digit_sprite(Digit_sprite sprite, SDL_Rect *rd);
void draw_digit(int value, int x, int y);

#endif