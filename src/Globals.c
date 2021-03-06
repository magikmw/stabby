/*
    Globals.c is a part of Stabby
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

// Graphics
sfTexture* textureArray[TEXTURE_NO];
sfRectangleShape* shapeArray[SHAPE_NO];

// Variables
sfClock* fpsClock;
Entity player;
int rooms_number;
int mobs_number;

// Dijkstra maps
DMap DMap_PlayerChase;
DMap DMap_PlayerSuspected;
DMap DMap_Light;

// Arrays
Tile map[MAP_X * MAP_Y];
Room* rooms[MAX_ROOMS];
sfSprite* staticUI[STATIC_UI_NO];

// Constants
// Relative positions of 8 tiles around n in array[MAP_X*MAP_Y]
const int neighbours[8] = {-MAP_X, 1, MAP_X, -1, -(MAP_X+1), -(MAP_X-1), MAP_X+1, MAP_X-1};
