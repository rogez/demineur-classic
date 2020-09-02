// 
// Démineur Classic 
// https://github.com/rogez/demineur-classic
// 
// MIT License - Copyright (C) 2020 Fredy Rogez (rogez.net)
// This file is subject to the terms and conditions defined in
// file "LICENSE", which is part of this source code package.

#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "common.h"

// MOUSE
bool is_mouse_over_cell(int mouse_x, int mouse_y, int *cell_x, int *cell_y);
bool is_mouse_over_emot(int mouse_x, int mouse_y);
bool is_mouse_over_menu(int mouse_x, int mouse_y);
void mouse_button_up(Uint8 button, int x, int y);
void update_mouse_state();

#endif