// 
// Démineur Classic 
// https://github.com/rogez/demineur-classic
// 
// MIT License - Copyright (C) 2020 Fredy Rogez (rogez.net)
// This file is subject to the terms and conditions defined in
// file "LICENSE", which is part of this source code package.

#include "common.h"

extern Game game;

// GUI
// Codé rapidement pour créer un menu
// Pas du tout optimisé mais fait le job... à revoir complètement...

void gui_init()
{
    TTF_Init();
    game.gui.ttf_menu = NULL;

    char fileTTF[] = FONT_MENU_FILE;

    game.gui.ttf_menu = TTF_OpenFont(fileTTF, FONT_MENU_SIZE);
    if (game.gui.ttf_menu == NULL)
    {
        printf("%s", TTF_GetError());
    }

    SDL_Surface *test_surface = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA32);
    game.gui.surface_pixel_format = *(test_surface->format);
    SDL_FreeSurface(test_surface);

    render_gui_texture();
}

SDL_Surface *render_menu_item(char *text, Menu_state menu_state)
{
    SDL_Color color_back;
    SDL_Color color_back_normal = {MENU_BACK_COLOR, 255};
    SDL_Color color_back_over = {MENU_BACK_COLOR_OVER, 255};
    SDL_Color color_back_select = {MENU_BACK_COLOR_SELECT, 255};

    SDL_Color color_font;
    SDL_Color color_font_normal = FONT_MENU_COLOR;
    SDL_Color color_font_over = FONT_MENU_COLOR_OVER;
    SDL_Color color_font_select = FONT_MENU_COLOR_SELECT;

    Uint32 surf_color;

    switch (menu_state)
    {
    case MENU_NORMAL:
        color_font = color_font_normal;
        color_back = color_back_normal;
        surf_color = MENU_BACK_COLOR_RGB;
        break;

    case MENU_OVER:
        color_font = color_font_over;
        color_back = color_back_over;
        surf_color = MENU_BACK_COLOR_OVER_RGB;
        break;

    case MENU_SELECT:
        color_font = color_font_select;
        color_back = color_back_select;
        surf_color = MENU_BACK_COLOR_SELECT_RGB;
        break;
    }

    SDL_Surface *surf_txt = TTF_RenderUTF8_Shaded(game.gui.ttf_menu, text, color_font, color_back);
    SDL_Surface *surf_ret = SDL_CreateRGBSurfaceWithFormat(0, surf_txt->w + FONT_MENU_PADDING * 2, MENU_HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_FillRect(surf_ret, NULL, surf_color);

    SDL_Rect rd;
    rd.w = surf_txt->w;
    rd.h = surf_txt->h;
    rd.x = (surf_ret->w - rd.w) / 2;
    rd.y = (surf_ret->h - rd.h) / 2;

    SDL_BlitSurface(surf_txt, NULL, surf_ret, &rd);
    SDL_FreeSurface(surf_txt);
    return surf_ret;
}

void render_gui_texture()
{
    SDL_Rect rd;

    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, 512, 512, 32, SDL_PIXELFORMAT_RGBA32);

    SDL_Surface *s1 = render_menu_item("Débutant", MENU_NORMAL);
    SDL_Surface *s2 = render_menu_item("Débutant", MENU_OVER);
    SDL_Surface *s3 = render_menu_item("Débutant", MENU_SELECT);

    rd.x = 0;
    rd.y = 0;
    rd.w = s1->w;
    rd.h = s1->h;

    game.gui.tx_rect_menu_debutant = rd;

    SDL_BlitSurface(s1, NULL, surf, &rd);
    rd.y += s1->h;
    SDL_BlitSurface(s2, NULL, surf, &rd);
    rd.y += s1->h;
    SDL_BlitSurface(s3, NULL, surf, &rd);
    rd.y += s1->h;

    rd.x += rd.w;

    SDL_FreeSurface(s1);
    SDL_FreeSurface(s2);
    SDL_FreeSurface(s3);

    s1 = render_menu_item("Intermédiaire", MENU_NORMAL);
    s2 = render_menu_item("Intermédiaire", MENU_OVER);
    s3 = render_menu_item("Intermédiaire", MENU_SELECT);

    rd.y = 0;
    rd.w = s1->w;
    rd.h = s1->h;

    game.gui.tx_rect_menu_intermediaire = rd;

    SDL_BlitSurface(s1, NULL, surf, &rd);
    rd.y += s1->h;
    SDL_BlitSurface(s2, NULL, surf, &rd);
    rd.y += s1->h;
    SDL_BlitSurface(s3, NULL, surf, &rd);
    rd.y += s1->h;

    rd.x += rd.w;

    SDL_FreeSurface(s1);
    SDL_FreeSurface(s2);
    SDL_FreeSurface(s3);

    s1 = render_menu_item("Expert", MENU_NORMAL);
    s2 = render_menu_item("Expert", MENU_OVER);
    s3 = render_menu_item("Expert", MENU_SELECT);

    rd.y = 0;
    rd.w = s1->w;
    rd.h = s1->h;

    game.gui.tx_rect_menu_expert = rd;

    SDL_BlitSurface(s1, NULL, surf, &rd);
    rd.y += s1->h;
    SDL_BlitSurface(s2, NULL, surf, &rd);
    rd.y += s1->h;
    SDL_BlitSurface(s3, NULL, surf, &rd);
    rd.y += s1->h;

    rd.x += rd.w;

    SDL_FreeSurface(s1);
    SDL_FreeSurface(s2);
    SDL_FreeSurface(s3);

    s1 = render_menu_item(" ? ", MENU_NORMAL);
    s2 = render_menu_item(" ? ", MENU_OVER);
    s3 = render_menu_item(" ? ", MENU_SELECT);

    rd.y = 0;
    rd.w = s1->w;
    rd.h = s1->h;

    game.gui.tx_rect_menu_help = rd;

    SDL_BlitSurface(s1, NULL, surf, &rd);
    rd.y += s1->h;
    SDL_BlitSurface(s2, NULL, surf, &rd);
    rd.y += s1->h;
    SDL_BlitSurface(s3, NULL, surf, &rd);
    rd.y += s1->h;

    rd.x += rd.w;

    SDL_FreeSurface(s1);
    SDL_FreeSurface(s2);
    SDL_FreeSurface(s3);

    game.gui.texture = SDL_CreateTextureFromSurface(game.renderer, surf);
    SDL_FreeSurface(surf);
}

