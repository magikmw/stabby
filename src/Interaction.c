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

boolean player_move(int direction, Entity* nul)
{
    // [TODO] Refactor to use the actual pointer instead of a global
    boolean moved = false;
    switch(direction){
        case N:
        {
            player.direction = N;
            if(checkCollision((sfVector2f){player.x, player.y}, N) && checkEntityCollision((sfVector2i){player.x, player.y}, N)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += 0;
                player.y += -1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                moved = true;
            }
            break;
        }
        case S:
        {
            player.direction = S;
            if(checkCollision((sfVector2f){player.x, player.y}, S) && checkEntityCollision((sfVector2i){player.x, player.y}, S)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += 0;
                player.y += 1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                moved = true;
            }
            break;
        }
        case W:
        {
            player.direction = W;
            if(checkCollision((sfVector2f){player.x, player.y}, W) && checkEntityCollision((sfVector2i){player.x, player.y}, W)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += -1;
                player.y += 0;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                moved = true;
            }
            break;
        }
        case E:
        {
            player.direction = E;
            if(checkCollision((sfVector2f){player.x, player.y}, E) && checkEntityCollision((sfVector2i){player.x, player.y}, E)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += 1;
                player.y += 0;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                moved = true;
            }
            break;
        }
        case NW:
        {
            player.direction = NW;
            if(checkCollision((sfVector2f){player.x, player.y}, NW) && checkEntityCollision((sfVector2i){player.x, player.y}, NW)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += -1;
                player.y += -1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                moved = true;
            }
            break;
        }
        case NE:
        {
            player.direction = NE;
            if(checkCollision((sfVector2f){player.x, player.y}, NE) && checkEntityCollision((sfVector2i){player.x, player.y}, NE)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += 1;
                player.y += -1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                moved = true;
            }
            break;
        }
        case SW:
        {
            player.direction = SW;
            if(checkCollision((sfVector2f){player.x, player.y}, SW) && checkEntityCollision((sfVector2i){player.x, player.y}, SW)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += -1;
                player.y += 1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                moved = true;
            }
            break;
        }
        case SE:
        {
            player.direction = SE;
            if(checkCollision((sfVector2f){player.x, player.y}, SE) && checkEntityCollision((sfVector2i){player.x, player.y}, SE)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                map[MAP_COORD(player.x,player.y)].entity = NULL;
                player.x += 1;
                player.y += 1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(player.x, player.y));
                moved = true;
            }
            break;
        }
    }

    map[MAP_COORD(player.x,player.y)].entity = &player;
    updateEntitySprite(&player);
    return moved;
}

