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
    sfFont* font;
    sfText* text;
    sfEvent event;

    /* Create the main window */
    char NAME_VERSION[] = WINDOW_NAME; strcat(NAME_VERSION, VERSION);
    window = sfRenderWindow_create(mode, NAME_VERSION, sfClose, NULL);
    // sfRenderWindow_setFramerateLimit(window, 120);
    sfRenderWindow_setIcon(window, window_icon.width, window_icon.height, window_icon.pixel_data);

    initRand(time(NULL));

    loadTextures(textureArray);
    createStaticUI(staticUI);

    //mapgen
    createMap();

    player.x = roomCenter(rooms[0]).x;
    player.y = roomCenter(rooms[0]).y;
    player.direction = N;
    player.sprite = sfSprite_create();
    sfSprite_setTexture(player.sprite, textureArray[0], sfTrue);
    sfSprite_setOrigin(player.sprite, (sfVector2f){TILE_SIZE/2, TILE_SIZE/2});
    sfSprite_setTextureRect(player.sprite, (sfIntRect){0*TILE_SIZE, 0*TILE_SIZE, TILE_SIZE, TILE_SIZE});
    sfSprite_setPosition(player.sprite, (sfVector2f){player.x*TILE_SIZE + TILE_SIZE/2 + BORDER_OFFSET, player.y*TILE_SIZE + TILE_SIZE/2 + BORDER_OFFSET});
    player.move = player_move;
    updatePlayerSprite();

    sfSprite* mob = sfSprite_create();
    sfSprite_setTexture(mob, textureArray[0], sfTrue);
    sfSprite_setTextureRect(mob, (sfIntRect){1*TILE_SIZE, 0*TILE_SIZE, TILE_SIZE, TILE_SIZE});
    sfSprite_setPosition(mob, (sfVector2f){4*TILE_SIZE + BORDER_OFFSET, 2*TILE_SIZE + BORDER_OFFSET});    

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

    int player_action = 0;

    sfRectangleShape *map_background = sfRectangleShape_create();
    sfRectangleShape_setSize(map_background, (sfVector2f){MAP_X*TILE_SIZE, MAP_Y*TILE_SIZE});
    sfRectangleShape_setPosition(map_background, (sfVector2f){BORDER_OFFSET, BORDER_OFFSET});
    sfRectangleShape_setFillColor(map_background, (sfColor){78, 78, 98, 255});


    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        sprintf(fps_text, "%.0f", draw_fps(&frame));
        sfText_setString(debug_text, fps_text);

        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed || player_action == 2)
                sfRenderWindow_close(window);
            else if (event.type == sfEvtKeyPressed)
                player_action = handleKeys();
        }

        // player_action = handleKeys();

        clearVisibility();
        doFOV();
        // showAll();

        /* Clear the screen */
        sfRenderWindow_clear(window, (sfColor){200, 200, 200});
        sfRenderWindow_drawRectangleShape(window, map_background, NULL);

        for(int i=0; i < STATIC_UI_NO; i++)
            sfRenderWindow_drawSprite(window, staticUI[i], NULL);
        
        // TODO Change into a function
        for(int x=0; x < MAP_X; x++)
            for(int y=0; y < MAP_Y; y++) {
                // printf("x:%i,y:%i\n", x, y);
                if(map[MAP_COORD(x,y)].visible){
                    sfSprite_setColor(map[MAP_COORD(x,y)].sprite, sfWhite);
                    sfRenderWindow_drawSprite(window, map[MAP_X * y + x].sprite, NULL);
                    if(map[MAP_X * y + x].edge != NULL)
                        for(int i = 0; i < 4; i++)
                            if(map[MAP_X * y + x].edge -> sprite[i] != NULL)
                                sfRenderWindow_drawSprite(window, map[MAP_X * y + x].edge -> sprite[i], NULL);
                }
                else if(map[MAP_COORD(x,y)].explored && (map[MAP_COORD(x,y)].light || hasAllEdges(x,y))){
                    sfSprite_setColor(map[MAP_COORD(x,y)].sprite, (sfColor){100,100,125,255});
                    sfRenderWindow_drawSprite(window, map[MAP_X * y + x].sprite, NULL);
                    if(map[MAP_X * y + x].edge != NULL)
                        for(int i = 0; i < 4; i++)
                            if(map[MAP_X * y + x].edge -> sprite[i] != NULL)
                                sfRenderWindow_drawSprite(window, map[MAP_X * y + x].edge -> sprite[i], NULL);
                }
                else if(map[MAP_COORD(x,y)].explored && !map[MAP_COORD(x,y)].light){
                    sfRectangleShape *blank = sfRectangleShape_create();
                    sfRectangleShape_setSize(blank, (sfVector2f){TILE_SIZE, TILE_SIZE});
                    sfRectangleShape_setPosition(blank, (sfVector2f){x*TILE_SIZE+BORDER_OFFSET,y*TILE_SIZE+BORDER_OFFSET});
                    // TODO use variables instead of colors, make that one computed instead of hardcoded
                    sfRectangleShape_setFillColor(blank, (sfColor){78,78,98,255});
                    sfRenderWindow_drawRectangleShape(window, blank, NULL);
                    sfRectangleShape_destroy(blank);
                    if(map[MAP_X * y + x].edge != NULL)
                        for(int i = 0; i < 4; i++)
                            if(map[MAP_X * y + x].edge -> sprite[i] != NULL)
                                sfRenderWindow_drawSprite(window, map[MAP_X * y + x].edge -> sprite[i], NULL);
                }
            }

        /* Draw the sprite */
        // sfRenderWindow_drawSprite(window, mob, NULL);

        sfRenderWindow_drawSprite(window, player.sprite, NULL);

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