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

// Textures
void loadTextures(sfTexture* [TEXTURE_NO]);
extern sfTexture* textureArray[TEXTURE_NO];

// Variables
extern sfClock* fpsClock;
extern Player player;

// Arrays
extern Tile map[MAP_X * MAP_Y];
extern sfSprite* staticUI[STATIC_UI_NO];

// Functions
void createMap(Tile* map);
void createStaticUI(sfSprite* staticUI[]);
int handleKeys(void);
void player_move(int);
void updatePlayerSprite(void);