// Basic monster move function, similiar to player's
// Monsters first turn, then move forward
boolean mob_move(int direction, Entity* mob)
{
    boolean moved = false;
    switch(direction){
        case N:
        {
            switch(mob->direction){
                case N:
                {
                    if(checkCollision((sfVector2f){mob->x, mob->y}, N) && checkEntityCollision((sfVector2i){mob->x, mob->y}, N)){
                        map[MAP_COORD(mob->x,mob->y)].entity = NULL;
                        mob->x += 0;
                        mob->y += -1;
                        moved = true;
                    }

                    break;  
                }
                case S:
                {
                    if(randInt(0,1) == 0){
                        mob->direction = SE;
                    }
                    else{
                        mob->direction = SW;
                    }

                    break;
                }
                case W:
                {
                    mob->direction = NW;

                    break;
                }
                case E:
                {
                    mob->direction = NE;
                    
                    break;
                }
                case NW:
                {
                    mob->direction = N;

                    break;
                }
                case NE:
                {
                    mob->direction = N;

                    break;
                }
                case SW:
                {
                    mob->direction = W;

                    break;
                }
                case SE:
                {
                    mob->direction = E;
                    
                    break;
                }
            }
            break;
        }
        case S:
        {
            switch(mob->direction){
                case N:
                {
                    if(randInt(0,1) == 0){
                        mob->direction = NW;
                    }
                    else{
                        mob->direction = NE;
                    }

                    break;  
                }
                case S:
                {
                    if(checkCollision((sfVector2f){mob->x, mob->y}, S) && checkEntityCollision((sfVector2i){mob->x, mob->y}, S)){
                        map[MAP_COORD(mob->x,mob->y)].entity = NULL;
                        mob->x += 0;
                        mob->y += 1;
                        moved = true;
                    }

                    break;
                }
                case W:
                {
                    mob->direction = SW;

                    break;
                }
                case E:
                {
                    mob->direction = SE;
                    
                    break;
                }
                case NW:
                {
                    mob->direction = W;
                    
                    break;
                }
                case NE:
                {
                    mob->direction = E;
                    
                    break;
                }
                case SW:
                {
                    mob->direction = S;
                    
                    break;
                }
                case SE:
                {
                    mob->direction = S;
                    
                    break;
                }
            }
            break;
        }
        case W:
        {
            switch(mob->direction){
                case N:
                {
                    mob->direction = NW;

                    break;  
                }
                case S:
                {
                    mob->direction = SW;

                    break;
                }
                case W:
                {
                    if(checkCollision((sfVector2f){mob->x, mob->y}, W) && checkEntityCollision((sfVector2i){mob->x, mob->y}, W)){
                        map[MAP_COORD(mob->x,mob->y)].entity = NULL;
                        mob->x += -1;
                        mob->y += 0;
                        moved = true;
                    }

                    break;
                }
                case E:
                {
                    if(randInt(0,1) == 0){
                        mob->direction = NE;
                    }
                    else{
                        mob->direction = SE;
                    }
                    
                    break;
                }
                case NW:
                {
                    mob->direction = W;
                    
                    break;
                }
                case NE:
                {
                    mob->direction = N;
                    
                    break;
                }
                case SW:
                {
                    mob->direction = W;
                    
                    break;
                }
                case SE:
                {
                    mob->direction = S;
                    
                    break;
                }
            }
            break;
        }
        case E:
        {
            switch(mob->direction){
                case N:
                {
                    mob->direction = NE;

                    break;  
                }
                case S:
                {
                    mob->direction = SE;

                    break;
                }
                case W:
                {
                    if(randInt(0,1) == 0){
                        mob->direction = SW;
                    }
                    else{
                        mob->direction = NW;
                    }

                    break;
                }
                case E:
                {
                    if(checkCollision((sfVector2f){mob->x, mob->y}, E) && checkEntityCollision((sfVector2i){mob->x, mob->y}, E)){
                        map[MAP_COORD(mob->x,mob->y)].entity = NULL;
                        mob->x += 1;
                        mob->y += 0;
                        moved = true;
                    }
                    
                    break;
                }
                case NW:
                {
                    mob->direction = N;
                    
                    break;
                }
                case NE:
                {
                    mob->direction = E;
                    
                    break;
                }
                case SW:
                {
                    mob->direction = S;
                    
                    break;
                }
                case SE:
                {
                    mob->direction = E;
                    
                    break;
                }
            }
            break;
        }
        case NW:
        {
            switch(mob->direction){
                case N:
                {
                    mob->direction = NW;

                    break;  
                }
                case S:
                {
                    mob->direction = SW;

                    break;
                }
                case W:
                {
                    mob->direction = NW;

                    break;
                }
                case E:
                {
                    mob->direction = NE;
                    
                    break;
                }
                case NW:
                {
                    if(checkCollision((sfVector2f){mob->x, mob->y}, NW) && checkEntityCollision((sfVector2i){mob->x, mob->y}, NW)){
                        map[MAP_COORD(mob->x,mob->y)].entity = NULL;
                        mob->x += -1;
                        mob->y += -1;
                        moved = true;
                    }
                    
                    break;
                }
                case NE:
                {
                    mob->direction = N;
                    
                    break;
                }
                case SW:
                {
                    mob->direction = W;
                    
                    break;
                }
                case SE:
                {
                    if(randInt(0,1) == 0){
                        mob->direction = E;
                    }
                    else{
                        mob->direction = S;
                    }
                    
                    break;
                }
            }
            break;
        }
        case NE:
        {
            switch(mob->direction){
                case N:
                {
                    mob->direction = NE;

                    break;  
                }
                case S:
                {
                    mob->direction = SE;

                    break;
                }
                case W:
                {
                    mob->direction = NW;

                    break;
                }
                case E:
                {
                    mob->direction = NE;
                    
                    break;
                }
                case NW:
                {
                    mob->direction = N;
                    
                    break;
                }
                case NE:
                {
                    if(checkCollision((sfVector2f){mob->x, mob->y}, NE) && checkEntityCollision((sfVector2i){mob->x, mob->y}, NE)){
                        map[MAP_COORD(mob->x,mob->y)].entity = NULL;
                        mob->x += 1;
                        mob->y += -1;
                        moved = true;
                    }
                    
                    break;
                }
                case SW:
                {
                    if(randInt(0,1) == 0){
                        mob->direction = S;
                    }
                    else{
                        mob->direction = W;
                    }
                    
                    break;
                }
                case SE:
                {
                    mob->direction = E;
                    
                    break;
                }
            }
            break;
        }
        case SW:
        {
            switch(mob->direction){
                case N:
                {
                    mob->direction = NW;

                    break;  
                }
                case S:
                {
                    mob->direction = SW;

                    break;
                }
                case W:
                {
                    mob->direction = SW;

                    break;
                }
                case E:
                {
                    mob->direction = SE;
                    
                    break;
                }
                case NW:
                {
                    mob->direction = W;
                    
                    break;
                }
                case NE:
                {
                    if(randInt(0,1) == 0){
                        mob->direction = N;
                    }
                    else{
                        mob->direction = E;
                    }
                    
                    break;
                }
                case SW:
                {
                    if(checkCollision((sfVector2f){mob->x, mob->y}, SW) && checkEntityCollision((sfVector2i){mob->x, mob->y}, SW)){
                        map[MAP_COORD(mob->x,mob->y)].entity = NULL;
                        mob->x += -1;
                        mob->y += 1;
                        moved = true;
                    }
                    
                    break;
                }
                case SE:
                {
                    mob->direction = S;
                    
                    break;
                }
            }
            break;
        }
        case SE:
        {
            switch(mob->direction){
                case N:
                {
                    mob->direction = NE;

                    break;  
                }
                case S:
                {
                    mob->direction = SE;

                    break;
                }
                case W:
                {
                    mob->direction = SW;

                    break;
                }
                case E:
                {
                    mob->direction = SE;
                    
                    break;
                }
                case NW:
                {
                    if(randInt(0,1) == 0){
                        mob->direction = W;
                    }
                    else{
                        mob->direction = N;
                    }
                    
                    break;
                }
                case NE:
                {
                    mob->direction = E;
                    
                    break;
                }
                case SW:
                {
                    mob->direction = S;
                    
                    break;
                }
                case SE:
                {
                    if(checkCollision((sfVector2f){mob->x, mob->y}, SE) && checkEntityCollision((sfVector2i){mob->x, mob->y}, SE)){
                        map[MAP_COORD(mob->x,mob->y)].entity = NULL;
                        mob->x += 1;
                        mob->y += 1;
                        moved = true;
                    }

                    break;
                }
            }
            break;
        }
    }

    map[MAP_COORD(mob->x,mob->y)].entity = mob;

    updateEntitySprite(mob);

    return moved;
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

boolean checkEntityCollision(sfVector2i origin, int direction){
    // returns true if there is no entity in given direction
    int x = origin.x;
    int y = origin.y;

    switch(direction)
    {
        case N:
            {
                if(map[MAP_COORD(x,y-1)].entity)
                    return false;

                break;
            }
            case S:
            {
                if(map[MAP_COORD(x,y+1)].entity)
                    return false;

                break;
            }
            case W:
            {
                if(map[MAP_COORD(x-1,y)].entity)
                    return false;

                break;
            }
            case E:
            {
                if(map[MAP_COORD(x+1,y)].entity)
                    return false;

                break;
            }
            case NW:
            {
                if(map[MAP_COORD(x-1,y-1)].entity)
                    return false;

                break;
            }
            case NE:
            {
                if(map[MAP_COORD(x+1,y-1)].entity)
                    return false;
                
                break;
            }
            case SW:
            {
                if(map[MAP_COORD(x-1,y+1)].entity)
                    return false;

                break;
            }
            case SE:
            {
                if(map[MAP_COORD(x+1,y+1)].entity)
                    return false;

                break;
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
