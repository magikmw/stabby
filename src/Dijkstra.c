/*
    Dijkstra.c is a part of Stabby
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

// This function only accepts sfVector2i arguments - positions to be set as 0 in the dmap
void createDMap(int dmap[MAP_X * MAP_Y], int npoints, ...){
    for(int x = 0; x < MAP_X; x++)
        for(int y = 0; y < MAP_Y; y++){
            dmap[MAP_COORD(x,y)] = -1;
        }

    va_list pos_list;
    va_start( pos_list, npoints );
    for(int i = 0; i < npoints; i++){
        sfVector2i point = va_arg( pos_list, sfVector2i);

        dmap[MAP_COORD(point.x, point.y)] = 0;
    }
}

void updateDMap(int dmap[MAP_X * MAP_Y]){
    boolean done = false;
    while(done == false){
        done = true;
        for(int x = 0; x < MAP_X; x++)
            for(int y = 0; y < MAP_Y; y++){
                if(hasAllEdges(x,y))
                    dmap[MAP_COORD(x,y)] = -2;
                else if(dmap[MAP_COORD(x,y)] >= 0){

                }
            }
    }
}