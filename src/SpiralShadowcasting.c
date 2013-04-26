/*
    SpiralShadowcasting.c is a part of Stabby
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

void clearVisibility(void){
    for(int x=0; x < MAP_X; x++)
        for(int y=0; y < MAP_Y; y++){
           map[MAP_COORD(x, y)].visible = false;
           // map[MAP_COORD(x, y)].explored = false;
       }
}

void showAll(void){
    for(int x=0; x < MAP_X; x++)
        for(int y=0; y < MAP_Y; y++)
            map[MAP_COORD(x, y)].visible = true;
}

// Following taken from source of Rook by Joshua Day, with my modifications
// https://github.com/joshuaday/rook/blob/master/src/board.c

typedef struct fovhead {
    int idx, len;
    double angle[2000];
    int blocked[2000];
} fovhead;

fovhead losbuf[2];

static int fovhead_zoomto(fovhead *dest, fovhead *src, double close, int block) {
    // do not try to make sense of this -- only a few hours to go --
    // lots of thrashing -- not good code -- 
    int haslos = src->len == 0;
    double endangle = 0.0;

    while (src->idx < src->len) {
        endangle = src->angle[src->idx];
        int breakout = 0;
        if (endangle >= close) {
            endangle = close;
            breakout = 1;
        }

        if (!src->blocked[src->idx]) {
            haslos = 1;
        }

        if (!block) {
            dest->angle[dest->idx] = endangle;
            dest->blocked[dest->idx] = src->blocked[src->idx];
            dest->idx++;
        }

        if (breakout) {
            break;
        } else {
            src->idx++;
        }
    }
    
    if (block) {
        dest->angle[dest->idx] = close;
        dest->blocked[dest->idx] = 1;
        dest->idx++;
    } else {
        if (endangle < close) {
            dest->angle[dest->idx] = close;
            dest->blocked[dest->idx] = 0;
            dest->idx++;
        }
    }

    return haslos;
}

void doFOV(void) {
    map[MAP_COORD(player.x, player.y)].visible = true;

    // toggle off, see: fov open, fov close, each loop around the spiral
    double x, y, z, t;
    fovhead *src, *dest;

    src = losbuf + 0;
    dest = losbuf + 1;
    src->len = 0;

    for (z = 1; z < VIEW_DISTANCE; z += 1.0) {
        x = player.x - z;
        y = player.y - z;

        int side;
        double sidelength = 2.0 * z;
        double length = 4.0 * sidelength;
        double cellnumber = 0.0;

        src->idx = 0;
        dest->idx = 0;

        for (side = 0; side < 4; side++) {
            if (side == 3.0) sidelength += 1.0;
            for (t = 0.0; t < sidelength; t += 1.0) {
                double close = (cellnumber + 0.5) / length;

                int cell_x = x;
                int cell_y = y;

                if (isMap(cell_x,cell_y)) {
                    int cellisopaque = hasEdges(cell_x, cell_y) && hasAllEdges(cell_x, cell_y);
                    int haslos = fovhead_zoomto(dest, src, close, cellisopaque);
                    map[MAP_COORD(cell_x,cell_y)].visible = haslos;
                    if(haslos && !map[MAP_COORD(cell_x,cell_y)].explored)
                        map[MAP_COORD(cell_x,cell_y)].explored = true;
                }
                else {
                    fovhead_zoomto(dest, src, close, 1);
                }
                
                if (side == 0) x++;
                if (side == 1) y++;
                if (side == 2) x--;
                if (side == 3) y--;

                cellnumber += 1.0;
            }
        }

        dest->len = dest->idx;

        // swap!
        fovhead *swap = src;
        src = dest;
        dest = swap;
    }
}

// End of Rook-butchered code.