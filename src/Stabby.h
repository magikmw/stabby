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
#include <math.h> // distance calculations

// SFML includes
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>

// libds
#include "ds.h"

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
#define MIN_ROOMS       6
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
#define VIEW_DISTANCE 25

// 'Safe' impossible travel distance
#define INFINITE_DISTANCE MAP_X * MAP_Y + 1

// Don't change the enum values below - some loops depend on them
enum directions {N=0, E=1, S=2, W=3, NW=4, NE=5, SE=6, SW=7};

enum player_actions {no_turn=0, turn=1, quit=2};

enum mob_types {Plain=0};

enum ai_states {standby = 0, alerted = 1, pursue = 2};

typedef struct Entity Entity;
typedef struct Edge Edge;
typedef struct AI AI;
typedef struct Tile Tile;
typedef struct Rect Rect;
typedef struct Room Room;
typedef struct DMap DMap;

// wall edge struct
struct Edge
{
    boolean N;
    boolean S;
    boolean W;
    boolean E;
    sfSprite* sprite[4];
};

// Mob AI component structure
struct AI
{
    void (*standby)(Entity* mob);
    void (*alerted)(Entity* mob);
    void (*pursue)(Entity* mob);
};

// Map entities
struct Entity
{
    int x, y;
    int direction;
    sfSprite* sprite;
    boolean (*move)(int, Entity*);
    boolean moved;
    int ai_state;
    AI* ai;
};

// basic tile struct
struct Tile
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
    Entity* entity;
};

// mapgen
struct Rect
{
    int x1;
    int y1;
    int x2;
    int y2;
};

struct Room
{
    int x1, y1, x2, y2;
    sfVector2f* doors[20];  // holds positions of entrances
    boolean light;          // true if the room is lit (tiles within permalit)
};

// Dijkstra map struct
struct DMap
{
    list_p poi_list;              // Holds the points with default values
    boolean poi_list_flag;        // Set true if poi_list has been changed
    int value_map[MAP_X * MAP_Y]; // Holds the calculated values
    list_p frontier;              // Used for floodfill
};
