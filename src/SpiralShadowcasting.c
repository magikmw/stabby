/*
   SpiralShadowcasting.c is a part of Stabby
   Copyright (C) 2013 MichaÅ Walczak

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
    double open;
    int blocked[2000];
} fovhead;

fovhead losbuf[2];

static void fovhead_rewind(fovhead *src) {
    src->idx = 0;
    src->open = 0.0;
}

static int fovhead_zoomto(fovhead *dest, fovhead *src, double close, int block) {
    // do not try to make sense of this -- only a few hours to go --
    // lots of thrashing -- not good code --
    double endangle = 0.0;
    double open = src->open;

    if (open == close) return src->len == 0;

    double total_angle = close - open;
    double fov_angle = 0.0;

    while (src->idx < src->len) {
        endangle = src->angle[src->idx];
        int breakout = 0;
        if (endangle >= close) {
            endangle = close;
            breakout = 1;
        }

        if (!src->blocked[src->idx]) {
            fov_angle += (endangle - open);
            // haslos = 1;
        }

        if (!block) {
            dest->angle[dest->idx] = endangle;
            dest->blocked[dest->idx] = src->blocked[src->idx];
            dest->idx++;
        }

        if (breakout) {
            break;
        } else {
            open = endangle;
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
    src->open = open;

    return (fov_angle / total_angle) > .125;
}


#define HAS_EDGE(x, y, side) (map[MAP_COORD((x),(y))].edge ? (&map[MAP_COORD((x),(y))].edge->N)[NESW[side]] : 0)

void doFOV(void) {
    static int NESW[4] = {0, 3, 1, 2}; // converts side number into an index into the Edge struct, treated as an array -- hackish but simple!

    map[MAP_COORD(player.x, player.y)].visible = true;

    // toggle off, see: fov open, fov close, each loop around the spiral
    int x, y, z;
    int t;
    fovhead *src, *dest;

    src = losbuf + 0;
    dest = losbuf + 1;
    src->len = 0;

    for (z = 0; z < VIEW_DISTANCE; z += 1.0) {
        {
            // THE SHELL
            // shells are the edges of concentric 'rings' of squares encircling the @

            // reset the tape
            fovhead_rewind(src);
            fovhead_rewind(dest);

            // loop around the shell clockwise, starting from the northwest corner
            int sidelength = 1 + 2 * z; // the number of edges on each side
            double invlength = 1.0 / (sidelength);

            int side;
            for (side = 0; side < 4; side++) {
                for (t = 0; t < sidelength; t++) {
                    double close = side + (t + 1.00) * invlength;

                    // there are faster ways to do this but branch prediction will do fine and eh, it's clear this way
                    if (side == 0) {
                        x = player.x - z + t;
                        y = player.y - z;
                    } else if (side == 1) {
                        x = player.x + z;
                        y = player.y - z + t;
                    } else if (side == 2) {
                        x = player.x + z - t;
                        y = player.y + z;
                    } else {
                        x = player.x - z;
                        y = player.y + z - t;
                    }

                    if (isMap(x, y)) {
                        int edgeisopaque = HAS_EDGE(x, y, side);
// edgeisopaque = 0;
                        int haslos = fovhead_zoomto(dest, src, close, edgeisopaque);
                        // this lighting can be offloaded, but it works well enough


                        if (haslos) { // && (distance(x,y,player.x, player.y) <= 2.5 || map[MAP_COORD(cell_x,cell_y)].light)){
                            map[MAP_COORD(x, y)].visible = true;
                            map[MAP_COORD(x, y)].explored = true;
                        }
                    } else {
                        fovhead_zoomto(dest, src, close, 1);
                    }
                }
            }
            dest->len = dest->idx;

            // swap!
            fovhead *swap = src;
            src = dest;
            dest = swap;
        }

        {
            // THE STRUTS
            // the struts are edges that connect shells; they reach outward from the @

            // reset the tape
            fovhead_rewind(src);
            fovhead_rewind(dest);

            // loop around the shell clockwise, starting from the northwest corner
            int sidelength = 2 + 2 * z; // 2 instead of 1, as it is for the SHELL
            int halfsidelength = 1 + z;

            int outersidelength = 1 + 2 * (z + 1);
            int innersidelength = 1 + 2 * z;

            double invouterlength = 1.0 / outersidelength; // this is the same as the next SHELL's invlength
            double invinnerlength = 1.0 / innersidelength; // and this is the same as the previous SHELL's invlength

            int side;
            for (side = 0; side < 4; side++) {
                for (t = 0; t < sidelength; t++) {
                    int strutside;

                    double close = side + (t + 1) * invouterlength;
                    double open = side + (t) * invinnerlength;

                    if (t < halfsidelength) {
                        strutside = (side + 3) & 3;
                    } else {
                        strutside = (side + 1) & 3;

                        double tmp = close;
                        close = open;
                        open = tmp;
                    }


                    // there are faster ways to do this but branch prediction will do fine and eh, it's clear this way
                    if (side == 0) {
                        x = player.x - (z + 1) + (t + (t < halfsidelength));
                        y = player.y - (z + 1);
                    } else if (side == 1) {
                        x = player.x + (z + 1);
                        y = player.y - (z + 1) + (t + (t < halfsidelength));
                    } else if (side == 2) {
                        x = player.x + (z + 1) - (t + (t < halfsidelength));
                        y = player.y + (z + 1);
                    } else {
                        x = player.x - (z + 1);
                        y = player.y + (z + 1) - (t + (t < halfsidelength));
                    }

                    // first skip forward to where this strut OPENs
                    fovhead_zoomto(dest, src, open, 0);
                    if (isMap(x, y)) {
                        int edgeisopaque = HAS_EDGE(x, y, strutside);
                        int haslos = fovhead_zoomto(dest, src, close, edgeisopaque);

                        // this lighting can be offloaded, but it works well enough

haslos = 0; // we don't want to mark it visible on this phase
                        if (haslos) { // && (distance(x,y,player.x, player.y) <= 2.5 || map[MAP_COORD(cell_x,cell_y)].light)){
                            map[MAP_COORD(x, y)].visible = true;
                            map[MAP_COORD(x, y)].explored = true;
                        }
                    } else {
                        fovhead_zoomto(dest, src, close, 1);
                    }
                }
            }


            dest->len = dest->idx;

            // swap!
            fovhead *swap = src;
            src = dest;
            dest = swap;
        }
    }
}

// End of Rook-butchered code.
