// 
// Démineur Classic 
// https://github.com/rogez/demineur-classic
// 
// MIT License - Copyright (C) 2020 Fredy Rogez (rogez.net)
// This file is subject to the terms and conditions defined in
// file "LICENSE", which is part of this source code package.

#include "common.h"
#include "mouse.h"

extern Game game;

// MOUSE
bool is_mouse_over_cell(int mouse_x, int mouse_y, int *cell_x, int *cell_y)
{
    if (mouse_x >= game.cell_map.x && mouse_x <= (game.cell_map.x + game.cell_map.width_pixels) && mouse_y >= game.cell_map.y && mouse_y <= (game.cell_map.y + game.cell_map.height_pixels))
    {
        *cell_x = (mouse_x - game.cell_map.x) / 32;
        *cell_y = (mouse_y - game.cell_map.y) / 32;
        return true;
    }
    else
    {
        return false;
    }
}

bool is_mouse_over_emot(int mouse_x, int mouse_y)
{
    return (mouse_x >= (game.window_width / 2 - 26) && mouse_x <= (game.window_width / 2 + 26) && mouse_y >= EMOT_MARGIN_Y && mouse_y <= EMOT_MARGIN_Y + 52);
}

void mouse_button_up(Uint8 button, int x, int y)
{

    int cell_x, cell_y;
    if (is_mouse_over_cell(x, y, &cell_x, &cell_y) && (game.state == RUNNING || game.state == START))
    {
        if (button == SDL_BUTTON_RIGHT)
        {
            if (is_cell_hidden(cell_x, cell_y))
            {
                if (is_cell_flag(cell_x, cell_y))
                {
                    unset_flag(cell_x, cell_y);
                }
                else
                {
                    set_flag(cell_x, cell_y);
                }
            }
        }

        if (button == SDL_BUTTON_LEFT)
        {
            if (game.state == START && !is_cell_flag(cell_x, cell_y))
            {
                game.timer_running = true;
                game.timer = 0;
                game.timer_started_time = SDL_GetTicks();
                map_first_click(cell_x, cell_y);
                game.state = RUNNING;
            }

            if (is_cell_hidden(cell_x, cell_y) && !is_cell_flag(cell_x, cell_y))
            {
                if (is_cell_mine(cell_x, cell_y))
                {
                    game.state = GAME_OVER;
                    set_boom(cell_x, cell_y);
                    game.timer_running = false;
                }

                if (get_cpt_mines(cell_x, cell_y) == 0)
                {
                    update_zero_cell(cell_x, cell_y);
                }
                else
                {
                    unset_hidden(cell_x, cell_y);
                }
            }
        }
    }

    if (is_mouse_over_emot(x, y) && button == SDL_BUTTON_LEFT)
    {
        game_restart();
    }

    if (game.mouse_state.over_menu)
    {
        if (game.mouse_state.over_menu_debutant)
        {
            game.level = LEVEL_DEBUTANT;
            game_restart();
        }
        if (game.mouse_state.over_menu_intermediaire)
        {
            game.level = LEVEL_INTERMEDIAIRE;
            game_restart();
        }
        if (game.mouse_state.over_menu_expert)
        {
            game.level = LEVEL_EXPERT;
            game_restart();
        }
        if (game.mouse_state.over_menu_help)
        {
            system(GAME_URL);
        }
    }
}

bool is_mouse_over_menu(int mouse_x, int mouse_y)
{
    SDL_Point p = {mouse_x, mouse_y};
    game.mouse_state.over_menu = false;
    game.mouse_state.over_menu_debutant = false;
    game.mouse_state.over_menu_intermediaire = false;
    game.mouse_state.over_menu_expert = false;
    game.mouse_state.over_menu_help = false;

    if (SDL_PointInRect(&p, &game.gui.tx_rect_menu_debutant))
    {
        game.mouse_state.over_menu = true;
        game.mouse_state.over_menu_debutant = true;
        return true;
    }

    if (SDL_PointInRect(&p, &game.gui.tx_rect_menu_intermediaire))
    {
        game.mouse_state.over_menu = true;
        game.mouse_state.over_menu_intermediaire = true;
        return true;
    }

    if (SDL_PointInRect(&p, &game.gui.tx_rect_menu_expert))
    {
        game.mouse_state.over_menu = true;
        game.mouse_state.over_menu_expert = true;
        return true;
    }

    if (SDL_PointInRect(&p, &game.gui.tx_rect_menu_help))
    {
        game.mouse_state.over_menu = true;
        game.mouse_state.over_menu_help = true;
        return true;
    }
    return false;
}

void update_mouse_state()
{
    int x = 0, y = 0;
    int cell_x = 0, cell_y = 0;
    Uint32 buttons = SDL_GetMouseState(&x, &y);
    game.mouse_state.x = x;
    game.mouse_state.y = y;

    if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        game.mouse_state.left_button = true;
    }
    else
    {
        game.mouse_state.left_button = false;
    }

    if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))
    {
        game.mouse_state.right_button = true;
    }
    else
    {
        game.mouse_state.right_button = false;
    }

    if (is_mouse_over_cell(x, y, &cell_x, &cell_y))
    {
        game.mouse_state.over_cell = true;
        game.mouse_state.cell_x = cell_x;
        game.mouse_state.cell_y = cell_y;
    }
    else
    {
        game.mouse_state.over_cell = false;
    }

    is_mouse_over_menu(x, y);
}
