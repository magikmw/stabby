/*
    StabbyMain.c is a part of Stabby
    Copyright (C) 2013 Michał Walczak

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#include "Stabby.h"
#include "IncludeGlobals.h"

double draw_fps(int *);

int main()
{
    sfVideoMode mode = {WINDOW_X, WINDOW_Y, 32};
    sfRenderWindow* window;
    sfTexture* texture;
    sfSprite* sprite;
    sfFont* font;
    sfText* text;
    sfEvent event;

    /* Create the main window */
    char NAME_VERSION[] = WINDOW_NAME; strcat(NAME_VERSION, VERSION);
    window = sfRenderWindow_create(mode, NAME_VERSION, sfClose, NULL);

    /* Load a sprite to display */
    texture = sfTexture_createFromFile("assets/sprites.png", NULL);
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setTextureRect(sprite, (sfIntRect){0*TILE_SIZE, 0*TILE_SIZE, TILE_SIZE, TILE_SIZE});
    sfSprite_setPosition(sprite, (sfVector2f){0*TILE_SIZE + BORDER_OFFSET, 0*TILE_SIZE + BORDER_OFFSET});
    // sfSprite_setScale(sprite, (sfVector2f){0.5, 0.5});

    loadTextures(textureArray);
    createMap(map);

    sfTexture* border_texture = sfTexture_createFromFile("assets/border.png", NULL);
    sfSprite* borderTop = sfSprite_create();
    sfSprite_setTexture(borderTop, border_texture, sfTrue);

    sfSprite* borderBot = sfSprite_create();
    sfSprite_setTexture(borderBot, border_texture, sfTrue);
    sfSprite_setPosition(borderBot, (sfVector2f){0, WINDOW_Y-BORDER_OFFSET});

    sfSprite* borderLeft = sfSprite_create();
    sfSprite_setTexture(borderLeft, border_texture, sfTrue);
    sfSprite_setPosition(borderLeft, (sfVector2f){BORDER_OFFSET, 0});
    sfSprite_setRotation(borderLeft, 90);
    
    sfSprite* borderRight = sfSprite_create();
    sfSprite_setTexture(borderRight, border_texture, sfTrue);
    sfSprite_setPosition(borderRight, (sfVector2f){WINDOW_X, 0});
    sfSprite_setRotation(borderRight, 90);

    sfSprite* borderPanel = sfSprite_create();
    sfSprite_setTexture(borderPanel, border_texture, sfTrue);
    sfSprite_setPosition(borderPanel, (sfVector2f){PANEL_ZERO_X+BORDER_OFFSET, 0});
    sfSprite_setRotation(borderPanel, 90);    

    /* Create a graphical text to display */
    font = sfFont_createFromFile("assets/mandrill.ttf");
    text = sfText_create();
    sfText_setString(text, "Panel Title!");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 24);
    // printf("strlen: %lu\n",  strlen(sfText_getString(text)));
    sfText_setPosition(text, (sfVector2f){(PANEL_ZERO_X + (WINDOW_X+BORDER_OFFSET - PANEL_ZERO_X)/2) - (sfText_getCharacterSize(text) * strlen(sfText_getString(text))/4), BORDER_OFFSET});
    // sfText_setPosition(text, (sfVector2f){PANEL_ZERO_X + (WINDOW_X - PANEL_ZERO_X)/2 - , BORDER_OFFSET});
    sfText_setColor(text, sfBlack);

    fpsClock = sfClock_create();
    int frame = 0;
    sfText* debug_text = sfText_create();
    sfText_setFont(debug_text, font);
    sfText_setCharacterSize(debug_text, 12);
    sfText_setColor(debug_text, sfBlack);
    sfText_setPosition(debug_text, (sfVector2f){WINDOW_X-BORDER_OFFSET*2-1, BORDER_OFFSET});
    char fps_text[5];

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        sprintf(fps_text, "%.0f", draw_fps(&frame));
        sfText_setString(debug_text, fps_text);

        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, (sfColor){200, 200, 200});

        sfRenderWindow_drawSprite(window, borderLeft, NULL);
        sfRenderWindow_drawSprite(window, borderRight, NULL);
        sfRenderWindow_drawSprite(window, borderPanel, NULL);
        sfRenderWindow_drawSprite(window, borderTop, NULL);
        sfRenderWindow_drawSprite(window, borderBot, NULL);
        
        for(int x=0; x < MAP_X; x++)
            for(int y=0; y < MAP_Y; y++) {
                // printf("x:%i,y:%i\n", x, y);
                sfRenderWindow_drawSprite(window, map[MAP_X * y + x].sprite, NULL);
            }

        /* Draw the sprite */
        sfRenderWindow_drawSprite(window, sprite, NULL);

        /* Draw the text */
        sfRenderWindow_drawText(window, text, NULL);
        sfRenderWindow_drawText(window, debug_text, NULL);

        /* Update the window */
        sfRenderWindow_display(window);

        frame++;
        // printf("Frames: %i\n", frame);
    }

    return 0;
}

double draw_fps(int *frames_in){
    // printf("draw_fps() call\n");
    static double last_fps = 0;
    sfTime elapsed_t = sfClock_getElapsedTime(fpsClock);
    signed long long mili_t = elapsed_t.microseconds / 1000;
    if (mili_t >= 1000){
        sfClock_restart(fpsClock);
        double fps = ((*frames_in)/(mili_t/1000+1));
        *frames_in = 0;
        // printf("FPS: %.0f\n", fps);
        last_fps = fps;
        return fps;
    }
    return last_fps;
}