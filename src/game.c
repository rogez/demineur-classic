// 
// Démineur Classic 
// https://github.com/rogez/demineur-classic
// 
// MIT License - Copyright (C) 2020 Fredy Rogez (rogez.net)
// This file is subject to the terms and conditions defined in
// file "LICENSE", which is part of this source code package.

#include "common.h"

extern Game game;

void game_init()
{
    srand((unsigned int)time(NULL));

    game.window = NULL;
    game.renderer = NULL;
    game.texture = NULL;
    game.cell_map.field = NULL;
    game.window_width = 32 * 9 + 8;
    game.window_height = 32 * 9 + 94;
    game.state = START;
    game.timer = 0;
    game.timer_running = false;
    game.rest_nb_mines = 0;
    game.level = LEVEL_DEBUTANT;

    SDL_Init(SDL_INIT_VIDEO | SDL_RENDERER_PRESENTVSYNC);

    game.window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game.window_width, game.window_height, SDL_WINDOW_SHOWN);
    if (game.window == NULL)
    {
        printf("ERROR : SDL_CreateWindow");
        exit(-1);
    }

    game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
    if (game.renderer == NULL)
    {
        printf("ERROR : SDL_CreateRenderer");
        exit(-1);
    }

    SDL_Surface *surface = SDL_LoadBMP("assets/gfx.bmp");
    game.texture = SDL_CreateTextureFromSurface(game.renderer, surface);
    SDL_FreeSurface(surface);

    gui_init();
}

void game_restart()
{
    free(game.cell_map.field);
    game.cell_map.field = NULL;
    game.state = START;
    game.timer = 0;
    game.timer_running = false;
    game.rest_nb_mines = 0;
    init_map(game.level);
}

void game_clean()
{
    free(game.cell_map.field);
    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyTexture(game.texture);
    SDL_DestroyWindow(game.window);
    gui_close();
    SDL_Quit();
}

void game_events()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        update_mouse_state();
        switch (event.type)
        {
        case SDL_QUIT: // Fermeture de la fenêtre
            game.running = false;
            break;

        case SDL_KEYDOWN: // Fermeture de la fenêtre
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
            {
                print_map();
            }

            break;

        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouse_button_up(SDL_BUTTON_LEFT, event.button.x, event.button.y);
                break;
            }
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                mouse_button_up(SDL_BUTTON_RIGHT, event.button.x, event.button.y);
                break;
            }
            break;
        }
    }
}
