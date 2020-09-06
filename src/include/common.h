// 
// Démineur Classic 
// https://github.com/rogez/demineur-classic
// 
// MIT License - Copyright (C) 2020 Fredy Rogez (rogez.net)
// This file is subject to the terms and conditions defined in
// file "LICENSE", which is part of this source code package.

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

// GAME BASE
#define GAME_VERSION "1.0.0"
#define GAME_NAME "Démineur Classic by Fredy Rogez"
#define GAME_URL "start https://link.rogez.net/demineur"

// MAP
#define MAP_MARGIN_X 4
#define MAP_MARGIN_Y 80

// EMOT
#define EMOT_MARGIN_Y 25
#define EMOT_WIDTH 26
#define EMOT_HEIGHT 26

// DIGIT
#define DIGIT_MARGIN_X 4
#define DIGIT_MARGIN_Y 25

// LEVELS
#define LEVEL_DEBUTANT_WIDTH 9
#define LEVEL_DEBUTANT_HEIGHT 9
#define LEVEL_DEBUTANT_MINES 10
#define LEVEL_INTERMEDIAIRE_WIDTH 16
#define LEVEL_INTERMEDIAIRE_HEIGHT 16
#define LEVEL_INTERMEDIAIRE_MINES 40
#define LEVEL_EXPERT_WIDTH 30
#define LEVEL_EXPERT_HEIGHT 16
#define LEVEL_EXPERT_MINES 99

// GUI
#define WINDOW_BACK_COLOR 192, 192, 192
#define FONT_MENU_FILE ".\\assets\\Comfortaa-Regular.ttf"
#define MENU_HEIGHT 22
#define FONT_MENU_SIZE 16
#define FONT_MENU_PADDING 4
#define MENU_BACK_COLOR 170, 170, 170
#define FONT_MENU_COLOR \
    {                   \
        36, 36, 36      \
    }
#define FONT_MENU_COLOR_BACK \
    {                        \
        MENU_BACK_COLOR      \
    }
#define MENU_BACK_COLOR_RGB SDL_MapRGB(&game.gui.surface_pixel_format, MENU_BACK_COLOR)

#define MENU_BACK_COLOR_OVER 190, 190, 190
#define FONT_MENU_COLOR_OVER \
    {                        \
        36, 36, 36           \
    }
#define FONT_MENU_COLOR_BACK_OVER \
    {                             \
        MENU_BACK_COLOR_OVER      \
    }
#define MENU_BACK_COLOR_OVER_RGB SDL_MapRGB(&game.gui.surface_pixel_format, MENU_BACK_COLOR_OVER)

#define MENU_BACK_COLOR_SELECT 0, 192, 0
#define FONT_MENU_COLOR_SELECT \
    {                          \
        36, 36, 36             \
    }
#define FONT_MENU_COLOR_BACK_SELECT \
    {                               \
        MENU_BACK_COLOR_SELECT      \
    }
#define MENU_BACK_COLOR_SELECT_RGB SDL_MapRGB(&game.gui.surface_pixel_format, MENU_BACK_COLOR_SELECT)

// MACRO
#define min(a,b) ((a)<=(b)?a:b)

// STRUCTS
typedef struct MouseState
{
    bool left_button;
    bool right_button;
    bool over_cell;
    bool over_menu;
    bool over_menu_debutant;
    bool over_menu_intermediaire;
    bool over_menu_expert;
    bool over_menu_help;
    int x;
    int y;
    int cell_x;
    int cell_y;
} MouseState;

typedef struct Gui
{
    TTF_Font *ttf_menu;
    SDL_Texture *texture;
    SDL_Rect tx_rect_menu_debutant;
    SDL_Rect tx_rect_menu_intermediaire;
    SDL_Rect tx_rect_menu_expert;
    SDL_Rect tx_rect_menu_help;
    int menu_offset_y;
    SDL_PixelFormat surface_pixel_format;
} Gui;

typedef enum MenuItem
{
    MENU_DEBUTANT,
    MENU_INTERMEDIAIRE,
    MENU_EXPERT,
    MENU_HELP
} MenuItem;

typedef enum MenuState
{
    MENU_NORMAL,
    MENU_OVER,
    MENU_SELECT
} MenuState;

typedef enum CellSprite
{
    CELL_0 = 10,
    CELL_1,
    CELL_2,
    CELL_3,
    CELL_4,
    CELL_5,
    CELL_6,
    CELL_7,
    CELL_8,
    CELL_HIDDEN,
    CELL_FLAG,
    CELL_MINE,
    CELL_RED_MINE,
    CELL_NO_MINE
} CellSprite;

typedef enum EmotSprite
{
    EMOT_UP = 0,
    EMOT_DOWN = 27,
    EMOT_HO = 54,
    EMOT_COOL = 81,
    EMOT_DEAD = 108
} EmotSprite;

typedef enum DigitSprite
{
    DIGIT_0,
    DIGIT_1,
    DIGIT_2,
    DIGIT_3,
    DIGIT_4,
    DIGIT_5,
    DIGIT_6,
    DIGIT_7,
    DIGIT_8,
    DIGIT_9

} DigitSprite;

typedef enum GameState
{
    START,
    FIRST_CLICK,
    RUNNING,
    GAME_OVER,
    GAME_WIN
} GameState;

typedef enum GameLevel
{
    LEVEL_DEBUTANT = 1,
    LEVEL_INTERMEDIAIRE,
    LEVEL_EXPERT
} GameLevel;

typedef struct Map
{
    int width;
    int height;
    int nb_mines;
    int width_pixels;
    int height_pixels;
    int x;
    int y;
    Uint8 *field;
} Map;

typedef struct Game
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Surface *icon;
    GameState state;
    GameLevel level;
    Map cell_map;
    Gui gui;
    MouseState mouse_state;
    bool running;
    int window_width;
    int window_height;
    int rest_nb_mines;
    int rest_nb_cells;
    int timer;
    int timer_started_time;
    bool timer_running;
} Game;

#include "mouse.h"
#include "map.h"
#include "gui.h"
#include "sprites.h"
#include "game.h"
