/*
    FieldOfView.c is a part of Stabby
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

void FOVfindCells(list_p targets, int origin, int edge_distance){
    // scans the map saving positions of cells closer than edge_distance
    // adds the positions to the list

    for(int x = map[origin].x - edge_distance; x < map[origin].x + edge_distance; x++){
        for(int y = map[origin].y - edge_distance; y < map[origin].y + edge_distance; y++){
            if(isMap(x, y) && (int)distance(map[origin].x, map[origin].y, x, y) < edge_distance){
                int position = MAP_COORD(x,y);
                // list_add(targets, &position, sizeof(int));
                map[position].visible = true;
            }
        }
    }

}

void FOVdrawLines(list_p targets, int origin){
    // Draw Bresenham's lines to all the cells with positions in 'targts'
    // Check for LOS on the way, break if none (basically same as wall collision)

    
}
