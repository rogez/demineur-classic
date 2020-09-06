// 
// Démineur Classic 
// https://github.com/rogez/demineur-classic
// 
// MIT License - Copyright (C) 2020 Fredy Rogez (rogez.net)
// This file is subject to the terms and conditions defined in
// file "LICENSE", which is part of this source code package.

#include "common.h"
#include "map.h"

static inline void draw_cell(int x, int y);

extern Game game;

// MAP
int get_random(int v_min, int v_max)
{
    return rand() % (v_max - v_min + 1) + v_min;
}

Uint8 get_cell(int x, int y)
{
    return game.cell_map.field[y * game.cell_map.width + x];
}

void set_cell(int x, int y, Uint8 value)
{
    game.cell_map.field[y * game.cell_map.width + x] = value;
}

Uint8 get_cpt_mines(int x, int y)
{
    Uint8 cell = get_cell(x, y);
    cell >>= 4;
    cell &= 0x0F;
    return (Uint8)cell;
}

void set_cpt_mines(int x, int y, Uint8 cpt)
{
    Uint8 cell = get_cell(x, y);
    cell &= 0xFF0F;
    cpt <<= 4;
    cell |= cpt;
    set_cell(x, y, cell);
}

void inc_cpt_mines(int x, int y)
{
    Uint8 cell_cpt = get_cpt_mines(x, y);
    set_cpt_mines(x, y, ++cell_cpt);
}

void update_cpt_mines(int x, int y)
{
    int ty = game.cell_map.height - 1;
    int tx = game.cell_map.width - 1;

    if (x > 0 && y > 0)
        inc_cpt_mines(x - 1, y - 1);
    if (y > 0)
        inc_cpt_mines(x, y - 1);
    if (x < tx && y > 0)
        inc_cpt_mines(x + 1, y - 1);
    if (x < tx)
        inc_cpt_mines(x + 1, y);
    if (x < tx && y < ty)
        inc_cpt_mines(x + 1, y + 1);
    if (y < ty)
        inc_cpt_mines(x, y + 1);
    if (x > 0 && y < ty)
        inc_cpt_mines(x - 1, y + 1);
    if (x > 0)
        inc_cpt_mines(x - 1, y);
}

void set_mine(int x, int y)
{
    Uint8 cell = get_cell(x, y) | 1;
    set_cell(x, y, cell);
}

bool is_cell_mine(int x, int y)
{
    return ((get_cell(x, y) & 1) == 1) ? true : false;
}

void set_boom(int x, int y)
{
    Uint8 cell = get_cell(x, y) | 8;
    set_cell(x, y, cell);
}

bool is_cell_boom(int x, int y)
{
    return ((get_cell(x, y) & 8) == 8) ? true : false;
}

void set_flag(int x, int y)
{
    Uint8 cell = get_cell(x, y) | 2;
    set_cell(x, y, cell);
}

void unset_flag(int x, int y)
{
    Uint8 cell = get_cell(x, y) & 0xFFFD;
    set_cell(x, y, cell);
}

bool is_cell_flag(int x, int y)
{
    return ((get_cell(x, y) & 2) == 2) ? true : false;
}

void set_hidden(int x, int y)
{
    Uint8 cell = get_cell(x, y) | 4;
    set_cell(x, y, cell);
}

void unset_hidden(int x, int y)
{
    Uint8 cell = get_cell(x, y) & 0xFFFB;
    set_cell(x, y, cell);
}

bool is_cell_hidden(int x, int y)
{
    return ((get_cell(x, y) & 4) == 4) ? true : false;
}

void set_all_hidden()
{
    for (int line = 0; line < game.cell_map.height; line++)
    {
        for (int row = 0; row < game.cell_map.width; row++)
        {
            set_hidden(row, line);
        }
    }
}

void unset_all_hidden()
{
    for (int line = 0; line < game.cell_map.height; line++)
    {
        for (int row = 0; row < game.cell_map.width; row++)
        {
            unset_hidden(row, line);
        }
    }
}

void update_zero_cell(int x, int y)
{
    if (get_cpt_mines(x, y) != 0)
    {
        unset_hidden(x, y);
        unset_flag(x, y);
        return;
    }
    else
    {
        if (is_cell_hidden(x, y) && get_cpt_mines(x, y) == 0)
        {
            int ty = game.cell_map.height - 1;
            int tx = game.cell_map.width - 1;
            unset_hidden(x, y);
            unset_flag(x, y);

            if (x > 0 && y > 0)
                update_zero_cell(x - 1, y - 1);
            if (y > 0)
                update_zero_cell(x, y - 1);
            if (x < tx && y > 0)
                update_zero_cell(x + 1, y - 1);
            if (x < tx)
                update_zero_cell(x + 1, y);
            if (x < tx && y < ty)
                update_zero_cell(x + 1, y + 1);
            if (y < ty)
                update_zero_cell(x, y + 1);
            if (x > 0 && y < ty)
                update_zero_cell(x - 1, y + 1);
            if (x > 0)
                update_zero_cell(x - 1, y);
        }
    }
}

