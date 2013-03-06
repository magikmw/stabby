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

void updatePlayerSprite(void)
{
    static int last_direction;
    if(last_direction != player.direction)
    {
        switch(player.direction)
        {
            case N:
            {
                sfSprite_setRotation(player.sprite, 0);
                break;
            }
            case S:
            {
                sfSprite_setRotation(player.sprite, 180);
                break;
            }
            case W:
            {
                sfSprite_setRotation(player.sprite, 270);
                break;
            }
            case E:
            {
                sfSprite_setRotation(player.sprite, 90);
                break;
            }
            case NW:
            {
                sfSprite_setRotation(player.sprite, 315);
                break;
            }
            case NE:
            {
                sfSprite_setRotation(player.sprite, 45);
                break;
            }
            case SW:
            {
                sfSprite_setRotation(player.sprite, 225);
                break;
            }
            case SE:
            {
                sfSprite_setRotation(player.sprite, 135);
                break;
            }
        }
    }
    last_direction = player.direction;
    sfSprite_setPosition(player.sprite, (sfVector2f){player.x*TILE_SIZE + TILE_SIZE/2 +BORDER_OFFSET, player.y*TILE_SIZE + TILE_SIZE/2 +BORDER_OFFSET});
}