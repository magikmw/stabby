/*
    Keyboard.c is a part of Stabby
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

int handleKeys(void)
{
    if(sfKeyboard_isKeyPressed(sfKeyNumpad8) || sfKeyboard_isKeyPressed(sfKeyK)){
        player.move(N);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad2) || sfKeyboard_isKeyPressed(sfKeyJ)){
        player.move(S);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad4) || sfKeyboard_isKeyPressed(sfKeyH)){
        player.move(W);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad6) || sfKeyboard_isKeyPressed(sfKeyL)){
        player.move(E);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad7)){
        player.move(NW);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad9)){
        player.move(NE);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad1)){
        player.move(SW);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad3)){
        player.move(SE);
        return 1;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyEscape)){
        return 2;
    }
    
    #ifdef DEBUG
    // DEBUG KEYS
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad0)){ // Display edge/wall status of a tile
        printf("---\nPlayer: %i,%i\n", player.x, player.y);
        printf("Tile has edge: %s\n", (map[MAP_X * player.y + player.x].edge != NULL) ? "Yes" : "No" );
        if(map[MAP_X * player.y + player.x].edge != NULL)
            printf("Edges: N:%i, S:%i, W:%i, E:%i\n", map[MAP_X * player.y + player.x].edge -> N, map[MAP_X * player.y + player.x].edge -> S, map[MAP_X * player.y + player.x].edge -> W, map[MAP_X * player.y + player.x].edge -> E);

        return 0;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyS)){
        printf("---\nClearing up vision map.\n");
        clearVisibility();

        return 0;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyD)){
        printf("---\nShow all.\n");
        showAll();

        return 0;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyA)){
        printf("---\nDo FOV.\n");
        doFOV();
        printf("End\n");
        return 0;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyR)){
        printf("---\nRandom int: %i\n", randInt(ROOM_MIN_SIZE, ROOM_MAX_SIZE));
        return 0;
    }
    #endif

    // No keys from the list above, skip
    else
        return 0;
}