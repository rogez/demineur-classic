// 
// Démineur Classic 
// https://github.com/rogez/demineur-classic
// 
// MIT License - Copyright (C) 2020 Fredy Rogez (rogez.net)
// This file is subject to the terms and conditions defined in
// file "LICENSE", which is part of this source code package.

#include "common.h"
#include "sprites.h"

static inline void draw_emot_sprite(EmotSprite sprite, SDL_Rect *rd);
static inline void draw_digit_sprite(DigitSprite sprite, SDL_Rect *rd);

extern Game game;

// DRAWS
void draw_emot()
{
    EmotSprite emot = EMOT_UP;
    SDL_Rect rect = {game.window_width / 2 - 26, EMOT_MARGIN_Y, 52, 52};
    if (game.mouse_state.left_button && game.mouse_state.over_cell)
    {
        emot = EMOT_HO;
    }
    if (game.state == GAME_OVER)
    {
        emot = EMOT_DEAD;
    }
    if (game.state == GAME_WIN)
    {
        emot = EMOT_COOL;
    }

    if (is_mouse_over_emot(game.mouse_state.x, game.mouse_state.y) && game.mouse_state.left_button)
    {
        emot = EMOT_DOWN;
    }
    draw_emot_sprite(emot, &rect);
}

void draw_digit(int value, int x, int y)
{
    SDL_Rect rd = {x, y, 26, 46};

    int d1, d2, d3;

    if (value >= 0)
    {
        d1 = value / 100;
        draw_digit_sprite(d1, &rd);

        d2 = (value - (d1 * 100)) / 10;
        rd.x += 26;
        draw_digit_sprite(d2, &rd);

        d3 = (value - (d1 * 100) - (d2 * 10));
        rd.x += 26;
        draw_digit_sprite(d3, &rd);
    }
    else
    {
        d1 = d2 = d3 = 0;
        draw_digit_sprite(d1, &rd);
        rd.x += 26;
        draw_digit_sprite(d2, &rd);
        rd.x += 26;
        draw_digit_sprite(d3, &rd);
    }
}

void draw_cell_sprite(CellSprite sprite, SDL_Rect *rd)
{
    SDL_Rect rs = {0, 68, 16, 16};

    switch (sprite)
    {
    case CELL_1:
        rs.x = 0;
        break;

    case CELL_2:
        rs.x = 17;
        break;

    case CELL_3:
        rs.x = 34;
        break;

    case CELL_4:
        rs.x = 51;
        break;

    case CELL_5:
        rs.x = 68;
        break;

    case CELL_6:
        rs.x = 85;
        break;

    case CELL_7:
        rs.x = 102;
        break;

    case CELL_8:
        rs.x = 119;
        break;

    case CELL_0:
        rs.x = 17;
        rs.y = 51;
        break;

    case CELL_HIDDEN:
        rs.x = 0;
        rs.y = 51;
        break;

    case CELL_FLAG:
        rs.x = 34;
        rs.y = 51;
        break;

    case CELL_MINE:
        rs.x = 85;
        rs.y = 51;
        break;

    case CELL_RED_MINE:
        rs.x = 102;
        rs.y = 51;
        break;

    case CELL_NO_MINE:
        rs.x = 119;
        rs.y = 51;
        break;
    }

    SDL_RenderCopy(game.renderer, game.texture, &rs, rd);
}

//PRIVATE
static inline void draw_emot_sprite(EmotSprite sprite, SDL_Rect *rd)
{
    SDL_Rect rs = {sprite, 24, EMOT_WIDTH, EMOT_HEIGHT};
    SDL_RenderCopy(game.renderer, game.texture, &rs, rd);
}

static inline void draw_digit_sprite(DigitSprite sprite, SDL_Rect *rd)
{
    SDL_Rect rs = {0, 0, 13, 23};
    rs.x = (sprite - 1) * 14;
    rs.x = sprite == DIGIT_0 ? 126 : rs.x;
    SDL_RenderCopy(game.renderer, game.texture, &rs, rd);
}
