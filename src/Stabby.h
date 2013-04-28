/*
    Stabby.h is a part of Stabby
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

// STD includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> // for srand, for now

// SFML includes
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>

#include "icon.h"

// Uncomment for debug mode
#define DEBUG

// Version and title name
#define WINDOW_NAME     "Stabby "
#define VERSION         "Alpha"

// Window dimensions in px
#define WINDOW_X        960
#define WINDOW_Y        540

// Map dimensions in tiles
#define MAP_X           24
#define MAP_Y           16

// Size of tiles/sprites in px
#define TILE_SIZE       32

// room properties
#define MAX_ROOMS       30
#define MIN_ROOMS       8
#define ROOM_MIN_SIZE   4
#define ROOM_MAX_SIZE   6

// Number of textures
#define TEXTURE_NO      2

// Number of static UI elements
#define STATIC_UI_NO    5

#define BORDER_OFFSET   14 // Useless border offset (window/panels)

// "0" X value for the right (menu) panel's right border
#define PANEL_ZERO_X    MAP_X * TILE_SIZE + BORDER_OFFSET

// let's make ourselves a boolean 'type'
#define boolean         char
#define true            1
#define false           0

// min/max macros
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

// map coordinate aid
#define MAP_COORD(x, y) (MAP_X * (y) + (x))

// FOV consts
#define VIEW_DISTANCE 3

enum directions {NW, N, NE, W, E, SW, S, SE};

// wall edge struct
typedef struct
{
    boolean N;
    boolean S;
    boolean W;
    boolean E;
    sfSprite* sprite[4];
} Edge;

// basic tile struct
typedef struct
{
    int x;
    int y;
    sfSprite* sprite;
    Edge* edge;
    boolean visible;
    boolean explored;
    boolean light;          // if the tile is lit
    boolean corridor;
    boolean corridor_end;
} Tile;

// mapgen
typedef struct
{
    int x1;
    int y1;
    int x2;
    int y2;
} Rect;

typedef struct
{
    int x1, y1, x2, y2;
    sfVector2f* doors[20];  // holds positions of entrances
    boolean light;          // true if the room is lit (tiles within permalit)
} Room;

// player character structure
typedef struct
{
    int x, y;
    int direction;
    sfSprite* sprite;
    void (*move)(int);
} Player;