/*
    Demographics.c is a part of Stabby
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

// AI function prototypes
void Plain_Standby(Entity* mob);
void Plain_Alerted(Entity* mob);
void Plain_Pursue(Entity* mob);

void spawnPlayer(void){
    sfVector2i position = roomCenter(rooms[0]);
    player.x = position.x;
    player.y = position.y;
    player.direction = N;
    player.sprite = sfSprite_create();
    sfSprite_setTexture(player.sprite, textureArray[0], sfTrue);
    sfSprite_setOrigin(player.sprite, (sfVector2f){TILE_SIZE/2, TILE_SIZE/2});
    sfSprite_setTextureRect(player.sprite, (sfIntRect){0*TILE_SIZE, 0*TILE_SIZE, TILE_SIZE, TILE_SIZE});
    sfSprite_setPosition(player.sprite, (sfVector2f){player.x*TILE_SIZE + TILE_SIZE/2 + BORDER_OFFSET, player.y*TILE_SIZE + TILE_SIZE/2 + BORDER_OFFSET});
    player.move = player_move;
    updateEntitySprite(&player);

    map[MAP_COORD(player.x, player.y)].entity = &player;
}

void createMob(int type, Tile map_tile){
    switch(type){
        case Plain:
        {
            map_tile.entity->x = map_tile.x;
            map_tile.entity->y = map_tile.y;
            map_tile.entity->direction = randInt(N, SW);
            map_tile.entity->sprite = sfSprite_create();
            sfSprite_setTexture(map_tile.entity->sprite, textureArray[0], sfTrue);
            sfSprite_setOrigin(map_tile.entity->sprite, (sfVector2f){TILE_SIZE/2, TILE_SIZE/2});
            sfSprite_setTextureRect(map_tile.entity->sprite, (sfIntRect){1*TILE_SIZE, 0*TILE_SIZE, TILE_SIZE, TILE_SIZE});
            sfSprite_setPosition(map_tile.entity->sprite, (sfVector2f){map_tile.entity->x*TILE_SIZE + TILE_SIZE/2 + BORDER_OFFSET, map_tile.entity->y * TILE_SIZE + TILE_SIZE/2 + BORDER_OFFSET});

            map_tile.entity->move = mob_move;
            map_tile.entity->took_turn = false;

            map_tile.entity->ai = (AI){Plain_Standby, Plain_Alerted, Plain_Pursue, ai_standby, 0};

            updateEntitySprite(map_tile.entity);
            break;
        }
        default:
        {
            #ifdef DEBUG
            printf("[Error] Wrong mob type specified in createMob()\n");
            #endif
        }
    }
}