void init_map(GameLevel level)
{

    switch (level)
    {
    case LEVEL_DEBUTANT:
        game.cell_map.width = LEVEL_DEBUTANT_WIDTH;
        game.cell_map.height = LEVEL_DEBUTANT_HEIGHT;
        game.cell_map.nb_mines = LEVEL_DEBUTANT_MINES;
        break;

    case LEVEL_INTERMEDIAIRE:
        game.cell_map.width = LEVEL_INTERMEDIAIRE_WIDTH;
        game.cell_map.height = LEVEL_INTERMEDIAIRE_HEIGHT;
        game.cell_map.nb_mines = LEVEL_INTERMEDIAIRE_MINES;
        break;

    case LEVEL_EXPERT:
        game.cell_map.width = LEVEL_EXPERT_WIDTH;
        game.cell_map.height = LEVEL_EXPERT_HEIGHT;
        game.cell_map.nb_mines = LEVEL_EXPERT_MINES;
        break;
    }

    int width = game.cell_map.width;
    int height = game.cell_map.height;

    game.cell_map.width_pixels = width * 32;
    game.cell_map.height_pixels = height * 32;
    game.cell_map.x = MAP_MARGIN_X;
    game.cell_map.y = MAP_MARGIN_Y;
    game.cell_map.field = calloc(width * height, sizeof(Uint8));
    game.timer = 0;
    game.rest_nb_mines = game.cell_map.nb_mines;
    game.rest_nb_cells = width * height;
    set_all_hidden();
    game.window_width = game.cell_map.width_pixels + (MAP_MARGIN_X * 2);
    game.window_height = game.cell_map.height_pixels + MAP_MARGIN_Y + MAP_MARGIN_X;
    SDL_SetWindowSize(game.window, game.window_width, game.window_height);
    SDL_SetWindowPosition(game.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void map_first_click(int first_x, int first_y)
{
    int x = 0, y = 0;
    int nb_mines = game.cell_map.nb_mines;
    while (nb_mines > 0)
    {
        x = get_random(0, game.cell_map.width - 1);
        y = get_random(0, game.cell_map.height - 1);
        if ((x == first_x && y == first_y) || is_cell_mine(x, y))
            continue;
        set_mine(x, y);
        update_cpt_mines(x, y);

        nb_mines--;
    }
}

void print_map()
{
    printf("\n\n");

    for (int line = 0; line < game.cell_map.height; line++)
    {
        for (int row = 0; row < game.cell_map.width; row++)
        {
            Uint8 cell = get_cell(row, line);
            printf(cell < 10 ? " %d " : "%d ", cell);
        }
        printf("\n");
    }
}

void draw_map()
{
    game.rest_nb_mines = game.cell_map.nb_mines;
    game.rest_nb_cells = game.cell_map.width * game.cell_map.height;

    for (int line = 0; line < game.cell_map.height; line++)
    {
        for (int row = 0; row < game.cell_map.width; row++)
        {
            draw_cell(row, line);
        }
    }
    if (game.state == GAME_WIN)
    {
        game.rest_nb_mines = 0;
    }
}

//PRIVATE
static inline void draw_cell(int x, int y)
{
    SDL_Rect r;
    r.x = x * 32 + MAP_MARGIN_X;
    r.y = y * 32 + MAP_MARGIN_Y;
    r.w = 32;
    r.h = 32;

    if (game.state == GAME_OVER)
    {
        if (is_cell_mine(x, y))
        {
            if (is_cell_boom(x, y))
            {
                draw_cell_sprite(CELL_RED_MINE, &r);
            }
            else
            {
                draw_cell_sprite(CELL_MINE, &r);
            }
        }
        else
        {
            if (is_cell_flag(x, y))
            {
                draw_cell_sprite(CELL_NO_MINE, &r);
            }
            else
            {
                if (is_cell_hidden(x, y))
                {
                    draw_cell_sprite(CELL_HIDDEN, &r);
                }
                else
                {
                    Uint8 cpt = get_cpt_mines(x, y);
                    draw_cell_sprite(cpt + 10, &r);
                }
            }
        }
    }
    else
    {
        if (is_cell_flag(x, y) && is_cell_hidden(x, y))
        {
            if (game.state == GAME_OVER && is_cell_mine(x, y))
            {
                draw_cell_sprite(CELL_NO_MINE, &r);
            }
            else
            {
                draw_cell_sprite(CELL_FLAG, &r);
                game.rest_nb_mines--;
            }
        }
        else
        {
            if (is_cell_hidden(x, y))
            {
                if (game.state == GAME_WIN)
                {
                    if (is_cell_mine(x, y))
                    {
                        draw_cell_sprite(CELL_FLAG, &r);
                    }
                }
                else
                {
                    if (game.mouse_state.over_cell && game.mouse_state.left_button && game.mouse_state.cell_x == x && game.mouse_state.cell_y == y)
                    {
                        draw_cell_sprite(CELL_0, &r);
                    }
                    else
                    {
                        draw_cell_sprite(CELL_HIDDEN, &r);
                    }
                }
            }
            else
            {
                if (is_cell_mine(x, y))
                {
                    if (is_cell_boom(x, y))
                    {
                        draw_cell_sprite(CELL_RED_MINE, &r);
                    }
                    else
                    {
                        if (game.state == GAME_WIN)
                        {
                            draw_cell_sprite(CELL_FLAG, &r);
                        }
                        else
                        {
                            draw_cell_sprite(CELL_MINE, &r);
                        }
                    }
                }
                else
                {
                    Uint8 cpt = get_cpt_mines(x, y);
                    draw_cell_sprite(cpt + 10, &r);
                    game.rest_nb_cells--;
                }
            }
        }
    }
}