void gui_close()
{
    SDL_DestroyTexture(game.gui.texture);
    TTF_CloseFont(game.gui.ttf_menu);
    TTF_Quit();
}

void draw_menu_item(Menu_item menu_item, Menu_state menu_state)
{
    SDL_Rect rs;
    SDL_Rect rd;

    switch (menu_item)
    {
    case MENU_DEBUTANT:
        rs = game.gui.tx_rect_menu_debutant;
        break;

    case MENU_INTERMEDIAIRE:
        rs = game.gui.tx_rect_menu_intermediaire;
        break;

    case MENU_EXPERT:
        rs = game.gui.tx_rect_menu_expert;
        break;

    case MENU_HELP:
        rs = game.gui.tx_rect_menu_help;
        break;
    }

    rd = rs;

    switch (menu_state)
    {
    case MENU_NORMAL:
        rs.y += 0;
        break;

    case MENU_OVER:
        rs.y += MENU_HEIGHT;
        break;

    case MENU_SELECT:
        rs.y += MENU_HEIGHT * 2;
        break;
    }
    SDL_RenderCopy(game.renderer, game.gui.texture, &rs, &rd);
}

void draw_menu()
{
    SDL_Rect r = {0, 0, game.window_width, MENU_HEIGHT};
    SDL_SetRenderDrawColor(game.renderer, MENU_BACK_COLOR, 255);
    SDL_RenderFillRect(game.renderer, &r);

    if (game.level == LEVEL_DEBUTANT)
        draw_menu_item(MENU_DEBUTANT, game.mouse_state.over_menu_debutant ? MENU_OVER : MENU_SELECT);
    else
        draw_menu_item(MENU_DEBUTANT, game.mouse_state.over_menu_debutant ? MENU_OVER : MENU_NORMAL);

    if (game.level == LEVEL_INTERMEDIAIRE)
        draw_menu_item(MENU_INTERMEDIAIRE, game.mouse_state.over_menu_intermediaire ? MENU_OVER : MENU_SELECT);
    else
        draw_menu_item(MENU_INTERMEDIAIRE, game.mouse_state.over_menu_intermediaire ? MENU_OVER : MENU_NORMAL);

    if (game.level == LEVEL_EXPERT)
        draw_menu_item(MENU_EXPERT, game.mouse_state.over_menu_expert ? MENU_OVER : MENU_SELECT);
    else
        draw_menu_item(MENU_EXPERT, game.mouse_state.over_menu_expert ? MENU_OVER : MENU_NORMAL);

    draw_menu_item(MENU_HELP, game.mouse_state.over_menu_help ? MENU_OVER : MENU_NORMAL);
}

