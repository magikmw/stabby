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
            if(checkCollision((sfVector2f){player.x, player.y}, N)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += 0;
                player.y += -1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
            }
            break;
        }
        case S:
        {
            player.direction = S;
            if(checkCollision((sfVector2f){player.x, player.y}, S)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += 0;
                player.y += 1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
            }
            break;
        }
        case W:
        {
            player.direction = W;
            if(checkCollision((sfVector2f){player.x, player.y}, W)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += -1;
                player.y += 0;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
            }
            break;
        }
        case E:
        {
            player.direction = E;
            if(checkCollision((sfVector2f){player.x, player.y}, E)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += 1;
                player.y += 0;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
            }
            break;
        }
        case NW:
        {
            player.direction = NW;
            if(checkCollision((sfVector2f){player.x, player.y}, NW)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += -1;
                player.y += -1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
            }
            break;
        }
        case NE:
        {
            player.direction = NE;
            if(checkCollision((sfVector2f){player.x, player.y}, NE)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += 1;
                player.y += -1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
            }
            break;
        }
        case SW:
        {
            player.direction = SW;
            if(checkCollision((sfVector2f){player.x, player.y}, SW)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += -1;
                player.y += 1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
            }
            break;
        }
        case SE:
        {
            player.direction = SE;
            if(checkCollision((sfVector2f){player.x, player.y}, SE)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += 1;
                player.y += 1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
            }
            break;
        }
    }

    map[MAP_COORD(player.x,player.y)].entity = &player;
    updatePlayerSprite();
}

// Basic monster move function, similiar to player's
// Monsters first turn, then move forward
void mob_move(int direction, Entity* mob)
{

    // [TODO] Rewrite updatePlayerSprite() to work with any entity and allow sprite changing per states
}

// returns true if you can move in the direction from origin
boolean checkCollision(sfVector2f origin, int direction)
{
    int x = origin.x;
    int y = origin.y;

    if(map[MAP_X * y + x].edge != NULL){
        switch(direction)
        {
            case N:
            {
                if(y-1 < 0 || map[MAP_X * y + x].edge -> N)
                    return false;

                break;
            }
            case S:
            {
                if(y+1 >= MAP_Y || map[MAP_X * y + x].edge -> S)
                    return false;

                break;
            }
            case W:
            {
                if(x-1 < 0 || map[MAP_X * y + x].edge -> W)
                    return false;

                break;
            }
            case E:
            {
                if(x+1 >= MAP_X || map[MAP_X * y + x].edge -> E)
                    return false;

                break;
            }
            case NW:
            {
                if(y-1 < 0 || x-1 <0) return false;
                if((map[MAP_X * y + x].edge -> N || (map[MAP_X * (y-1) + x].edge != NULL && map[MAP_X * (y-1) + x].edge -> W))
                    && (map[MAP_X * y + x].edge -> W || (map[MAP_X * y + (x-1)].edge != NULL && map[MAP_X * y + (x-1)].edge -> N)))
                        return false;

                break;
            }
            case NE:
            {
                if(y-1 < 0 || x+1 >= MAP_X) return false;
                if((map[MAP_X * y + x].edge -> N || (map[MAP_X * (y-1) + x].edge != NULL && map[MAP_X * (y-1) + x].edge -> E))
                    && (map[MAP_X * y + x].edge -> E || (map[MAP_X * y + (x+1)].edge != NULL && map[MAP_X * y + (x+1)].edge -> N)))
                        return false;

                break;
            }
            case SW:
            {
                if(y+1 >= MAP_Y || x-1 < 0) return false;
                if((map[MAP_X * y + x].edge -> S || (map[MAP_X * (y+1) + x].edge != NULL && map[MAP_X * (y+1) + x].edge -> W))
                    && (map[MAP_X * y + x].edge -> W || (map[MAP_X * y + (x-1)].edge != NULL && map[MAP_X * y + (x-1)].edge -> S)))
                        return false;

                break;
            }
            case SE:
            {
                if(y+1 >= MAP_Y || x+1 >= MAP_X) return false;
                if((map[MAP_X * y + x].edge -> S || (map[MAP_X * (y+1) + x].edge != NULL && map[MAP_X * (y+1) + x].edge -> E))
                    && (map[MAP_X * y + x].edge -> E || (map[MAP_X * y + (x+1)].edge != NULL && map[MAP_X * y + (x+1)].edge -> S)))
                        return false;

                break;
            }

        }
    }
    else
    {
        switch(direction)
        {
            case NW:
            {
                if(y-1 < 0 || x-1 <0) return false;
                if((map[MAP_X * (y-1) + x].edge != NULL && map[MAP_X * (y-1) + x].edge -> W)
                    && (map[MAP_X * y + (x-1)].edge != NULL && map[MAP_X * y + (x-1)].edge -> N))
                        return false;

                break;
            }
            case NE:
            {
                if(y-1 < 0 || x+1 >= MAP_X) return false;
                if((map[MAP_X * (y-1) + x].edge != NULL && map[MAP_X * (y-1) + x].edge -> E)
                    && (map[MAP_X * y + (x+1)].edge != NULL && map[MAP_X * y + (x+1)].edge -> N))
                        return false;

                break;
            }
            case SW:
            {
                if(y+1 >= MAP_Y || x-1 < 0) return false;
                if((map[MAP_X * (y+1) + x].edge != NULL && map[MAP_X * (y+1) + x].edge -> W)
                    && (map[MAP_X * y + (x-1)].edge != NULL && map[MAP_X * y + (x-1)].edge -> S))
                        return false;

                break;
            }
            case SE:
            {
                if(y+1 >= MAP_Y || x+1 >= MAP_X) return false;
                if((map[MAP_X * (y+1) + x].edge != NULL && map[MAP_X * (y+1) + x].edge -> E)
                    && (map[MAP_X * y + (x+1)].edge != NULL && map[MAP_X * y + (x+1)].edge -> S))
                        return false;

                break;
            }
        }
    }
    
    return true;
}

double distance(int x1, int y1, int x2, int y2){
    int dx = x1 - x2;
    int dy = y1 - y2;
    double distance = sqrt(pow(dx,2) + pow(dy,2));

    return distance;
}