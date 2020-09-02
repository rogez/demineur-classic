// 
// Démineur Classic 
// https://github.com/rogez/demineur-classic
// 
// MIT License - Copyright (C) 2020 Fredy Rogez (rogez.net)
// This file is subject to the terms and conditions defined in
// file "LICENSE", which is part of this source code package.

#include "common.h"

Game game;

int main(int argc, char **args)
{
    game.running = true;
    game_init();
    init_map(LEVEL_DEBUTANT);

    while (game.running)
    {
        game_events();

        // UPDATE
        if (game.timer_running)
            game.timer = SDL_GetTicks() - game.timer_started_time;

        if (game.state == RUNNING && game.rest_nb_cells == game.cell_map.nb_mines)
        {
            game.state = GAME_WIN;
            game.timer_running = false;
        }

        // DRAW
        SDL_SetRenderDrawColor(game.renderer, WINDOW_BACK_COLOR, 255);
        SDL_RenderClear(game.renderer);
        draw_map();
        draw_digit(game.rest_nb_mines, DIGIT_MARGIN_X, DIGIT_MARGIN_Y);
        draw_digit(min(game.timer/1000, 999), game.window_width - 26 * 3 - DIGIT_MARGIN_X, DIGIT_MARGIN_Y);
        draw_emot();
        draw_menu();
        SDL_RenderPresent(game.renderer);

        SDL_Delay(10);
    }

    game_clean();
    return 0;
}
