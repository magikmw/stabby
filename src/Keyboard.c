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
    boolean game_action = false; // did the player take action _in_game_ (turn passes)
    if(sfKeyboard_isKeyPressed(sfKeyNumpad8) || sfKeyboard_isKeyPressed(sfKeyK)){
        game_action = player.move(N, NULL);
        return game_action;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad2) || sfKeyboard_isKeyPressed(sfKeyJ)){
        game_action = player.move(S, NULL);
        return game_action;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad4) || sfKeyboard_isKeyPressed(sfKeyH)){
        game_action = player.move(W, NULL);
        return game_action;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad6) || sfKeyboard_isKeyPressed(sfKeyL)){
        game_action = player.move(E, NULL);
        return game_action;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad7) || sfKeyboard_isKeyPressed(sfKeyY)){
        game_action = player.move(NW, NULL);
        return game_action;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad9) || sfKeyboard_isKeyPressed(sfKeyU)){
        game_action = player.move(NE, NULL);
        return game_action;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad1) || sfKeyboard_isKeyPressed(sfKeyB)){
        game_action = player.move(SW, NULL);
        return game_action;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad3) || sfKeyboard_isKeyPressed(sfKeyN)){
        game_action = player.move(SE, NULL);
        return game_action;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad5) || sfKeyboard_isKeyPressed(sfKeyPeriod)){
        // wait/pass
        return turn;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyEscape)){
        return quit;
    }

    #ifdef DEBUG
    // DEBUG KEYS
    else if(sfKeyboard_isKeyPressed(sfKeyNumpad0)){ // Display edge/wall status of a tile
        printf("---\nPlayer: %i,%i\n", player.x, player.y);
        printf("Tile has edge: %s\n", (map[MAP_X * player.y + player.x].edge != NULL) ? "Yes" : "No" );
        if(map[MAP_X * player.y + player.x].edge != NULL)
            printf("Edges: N:%i, S:%i, W:%i, E:%i\n", map[MAP_X * player.y + player.x].edge -> N, map[MAP_X * player.y + player.x].edge -> S, map[MAP_X * player.y + player.x].edge -> W, map[MAP_X * player.y + player.x].edge -> E);

        return no_turn;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyS)){
        printf("---\nClearing up vision map.\n");
        clearVisibility();

        return no_turn;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyD)){
        printf("---\nShow all.\n");
        showAll();

        return no_turn;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyA)){
        printf("---\nDo FOV.\n");
        doFOV();
        printf("End\n");
        return no_turn;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyR)){
        printf("---\nRandom int: %i\n", randInt(ROOM_MIN_SIZE, ROOM_MAX_SIZE));
        return no_turn;
    }
    else if(sfKeyboard_isKeyPressed(sfKeyF)){
        return -1;
    }
    #endif

    // No keys from the list above, skip
    else
        return no_turn;
}
