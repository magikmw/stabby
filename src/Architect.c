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
Edge* makeWall(int direction);
void makeBorders(int x, int y, int w, int h, char* mod);

void createMap(Tile* map){

    makeBorders(0, 0, MAP_X, MAP_Y, "in"); // make map edge walls
    makeBorders(3, 3, 4, 4, "both");
    makeBorders(5, 5, 1, 1, "both");
    makeBorders(1, 1, 10, 10, "both");

    for(int x=0; x < MAP_X; x++)
        for(int y=0; y < MAP_Y; y++) {
            // printf("Array index: %i\n", MAP_X * y + x);
            map[MAP_X * y + x].x = x;
            map[MAP_X * y + x].y = y;
            map[MAP_X * y + x].sprite = sfSprite_create();
            sfSprite_setTexture(map[MAP_X * y + x].sprite, textureArray[0], sfTrue);
            sfSprite_setTextureRect(map[MAP_X * y + x].sprite, (sfIntRect){0*TILE_SIZE,1*TILE_SIZE,TILE_SIZE,TILE_SIZE});
            sfSprite_setPosition(map[MAP_X * y + x].sprite, (sfVector2f){map[MAP_X * y + x].x * TILE_SIZE + BORDER_OFFSET, map[MAP_X * y + x].y * TILE_SIZE + BORDER_OFFSET});



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

Edge* makeWall(int direction)
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

void makeBorders(int point_x, int point_y, int w, int h, char* mod)
{
    // printf("makeBorders() call strcmp(mod, in): %i\n", strcmp(mod, "in"));

    int mode = 3; // mode flag - 0 for in, 1 of out, 2 for both

    if(strcmp(mod, "in") == 0)
        mode = 0;
    else if(strcmp(mod, "out") == 0)
        mode = 1;
    else if(strcmp(mod, "both") == 0)
        mode = 2;
    else
        printf("makeBorders(): ERROR, WRONG MODE PROVIDED: %s\n", mod);

    // printf("makeBorders(): %i\n", mode);

    if(mode == 0 || mode == 2)
    {
        // printf("in executed\n");
        for(int x=point_x; x < point_x+w; x++)
            for(int y=point_y; y < point_y+h; y++) {
                if(x == point_x)
                {
                    if(map[MAP_X * y + x].edge == NULL)
                        map[MAP_X * y + x].edge = makeWall(W);
                    else
                        map[MAP_X * y + x].edge -> W = true;
                }
                if(x == point_x + w-1)
                {
                    if(map[MAP_X * y + x].edge == NULL)
                        map[MAP_X * y + x].edge = makeWall(E);
                    else
                        map[MAP_X * y + x].edge -> E = true;
                }
                if(y == point_y)
                {
                    if(map[MAP_X * y + x].edge == NULL)
                        map[MAP_X * y + x].edge = makeWall(N);
                    else
                        map[MAP_X * y + x].edge -> N = true;
                }
                if(y == point_y + h - 1)
                {
                    if(map[MAP_X * y + x].edge == NULL)
                        map[MAP_X * y + x].edge = makeWall(S);
                    else
                        map[MAP_X * y + x].edge -> S = true;
                }   
            }
    }

    if(mode == 1 || mode == 2)
    {
       for(int x=point_x; x < point_x+w; x++)
            for(int y=point_y; y < point_y+h; y++) {
                if(x == point_x && point_x-1 >= 0)
                {
                    if(map[MAP_X * y + (x-1)].edge == NULL)
                        map[MAP_X * y + (x-1)].edge = makeWall(E);
                    else
                        map[MAP_X * y + (x-1)].edge -> E = true;
                }
                if(x == point_x + w-1 && point_x+w < MAP_X)
                {
                    if(map[MAP_X * y + (x+1)].edge == NULL)
                        map[MAP_X * y + (x+1)].edge = makeWall(W);
                    else
                        map[MAP_X * y + (x+1)].edge -> W = true;
                }
                if(y == point_y && point_y -1 >= 0)
                {
                    if(map[MAP_X * (y-1) + x].edge == NULL)
                        map[MAP_X * (y-1) + x].edge = makeWall(S);
                    else
                        map[MAP_X * (y-1) + x].edge -> S = true;
                }
                if(y == point_y + h - 1 && point_y+h < MAP_Y)
                {
                    if(map[MAP_X * (y+1) + x].edge == NULL)
                        map[MAP_X * (y+1) + x].edge = makeWall(N);
                    else
                        map[MAP_X * (y+1) + x].edge -> N = true;
                }   
            }
    }
}

boolean hasEdges(int x, int y){
    if(isMap(x, y) == false || map[MAP_COORD(x,y)].edge == NULL)
        return false;
    else
        return true;
}

boolean isMap(int x, int y){
    if(x < 0 || x >= MAP_X || y < 0 || y >= MAP_Y)
        return false;
    else
        return true;
}