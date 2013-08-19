/*
    IncludeGlobals.h is a part of Stabby
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

#ifndef __INCLUDE_GLOBALS_H__
#define __INCLUDE_GLOBALS_H__

// Graphics
void loadTextures(void);
void makeShapes(void);
extern sfTexture* textureArray[TEXTURE_NO];
extern sfRectangleShape* shapeArray[SHAPE_NO];

// Variables
extern sfClock* fpsClock;
extern Entity player;
extern int rooms_number;
extern int mobs_number;

// Dijkstra maps
extern DMap DMap_PlayerChase;
extern DMap DMap_PlayerSuspected;
extern DMap DMap_Light;
/*
    [TODO] DMap DMap_Patrol;
    [TODO] DMap DMap_Flee;
*/

// Arrays
extern Tile map[MAP_X * MAP_Y];
extern sfSprite* staticUI[STATIC_UI_NO];
extern Room* rooms[MAX_ROOMS];

// Constants
extern const int neighbours[8];

// Functions
void createMap();
void createStaticUI(void);
int handleKeys(void);
double distance(int x1, int y1, int x2, int y2);

// Interaction
boolean player_move(int direction, Entity* nul);
boolean mob_move(int direction, Entity* mob);
boolean checkCollision(sfVector2f origin, int direction);
boolean checkEntityCollision(sfVector2i origin, int direction);

// graphics
void updateEntitySprite(Entity* entity);
void makeMapSprites(void);

// map properties checks
boolean hasEdges(int x, int y);
boolean hasAllEdges(int x, int y);
boolean isMap(int x, int y);
sfVector2i roomCenter(Room* room);

// fov functions
void showAll(void);
void clearVisibility(void);
void doFOV(void);

// random
void initRand(unsigned int seed);
int randInt(int, int);

// dijkstra maps related
void DMapCreate(DMap*);
void DMapAddPOI(DMap*, int);
void DMapRemPOI(DMap*, int);
void DMapUpdate(DMap*);
void DMapDestroy(DMap*);
void addToFrontier(list_p, int*, int);
int DMapFollow(DMap* dmap, int current);

// demographics
void spawnPlayer(void);
void createMob(int type, Tile map_tile);
void spawnMobs(void);

// [TODO] Sort the function prototypes properly by files + re add the variable names

#endif
