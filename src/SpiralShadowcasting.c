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
        for(int y=0; y < MAP_Y; y++)
            map[MAP_COORD(x, y)].visible = false;
}

void showAll(void){
    for(int x=0; x < MAP_X; x++)
        for(int y=0; y < MAP_Y; y++)
            map[MAP_COORD(x, y)].visible = true;
}

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

    // check the player tile
    src -> idx = 0; dest -> idx = 0;
    fovhead_zoomto(dest, src, .25, hasEdges(player.x, player.y) && map[MAP_COORD(player.x, player.y)].edge -> N);
    fovhead_zoomto(dest, src, .5, hasEdges(player.x, player.y) && map[MAP_COORD(player.x, player.y)].edge -> E);
    fovhead_zoomto(dest, src, .75, hasEdges(player.x, player.y) && map[MAP_COORD(player.x, player.y)].edge -> S);
    fovhead_zoomto(dest, src, 1.0, hasEdges(player.x, player.y) && map[MAP_COORD(player.x, player.y)].edge -> W);

    fovhead *swap = src;
    src = dest;
    dest = swap;

    printf("1\n");
    for (z = 1; z < VIEW_DISTANCE; z += 1.0) {
        x = player.x - z;
        y = player.y - z;

        int side;
        double sidelength = 2.0 * z;
        double length = 4.0 * sidelength;
        double cellnumber = 0.0;

        src->idx = 0;
        dest->idx = 0;

        printf("2\n");
        for (side = 0; side < 4; side++) {
            if (side == 3.0) sidelength += 1.0;
            printf("3\n");
            for (t = 0.0; t < sidelength; t += 1.0) {
                double close = (cellnumber + 0.5) / length;

                int cell_x = x;
                int cell_y = y;

                printf("4 cell_x:%i, cell_y:%i\n", cell_x, cell_y);
                if (isMap(cell_x,cell_y)) {
                    int cellisopaque;
                    printf("4.5\n");
                    // printf("close == %.4f\n", close);
                    switch(side){
                        case 0:
                        {
                            if (cell_x < player.x)
                                cellisopaque = (hasEdges(cell_x,cell_y) && map[MAP_COORD(cell_x,cell_y)].edge -> N) || (hasEdges(cell_x+1,cell_y) && map[MAP_COORD(cell_x+1,cell_y)].edge -> W);
                            else if (cell_x > player.x)
                                cellisopaque = (hasEdges(cell_x,cell_y) && map[MAP_COORD(cell_x,cell_y)].edge -> N) || (hasEdges(cell_x-1,cell_y) && map[MAP_COORD(cell_x-1,cell_y)].edge -> E);
                            else
                                cellisopaque = hasEdges(cell_x,cell_y) && map[MAP_COORD(cell_x,cell_y)].edge -> N;
                            break;
                        }
                        case 1:
                        {
                            if (cell_y < player.y)
                                cellisopaque = (hasEdges(cell_x,cell_y) && map[MAP_COORD(cell_x,cell_y)].edge -> E) || (hasEdges(cell_x,cell_y+1) && map[MAP_COORD(cell_x,cell_y+1)].edge -> N);
                            else if (cell_y > player.y)
                                cellisopaque = (hasEdges(cell_x,cell_y) && map[MAP_COORD(cell_x,cell_y)].edge -> E) || (hasEdges(cell_x,cell_y-1) && map[MAP_COORD(cell_x,cell_y-1)].edge -> S);
                            else
                                cellisopaque = hasEdges(cell_x,cell_y) && map[MAP_COORD(cell_x,cell_y)].edge -> E;
                            break;
                        }
                        case 2:
                        {
                            if (cell_x < player.x)
                                cellisopaque = (hasEdges(cell_x,cell_y) && map[MAP_COORD(cell_x,cell_y)].edge -> S) || (hasEdges(cell_x+1,cell_y) && map[MAP_COORD(cell_x+1,cell_y)].edge -> W);
                            else if (cell_x > player.x)
                                cellisopaque = (hasEdges(cell_x,cell_y) && map[MAP_COORD(cell_x,cell_y)].edge -> S) || (hasEdges(cell_x-1,cell_y) && map[MAP_COORD(cell_x-1,cell_y)].edge -> E);
                            else
                                cellisopaque = hasEdges(cell_x,cell_y) && map[MAP_COORD(cell_x,cell_y)].edge -> S;
                            break;
                        }
                        case 3:
                        {
                            if (cell_y < player.y)
                                cellisopaque = (hasEdges(cell_x,cell_y) && map[MAP_COORD(cell_x,cell_y)].edge -> W) || (hasEdges(cell_x,cell_y+1) && map[MAP_COORD(cell_x,cell_y+1)].edge -> N);
                            else if (cell_y > player.y)
                                cellisopaque = (hasEdges(cell_x,cell_y) && map[MAP_COORD(cell_x,cell_y)].edge -> W) || (hasEdges(cell_x,cell_y-1) && map[MAP_COORD(cell_x,cell_y-1)].edge -> S);
                            else
                                cellisopaque = (hasEdges(cell_x,cell_y) && map[MAP_COORD(cell_x,cell_y)].edge -> W);
                            break;
                        }
                    }

                    printf("5\n");
                    int haslos = fovhead_zoomto(dest, src, close, cellisopaque);
                    map[MAP_COORD(cell_x,cell_y)].visible = haslos;
                }
                else {
                    fovhead_zoomto(dest, src, close, 1);
                }
                
                if (side == 0) x++;
                if (side == 1) y++;
                if (side == 2) x--;
                if (side == 3) y--;

                cellnumber += 1.0;

                printf("6\n");
            }
            printf("7\n");
        }

        dest->len = dest->idx;

        // swap!
        fovhead *swap = src;
        src = dest;
        dest = swap;
    }
}