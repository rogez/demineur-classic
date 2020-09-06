// 
// Démineur Classic 
// https://github.com/rogez/demineur-classic
// 
// MIT License - Copyright (C) 2020 Fredy Rogez (rogez.net)
// This file is subject to the terms and conditions defined in
// file "LICENSE", which is part of this source code package.

#pragma once

#include "common.h"

// MAP
int get_random(int v_min, int v_max);
Uint8 get_cell(int x, int y);
void set_cell(int x, int y, Uint8 value);
Uint8 get_cpt_mines(int x, int y);
void set_cpt_mines(int x, int y, Uint8 cpt);
void inc_cpt_mines(int x, int y);
void update_cpt_mines(int x, int y);
void set_mine(int x, int y);
bool is_cell_mine(int x, int y);
void set_boom(int x, int y);
bool is_cell_boom(int x, int y);
void set_flag(int x, int y);
void unset_flag(int x, int y);
bool is_cell_flag(int x, int y);
void set_hidden(int x, int y);
void unset_hidden(int x, int y);
bool is_cell_hidden(int x, int y);
void set_all_hidden();
void unset_all_hidden();
void update_zero_cell(int x, int y);
void init_map(GameLevel level);
void map_first_click(int first_x, int first_y);
void print_map();
void draw_map();
