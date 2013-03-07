/*
    Architect.c is a part of Stabby
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

Edge* alloc_edge(void);
Edge* makeBorders(int direction);

void createMap(Tile* map){
    map[MAP_X * 5 + 5].edge = alloc_edge();
    map[MAP_X * 5 + 5].edge -> N = true;
    map[MAP_X * 5 + 5].edge -> E = true;
    for(int x=0; x < MAP_X; x++)
        for(int y=0; y < MAP_Y; y++) {
            // printf("Array index: %i\n", MAP_X * y + x);
            map[MAP_X * y + x].x = x;
            map[MAP_X * y + x].y = y;
            map[MAP_X * y + x].sprite = sfSprite_create();
            sfSprite_setTexture(map[MAP_X * y + x].sprite, textureArray[0], sfTrue);
            sfSprite_setTextureRect(map[MAP_X * y + x].sprite, (sfIntRect){0*TILE_SIZE,1*TILE_SIZE,TILE_SIZE,TILE_SIZE});
            sfSprite_setPosition(map[MAP_X * y + x].sprite, (sfVector2f){map[MAP_X * y + x].x * TILE_SIZE + BORDER_OFFSET, map[MAP_X * y + x].y * TILE_SIZE + BORDER_OFFSET});


            // This section creates border walls (so nothing will fall off)
            switch(x)
            {
                case 0:
                {
                    map[MAP_X * y + x].edge = makeBorders(W);
                    break;
                }
                case MAP_X - 1:
                {
                    map[MAP_X * y + x].edge = makeBorders(E);
                    break;
                }
            }
            switch(y)
            {
                case 0:
                {
                    if(map[MAP_X * y + x].edge == NULL)
                        map[MAP_X * y + x].edge = makeBorders(N);
                    else
                        map[MAP_X * y + x].edge -> N = true;
                    break;
                }
                case MAP_Y - 1:
                {
                    if(map[MAP_X * y + x].edge == NULL)
                        map[MAP_X * y + x].edge = makeBorders(S);
                    else
                        map[MAP_X * y + x].edge -> S = true;
                    break;
                }   
            }

            // This section creates the sprites for the walls
            if(map[MAP_X * y + x].edge != NULL)
            {
                if(map[MAP_X * y + x].edge -> N == true)
                {
                    map[MAP_X * y + x].edge -> sprite[0] = sfSprite_create();
                    sfSprite_setTexture(map[MAP_X * y + x].edge -> sprite[0], textureArray[0], sfTrue);
                    sfSprite_setTextureRect(map[MAP_X * y + x].edge -> sprite[0], (sfIntRect){1*TILE_SIZE, 1*TILE_SIZE, TILE_SIZE, TILE_SIZE});
                    sfSprite_setPosition(map[MAP_X * y + x].edge -> sprite[0], sfSprite_getPosition(map[MAP_X * y + x].sprite));
                }
                if(map[MAP_X * y + x].edge -> S == true)
                {
                    map[MAP_X * y + x].edge -> sprite[1] = sfSprite_create();
                    sfSprite_setTexture(map[MAP_X * y + x].edge -> sprite[1], textureArray[0], sfTrue);
                    sfSprite_setTextureRect(map[MAP_X * y + x].edge -> sprite[1], (sfIntRect){2*TILE_SIZE, 1*TILE_SIZE, TILE_SIZE, TILE_SIZE});
                    sfSprite_setPosition(map[MAP_X * y + x].edge -> sprite[1], sfSprite_getPosition(map[MAP_X * y + x].sprite));
                }
                if(map[MAP_X * y + x].edge -> W == true)
                {
                    map[MAP_X * y + x].edge -> sprite[2] = sfSprite_create();
                    sfSprite_setTexture(map[MAP_X * y + x].edge -> sprite[2], textureArray[0], sfTrue);
                    sfSprite_setTextureRect(map[MAP_X * y + x].edge -> sprite[2], (sfIntRect){3*TILE_SIZE, 1*TILE_SIZE, TILE_SIZE, TILE_SIZE});
                    sfSprite_setPosition(map[MAP_X * y + x].edge -> sprite[2], sfSprite_getPosition(map[MAP_X * y + x].sprite));
                }
                if(map[MAP_X * y + x].edge -> E == true)
                {
                    map[MAP_X * y + x].edge -> sprite[3] = sfSprite_create();
                    sfSprite_setTexture(map[MAP_X * y + x].edge -> sprite[3], textureArray[0], sfTrue);
                    sfSprite_setTextureRect(map[MAP_X * y + x].edge -> sprite[3], (sfIntRect){4*TILE_SIZE, 1*TILE_SIZE, TILE_SIZE, TILE_SIZE});
                    sfSprite_setPosition(map[MAP_X * y + x].edge -> sprite[3], sfSprite_getPosition(map[MAP_X * y + x].sprite));
                }
            }
        }
}

Edge* alloc_edge(void)
{
    return (Edge*) calloc(1, sizeof(Edge) +1);
}

Edge* makeBorders(int direction)
{
    Edge* temp_ptr = alloc_edge();
    switch(direction)
    {
        case N:
        {
            temp_ptr -> N = true;
            break;
        }
        case S:
        {
            temp_ptr -> S = true;
            break;
        }
        case W:
        {
            temp_ptr -> W = true;
            break;
        }
        case E:
        {
            temp_ptr -> E = true;
            break;
        }
    }

    return temp_ptr;
}