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

// Include the icon data
#include "icon.h"

#ifdef DEBUG
int draw_fps(int *);
#endif

int main(void)
{
    #ifdef DEBUG
        printf("[INFO] Debug mode ON\n");
    #endif

    /* Create the main window */
    sfRenderWindow* window = sfRenderWindow_create( \
        (sfVideoMode){WINDOW_X, WINDOW_Y, 32}, NAME_VERSION, sfClose, NULL);
    sfRenderWindow_setVerticalSyncEnabled(window, true);
    sfRenderWindow_setIcon(window, window_icon.width, window_icon.height, window_icon.pixel_data);

    // Initialize the pseudorandom generator
    initRand(time(NULL));

    // Initialize graphics
    loadTextures();
    makeShapes();

    // Initialize static UI elements
    createStaticUI();

    // mapgen
    createMap();

    // player creation
    spawnPlayer();

    // spawn mobs
    spawnMobs();

    // Create DMaps
    DMapCreate(&DMap_PlayerChase);
    DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
    DMapUpdate(&DMap_PlayerChase);

    /* Create a graphical text to display */
    sfFont* font;
    sfText* text;
    font = sfFont_createFromFile("assets/mandrill.ttf");
    text = sfText_create();
    sfText_setString(text, "Panel Title!");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 24);
    // printf("strlen: %lu\n",  strlen(sfText_getString(text)));
    sfText_setPosition(text, (sfVector2f){(PANEL_ZERO_X + (WINDOW_X+BORDER_OFFSET - PANEL_ZERO_X)/2) - (sfText_getCharacterSize(text) * strlen(sfText_getString(text))/4), BORDER_OFFSET});
    // sfText_setPosition(text, (sfVector2f){PANEL_ZERO_X + (WINDOW_X - PANEL_ZERO_X)/2 - , BORDER_OFFSET});
    sfText_setColor(text, sfBlack);    

    #ifdef DEBUG
    // DMap debug text object
    sfText* text_dmap_value = sfText_create();
    sfText_setFont(text_dmap_value, font);
    sfText_setCharacterSize(text_dmap_value, 12);
    sfText_setColor(text_dmap_value, sfMagenta);

    // fps counter
    fpsClock = sfClock_create();
    int frame = 0;
    sfText* debug_text = sfText_create();
    sfText_setFont(debug_text, font);
    sfText_setCharacterSize(debug_text, 12);
    sfText_setColor(debug_text, sfBlack);
    sfText_setPosition(debug_text, (sfVector2f){WINDOW_X-BORDER_OFFSET*2-1, BORDER_OFFSET});
    char fps_text[5];
    
    // Debug variables
    boolean debug_dmap_view = false;
    #endif

    sfEvent event;
    int player_action = no_turn;

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        #ifdef DEBUG
        sprintf(fps_text, "%i", draw_fps(&frame));
        sfText_setString(debug_text, fps_text);
        #endif

        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed || player_action == 2)
                sfRenderWindow_close(window);
            else if (event.type == sfEvtKeyPressed)
                player_action = handleKeys();
        }

        #ifdef DEBUG // Various debug key toggles
        if(player_action == -1 && debug_dmap_view == false)
            debug_dmap_view = true;
        else if(player_action == -1 && debug_dmap_view == true)
            debug_dmap_view = false;
        #endif

        // Update DMaps
        DMapUpdate(&DMap_PlayerChase);

        if(player_action == turn){
            // AI take turn
            for(int x=0; x < MAP_X; x++){
                for(int y=0; y < MAP_Y; y++) {
                    if(map[MAP_COORD(x,y)].entity != NULL && map[MAP_COORD(x,y)].entity != &player){
                        if(!map[MAP_COORD(x,y)].entity->took_turn){
                            map[MAP_COORD(x,y)].entity->took_turn = true;
                            switch(map[MAP_COORD(x,y)].entity->ai.state){
                                case ai_standby:
                                {
                                    map[MAP_COORD(x,y)].entity->ai.standby(map[MAP_COORD(x,y)].entity);
                                    break;
                                }
                                case ai_alerted:
                                {
                                    map[MAP_COORD(x,y)].entity->ai.alerted(map[MAP_COORD(x,y)].entity);
                                    break;
                                }
                                case ai_pursue:
                                {
                                    map[MAP_COORD(x,y)].entity->ai.pursue(map[MAP_COORD(x,y)].entity);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            // reset the move status
            for(int x=0; x < MAP_X; x++){
                for(int y=0; y < MAP_Y; y++) {
                    if(map[MAP_COORD(x,y)].entity != NULL && map[MAP_COORD(x,y)].entity != &player){
                        if(map[MAP_COORD(x,y)].entity->took_turn){
                            map[MAP_COORD(x,y)].entity->took_turn = false;
                        }
                    }
                }
            }
        }

        // FOV control
        clearVisibility();
        // doFOV();
        showAll();

        /* Clear the screen */
        sfRenderWindow_clear(window, COLOR_BACKGROUND);
        sfRenderWindow_drawRectangleShape(window, shapeArray[0], NULL);

        // Draw static UI
        for(int i=0; i < STATIC_UI_NO; i++)
            sfRenderWindow_drawSprite(window, staticUI[i], NULL);
        
        // Render the map and entities
        // [TODO] Change into a function
        for(int x=0; x < MAP_X; x++)
            for(int y=0; y < MAP_Y; y++) {
                if(map[MAP_COORD(x,y)].visible){
                    sfSprite_setColor(map[MAP_COORD(x,y)].sprite, sfWhite);
                    sfRenderWindow_drawSprite(window, map[MAP_X * y + x].sprite, NULL);
                    if(map[MAP_X * y + x].edge != NULL)
                        for(int i = 0; i < 4; i++)
                            if(map[MAP_X * y + x].edge -> sprite[i] != NULL)
                                sfRenderWindow_drawSprite(window, map[MAP_X * y + x].edge -> sprite[i], NULL);
                }
                else if(map[MAP_COORD(x,y)].explored && (map[MAP_COORD(x,y)].light || hasAllEdges(x,y))){
                    sfSprite_setColor(map[MAP_COORD(x,y)].sprite, COLOR_EXPLORED_LIGHT);
                    sfRenderWindow_drawSprite(window, map[MAP_X * y + x].sprite, NULL);
                    if(map[MAP_X * y + x].edge != NULL)
                        for(int i = 0; i < 4; i++)
                            if(map[MAP_X * y + x].edge -> sprite[i] != NULL)
                                sfRenderWindow_drawSprite(window, map[MAP_X * y + x].edge -> sprite[i], NULL);
                }
                else if(map[MAP_COORD(x,y)].explored && !map[MAP_COORD(x,y)].light){
                    sfRectangleShape_setPosition(shapeArray[1], (sfVector2f){x*TILE_SIZE+BORDER_OFFSET,y*TILE_SIZE+BORDER_OFFSET});
                    sfRenderWindow_drawRectangleShape(window, shapeArray[1], NULL);
                    if(map[MAP_X * y + x].edge != NULL)
                        for(int i = 0; i < 4; i++)
                            if(map[MAP_X * y + x].edge -> sprite[i] != NULL)
                                sfRenderWindow_drawSprite(window, map[MAP_X * y + x].edge -> sprite[i], NULL);
                }

                if(map[MAP_COORD(x,y)].visible && map[MAP_COORD(x,y)].entity)
                    sfRenderWindow_drawSprite(window, map[MAP_COORD(x,y)].entity->sprite, NULL);



                #ifdef DEBUG // debug printing of the DMap_PlayerChase values
                if(debug_dmap_view == true)
                {
                    char str_value[5];
                    sprintf(str_value, "%d", DMap_PlayerChase.value_map[MAP_COORD(x,y)]);
                    sfText_setString(text_dmap_value, str_value);
                    sfText_setPosition(text_dmap_value, (sfVector2f){BORDER_OFFSET + TILE_SIZE * x + TILE_SIZE/2 - (sfText_getCharacterSize(text_dmap_value) * strlen(sfText_getString(text_dmap_value))/5), BORDER_OFFSET + TILE_SIZE * y + TILE_SIZE/4});
                    sfRenderWindow_drawText(window, text_dmap_value, NULL);
                }
                #endif
            }

        /* Draw the text */
        sfRenderWindow_drawText(window, text, NULL);

        #ifdef DEBUG // FPS counter
        sfRenderWindow_drawText(window, debug_text, NULL);
        frame++;
        #endif

        /* Update the window */
        sfRenderWindow_display(window);

        player_action = no_turn; // reset
    }

    // [TODO] Cleanup
    #ifdef DEBUG
    sfText_destroy(text_dmap_value);
    sfText_destroy(debug_text);
    sfClock_destroy(fpsClock);
    #endif

    sfRenderWindow_destroy(window);
    sfText_destroy(text);
    sfFont_destroy(font);
    DMapDestroy(&DMap_PlayerChase);

    #ifdef DEBUG
    printf("[INFO] Have a nice day.\n");
    #endif

    return 0;
}

#ifdef DEBUG
int draw_fps(int *frames_in){
    static int last_fps = 0;
    sfTime elapsed_t = sfClock_getElapsedTime(fpsClock);
    signed long long mili_t = elapsed_t.microseconds / 1000;
    if (mili_t >= 1000){
        sfClock_restart(fpsClock);
        int fps = ((*frames_in)/(mili_t/1000));
        *frames_in = 0;
        last_fps = fps;
        return fps;
    }
    return last_fps;
}
#endif