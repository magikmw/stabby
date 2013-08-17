/*
    Graphics.c is a part of Stabby
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

void loadTextures(void){
    textureArray[0] = sfTexture_createFromFile("assets/sprites.png", NULL);
    textureArray[1] = sfTexture_createFromFile("assets/border.png", NULL);
}

void makeShapes(void){
    shapeArray[0] = sfRectangleShape_create();
    sfRectangleShape_setSize(shapeArray[0], (sfVector2f){MAP_X*TILE_SIZE, MAP_Y*TILE_SIZE});
    sfRectangleShape_setPosition(shapeArray[0], (sfVector2f){BORDER_OFFSET, BORDER_OFFSET});
    sfRectangleShape_setFillColor(shapeArray[0], COLOR_MAP_BACKGROUND);

    shapeArray[1] = sfRectangleShape_create();
    sfRectangleShape_setSize(shapeArray[1], (sfVector2f){TILE_SIZE, TILE_SIZE});
    sfRectangleShape_setFillColor(shapeArray[1], COLOR_MAP_BACKGROUND);
}

void updateEntitySprite(Entity* entity)
{
    switch(entity->direction)
        {
            case N:
            {
                sfSprite_setRotation(entity->sprite, 0);
                break;
            }
            case S:
            {
                sfSprite_setRotation(entity->sprite, 180);
                break;
            }
            case W:
            {
                sfSprite_setRotation(entity->sprite, 270);
                break;
            }
            case E:
            {
                sfSprite_setRotation(entity->sprite, 90);
                break;
            }
            case NW:
            {
                sfSprite_setRotation(entity->sprite, 315);
                break;
            }
            case NE:
            {
                sfSprite_setRotation(entity->sprite, 45);
                break;
            }
            case SW:
            {
                sfSprite_setRotation(entity->sprite, 225);
                break;
            }
            case SE:
            {
                sfSprite_setRotation(entity->sprite, 135);
                break;
            }
        }

    sfSprite_setPosition(entity->sprite, (sfVector2f){entity->x * TILE_SIZE + TILE_SIZE/2 + BORDER_OFFSET, entity->y * TILE_SIZE + TILE_SIZE/2 + BORDER_OFFSET});
}

Room* isInRoom(int x, int y);

void makeMapSprites(void){
    for(int x=0; x < MAP_X; x++)
        for(int y=0; y < MAP_Y; y++) {

            map[MAP_X * y + x].x = x;
            map[MAP_X * y + x].y = y;
            map[MAP_X * y + x].sprite = sfSprite_create();
            sfSprite_setTexture(map[MAP_X * y + x].sprite, textureArray[0], sfTrue);
            if(hasAllEdges(x,y))
                sfSprite_setTextureRect(map[MAP_X * y + x].sprite, (sfIntRect){5*TILE_SIZE,1*TILE_SIZE,TILE_SIZE,TILE_SIZE});    
            else
                sfSprite_setTextureRect(map[MAP_X * y + x].sprite, (sfIntRect){0*TILE_SIZE,1*TILE_SIZE,TILE_SIZE,TILE_SIZE});
            sfSprite_setPosition(map[MAP_X * y + x].sprite, (sfVector2f){map[MAP_X * y + x].x * TILE_SIZE + BORDER_OFFSET, map[MAP_X * y + x].y * TILE_SIZE + BORDER_OFFSET});
            // if(isInRoom(x,y) != NULL){
            //     sfSprite_setColor(map[MAP_X * y + x].sprite, sfRed);
            // }

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
