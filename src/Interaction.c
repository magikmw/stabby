/*
    Interaction.c is a part of Stabby
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


void player_move(int direction)
{
    switch(direction){
        case N:
        {
            player.direction = N;
            player.x += 0;
            player.y += -1;
            break;
        }
        case S:
        {
            player.direction = S;
            player.x += 0;
            player.y += 1;
            break;
        }
        case W:
        {
            player.direction = W;
            player.x += -1;
            player.y += 0;
            break;
        }
        case E:
        {
            player.direction = E;
            player.x += 1;
            player.y += 0;
            break;
        }
        case NW:
        {
            player.direction = NW;
            player.x += -1;
            player.y += -1;
            break;
        }
        case NE:
        {
            player.direction = NE;
            player.x += 1;
            player.y += -1;
            break;
        }
        case SW:
        {
            player.direction = SW;
            player.x += -1;
            player.y += 1;
            break;
        }
        case SE:
        {
            player.direction = SE;
            player.x += 1;
            player.y += 1;
            break;
        }
    }

    updatePlayerSprite();
}