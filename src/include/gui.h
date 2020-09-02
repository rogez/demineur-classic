// 
// Démineur Classic 
// https://github.com/rogez/demineur-classic
// 
// MIT License - Copyright (C) 2020 Fredy Rogez (rogez.net)
// This file is subject to the terms and conditions defined in
// file "LICENSE", which is part of this source code package.

#ifndef __GUI_H__
#define __GUI_H__

#include "common.h"

// GUI
void gui_init();
void gui_close();
SDL_Surface *render_menu_item(char *text, Menu_state menu_state);
void render_gui_texture();
void draw_menu();
void draw_emot();

#endif