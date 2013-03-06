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

void createMap(Tile* map){
    for(int x=0; x < MAP_X; x++)
        for(int y=0; y < MAP_Y; y++) {
            // printf("Array index: %i\n", MAP_X * y + x);
            map[MAP_X * y + x].x = x;
            map[MAP_X * y + x].y = y;
            map[MAP_X * y + x].sprite = sfSprite_create();
            sfSprite_setTexture(map[MAP_X * y + x].sprite, textureArray[0], sfTrue);
            sfSprite_setTextureRect(map[MAP_X * y + x].sprite, (sfIntRect){0*TILE_SIZE,1*TILE_SIZE,TILE_SIZE,TILE_SIZE});
            sfSprite_setPosition(map[MAP_X * y + x].sprite, (sfVector2f){map[MAP_X * y + x].x * TILE_SIZE + BORDER_OFFSET, map[MAP_X * y + x].y * TILE_SIZE + BORDER_OFFSET});
        }
}