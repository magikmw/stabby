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

boolean player_move(int direction, Entity* pc)
{
    boolean moved = false;
    switch(direction){
        case N:
        {
            pc->direction = N;
            if(checkCollision(MAP_COORD(pc->x, pc->y), N) && checkEntityCollision(MAP_COORD(pc->x, pc->y), N)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                map[MAP_COORD(pc->x,pc->y)].entity = NULL;
                pc->x += 0;
                pc->y += -1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                moved = true;
            }
            break;
        }
        case S:
        {
            pc->direction = S;
            if(checkCollision(MAP_COORD(pc->x, pc->y), S) && checkEntityCollision(MAP_COORD(pc->x, pc->y), S)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                map[MAP_COORD(pc->x,pc->y)].entity = NULL;
                pc->x += 0;
                pc->y += 1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                moved = true;
            }
            break;
        }
        case W:
        {
            pc->direction = W;
            if(checkCollision(MAP_COORD(pc->x, pc->y), W) && checkEntityCollision(MAP_COORD(pc->x, pc->y), W)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                map[MAP_COORD(pc->x,pc->y)].entity = NULL;
                pc->x += -1;
                pc->y += 0;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                moved = true;
            }
            break;
        }
        case E:
        {
            pc->direction = E;
            if(checkCollision(MAP_COORD(pc->x, pc->y), E) && checkEntityCollision(MAP_COORD(pc->x, pc->y), E)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                map[MAP_COORD(pc->x,pc->y)].entity = NULL;
                pc->x += 1;
                pc->y += 0;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                moved = true;
            }
            break;
        }
        case NW:
        {
            pc->direction = NW;
            if(checkCollision(MAP_COORD(pc->x, pc->y), NW) && checkEntityCollision(MAP_COORD(pc->x, pc->y), NW)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                map[MAP_COORD(pc->x,pc->y)].entity = NULL;
                pc->x += -1;
                pc->y += -1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                moved = true;
            }
            break;
        }
        case NE:
        {
            pc->direction = NE;
            if(checkCollision(MAP_COORD(pc->x, pc->y), NE) && checkEntityCollision(MAP_COORD(pc->x, pc->y), NE)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                map[MAP_COORD(pc->x,pc->y)].entity = NULL;
                pc->x += 1;
                pc->y += -1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                moved = true;
            }
            break;
        }
        case SW:
        {
            pc->direction = SW;
            if(checkCollision(MAP_COORD(pc->x, pc->y), SW) && checkEntityCollision(MAP_COORD(pc->x, pc->y), SW)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                map[MAP_COORD(pc->x,pc->y)].entity = NULL;
                pc->x += -1;
                pc->y += 1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                moved = true;
            }
            break;
        }
        case SE:
        {
            pc->direction = SE;
            if(checkCollision(MAP_COORD(pc->x, pc->y), SE) && checkEntityCollision(MAP_COORD(pc->x, pc->y), SE)){
                DMapRemPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                map[MAP_COORD(pc->x,pc->y)].entity = NULL;
                pc->x += 1;
                pc->y += 1;
                DMapAddPOI(&DMap_PlayerChase, MAP_COORD(pc->x, pc->y));
                moved = true;
            }
            break;
        }
    }

    map[MAP_COORD(pc->x,pc->y)].entity = pc;
    updateEntitySprite(pc);
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
                    if(checkCollision(MAP_COORD(mob->x, mob->y), N) && checkEntityCollision(MAP_COORD(mob->x, mob->y), N)){
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
                    if(checkCollision(MAP_COORD(mob->x, mob->y), S) && checkEntityCollision(MAP_COORD(mob->x, mob->y), S)){
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
                    if(checkCollision(MAP_COORD(mob->x, mob->y), W) && checkEntityCollision(MAP_COORD(mob->x, mob->y), W)){
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
                    if(checkCollision(MAP_COORD(mob->x, mob->y), E) && checkEntityCollision(MAP_COORD(mob->x, mob->y), E)){
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
                    if(checkCollision(MAP_COORD(mob->x, mob->y), NW) && checkEntityCollision(MAP_COORD(mob->x, mob->y), NW)){
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
                    if(checkCollision(MAP_COORD(mob->x, mob->y), NE) && checkEntityCollision(MAP_COORD(mob->x, mob->y), NE)){
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
                    if(checkCollision(MAP_COORD(mob->x, mob->y), SW) && checkEntityCollision(MAP_COORD(mob->x, mob->y), SW)){
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
                    if(checkCollision(MAP_COORD(mob->x, mob->y), SE) && checkEntityCollision(MAP_COORD(mob->x, mob->y), SE)){
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
boolean checkCollision(int origin, int direction)
{
    int x = map[origin].x;
    int y = map[origin].y;

    if(map[MAP_COORD(x,y)].edge != NULL){
        switch(direction)
        {
            case N:
            {
                if(y-1 < 0 || map[MAP_COORD(x,y)].edge -> N)
                    return false;

                break;
            }
            case S:
            {
                if(y+1 >= MAP_Y || map[MAP_COORD(x,y)].edge -> S)
                    return false;

                break;
            }
            case W:
            {
                if(x-1 < 0 || map[MAP_COORD(x,y)].edge -> W)
                    return false;

                break;
            }
            case E:
            {
                if(x+1 >= MAP_X || map[MAP_COORD(x,y)].edge -> E)
                    return false;

                break;
            }
            case NW:
            {
                if(y-1 < 0 || x-1 <0) return false;
                if((map[MAP_COORD(x,y)].edge -> N || (map[MAP_COORD(x,y-1)].edge != NULL && map[MAP_COORD(x,y-1)].edge -> W))
                    && (map[MAP_COORD(x,y)].edge -> W || (map[MAP_COORD(x-1,y)].edge != NULL && map[MAP_COORD(x-1,y)].edge -> N)))
                        return false;

                break;
            }
            case NE:
            {
                if(y-1 < 0 || x+1 >= MAP_X) return false;
                if((map[MAP_COORD(x,y)].edge -> N || (map[MAP_COORD(x,y-1)].edge != NULL && map[MAP_COORD(x,y-1)].edge -> E))
                    && (map[MAP_COORD(x,y)].edge -> E || (map[MAP_COORD(x+1,y)].edge != NULL && map[MAP_COORD(x+1,y)].edge -> N)))
                        return false;

                break;
            }
            case SW:
            {
                if(y+1 >= MAP_Y || x-1 < 0) return false;
                if((map[MAP_COORD(x,y)].edge -> S || (map[MAP_COORD(x,y+1)].edge != NULL && map[MAP_COORD(x,y+1)].edge -> W))
                    && (map[MAP_COORD(x,y)].edge -> W || (map[MAP_COORD(x-1,y)].edge != NULL && map[MAP_COORD(x-1,y)].edge -> S)))
                        return false;

                break;
            }
            case SE:
            {
                if(y+1 >= MAP_Y || x+1 >= MAP_X) return false;
                if((map[MAP_COORD(x,y)].edge -> S || (map[MAP_COORD(x,y+1)].edge != NULL && map[MAP_COORD(x,y+1)].edge -> E))
                    && (map[MAP_COORD(x,y)].edge -> E || (map[MAP_COORD(x+1,y)].edge != NULL && map[MAP_COORD(x+1,y)].edge -> S)))
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
                if((map[MAP_COORD(x,y-1)].edge != NULL && map[MAP_COORD(x,y-1)].edge -> W)
                    && (map[MAP_COORD(x-1,y)].edge != NULL && map[MAP_COORD(x-1,y)].edge -> N))
                        return false;

                break;
            }
            case NE:
            {
                if(y-1 < 0 || x+1 >= MAP_X) return false;
                if((map[MAP_COORD(x,y-1)].edge != NULL && map[MAP_COORD(x,y-1)].edge -> E)
                    && (map[MAP_COORD(x+1,y)].edge != NULL && map[MAP_COORD(x+1,y)].edge -> N))
                        return false;

                break;
            }
            case SW:
            {
                if(y+1 >= MAP_Y || x-1 < 0) return false;
                if((map[MAP_COORD(x,y+1)].edge != NULL && map[MAP_COORD(x,y+1)].edge -> W)
                    && (map[MAP_COORD(x-1,y)].edge != NULL && map[MAP_COORD(x-1,y)].edge -> S))
                        return false;

                break;
            }
            case SE:
            {
                if(y+1 >= MAP_Y || x+1 >= MAP_X) return false;
                if((map[MAP_COORD(x,y+1)].edge != NULL && map[MAP_COORD(x,y+1)].edge -> E)
                    && (map[MAP_COORD(x+1,y)].edge != NULL && map[MAP_COORD(x+1,y)].edge -> S))
                        return false;

                break;
            }
        }
    }

    return true;
}

boolean checkEntityCollision(int origin, int direction){
    // returns true if there is no entity in given direction
    int x = map[origin].x;
    int y = map[origin].y;

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
